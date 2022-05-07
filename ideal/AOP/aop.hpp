template<typename T, typename... Args>
struct has_aop_methods_impl {
private:
    template<typename U>
    static auto check(int) -> decltype(
        std::declval<U>().aop_before(std::declval<Args>()...),
        std::declval<U>().aop_after(std::declval<Args>()...),
        std::true_type{});

    template<typename U>
    static std::false_type check(...);
public:
    using type = decltype(check<T>(0));
    enum : bool {
        value = std::is_same_v<type, std::true_type>,
    };
};

template<typename T, typename... Args>
constexpr auto has_aop_methods_v = has_aop_methods_impl<T, Args...>::value;

template<typename F, typename... Args>
struct AOP {
public:
    AOP(F&& f) : f_(std::forward<F>(f)) {}

    template<typename T>
    void invoke(Args&&... args, T&& t) {
        if constexpr (has_aop_methods_v<T, Args...>) {
            t.aop_before(std::forward<Args>(args)...);
        }

        f_(std::forward<Args>(args)...);

        if constexpr (has_aop_methods_v<T, Args...>) {
            t.aop_after(std::forward<Args>(args)...);
        }
    }
    template<typename T0, typename... TRes>
    void invoke(Args&&... args, T0&& t, TRes&&... tRes) {
        if constexpr (has_aop_methods_impl<T0, Args...>::value) {
            t.aop_before(std::forward<Args>(args)...);
        }

        invoke(std::forward<Args>(args)..., std::forward<TRes>(tRes)...);

        if constexpr (has_aop_methods_impl<T0, Args...>::value) {
            t.aop_after(std::forward<Args>(args)...);
        }
    }
private:
    F f_;
};

template<typename...AOPs, typename F, typename... Args>
void invoke(F&& f, Args&&... args) {
    AOP<F, Args...> aop(std::forward<F>(f));
    aop.invoke(std::forward<Args>(args)..., AOPs()...);
}

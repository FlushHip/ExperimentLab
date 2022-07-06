## 如何在编译期获取传统数组的大小

C++中，数组和函数都会退化成指针，常规的传值型类型推导是行不通的。
通过函数模板类型推导，对模板函数声明一个指向**数组的引用**使得我们可以在模板函数中推导出数组的大小。
```cpp
template<typename T, std::size_t N>
constexpr std::size_t arraySize(T (&)[N]) noexcept
{
    return N;
}

int A[] = { 1, 2, 3, 4 };
int B[arraySize(A)];
std::array<int, arrsize(B)> C;
```

## 如何简化`std::tuple`中的`std::get<1>`的魔数

使用非限域枚举非常方便；
使用限域枚举时需要转换。
同时为了避免没有封装性，使用结构体把所有东西绑定在一起。

```cpp
#include <iostream>
#include <tuple>
#include <string>

struct UserInfoA {
    using type = std::tuple<int, int, std::string>;
    enum fields {
        one,
        two,
        three,
    };
};

struct UserInfoB {
    using type = std::tuple<int, int, std::string>;
    enum class fields {
        one,
        two,
        three,
    };
};

template<typename E>
constexpr auto to(E enumerator) noexcept
{
    return static_cast<std::underlying_type_t<E>>(enumerator);
}

int main(int argc, char **argv)
{
    UserInfoA::type tuA{ 1, 2, "flushhip" };
    std::cout << std::get<UserInfoA::fields::one>(tuA) << std::endl;
    std::cout << std::get<UserInfoA::three>(tuA) << std::endl;

    UserInfoB::type tuB{ 2, 1, "lisi" };
    std::cout << std::get<to(UserInfoB::fields::one)>(tuB) << std::endl;
    std::cout << std::get<to(UserInfoB::fields::three)>(tuB) << std::endl;

    return 0;
}

```

## 成员函数如何写出与对象的左值和右值相对应的函数

这个问题就类似于给成员函数加上`const`限定，重载`operator[]`比较常见；
这里也有一个**成员函数的引用限定`&`, `&&`**。

```cpp
class Widget {
public:
    ...
    void doWork() &; //只有*this为左值的时候才能被调用
    void doWork() &&; //只有*this为右值的时候才能被调用
};
```

通过重载成员函数的引用限定来达到性能优化的目标：

```cpp
class Widget {
public:
    using DataType = std::vector<double>;
    ...
    DataType& data() &              // 对于左值Widgets,
    { return values; }              // 返回左值
    DataType data() &&              // 对于右值Widgets,
    { return std::move(values); }   // 返回右值
    ...
private:
    DataType values;
};

auto vals1 = w.data();              //调用左值重载版本的Widget::data，拷⻉构造vals1
auto vals2 = makeWidget().data();   //调用右值重载版本的Widget::data, 移动构造vals2

```

## 成员函数声明为`const`，但是需要在成员函数中需要改变一些不那么重要的成员变量（例如一些成员函数中需要使用缓存）

把这些成员变量用`mutable`修饰，如同在$lambda$函数中需要改变捕获列表中的内容那样。

## 为啥不能在构造函数中使用`shared_from_this`

首先，`shared_ptr`的控制块只可能在下列三种情况下生成：
+ `std::make_shared`
+ 从`std::unique_ptr`上生成`std::shared_ptr`
+ 从裸指针上生成`std::shared_ptr`

而`shared_from_this`中的`shared_ptr`却不会创建多余控制块，从内部来说，`shared_from_this`查找当前对象的控制块，然后创建一个新的`shared_ptr`指向这个控制块，这也就是为啥继承自`std::enable_shared_from_this`的类需要用`share_ptr`去管理。与是，在构造函数中使用`shared_from_this`就变成了“先有鸡还是先有蛋”的问题。

## `weak_ptr`的使用场景

类似于”偷看“的场景，“有的话我就用，没有的话我也算了”，因此，**缓存模型**和**观察者模式**特别适合保存`weak_ptr`；如果出现循环引用的场景也是可以用`weak_ptr`去”偷看“的。

这里要提到pimpl模式了（有可能出现循环引用），通常，impl用`unique_ptr`包裹，而impl中也需要上层对象的指针，这个指针就可以用裸指针，因为这里两个对象的生命周期有着明确的大小关系，可以保证裸指针不悬空。

## 智能指针控制块释放时机

只要`std::weak_ptr`引用一个控制块(即weak count大于零)，该控制块必须继续存在。只要控制块存在，包含它的内存就必须保持分配。通过`std::shared_ptr` make函数分配的内存，直到最后一个`std::shared_ptr` 和最后一个指向它的`std::weak_ptr`已被销毁，才会释放。

## 用`std::unique_ptr`实现pimpl模式可能出现的编译问题

”未完成类型“是最常见的编译错误类型。原因就是对象可能自动生成析构函数，而析构函数里需要析构`std::unique_ptr`，这里就需要一个完整的类型；
同理，使用`std::shared_ptr`就不会有这种情况发生，原因是析构`std::shared_ptr`时只是减少引用计数，这里并不需要直接析构impl类型。

> `std::unique_ptr` 和`std::shared_ptr` 在pImpl 指针上的表现上的区别的深层原因在于，他们支持自定义销毁器(custom deleter)的方式不同。 对`std::unique_ptr` 而言，销毁器的类型是`unique_ptr` 的一部分，这让编译器有可能生成更小的运行时数据结构和更快的运行代码。 这种更高效率的后果之一就是`unique_ptr` 指向的类型，在编译器的生成特殊成员函数被调用时(如析构函数，移动操作)时，必须已经是一个完成类型。 而对`std::shared_ptr` 而言，销毁器的类型不是该智能指针的一部分，这让它会生成更大的运行时数据结构和稍微慢点的代码，但是当编译器生成的特殊成员函数被使用的时候，指向的对象不必是一个完成类型。

解决方式如下：编译器自动生成的函数都是inline的，因此就会出现在impl的实现前。**可以先声明析构函数，然后把析构函数定义放到impl类型实现的后面，这样就可以强制改变代码顺序，使得析构的时候能看到完整的类型。**

## 通过tag-dispath和SFINAE来控制通用引用上的重载

```cpp
class Person { // C++14
public:
  template<
    typename T,
    typename = std::enable_if_t<
     !std::is_base_of<Person, std::decay_t<T>::value
       &&
       !std::is_integral<std::remove_reference_t<T>>::value
    >
  >
  explicit Person(T&& n): name(std::forward<T>(n))
  {...} // ctor for std::strings and args convertible to strings

  explicit Person(int idx): name(nameFromIdx(idx))
  {...} // ctor for integral args

  ... // copy and move ctors, etc
private:
  std::string name;
};

class SpecialPerson: public Person {
public:
  SpecialPerson(const SpecialPerson& rhs): Person(rhs)
  {...} // copy ctor; calls base class forwarding ctor!
  SpecialPerson(SpecialPerson&& rhs): Person(std::move(rhs))
  {...} // move ctor; calls base class forwarding ctor!
};

Person p("Nancy");
auto cloneOfP(p);

Person q(2)
Person k(std::string("flushhip"))

```

## `std::bind`何时会绑定失败

当需要绑定的对象存在重载行为时，`std::bind`不能正常工作；原因就是通用引用+完美转发不能正确推导出绑定对象的类型，如果要求能正常工作，就需要使用`static_cast`显式对绑定对象进行指定。

因此啊，更推荐使用`lambda`表达式来替代`std::bind`。

而且，`std::bind`中绑定的一些参数会在bind时就求值，对于有些需要推迟求值的需求来说需要嵌套可调用对象。

```cpp
auto setSoundL =
  [](Sound s)
  {
    using namespace std::chrono;
    using namespace std::literals; // for C++14 suffixes
        setAlarm(steady_clock::now() + 1h, // C++14, but
             s, // same meaning
             30s); // as above
    };

auto setSoundB =
     std::bind(setAlarm,
     std::bind(std::plus<>(), steady_clock::now(), 1h), _1,
     30s);

```

而且，`std::bind`处理更复杂的情况会更加麻烦：

```cpp
auto betweenL =
     [lowVal, highVal]
     (const auto& val)                          // C++14
     { return lowVal <= val && val <= highVal; };

using namespace std::placeholders;           // as above
auto betweenB =
    std::bind(std::logical_and<>(), // C++14
                        std::bind(std::less_equal<>(), lowVal, _1),
                    std::bind(std::less_equal<>(), _1, highVal));
```

`std::bind` 的工作方式是传递给绑定对象的所有参数都是通过引用传递的，因为此类对象的函数调用运算符使用完美转发。

## CRTP

## RTTI

## SFINAE

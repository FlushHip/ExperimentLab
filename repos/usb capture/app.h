#pragma once

#include <memory>

namespace hestina {
class app {
public:
    int run(int argc, char** argv);
    int main();

    static app& get() {
        static app sapplication;
        return sapplication;
    }

private:
    app();
    ~app();
    int init_options(int argc, char** argv);
    int rigister_service();
    int unrigister_service();

private:
    struct context;
    std::unique_ptr<context> context_;
};

}  // namespace hestina

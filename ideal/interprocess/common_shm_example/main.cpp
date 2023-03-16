#include <cstdlib>
#include <iostream>
#include <string_view>
#include <thread>

#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/shared_memory_object.hpp>

constexpr std::string_view kshm_object_name = "shm_flushhip";
constexpr int kshm_object_size = 1000;

int main(int argc, char** argv) {
    if (argc == 1) {  // server
        struct raii {
            raii() {
                std::cout << std::boolalpha
                          << boost::interprocess::shared_memory_object::remove(
                                 kshm_object_name.data())
                          << std::endl;
            }
            ~raii() {
                std::cout << std::boolalpha
                          << boost::interprocess::shared_memory_object::remove(
                                 kshm_object_name.data())
                          << std::endl;
            }
        } raii;

        boost::interprocess::shared_memory_object shm(
            boost::interprocess::create_only, kshm_object_name.data(),
            boost::interprocess::read_write);

        shm.truncate(kshm_object_size);

        boost::interprocess::mapped_region mreg(
            shm, boost::interprocess::read_write);

        std::memset(mreg.get_address(), 1, mreg.get_size());

        std::string cmd{argv[0]};
        cmd += " client";

        std::system(cmd.c_str());
    } else {  // client
        boost::interprocess::shared_memory_object shm(
            boost::interprocess::open_only, kshm_object_name.data(),
            boost::interprocess::read_only);

        boost::interprocess::mapped_region mreg(
            shm, boost::interprocess::read_only);

        if (std::all_of(static_cast<const char*>(mreg.get_address()),
                static_cast<const char*>(mreg.get_address()) + mreg.get_size(),
                [](auto c) { return c == 1; })) {
            std::cout << "fantasticate..." << std::endl;
        } else {
            std::cerr << "error..." << std::endl;
        }

        using namespace std::literals::chrono_literals;
        std::this_thread::sleep_for(5s);
    }
    return 0;
}

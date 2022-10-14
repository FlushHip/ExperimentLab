#include <cstdlib>
#include <fstream>
#include <ios>
#include <iostream>
#include <string_view>
#include <thread>

#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>

constexpr std::string_view kmmf_file_name = "flushhip.bin";
constexpr int kmmf_file_size = 1000;
constexpr char ktag = '~';

int main(int argc, char** argv) {
    if (argc == 1) {  // server
        {
            boost::interprocess::file_mapping::remove(kmmf_file_name.data());

            std::filebuf fbuf;
            fbuf.open(kmmf_file_name.data(),
                std::ios_base::in | std::ios_base::out | std::ios_base::trunc |
                    std::ios_base::binary);
            fbuf.pubseekoff(kmmf_file_size - 1, std::ios_base::beg);
            fbuf.sputc(0);
        }

        struct raii {
            ~raii() {
                [&] {
                    boost::interprocess::file_mapping::remove(
                        kmmf_file_name.data());
                }();
            }
        } raii;

        boost::interprocess::file_mapping mmf(
            kmmf_file_name.data(), boost::interprocess::read_write);

        boost::interprocess::mapped_region mreg(
            mmf, boost::interprocess::read_write);

        std::memset(mreg.get_address(), ktag, mreg.get_size());

        std::string cmd{argv[0]};
        cmd += " client";

        std::system(cmd.c_str());
    } else {  // client
        boost::interprocess::file_mapping mmf(
            kmmf_file_name.data(), boost::interprocess::read_only);

        {
            boost::interprocess::mapped_region mreg(
                mmf, boost::interprocess::read_only);
            if (std::all_of(static_cast<const char*>(mreg.get_address()),
                    static_cast<const char*>(mreg.get_address()) +
                        mreg.get_size(),
                    [](auto c) { return c == ktag; })) {
                std::cout << "fantasticate..." << std::endl;
            } else {
                std::cerr << "error..." << std::endl;
            }
        }
        {
            std::filebuf fbuf;
            fbuf.open(kmmf_file_name.data(),
                std::ios_base::in | std::ios_base::binary);
            std::vector<char> buff(kmmf_file_size, 0);
            fbuf.sgetn(buff.data(), buff.size());
            if (std::all_of(buff.begin(), buff.end(),
                    [](auto c) { return c == ktag; })) {
                std::cout << "fantasticate..." << std::endl;
            } else {
                std::cerr << "error..." << std::endl;
            }
        }

        using namespace std::literals::chrono_literals;
        std::this_thread::sleep_for(5s);
    }
    return 0;
}

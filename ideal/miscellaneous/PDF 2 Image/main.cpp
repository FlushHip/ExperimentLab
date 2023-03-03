#include <cstdlib>
#include <exception>
#include <filesystem>
#include <functional>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>
#include <thread>

#include <argagg/argagg.hpp>

int dpi = 100;
int total_nums;
int thread_nums;
bool verbose;

std::mutex mtx_out;

void convert(const std::filesystem::path& infile,
    size_t count,
    const std::filesystem::path& prefix) {
    auto tofile = infile.string();
    tofile.replace(0, count, prefix.string());

    auto des_parent_path =
        (std::filesystem::path(tofile).parent_path() / "__")
            .concat(std::filesystem::path(tofile).stem().string());
    if (!std::filesystem::exists(des_parent_path)) {
        std::filesystem::create_directories(des_parent_path);
    }
    auto des_path = des_parent_path / "img";

    std::stringstream ss;

    ss << "inc\\pdftopng.exe "
       << "-r " << dpi << (verbose ? " -verbose" : "") << " "
       << std::quoted(infile.string()) << " " << std::quoted(des_path.string());

    auto ret = std::system(ss.str().c_str());

    std::unique_lock<std::mutex> lock(mtx_out, std::defer_lock);
    if (thread_nums != 1) {
        lock.lock();
    }
    if (ret == 0) {
        std::clog << "+++ " << tofile << " -> " << des_parent_path << std::endl;
        ++total_nums;
        std::clog.flush();
    } else {
        std::cerr << "--- " << tofile << " -> " << des_parent_path << std::endl;
    }
}

int main(int argc, char* argv[]) {
    int ret = 0;

    argagg::parser argparser{{
        {"help", {"-h", "--help"}, "show help message", 0},
        {"input", {"-i", "--input"}, "folder or filename", 1},
        {"output", {"-o", "--output"}, "output folder", 1},
        {"dpi", {"-r"}, "dpi, more large more clear, default is 100", 1},
        {"verbose", {"-v"},
            "verbose will use single thread, so will slower than normal", 0},
    }};

    do {
        std::filesystem::path input_path{};
        std::filesystem::path output_path{};

        argagg::parser_results args;
        try {
            args = argparser.parse(argc, argv);
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            ret = 1;
            break;
        }

        if (argc == 1 || args["help"]) {
            auto exe_name = std::filesystem::path(argv[0]).stem().string();
            std::cerr << "Usage: " << exe_name
                      << " <-i name> [options] [-o name]" << std::endl
                      << argparser;
            ret = 1;
            break;
        }
        if (args["input"]) {
            input_path = args["input"].as<std::string>();
        } else {
            std::cerr << "Not input, invalid." << std::endl;
            ret = 1;
            break;
        }
        if (args["output"]) {
            output_path = args["output"].as<std::string>();
        }
        if (args["dpi"]) {
            dpi = args["dpi"].as<int>();
        }
        if (!args["verbose"]) {
            thread_nums = std::thread::hardware_concurrency();
            verbose = false;
        } else {
            thread_nums = 1;
            verbose = true;
        }

        std::filesystem::path prefix;
        if (!output_path.empty() && output_path.has_root_path()) {
            prefix = output_path;
        } else if (std::filesystem::is_directory(input_path)) {
            prefix = input_path;
        } else {
            prefix = input_path.parent_path();
        }

        if (!std::filesystem::is_directory(input_path)) {
            convert(
                input_path, input_path.parent_path().string().size(), prefix);
        } else {
            size_t count = input_path.string().size();

            std::vector<std::vector<std::function<void()>>> tasks_queue(
                thread_nums);

            int index = 0;
            for (const auto& entry :
                std::filesystem::recursive_directory_iterator(input_path)) {
                if (entry.path().has_extension() &&
                    entry.path().extension() == ".pdf") {
                    tasks_queue[index++ % thread_nums].emplace_back(
                        [infile = entry.path(), count, &prefix] {
                            return convert(infile, count, prefix);
                        });
                }
            }

            std::vector<std::thread> threads;
            for (int i = 0; i < thread_nums; ++i) {
                threads.emplace_back([&, i] {
                    for (const auto& task : tasks_queue[i]) {
                        task();
                    }
                });
            }
            for (int i = 0; i < thread_nums; ++i) {
                threads[i].join();
            }
        }

        std::cout << std::endl
                  << "Total convert " << total_nums << " files" << std::endl;

    } while (false);

    return ret;
}

#include <iostream>

#include <cinatra/client_factory.hpp>
#include <cinatra/http_client.hpp>

#include <nlohmann/json.hpp>

int main(int argc, char** argv) {
    auto client = cinatra::client_factory::instance().new_client();
    std::string uri =
        "https://justmysocks5.net/members/"
        "getbwcounter.php?service=199531&id=5fc17877-6504-49a6-85fa-"
        "fdc87ec5297a";
    auto result = client->get(uri);

    if (result.ec) {
        std::cerr << result.ec.message() << std::endl;
        return 1;
    }
    if (result.status != 200) {
        std::cerr << "status code : " << result.status << std::endl;
        return 1;
    }

    constexpr int unit = 1000;
    auto j = nlohmann::json::parse(result.resp_body);
    auto total_bw = j["monthly_bw_limit_b"].get<double>() / unit / unit;
    auto consume_bw = j["bw_counter_b"].get<double>() / unit / unit;
    auto reset_day = j["bw_reset_day_of_month"].get<int>();

    std::cout << std::endl << __TIMESTAMP__ << std::endl;
    std::cout << "\thttps get url[" << uri << "]" << std::endl
              << "\ttotal bw : "
              << "\x1b[32m" << total_bw / unit << "\x1b[0m GB" << std::endl
              << "\tconsume bw : "
              << "\x1b[32m" << consume_bw / unit << "\x1b[0m GB" << std::endl
              << "\tthe month of reset days : "
              << "\x1b[32m" << reset_day << "\x1b[0m" << std::endl
              << "\tavarage bw you can use(rest of the month) : "
              << "\x1b[32m" << (total_bw - consume_bw) / reset_day / unit
              << "\x1b[0m GB" << std::endl;
    return 0;
}

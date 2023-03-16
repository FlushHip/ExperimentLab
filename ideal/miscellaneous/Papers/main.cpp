#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

int longestCommonSubsequence(std::string_view text1, std::string_view text2) {
    int m = (int)text1.length(), n = (int)text2.length();
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));
    for (int i = 1; i <= m; i++) {
        char c1 = text1.at(i - 1);
        for (int j = 1; j <= n; j++) {
            char c2 = text2.at(j - 1);
            if (c1 == c2) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[m][n];
}

int main(int argc, char *argv[]) {
    std::vector<std::string> papers_lines;
    std::ifstream papers_lines_txt(R"(C:\Users\FlushHip\Desktop\papers.txt)");

    if (!papers_lines_txt.is_open()) {
        std::cerr << "Error opening papers.txt" << std::endl;
        return 1;
    }

    while (!papers_lines_txt.eof()) {
        std::string line;
        std::getline(papers_lines_txt, line);
        std::transform(line.begin(), line.end(), line.begin(), ::tolower);
        papers_lines.push_back(std::move(line));
    }

    auto fn = [&papers_lines](std::string &line) {
        std::transform(line.begin(), line.end(), line.begin(), ::tolower);
        for (const auto &paper_line : papers_lines) {
            if (std::abs((int)paper_line.size() - (int)line.size()) > 5) {
                continue;
            }
            if (std::abs((int)line.size() - longestCommonSubsequence(paper_line, line)) < 5) {
                return true;
            }
        }
        return false;
    };

    std::filesystem::path root_path = R"(C:\Users\FlushHip\Desktop\papers)";
    std::filesystem::path des_path = R"(C:\Users\FlushHip\Desktop\PDF)";
    std::filesystem::create_directory(des_path);

    int cnt = 0;
    for (const auto &entry : std::filesystem::directory_iterator(root_path)) {
        auto paper_path = entry.path();
        auto paper_name = paper_path.filename();

        if (fn(paper_name.string())) {
            std::filesystem::path des_paper_path = des_path / paper_name;
            std::filesystem::copy_file(paper_path, des_paper_path);
            std::cout << "Copy " << ++cnt << " : " << paper_name << std::endl;
        }
    }

    std::cout << "Total " << cnt << " papers copied" << std::endl;

    return 0;
}

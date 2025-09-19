#include "headers.h"

class Spreadsheet {
private:
    std::vector<std::array<int, 26>> map_;

    std::pair<int, int> cell(std::string_view str) {
        int col = str.front() - 'A';
        int row = std::stoi(std::string(str.substr(1)));
        return std::make_pair(row - 1, col);
    }

    int value(std::string_view str) {
        if (str.front() >= 'A' && str.front() <= 'Z') {
            auto [row, col] = cell(str);
            return row < map_.size() ? map_[row][col] : 0;
        }
        return std::stoi(std::string(str));
    }
public:
    explicit Spreadsheet(int rows) : map_{static_cast<size_t>(rows),} {
        for (auto& row : map_) {
            row.fill(0);
        }
    }
    
    void setCell(string cell, int value) {
        auto [row, col] = this->cell(cell);
        map_[row][col] = value;
    }
    
    void resetCell(string cell) {
        auto [row, col] = this->cell(cell);
        map_[row][col] = 0;
    }
    
    int getValue(string formula) {
        auto position = formula.find('+');
        return value(formula.substr(1, position - 1)) + value(formula.substr(position + 1));
    }
};
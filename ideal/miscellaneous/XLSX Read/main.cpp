#include <OpenXLSX.hpp>

#include <exception>
#include <filesystem>
#include <iostream>

// 不能合并单元格，单元格中有中文也不能显示

int main(int argc, char* argv[]) {
    try {
        std::filesystem::path xlsx_path(
            LR"(C:\Users\FlushHip\Desktop\一.xlsx)");
        OpenXLSX::XLDocument doc(xlsx_path.string());
        auto wks1 =
            doc.workbook().worksheet(std::filesystem::path(L"一").string());
        std::cout << std::filesystem::path(
                         wks1.cell("B4").value().get<std::string>())
                         .string()
                  << std::endl;
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}

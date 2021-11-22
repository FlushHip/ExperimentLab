#pragma once

#include "base.h"

#include <memory>

class MainWindow;

class MainWindowExecution : public ExecutionBase
{
public:
    MainWindowExecution();
    ~MainWindowExecution() override;
    int main() override;

private:
    std::unique_ptr<MainWindow> mainWindow_;
};

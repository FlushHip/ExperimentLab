#pragma once

#include <memory>

#include <QWidget>

#include "base.h"

class SpreadsheetExecution : public ExecutionBase
{
public:
    int main() override;
private:
    std::unique_ptr<QWidget> w_;
};

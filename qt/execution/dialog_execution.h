#pragma once

#include <vector>
#include <memory>

#include <QWidget>

#include "base.h"

class DialogExecution : public ExecutionBase
{
public:
    int main() override;
private:
    std::vector<std::unique_ptr<QWidget>> wList_;
};

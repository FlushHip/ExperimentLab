#include "spreadsheet_execution.h"


#include "forms/spreadsheet.h"

int SpreadsheetExecution::main()
{
    w_ = std::make_unique<Spreadsheet>();
    w_->setFixedSize(QSize(600, 400));
    w_->show();
    return 0;
}

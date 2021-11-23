#include "customwidgets_execution.h"

#include "forms/hexspinbox.h"
#include "forms/iconeditor.h"

int CustomWidgetsExecution::main()
{
    wList_.push_back(std::make_unique<IconEditor>());
    wList_.push_back(std::make_unique<HexSpinBox>());

    wList_[0]->show();

    return 0;
}

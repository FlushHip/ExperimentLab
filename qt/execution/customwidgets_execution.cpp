#include "customwidgets_execution.h"

#include "forms/hexspinbox.h"
#include "forms/iconeditor.h"

int CustomWidgetsExecution::main()
{
    auto iconEditor = std::make_unique<IconEditor>();
    iconEditor->setIconImage(QImage(":/images/mouse.png"));
    wList_.push_back(std::move(iconEditor));
    wList_.push_back(std::make_unique<HexSpinBox>());

    wList_[0]->show();

    return 0;
}

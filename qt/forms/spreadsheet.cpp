#include "spreadsheet.h"

#include <QFile>
#include <QMessageBox>
#include <QDataStream>
#include <QApplication>
#include <QClipboard>

#include "items/cell.h"

Spreadsheet::Spreadsheet(QWidget *parent)
    : QTableWidget(parent)
    , autoRecalc_(true)
{
    setItemPrototype(new Cell);
    setSelectionMode(QTableWidget::ContiguousSelection);

    connect(this, &Spreadsheet::itemChanged, this, &Spreadsheet::somethingChanged);

    clear();
}

Spreadsheet::~Spreadsheet() = default;

void Spreadsheet::clear()
{
    setRowCount(0);
    setColumnCount(0);

    setRowCount(RowCount);
    setColumnCount(ColumnCount);

    for (int i = 0; i< ColumnCount; ++i) {
        auto item = new QTableWidgetItem;
        item->setText(QString('A' + i));
        setHorizontalHeaderItem(i, item);
    }

    setCurrentCell(0, 0);
}

Cell *Spreadsheet::cell(int row, int column) const
{
    return static_cast<Cell *>(item(row, column));
}

QString Spreadsheet::text(int row, int column) const
{
    auto c = cell(row, column);
    if (c != nullptr) {
        return c->text();
    }
    return "";
}

QString Spreadsheet::formula(int row, int column) const
{
    auto c = cell(row, column);
    if (c != nullptr) {
        return c->formula();
    }
    return "";
}

void Spreadsheet::setFormula(int row, int column, const QString &formula)
{
    auto c = cell(row, column);
    if (c == nullptr) {
        c = new Cell;
        setItem(row, column, c);
    }
    c->setFormula(formula);
}

QString Spreadsheet::currentLocation() const
{
    return QChar('A' + currentColumn()) + QString::number(1 + currentRow());
}

QString Spreadsheet::currentFormula() const
{
    return formula(currentColumn(), currentRow());
}

void Spreadsheet::somethingChanged()
{
    if (autoRecalc_) {
        recalculate();
    }
    emit modified();
}

bool Spreadsheet::writeFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, tr("Spreadsheet")
            , tr("Can't write file %1:\n%2.").arg(file.fileName()).arg(file.errorString()));
        return false;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_9);

    out << quint32(MagicNumber);

    QApplication::setOverrideCursor(Qt::WaitCursor);
    for (int row = 0; row < RowCount; ++row) {
        for (int column = 0; column < ColumnCount; ++column) {
            auto str = formula(row, column);
            if (!str.isEmpty()) {
                out << quint16(row) << quint16(column) << str;
            }
        }
    }

    QApplication::restoreOverrideCursor();

    return true;
}

bool Spreadsheet::readFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, tr("Spreadsheet")
            , tr("Can't read file %1:\n%2.").arg(file.fileName()).arg(file.errorString()));
        return false;
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_9);

    quint32 magic;
    in >> magic;
    if (magic != MagicNumber) {
        QMessageBox::warning(this, tr("Spreadsheet")
            , tr("The file isn't a Spreadsheet file."));
        return false;
    }

    clear();

    quint16 row = 0, column = 0;
    QString str;

    QApplication::setOverrideCursor(Qt::WaitCursor);
    while (!in.atEnd()) {
        in >> row >> column >> str;
        setFormula(row, column, str);
    }
    QApplication::restoreOverrideCursor();

    return true;
}

void Spreadsheet::cut()
{
    copy();
    del();
}

void Spreadsheet::copy()
{
    QTableWidgetSelectionRange range = selectedRange();
    QString str;

    for (int i = 0; i < range.rowCount(); ++i) {
        if (i > 0) {
            str += "\n";
        }
        for (int j = 0; j < range.columnCount(); ++j) {
            if (j > 0) {
                str += '\t';
            }
            str += formula(range.topRow() + i, range.leftColumn() + j);
        }
    }

    QApplication::clipboard()->setText(str);
}

QTableWidgetSelectionRange Spreadsheet::selectedRange() const
{
    auto ranges = selectedRanges();
    if (ranges.isEmpty()) {
        return {};
    }
    return ranges.first();
}

void Spreadsheet::paste()
{
    auto range = selectedRange();
    QString str = QApplication::clipboard()->text();
    QStringList rows = str.split('\n');
    int numRows = rows.count();
    int numColumns = rows.first().count('\t') + 1;

    if (range.rowCount() * range.columnCount() != 1
        && (range.rowCount() != numRows || range.columnCount() != numColumns)) {
        QMessageBox::warning(this, tr("Spreadsheet")
            , tr("The information cann't be pasted because the copy"
                    "and paste areas aren't the same size."));
        return;
    }

    for (int i = 0; i < numRows; ++i) {
        int row = range.topRow() + i;
        if (!(row < RowCount)) {
            break;
        }
        QStringList columns = rows[i].split('\t');
        for (int j = 0; j < numColumns; ++j) {
            int column = range.leftColumn() + j;
            if (column < ColumnCount) {
                setFormula(row, column, columns[j]);
            }
        }
    }

    somethingChanged();
}

void Spreadsheet::del()
{
    auto items = selectedItems();
    if (!items.isEmpty()) {
        for (auto item : items) {
            delete item;
        }
        somethingChanged();
    }
}
void Spreadsheet::selectCurrentRow()
{
    selectRow(currentRow());
}

void Spreadsheet::selectCurrentColumn()
{
    selectColumn(currentColumn());
}

void Spreadsheet::findNext(const QString &str, Qt::CaseSensitivity cs)
{
    for (int row = currentRow(); row < RowCount; ++row) {
        for (int column = row == currentRow() ? currentColumn() + 1 : 0
            ; column < ColumnCount; ++column) {
            if (text(row, column).contains(str, cs)) {
                clearSelection();
                setCurrentCell(row, column);
                activateWindow();

                return;
            }
        }
    }
    QApplication::beep();
}

void Spreadsheet::findPrevious(const QString &str, Qt::CaseSensitivity cs)
{
    for (int row = currentRow(); row >= 0; --row) {
        for (int column = row == currentRow() ? currentColumn() - 1 : ColumnCount - 1
            ; column >= 0; --column) {
            if (text(row, column).contains(str, cs)) {
                clearSelection();
                setCurrentCell(row, column);
                activateWindow();

                return;
            }
        }
    }
    QApplication::beep();
}

void Spreadsheet::recalculate()
{
    for (int row = 0; row < RowCount; ++row) {
        for (int column = 0; column < ColumnCount; ++column) {
            if (auto c = cell(row, column)) {
                c->setDirty();
            }
        }
    }

    viewport()->update();
}

void Spreadsheet::setAutoRecalculate(bool recalc)
{
    autoRecalc_ = recalc;
    if (autoRecalc_) {
        recalculate();
    }
}

void Spreadsheet::sort(const SpreadsheetCompare &compare)
{
    auto range = selectedRange();

    QList<QStringList> rows;
    for (int i = 0; i < range.rowCount(); ++i) {
        QStringList row;
        for (int j = 0; j < range.columnCount(); ++j) {
            row.append(formula(range.topRow() + i, range.leftColumn() + j));
        }
        rows.append(row);
    }

    std::stable_sort(rows.begin(), rows.end(), compare);

    for (int i = 0; i < range.rowCount(); ++i) {
        for (int j = 0; i < range.columnCount(); ++j) {
            setFormula(range.topRow() + i, range.leftColumn() + j, rows[i][j]);
        }
    }

    clearSelection();
    somethingChanged();
}

bool SpreadsheetCompare::operator()(const QStringList &row1, const QStringList &row2) const
{
    for (int i = 0; i < KeyCount; ++i) {
        int column = keys[i];
        if (column == -1) {
            continue;
        }
        if (row1[column] != row2[column]) {
            return ascending[i] ? row1[column] < row2[column] : row1[column] > row2[column];
        }
    }
    return false;
}

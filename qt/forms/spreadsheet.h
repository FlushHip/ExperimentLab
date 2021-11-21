#pragma once

#include <QTableWidget>

class Cell;
class SpreadsheetCompare;

class Spreadsheet : public QTableWidget
{
    Q_OBJECT
public:
    explicit Spreadsheet(QWidget *parent = Q_NULLPTR);
    ~Spreadsheet() override;

    bool autoRecalculate() const { return autoRecalc_; };
    QString currentLocation() const;
    QString currentFormula() const;
    QTableWidgetSelectionRange selectedRange() const;

    void clear();
    bool readFile(const QString &fileName);
    bool writeFile(const QString &fileName);
    void sort(const SpreadsheetCompare &compare);

public:

public slots:
    void cut();
    void copy();
    void paste();
    void del();
    void selectCurrentRow();
    void selectCurrentColumn();
    void recalculate();
    void setAutoRecalculate(bool recalc);
    void findNext(const QString &str, Qt::CaseSensitivity cs);
    void findPrevious(const QString &str, Qt::CaseSensitivity cs);

signals:
    void modified();

private slots:
    void somethingChanged();

private:
    Cell *cell(int row, int column) const;
    QString text(int row, int column) const;
    QString formula(int row, int column) const;
    void setFormula(int row, int column, const QString &formula);

private:
    enum {
        MagicNumber = 0x7E51C883,
        RowCount = 999,
        ColumnCount = 26,
    };

    bool autoRecalc_;
};

class SpreadsheetCompare
{
public:
    bool operator()(const QStringList &row1, const QStringList &row2) const;
    enum { KeyCount = 3 };

    int keys[KeyCount];
    bool ascending[KeyCount];
};

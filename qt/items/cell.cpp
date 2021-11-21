#include "cell.h"

Cell::Cell()
{
    setDirty();
}

QTableWidgetItem *Cell::clone() const
{
    return new Cell(*this);
}

void Cell::setFormula(const QString &formula)
{
    setData(Qt::EditRole, formula);
}

QString Cell::formula() const
{
    return data(Qt::EditRole).toString();
}

void Cell::setData(int role, const QVariant &value)
{
    QTableWidgetItem::setData(role, value);
    if (role == Qt::EditRole) {
        setDirty();
    }
}

QVariant Cell::data(int role) const
{
    if (role == Qt::DisplayRole) {
        if (value().isValid()) {
            return value().toString();
        }
        return "####";
    } else if (role == Qt::TextAlignmentRole) {
        if (value().type() == QVariant::String) {
            return int(Qt::AlignLeft | Qt::AlignVCenter);
        }
        return int(Qt::AlignRight | Qt::AlignVCenter);
    }
    return QTableWidgetItem::data(role);
}

void Cell::setDirty()
{
    cacheIsDirty_ = true;
}

QVariant Cell::value() const
{
    if (cacheIsDirty_) {
        cacheIsDirty_ = false;
        QString formulaStr = formula();
        if (formulaStr.startsWith('\'')) {
            cachedValue_ = formulaStr.mid(1);
        } else if (formulaStr.startsWith('=')) {
            cachedValue_ = QVariant(QVariant::Invalid);
            QString expr = formulaStr.mid(1);
            expr.replace(" ", "");
            expr.append(QChar::Null);

            int pos = 0;
            cachedValue_ = evalExpression(expr, pos);
            if (expr[pos] != QChar::Null) {
                cachedValue_ = QVariant(QVariant::Invalid);
            }
        } else {
            bool ok = false;
            double d = formulaStr.toDouble(&ok);
            if (ok) {
                cachedValue_ = d;
            } else {
                cachedValue_ = formulaStr;
            }
        }
    }

    return cachedValue_;
}

QVariant Cell::evalExpression(const QString &str, int &pos) const
{
    QVariant ans = evalTerm(str, pos);
    while (str[pos] != QChar::Null) {
        if (ans.type() != QVariant::Double) {
            return QVariant(QVariant::Invalid);
        }
        auto op = str[pos];
        if (op != '+' && op != '-') {
            return ans;
        }

        ++pos;
        auto term = evalTerm(str, pos);
        if (term.type() != QVariant::Double) {
            return QVariant(QVariant::Invalid);
        }
        if (op == '+') {
            ans = ans.toDouble() + term.toDouble();
        } else {
            ans = ans.toDouble() - term.toDouble();
        }
    }
    return ans;
}

QVariant Cell::evalTerm(const QString &str, int &pos) const
{
    QVariant ans = evalFactor(str, pos);
    while (str[pos] != QChar::Null) {
        if (ans.type() != QVariant::Double) {
            return QVariant(QVariant::Invalid);
        }
        auto op = str[pos];
        if (op != '*' && op != '/') {
            return ans;
        }

        ++pos;
        auto factor = evalFactor(str, pos);
        if (factor.type() != QVariant::Double) {
            return QVariant(QVariant::Invalid);
        }
        if (op == '*') {
            ans = ans.toDouble() * factor.toDouble();
        } else {
            if (factor.toDouble() == '0.0') {
                return QVariant(QVariant::Invalid);
            }
            ans = ans.toDouble() / factor.toDouble();
        }
    }
    return ans;

}

QVariant Cell::evalFactor(const QString &str, int &pos) const
{
    QVariant ans;
    bool negative = false;

    if (str[pos] == QChar::Null) {
        return ans;
    }

    if (str[pos] == '-') {
        negative = true;
        ++pos;
    }

    if (str[pos] == QChar::Null) {
        return ans;
    }

    if (str[pos] == '(') {
        ++pos;
        ans = evalExpression(str, pos);
        if (str[pos] != ')') {
            return QVariant(QVariant::Invalid);
        }
        ++pos;
    } else {
        QRegExp regExp("[A-Za-z][1-9][0-9]{0, 2}");
        QString token;
        while (str[pos].isLetterOrNumber() || str[pos] == '.') {
            token.push_back(str[pos]);
            ++pos;
        }

        if (regExp.exactMatch(token)) {
            int column = token[0].toUpper().unicode() - 'A';
            int row = token.mid(1).toInt() - 1;

            auto c = static_cast<Cell *>(tableWidget()->item(row, column));
            if (c != nullptr) {
                ans = c->value();
            } else {
                ans = 0.0;
            }
        } else {
            bool ok = false;
            ans = token.toDouble(&ok);
            if (!ok) {
                ans = QVariant(QVariant::Invalid);
            }
        }
    }
    if (negative && ans.type() == QVariant::Double) {
        ans = -ans.toDouble();
    }
    return ans;
}

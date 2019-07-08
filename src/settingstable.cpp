#include "settingstable.h"

#include <QMetaEnum>
#include <QHeaderView>
#include <QComboBox>

SettingsTable::SettingsTable(QWidget *parent)
    : QTableWidget (parent)
{
    setup();

    setValue(7, 0, 11);
}

void SettingsTable::setup()
{
    auto axisLabels = createLabelsNames("Ось #", sf::Joystick::AxisCount);
    auto motorLabels = createLabelsFromEnum(this, "Motors");

    setRowCount(axisLabels.count());
    setColumnCount(motorLabels.count());

    setItemDelegate(new NumberValidator);
    setSelectionMode(SelectionMode::SingleSelection);
    setVerticalHeaderLabels(axisLabels);
    setHorizontalHeaderLabels(motorLabels);
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(this, &SettingsTable::itemChanged, [this](QTableWidgetItem *item) {
        auto data = item->data(Qt::ItemDataRole::DisplayRole);
        auto row = item->row();
        auto col = item->column();
        auto value = data.value<qreal>();
        emit changed(row, col, value);
    });
}

void SettingsTable::setValue(int row, int column, qreal value)
{
    QTableWidgetItem *item = this->item(row, column);
    if(!item) {
        item = new QTableWidgetItem();
        setItem(row, column, item);
    }
    item->setData(Qt::ItemDataRole::EditRole, value);
}

qreal SettingsTable::getValue(int row, int column)
{
    QTableWidgetItem *item = this->item(row, column);
    if(!item) {
        item = new QTableWidgetItem();
        setItem(row, column, item);
        item->setData(Qt::ItemDataRole::EditRole, 0);
        return 0;
    }
    auto data = item->data(Qt::ItemDataRole::DisplayRole);
    return data.value<qreal>();
}

QVector<qreal> SettingsTable::getValue(int axis)
{
    auto columns = columnCount();
    QVector<qreal> result(columns);
    for (int i =0; i < columns; ++i)
    {
        result[i] = getValue(axis, i);
    }
    return result;
}



QWidget *NumberValidator::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)

    QLineEdit *lineEdit = new QLineEdit(parent);
    QDoubleValidator *validator = new QDoubleValidator(-100.0, 100.0, 2, lineEdit);
    lineEdit->setValidator(validator);
    return lineEdit;
}

template<typename T>
QStringList createLabelsFromEnum(T *object, const char *enumName)
{
    Q_UNUSED(object)
    auto metaObject = T::staticMetaObject;
    auto enumIndex = metaObject.indexOfEnumerator(enumName);
    auto axisEnum = metaObject.enumerator(enumIndex);
    int axisCount = axisEnum.keyCount();

    QStringList names;
    for (int i = 0; i < axisCount; ++i)
    {
        auto key = axisEnum.key(i);
        names.append(key);
    }
    return names;
}

QStringList createLabelsNames(QString prefix, int count)
{
    QStringList names;
    QString format("%1%2");
    for (int i = 0; i < count; ++i)
    {
        names.append(format.arg(prefix, QString::number(i+1)));
    }

    return names;
}

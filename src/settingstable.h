#ifndef SETTINGSTABLE_H
#define SETTINGSTABLE_H

#include <QTableWidget>
#include <QAbstractTableModel>

#include <QItemDelegate>
#include <QLineEdit>
#include <SFML/Window.hpp>

class SettingsTable : public QTableWidget
{
    Q_OBJECT
public:
//    static const int AXIS_COUNT = 8;
//    static const int MOTOR_COUNT = 6;

    enum JoystickAxis
    {
        X,
        Y,
        Z,
        R,
        U,
        V,
        PovX,
        PovY
    };
    Q_ENUM(JoystickAxis)

    enum Motors
    {
        FrontLeft,
        FrontRight,
        BackLeft,
        BackRight,
        VerticalFront,
        VerticalBack,
        ServoX,
        ServoY,
        Manipulator
    };
    Q_ENUM(Motors)

    SettingsTable(QWidget *parent = nullptr);

    void resetData();
    void setValue(int row, int column, qreal value);
    qreal getValue(int row, int column);
    QVector<qreal> getValue(int axis);

signals:
    void changed(int axis, int engine, qreal);

private:
    void setup();
};

class NumberValidator : public QItemDelegate
{
public:
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem & option, const QModelIndex & index) const;
};

template<typename T>
QStringList createLabelsFromEnum(T *object, const char *enumName);

#endif // SETTINGSTABLE_H

#include "SfJoystickSettingsDialog.hpp"
#include <QDebug>
#include <QLabel>
#include <QVBoxLayout>
#include <QMetaEnum>

#include "settingstable.h"

SfJoystickSettingsDialog::SfJoystickSettingsDialog(QWidget* parent)
    : QDialog(parent)
    , m_settingsTable(new SettingsTable(this))
    , m_buttonCombobox1(new QComboBox(this))
    , m_buttonCombobox2(new QComboBox(this))
    , m_settings(new QSettings("RovSettings.ini", QSettings::IniFormat))
    , m_openButtonIndex(0)
    , m_closeButtonIndex(0)

{
    createLayout();
    loadSettings();
    createConnections();
}

RealList SfJoystickSettingsDialog::getThrustersSpeed(sf::Joystick::Axis axis)
{
    auto motorMultipliers = m_settingsTable->getValue(axis);
    auto value = sf::Joystick::getAxisPosition(0, axis);

    QVector<qreal> result;
    for(auto multiplier: motorMultipliers)
    {
        result.append(value * multiplier);
    }
    return result;
}

quint32 SfJoystickSettingsDialog::getOpenButtonIndex()
{
    return m_openButtonIndex;
}

quint32 SfJoystickSettingsDialog::getCloseButtonIndex()
{
    return m_closeButtonIndex;
}

void SfJoystickSettingsDialog::createLayout()
{
    auto createButtonBox = [](QComboBox* box) {
        for (size_t buttons = 0; buttons < sf::Joystick::getButtonCount(0); ++buttons) {
            box->addItem(QString("Копка #%1").arg(buttons));
        }
    };

    auto addToLayout = [](QComboBox* box, QString lName, QVBoxLayout* layout) {
            QHBoxLayout* row = new QHBoxLayout;
            row->setAlignment(Qt::Alignment(Qt::AlignmentFlag::AlignLeft | Qt::AlignmentFlag::AlignVCenter));
            QLabel* name = new QLabel(lName);
            name->setFixedSize(150, 20);
            row->addWidget(name);
            row->addWidget(box);
            layout->addLayout(row);
    };

    QVBoxLayout *layout = new QVBoxLayout();
    createButtonBox(m_buttonCombobox1);
    createButtonBox(m_buttonCombobox2);

    layout->addWidget(m_settingsTable);
    addToLayout(m_buttonCombobox1, "Кнопка открытия клешни", layout);
    addToLayout(m_buttonCombobox2, "Кнопка закрытия клешни", layout);

    resize(700, 300);
    setLayout(layout);
}

void SfJoystickSettingsDialog::createConnections()
{
    connect(m_settingsTable, &SettingsTable::changed, this, &SfJoystickSettingsDialog::saveSettings);
    connect(m_buttonCombobox1, QOverload<int>::of(&QComboBox::currentIndexChanged), [this](int index){ m_openButtonIndex = index;  });
    connect(m_buttonCombobox2, QOverload<int>::of(&QComboBox::currentIndexChanged), [this](int index){ m_closeButtonIndex = index; });

}

QString getEnumName(int index)
{
    auto metaObject = SettingsTable::staticMetaObject;
    auto enumIndex = metaObject.indexOfEnumerator("JoystickAxis");
    auto axisEnum = metaObject.enumerator(enumIndex);
    return axisEnum.key(index);
}

void SfJoystickSettingsDialog::saveSettings(int axis, int engine, qreal value)
{
    QString name = getEnumName(axis);
    name.append(QString::number(engine));

    m_settings->beginGroup("Joystick");
    m_settings->setValue(name, value);
    m_settings->endGroup();
}

void SfJoystickSettingsDialog::loadSettings()
{
    m_settings->beginGroup("Joystick");

    for (int i = 0; i < m_settingsTable->rowCount(); ++i)
    {
        for (int j = 0; j < m_settingsTable->columnCount(); ++j)
        {
            auto key = getEnumName(i).append(QString::number(j));
            auto value = m_settings->value(key, 0).value<qreal>();
            m_settingsTable->setValue(i, j, value);
        }
    }

    m_settings->endGroup();
}

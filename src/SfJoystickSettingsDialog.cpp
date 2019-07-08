#include "SfJoystickSettingsDialog.hpp"
#include <QDebug>
#include <QLabel>
#include <QVBoxLayout>
#include <QMetaEnum>

#include "settingstable.h"

SfJoystickSettingsDialog::SfJoystickSettingsDialog(QWidget* parent)
    : QDialog(parent)
    , m_settingsTable(new SettingsTable(this))
    , m_settings(new QSettings("RovSettings.ini", QSettings::IniFormat))

{
    createLayout();
    loadSettings();
    createConnections();
}

QVector<qreal> SfJoystickSettingsDialog::getMotorSpeeds(sf::Joystick::Axis axis)
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

void SfJoystickSettingsDialog::createLayout()
{
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(m_settingsTable);

    resize(500, 300);
    setLayout(layout);
}

void SfJoystickSettingsDialog::createConnections()
{
    connect(m_settingsTable, &SettingsTable::changed, this, &SfJoystickSettingsDialog::saveSettings);
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

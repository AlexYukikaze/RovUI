#pragma once

#include <QWidget>
#include <QDialog>
#include <QPushButton>
#include <QSettings>
#include <SFML/Window.hpp>

#include "settingstable.h"

using RealList = QVector<qreal>;

class SfJoystickSettingsDialog : public QDialog {
    Q_OBJECT
public:
    explicit SfJoystickSettingsDialog(QWidget* parent = nullptr);
    RealList getThrustersSpeed(sf::Joystick::Axis axis);

signals:

private:
    void createLayout();
    void createConnections();
    void loadSettings();
    void saveSettings(int axis, int engine, qreal value);

    SettingsTable *m_settingsTable;
    QSettings *m_settings;
    bool m_ready;
};

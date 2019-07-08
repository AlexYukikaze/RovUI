#pragma once

#include <QWidget>
#include <QDialog>

#include <QPushButton>

#include <QSettings>



#include <SFML/Window.hpp>

#include "settingstable.h"

class SfJoystickSettingsDialog : public QDialog {
    Q_OBJECT
public:
    explicit SfJoystickSettingsDialog(QWidget* parent = nullptr);
    QVector<qreal> getMotorSpeeds(sf::Joystick::Axis axis);

signals:

private:
    void createLayout();
    void createConnections();
    void onLoaded();
    void loadSettings();
    void saveSettings(int axis, int engine, qreal value);

    SettingsTable *m_settingsTable;
    QSettings *m_settings;
    bool m_ready;
};

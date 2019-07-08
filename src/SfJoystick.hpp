#pragma once

#include "SfJoystickSettingsDialog.hpp"
#include <QObject>

class SfJoystick : public QObject {
    Q_OBJECT
public:
    SfJoystick(QObject* parent = nullptr);
    ~SfJoystick();
    bool isConnected();

    int servoXAxis();
    int servoYAxis();

    SfJoystickSettingsDialog* settingsDialog();

private slots:

    void timerEvent(QTimerEvent*);

private:
    int m_servoX = 0;
    int m_servoY = 0;
    int m_manipulatorRotate = 0;
    int m_openManipulator = 0;
    int m_closeManipulator = 0;

    enum { MinAxisValue = 10 };

    QScopedPointer<SfJoystickSettingsDialog> m_joystickSettingsDialog;
};

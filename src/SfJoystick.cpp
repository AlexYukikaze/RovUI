#include "SfJoystick.hpp"
#include "RovSingleton.hpp"
#include <QDebug>
#include <SFML/Window.hpp>

SfJoystick::SfJoystick(QObject* parent)
    : QObject(parent)
    , m_servoX(0)
    , m_servoY(0)
    , m_manipulatorRotate(0)
    , m_joystickSettingsDialog(new SfJoystickSettingsDialog)
{
    startTimer(80);
}

SfJoystick::~SfJoystick()
{
}

int SfJoystick::servoXAxis()
{
    return m_servoX;
}

int SfJoystick::servoYAxis()
{
    return m_servoY;
}

void SfJoystick::timerEvent(QTimerEvent*)
{
    sf::Joystick::update();

    if (isConnected()) {
        auto dialog = settingsDialog();
        for (int i = 0; i < sf::Joystick::AxisCount; ++i)
        {
            auto axis = static_cast<sf::Joystick::Axis>(i);
            auto thrustersValue = dialog->getThrustersSpeed(axis);
            auto& thrusters = RovSingleton::instance()->control().thrusterPower;

            for (int j =0; j < thrustersValue.count(); ++j)
            {
                auto thrust = thrustersValue[j];
                thrusters[j] += static_cast<uint8_t>(thrust);
            }
            m_servoX += thrustersValue[6];
            m_servoY += thrustersValue[7];
            m_manipulatorRotate += thrustersValue[8];
        }
    }

    if (isConnected()) {
        RovSingleton::instance()->control().cameraRotation[0] = static_cast<qint8>(m_servoX);
        RovSingleton::instance()->control().cameraRotation[1] = static_cast<qint8>(m_servoY);
        RovSingleton::instance()->control().manipulatorRotation = static_cast<qint8>(m_manipulatorRotate);
//        RovSingleton::instance()->control().manipulatorOpenClose = sf::Joystick::isButtonPressed(0, m_joystickSettingsDialog.data()->manipulatorOpenButton()) - sf::Joystick::isButtonPressed(0, m_joystickSettingsDialog.data()->manipulatorCloseButton());
    } else {
        RovSingleton::instance()->control().cameraRotation[0] = static_cast<qint8>(0);
        RovSingleton::instance()->control().cameraRotation[1] = static_cast<qint8>(0);
        RovSingleton::instance()->control().manipulatorRotation = 0;
    }
}

bool SfJoystick::isConnected()
{
    return sf::Joystick::isConnected(0);
}

SfJoystickSettingsDialog* SfJoystick::settingsDialog()
{
    return m_joystickSettingsDialog.data();
}

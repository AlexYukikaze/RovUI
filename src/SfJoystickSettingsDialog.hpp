#pragma once

#include <QWidget>
#include <QDialog>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QSettings>
#include <SFML/Window.hpp>

#include "settingstable.h"

using RealList = QVector<qreal>;

class SfJoystickSettingsDialog : public QDialog {
    Q_OBJECT
public:
    explicit SfJoystickSettingsDialog(QWidget* parent = nullptr);
    RealList getThrustersSpeed(sf::Joystick::Axis axis);

    quint32 getOpenButtonIndex();
    quint32 getCloseButtonIndex();

signals:

private:
    void createLayout();
    void createConnections();
    void loadSettings();
    void saveSettings(int axis, int engine, qreal value);

    SettingsTable *m_settingsTable;
    QComboBox *m_buttonCombobox1;
    QComboBox *m_buttonCombobox2;
    QSettings *m_settings;
    int m_openButtonIndex;
    int m_closeButtonIndex;
};

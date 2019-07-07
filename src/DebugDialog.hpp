#pragma once
#include <QCheckBox>
#include <QDialog>
#include <QLabel>
#include <QSlider>
#include <QWidget>

class DebugDialog : public QDialog {
    Q_OBJECT
public:
    explicit DebugDialog(QWidget* parent = nullptr);

signals:
private slots:
    void timerEvent(QTimerEvent* event);
public slots:
private:
    void createConnections();
    void createLayout();

    QScopedPointer<QCheckBox> m_isDebug;

    QScopedPointer<QSlider> m_thrusterOneSlider;
    QScopedPointer<QSlider> m_thrusterTwoSlider;
    QScopedPointer<QSlider> m_thrusterThreeSlider;
    QScopedPointer<QSlider> m_thrusterFourSlider;
    QScopedPointer<QSlider> m_thrusterFiveSlider;
    QScopedPointer<QSlider> m_thrusterSixSlider;

    QScopedPointer<QLabel> m_thrusterOneLabel;
    QScopedPointer<QLabel> m_thrusterTwoLabel;
    QScopedPointer<QLabel> m_thrusterThreeLabel;
    QScopedPointer<QLabel> m_thrusterFourLabel;
    QScopedPointer<QLabel> m_thrusterFiveLabel;
    QScopedPointer<QLabel> m_thrusterSixLabel;
};

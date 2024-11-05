#ifndef SET_HPP
#define SET_HPP

#include <QObject>
#include <QSlider>
#include <QSpinBox>
#include <vector>

class Set : public QObject
{
    Q_OBJECT

public:
    Set(QObject *parent = nullptr);
    void connectHSVSyncedSliders();

private:
    void syncSliderAndSpinBox(QSlider *slider, QSpinBox *spinBox);
};

#endif // SET_HPP

#include "cam_opencv/set.hpp"

#include <QWidget>
#include <QSlider>
#include <QSpinBox>
#include <QMainWindow>

Set::Set(QObject *parent) : QObject(parent)
{
}

void Set::connectHSVSyncedSliders()
{
    QMainWindow *mainWindow = qobject_cast<QMainWindow*>(parent());

    // H Lower
    syncSliderAndSpinBox(mainWindow->findChild<QSlider*>("sliderHlower"), mainWindow->findChild<QSpinBox*>("spinHLower"));
    syncSliderAndSpinBox(mainWindow->findChild<QSlider*>("sliderHlower_2"), mainWindow->findChild<QSpinBox*>("spinHLower_2"));
    syncSliderAndSpinBox(mainWindow->findChild<QSlider*>("sliderHlower_3"), mainWindow->findChild<QSpinBox*>("spinHLower_3"));

    // H Upper
    syncSliderAndSpinBox(mainWindow->findChild<QSlider*>("sliderHUpper"), mainWindow->findChild<QSpinBox*>("spinHUpper"));
    syncSliderAndSpinBox(mainWindow->findChild<QSlider*>("sliderHUpper_2"), mainWindow->findChild<QSpinBox*>("spinHUpper_2"));
    syncSliderAndSpinBox(mainWindow->findChild<QSlider*>("sliderHUpper_3"), mainWindow->findChild<QSpinBox*>("spinHUpper_3"));

    // S Lower
    syncSliderAndSpinBox(mainWindow->findChild<QSlider*>("sliderSLower"), mainWindow->findChild<QSpinBox*>("spinSLower"));
    syncSliderAndSpinBox(mainWindow->findChild<QSlider*>("sliderSLower_2"), mainWindow->findChild<QSpinBox*>("spinSLower_2"));
    syncSliderAndSpinBox(mainWindow->findChild<QSlider*>("sliderSLower_3"), mainWindow->findChild<QSpinBox*>("spinSLower_3"));

    // S Upper
    syncSliderAndSpinBox(mainWindow->findChild<QSlider*>("sliderSUpper"), mainWindow->findChild<QSpinBox*>("spinSUpper"));
    syncSliderAndSpinBox(mainWindow->findChild<QSlider*>("sliderSUpper_2"), mainWindow->findChild<QSpinBox*>("spinSUpper_2"));
    syncSliderAndSpinBox(mainWindow->findChild<QSlider*>("sliderSUpper_3"), mainWindow->findChild<QSpinBox*>("spinSUpper_3"));

    // V Lower
    syncSliderAndSpinBox(mainWindow->findChild<QSlider*>("sliderVLower"), mainWindow->findChild<QSpinBox*>("spinVLower"));
    syncSliderAndSpinBox(mainWindow->findChild<QSlider*>("sliderVLower_2"), mainWindow->findChild<QSpinBox*>("spinVLower_2"));
    syncSliderAndSpinBox(mainWindow->findChild<QSlider*>("sliderVLower_3"), mainWindow->findChild<QSpinBox*>("spinVLower_3"));

    // V Upper
    syncSliderAndSpinBox(mainWindow->findChild<QSlider*>("sliderVUpper"), mainWindow->findChild<QSpinBox*>("spinVUpper"));
    syncSliderAndSpinBox(mainWindow->findChild<QSlider*>("sliderVUpper_2"), mainWindow->findChild<QSpinBox*>("spinVUpper_2"));
    syncSliderAndSpinBox(mainWindow->findChild<QSlider*>("sliderVUpper_3"), mainWindow->findChild<QSpinBox*>("spinVUpper_3"));
}

void Set::syncSliderAndSpinBox(QSlider *slider, QSpinBox *spinBox)
{
    connect(slider, &QSlider::valueChanged, spinBox, &QSpinBox::setValue);
    connect(spinBox, QOverload<int>::of(&QSpinBox::valueChanged), slider, &QSlider::setValue);

    // 초기 값 동기화
    spinBox->setValue(slider->value());
}

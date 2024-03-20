#include <QApplication>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QSlider>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("Enter Youer Age");

    QSpinBox spinBox;
    QSlider slider(Qt::Horizontal);
    spinBox.setRange(0, 145);
    slider.setRange(0, 145);

    QObject::connect(&spinBox, SIGNAL(valueChanged(int)), &slider, SLOT(setValue(int)));
    QObject::connect(&slider, SIGNAL(valueChanged(int)), &spinBox, SLOT(setValue(int)));
    spinBox.setValue(31);

    QHBoxLayout layout;
    layout.addWidget(&spinBox);
    layout.addWidget(&slider);
    window.setLayout(&layout);

    window.show();

    return app.exec();
}

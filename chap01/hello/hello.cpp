#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    // IDE直接帮我们解决了书中说的内存泄露的问题：使用局部变量即可
    QLabel label("<h2><i>Hello</i> <font color=red>Qt!</font></h2>");
    label.show();
    return app.exec();
}

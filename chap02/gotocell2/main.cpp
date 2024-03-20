#include "gotocelldialog.h"

#include <QApplication>

#include <iostream>
// using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    GoToCellDialog dialog;
    dialog.show();
    return app.exec();
}

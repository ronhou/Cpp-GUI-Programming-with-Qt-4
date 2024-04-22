#include "mainwindow.h"

#include <QApplication>
#include <QSplashScreen>
#include <QPixmap>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/images/splash.png"));
    splash->show();

    Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
    splash->showMessage(QObject::tr("Setting up the main window..."), topRight, Qt::white);

    MainWindow *mainWin = new MainWindow;

    splash->showMessage(QObject::tr("Loading modules..."), topRight, Qt::white);

    mainWin->show();
    splash->finish(mainWin);
    delete splash;

    return app.exec();
}

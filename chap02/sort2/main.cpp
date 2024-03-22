#include <QApplication>
#include <QUiLoader>
#include <QFile>
#include <QWidget>
#include <QGroupBox>
#include <QComboBox>

bool hideWidget(QWidget *mainWidget, const QString &widgetName)
{
    QWidget *widget = mainWidget->findChild<QWidget *>(widgetName);
    if (widget) {
        widget->hide();
        return true;
    }
    return false;
}

bool columnComboBoxAddItems(QWidget *mainWidget, const QString &widgetName, QChar first, QChar last)
{
    QComboBox *columnCombo = mainWidget->findChild<QComboBox *>(widgetName);
    if (columnCombo) {
        for (QChar ch = first; ch <= last; ch = ch.unicode() + 1)
        {
            columnCombo->addItem(ch);
        }
        return true;
    }
    return false;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QUiLoader uiLoader;
    QFile file("sortdialog.ui");
    QWidget *sortDialog = uiLoader.load(&file);
    if (sortDialog) {
        hideWidget(sortDialog, "secondaryGroupBox");
        hideWidget(sortDialog, "tertiaryGroupBox");
        columnComboBoxAddItems(sortDialog, "primaryColumnCombo", 'A', 'Z');
        columnComboBoxAddItems(sortDialog, "secondaryColumnCombo", 'B', 'Y');
        columnComboBoxAddItems(sortDialog, "tertiaryColumnCombo", 'C', 'X');

        sortDialog->show();
        return app.exec();
    }
    return 0;
}

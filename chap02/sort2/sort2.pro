QT       += core gui
QT       += uitools

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp

HEADERS +=

FORMS += \
    sortdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# 自定义两个变量：源路径和目标路径
SOURCE_PWD = $$PWD
OUTPUT_PWD = $$OUT_PWD
# 将路径中的正斜杠替换为反斜杠
SOURCE_PWD_WIN = $$replace(SOURCE_PWD, /, \\)
OUTPUT_PWD_WIN = $$replace(OUTPUT_PWD, /, \\)
QMAKE_POST_LINK = xcopy $$SOURCE_PWD_WIN\sortdialog.ui $$OUTPUT_PWD_WIN

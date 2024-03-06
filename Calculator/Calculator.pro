QT += core gui

greaterThan(QT_MAJOR_VERSION, 5):
QT += widgets

CONFIG += c++17

SOURCES += \
    main.cpp \
    calculator.cpp

HEADERS += \
    calculator.h

FORMS += \
    calculator.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

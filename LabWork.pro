QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Parser.cpp \
    colordelegate.cpp \
    comboboxdelegate.cpp \
    datamodel.cpp \
    errormodel.cpp \
    imp_out.cpp \
    main.cpp \
    mainwindow.cpp \
    manager.cpp \
    namingmodel.cpp \
    plots/plot2d.cpp \
    plots/plotChoice.cpp \
    plots/plotHist.cpp \
    plots/plotScatter.cpp \
    qcpdocumentobject.cpp \
    qcustomplot.cpp \
    variable_data.cpp \
    visualmodel.cpp

HEADERS += \
    Grammar.h \
    Parser.h \
    colordelegate.h \
    comboboxdelegate.h \
    datamodel.h \
    errormodel.h \
    imp_out.h \
    mainwindow.h \
    manager.h \
    namingmodel.h \
    plots/plot.h \
    plots/plot2d.h \
    plots/plotChoice.h \
    plots/plotHist.h \
    plots/plotScatter.h \
    qcpdocumentobject.h \
    qcustomplot.h \
    variable_data.h \
    visualmodel.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    LabWork.pro.user \
    README.md

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++20

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../build-lababand212-Desktop_x86_windows_msvc2022_pe_64bit-Debug/debug/moc_mainwindow.cpp \
    ../build-lababand212-Desktop_x86_windows_msvc2022_pe_64bit-Debug/debug/moc_plot.cpp \
    ../build-lababand212-Desktop_x86_windows_msvc2022_pe_64bit-Debug/debug/moc_plot2d.cpp \
    ../build-lababand212-Desktop_x86_windows_msvc2022_pe_64bit-Debug/debug/moc_plotChoice.cpp \
    ../build-lababand212-Desktop_x86_windows_msvc2022_pe_64bit-Debug/debug/moc_plotHist.cpp \
    ../build-lababand212-Desktop_x86_windows_msvc2022_pe_64bit-Debug/debug/moc_plotScatter.cpp \
    ../build-lababand212-Desktop_x86_windows_msvc2022_pe_64bit-Debug/debug/moc_qcpdocumentobject.cpp \
    ../build-lababand212-Desktop_x86_windows_msvc2022_pe_64bit-Debug/debug/moc_qcustomplot.cpp \
    colordelegate.cpp \
    comboboxdelegate.cpp \
    datamodel.cpp \
    errormodel.cpp \
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
    ../build-lababand212-Desktop_x86_windows_msvc2022_pe_64bit-Debug/debug/moc_predefs.h \
    colordelegate.h \
    comboboxdelegate.h \
    datamodel.h \
    errormodel.h \
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
    ../build-lababand212-Desktop_x86_windows_msvc2022_pe_64bit-Debug/debug/colordelegate.obj \
    ../build-lababand212-Desktop_x86_windows_msvc2022_pe_64bit-Debug/debug/comboboxdelegate.obj \
    ../build-lababand212-Desktop_x86_windows_msvc2022_pe_64bit-Debug/debug/datamodel.obj \
    ../build-lababand212-Desktop_x86_windows_msvc2022_pe_64bit-Debug/debug/errormodel.obj \
    ../build-lababand212-Desktop_x86_windows_msvc2022_pe_64bit-Debug/debug/lababand212.pdb \
    ../build-lababand212-Desktop_x86_windows_msvc2022_pe_64bit-Debug/debug/lababand212.vc.pdb \
    ../build-lababand212-Desktop_x86_windows_msvc2022_pe_64bit-Debug/debug/main.obj \
    ../build-lababand212-Desktop_x86_windows_msvc2022_pe_64bit-Debug/debug/mainwindow.obj \
    ../build-lababand212-Desktop_x86_windows_msvc2022_pe_64bit-Debug/debug/manager.obj \
    ../build-lababand212-Desktop_x86_windows_msvc2022_pe_64bit-Debug/debug/moc_mainwindow.obj \
    ../build-lababand212-Desktop_x86_windows_msvc2022_pe_64bit-Debug/debug/moc_plot.obj \
    ../build-lababand212-Desktop_x86_windows_msvc2022_pe_64bit-Debug/debug/moc_plot2d.obj \
    ../build-lababand212-Desktop_x86_windows_msvc2022_pe_64bit-Debug/debug/moc_plotChoice.obj \
    ../build-lababand212-Desktop_x86_windows_msvc2022_pe_64bit-Debug/debug/moc_plotHist.obj \
    ../build-lababand212-Desktop_x86_windows_msvc2022_pe_64bit-Debug/debug/moc_plotScatter.obj \
    ../build-lababand212-Desktop_x86_windows_msvc2022_pe_64bit-Debug/debug/moc_qcpdocumentobject.obj \
    ../build-lababand212-Desktop_x86_windows_msvc2022_pe_64bit-Debug/debug/moc_qcustomplot.obj \
    ../build-lababand212-Desktop_x86_windows_msvc2022_pe_64bit-Debug/debug/namingmodel.obj \
    ../build-lababand212-Desktop_x86_windows_msvc2022_pe_64bit-Debug/debug/plot2d.obj \
    ../build-lababand212-Desktop_x86_windows_msvc2022_pe_64bit-Debug/debug/plotChoice.obj \
    ../build-lababand212-Desktop_x86_windows_msvc2022_pe_64bit-Debug/debug/plotHist.obj \
    ../build-lababand212-Desktop_x86_windows_msvc2022_pe_64bit-Debug/debug/plotScatter.obj \
    ../build-lababand212-Desktop_x86_windows_msvc2022_pe_64bit-Debug/debug/qcpdocumentobject.obj \
    ../build-lababand212-Desktop_x86_windows_msvc2022_pe_64bit-Debug/debug/qcustomplot.obj \
    ../build-lababand212-Desktop_x86_windows_msvc2022_pe_64bit-Debug/debug/variable_data.obj \
    ../build-lababand212-Desktop_x86_windows_msvc2022_pe_64bit-Debug/debug/visualmodel.obj

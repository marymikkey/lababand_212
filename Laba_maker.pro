QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QMAKE_CXXFLAGS += -v
#INCLUDEPATH += C:/Boost_directory/include/boost-1_60/
#LIBS += "-LC:\QTlibraries\boost_1_60_0\stage\lib"
#LIBS += -lboost_system #-mgw63-mt-1_60

greaterThan(QT_MAJOR_VERSION, 4) {
    TARGET_ARCH=$${QT_ARCH}
} else {
    TARGET_ARCH=$${QMAKE_HOST.arch}
}

contains(TARGET_ARCH, x86_64) {
    ARCHITECTURE = x64
} else {
    ARCHITECTURE = x86
}

win32-g++:contains(ARCHITECTURE, x86): {
    INCLUDEPATH += C:/Boost_for_Qt/include/boost-1_66
    LIBS += "-LC:/Boost_for_Qt/lib" \
        -llibboost_locale-mgw112-mt-x64-1_66
}
win32-g++:contains(ARCHITECTURE, x64): {
    INCLUDEPATH +=C:/Boost_for_Qt/include/boost-1_66
    LIBS += "-LC:/Boost_for_Qt/lib" \
        -llibboost_locale-mgw112-mt-x64-1_66
}
win32-msvc*:contains(ARCHITECTURE, x86) {
    INCLUDEPATH += C:/Boost_for_Qt/include/boost-1_66
    LIBS += "-LC:/Boost_for_Qt/lib" \
        -llibboost_locale-mgw112-mt-x64-1_66
}
win32-msvc*:contains(ARCHITECTURE, x64) {
    INCLUDEPATH += C:/Boost_for_Qt/include/boost-1_66
    LIBS += "-LC:/Boost_for_Qt/lib" \
        -llibboost_locale-mgw112-mt-x64-1_66
}



SOURCES += \
    Manager.cpp \
    VariableData.cpp \
    VisualModel.cpp \
    colordelegate.cpp \
    comboboxdelegate.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp

HEADERS += \
    Manager.h \
    VariableData.h \
    VisualModel.h \
    colordelegate.h \
    comboboxdelegate.h \
    mainwindow.h \
    qcustomplot.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

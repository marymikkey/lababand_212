QT       += core gui printsupport

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
        -llibboost_locale-mgw112-mt-x64-1_66 \
        #-llibboost_atomic-mgw112-mt-x64-1_66 \
        #-llibboost_chrono-mgw112-mt-x64-1_66 \
        #-llibboost_container-mgw112-mt-x64-1_66 \
        #-llibboost_context-mgw112-mt-x64-1_66 \
        #-llibboost_coroutine-mgw112-mt-x64-1_66 \
        #-llibboost_exception-mgw112-mt-x64-1_66 \
        #-llibboost_filesystem-mgw112-mt-x64-1_66 \
        #-llibboost_graph-mgw112-mt-x64-1_66 \
        #-llibboost_log_setup-mgw112-mt-x64-1_66 \
        #-llibboost_log-mgw112-mt-x64-1_66 \
        #-llibboost_math_c99-mgw112-mt-x64-1_66 \
        #-llibboost_random-mgw112-mt-x64-1_66 \
        #-llibboost_regex-mgw112-mt-x64-1_66 \
        #-llibboost_signals-mgw112-mt-x64-1_66 \
        #-llibboost_serialization-mgw112-mt-x64-1_66 \
        #-llibboost_system-mgw112-mt-x64-1_66 \
        -llibboost_iostreams-mgw112-mt-x64-1_66 \
        -llibboost_type_erasure-mgw112-mt-x64-1_66
}
win32-g++:contains(ARCHITECTURE, x64): {
    INCLUDEPATH +=C:/Boost_for_Qt/include/boost-1_66
    LIBS += "-LC:/Boost_for_Qt/lib" \
        -llibboost_locale-mgw112-mt-x64-1_66 \
        #-llibboost_atomic-mgw112-mt-x64-1_66 \
        #-llibboost_chrono-mgw112-mt-x64-1_66 \
        #-llibboost_container-mgw112-mt-x64-1_66 \
        #-llibboost_context-mgw112-mt-x64-1_66 \
        #-llibboost_coroutine-mgw112-mt-x64-1_66 \
        #-llibboost_exception-mgw112-mt-x64-1_66 \
        #-llibboost_filesystem-mgw112-mt-x64-1_66 \
        #-llibboost_graph-mgw112-mt-x64-1_66 \
        #-llibboost_log_setup-mgw112-mt-x64-1_66 \
        #-llibboost_log-mgw112-mt-x64-1_66 \
        #-llibboost_math_c99-mgw112-mt-x64-1_66 \
        #-llibboost_random-mgw112-mt-x64-1_66 \
        #-llibboost_regex-mgw112-mt-x64-1_66 \
        #-llibboost_signals-mgw112-mt-x64-1_66 \
        #-llibboost_serialization-mgw112-mt-x64-1_66 \
        #-llibboost_system-mgw112-mt-x64-1_66 \
        -llibboost_iostreams-mgw112-mt-x64-1_66 \
        -llibboost_type_erasure-mgw112-mt-x64-1_66
}
win32-msvc*:contains(ARCHITECTURE, x86) {
    INCLUDEPATH += C:/Boost_for_Qt/include/boost-1_66
    LIBS += "-LC:/Boost_for_Qt/lib" \
        -llibboost_locale-mgw112-mt-x64-1_66 \
        #-llibboost_atomic-mgw112-mt-x64-1_66 \
        #-llibboost_chrono-mgw112-mt-x64-1_66 \
        #-llibboost_container-mgw112-mt-x64-1_66 \
        #-llibboost_context-mgw112-mt-x64-1_66 \
        #-llibboost_coroutine-mgw112-mt-x64-1_66 \
        #-llibboost_exception-mgw112-mt-x64-1_66 \
        #-llibboost_filesystem-mgw112-mt-x64-1_66 \
        #-llibboost_graph-mgw112-mt-x64-1_66 \
        #-llibboost_log_setup-mgw112-mt-x64-1_66 \
        #-llibboost_log-mgw112-mt-x64-1_66 \
        #-llibboost_math_c99-mgw112-mt-x64-1_66 \
        #-llibboost_random-mgw112-mt-x64-1_66 \
        #-llibboost_regex-mgw112-mt-x64-1_66 \
        #-llibboost_signals-mgw112-mt-x64-1_66 \
        #-llibboost_serialization-mgw112-mt-x64-1_66 \
        #-llibboost_system-mgw112-mt-x64-1_66 \
        -llibboost_iostreams-mgw112-mt-x64-1_66 \
        -llibboost_type_erasure-mgw112-mt-x64-1_66
}
win32-msvc*:contains(ARCHITECTURE, x64) {
    INCLUDEPATH += C:/Boost_for_Qt/include/boost-1_66
    LIBS += "-LC:/Boost_for_Qt/lib" \
        -llibboost_locale-mgw112-mt-x64-1_66 \
        #-llibboost_atomic-mgw112-mt-x64-1_66 \
        #-llibboost_chrono-mgw112-mt-x64-1_66 \
        #-llibboost_container-mgw112-mt-x64-1_66 \
        #-llibboost_context-mgw112-mt-x64-1_66 \
        #-llibboost_coroutine-mgw112-mt-x64-1_66 \
        #-llibboost_exception-mgw112-mt-x64-1_66 \
        #-llibboost_filesystem-mgw112-mt-x64-1_66 \
        #-llibboost_graph-mgw112-mt-x64-1_66 \
        #-llibboost_log_setup-mgw112-mt-x64-1_66 \
        #-llibboost_log-mgw112-mt-x64-1_66 \
        #-llibboost_math_c99-mgw112-mt-x64-1_66 \
        #-llibboost_random-mgw112-mt-x64-1_66 \
        #-llibboost_regex-mgw112-mt-x64-1_66 \
        #-llibboost_signals-mgw112-mt-x64-1_66 \
        #-llibboost_serialization-mgw112-mt-x64-1_66 \
        #-llibboost_system-mgw112-mt-x64-1_66 \
        -llibboost_iostreams-mgw112-mt-x64-1_66 \
        -llibboost_type_erasure-mgw112-mt-x64-1_66
}




























SOURCES += \
    Parser.cpp \
    main.cpp \
    mainwindow.cpp \
    manager.cpp \
    plots/plot_scatter.cpp \
    qcpdocumentobject.cpp \
    qcustomplot.cpp \
    variable_data.cpp

HEADERS += \
    Parser.h \
    mainwindow.h \
    manager.h \
    plots/plot.h \
    plots/plot_scatter.h \
    qcpdocumentobject.h \
    qcustomplot.h \
    variable_data.h

FORMS += \
    mainwindow.ui

QMAKE_CXXFLAGS += -Wa,-mbig-ob

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

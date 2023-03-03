TEMPLATE = lib
TARGET = CCQuick
QT += qml quick quick-private
CONFIG += plugin c++11

TARGET = $$qtLibraryTarget($$TARGET)
uri = quick.cc.qmlcomponents

include(private/private.pri)

# Input
SOURCES += \
        CCQuickFramelessWindow.cpp \
        CCQuick_plugin.cpp

HEADERS += \
        CCQuickFramelessWindow.h \
        CCQuick_plugin.h

DISTFILES = qmldir

DESTDIR = $${_PRO_FILE_PWD_}/../bin/plugins/$${replace(uri, \., /)}

!equals(_PRO_FILE_PWD_, $$DESTDIR) {
    copy_qmldir.target = $$DESTDIR/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) "$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)" "$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = qmldir
unix {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \., /)
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}

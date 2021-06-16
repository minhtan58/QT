QT += widgets qml quick
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += \
    $$PWD/app/engine \
    $$PWD/app/gui \
    $$PWD/app/element


HEADERS += \
    app/engine/FireDetection.h \
    app/gui/FireWindow.h \
    app/element/CommonImage.h

SOURCES += app/main.cpp \
    app/engine/FireDetection.cpp \
    app/gui/FireWindow.cpp \
    app/element/CommonImage.cpp

RESOURCES += resource/asset.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#opencv lib
INCLUDEPATH += C:/opencv310/install/include

#LIBS += \
#    C:/opencv310/install/x86/mingw/bin/libopencv_core310.dll \
#    C:/opencv310/install/x86/mingw/bin/libopencv_highgui310.dll \
#    C:/opencv310/install/x86/mingw/bin/libopencv_imgproc310.dll \
#    C:/opencv310/install/x86/mingw/bin/libopencv_imgcodecs310.dll \
#    C:/opencv310/install/x86/mingw/bin/libopencv_features2d310.dll \
#    C:/opencv310/install/x86/mingw/bin/libopencv_calib3d310.dll \
#    C:/opencv310/install/x86/mingw/bin/libopencv_video310.dll

LIBS += C:/opencv310/install/x86/mingw/bin/*.dll

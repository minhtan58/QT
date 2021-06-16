INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

QT += network

# Enable very detailed debug messages when compiling the debug version
CONFIG(debug, debug|release) {
    DEFINES += SUPERVERBOSE
}

HEADERS += \
#    $$PWD/ads1115.h \
#    $$PWD/bmp180.h \
#    $$PWD/drcNet.h \
#    $$PWD/drcSerial.h \
#    $$PWD/ds18b20.h \
#    $$PWD/htu21d.h \
#    $$PWD/max5322.h \
#    $$PWD/max31855.h \
#    $$PWD/mcp23s08.h \
#    $$PWD/mcp23s17.h \
#    $$PWD/mcp23x08.h \
#    $$PWD/mcp23x0817.h \
#    $$PWD/mcp3002.h \
#    $$PWD/mcp3004.h \
#    $$PWD/mcp3422.h \
#    $$PWD/mcp4802.h \
#    $$PWD/mcp23008.h \
#    $$PWD/mcp23016.h \
#    $$PWD/mcp23016reg.h \
#    $$PWD/mcp23017.h \
#    $$PWD/pcf8574.h \
    $$PWD/pcf8591.h \
#    $$PWD/pseudoPins.h \
#    $$PWD/rht03.h \
#    $$PWD/sn3218.h \
    $$PWD/softPwm.h \
#    $$PWD/softServo.h \
    $$PWD/softTone.h \
#    $$PWD/sr595.h \
    $$PWD/wiringPi.h \
    $$PWD/wiringPiI2C.h \
    $$PWD/wiringPiSPI.h \
    $$PWD/wiringSerial.h \
    $$PWD/wiringShift.h \
#    $$PWD/wpiExtensions.h

SOURCES += \
#    $$PWD/ads1115.c \
#    $$PWD/bmp180.c \
#    $$PWD/drcNet.c \
#    $$PWD/drcSerial.c \
#    $$PWD/ds18b20.c \
#    $$PWD/htu21d.c \
#    $$PWD/max5322.c \
#    $$PWD/max31855.c \
#    $$PWD/mcp23s08.c \
#    $$PWD/mcp23s17.c \
#    $$PWD/mcp3002.c \
#    $$PWD/mcp3004.c \
#    $$PWD/mcp3422.c \
#    $$PWD/mcp4802.c \
#    $$PWD/mcp23008.c \
#    $$PWD/mcp23016.c \
#    $$PWD/mcp23017.c \
#    $$PWD/pcf8574.c \
    $$PWD/pcf8591.c \
    $$PWD/piHiPri.c \
    $$PWD/piThread.c \
#    $$PWD/pseudoPins.c \
#    $$PWD/rht03.c \
#    $$PWD/sn3218.c \
    $$PWD/softPwm.c \
#    $$PWD/softServo.c \
    $$PWD/softTone.c \
#    $$PWD/sr595.c \
    $$PWD/wiringPi.c \
    $$PWD/wiringPiI2C.c \
    $$PWD/wiringPiSPI.c \
    $$PWD/wiringSerial.c \
    $$PWD/wiringShift.c \
#    $$PWD/wpiExtensions.c

DISTFILES += \
    $$PWD/wiringpi.pri

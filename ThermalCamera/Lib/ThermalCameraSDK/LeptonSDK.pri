INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

# Enable very detailed debug messages when compiling the debug version
CONFIG(debug, debug|release) {
    DEFINES += SUPERVERBOSE
}

HEADERS += \
    $$PWD/leptonSDKEmb32PUB/LEPTON_Macros.h \
    $$PWD/leptonSDKEmb32PUB/LEPTON_OEM.h \
    $$PWD/leptonSDKEmb32PUB/LEPTON_SDK.h \
    $$PWD/leptonSDKEmb32PUB/LEPTON_SDKConfig.h \
    $$PWD/leptonSDKEmb32PUB/LEPTON_SYS.h \
    $$PWD/leptonSDKEmb32PUB/LEPTON_Types.h \
    $$PWD/leptonSDKEmb32PUB/LEPTON_VID.h \
    $$PWD/leptonSDKEmb32PUB/LEPTON_AGC.h \
    $$PWD/leptonSDKEmb32PUB/LEPTON_ErrorCodes.h \
    $$PWD/leptonSDKEmb32PUB/LEPTON_I2C_Protocol.h \
    $$PWD/leptonSDKEmb32PUB/LEPTON_I2C_Reg.h \
    $$PWD/leptonSDKEmb32PUB/LEPTON_I2C_Service.h \
    $$PWD/leptonSDKEmb32PUB/raspi_I2C.h \
    $$PWD/leptonSDKEmb32PUB/crc16.h \
    $$PWD/sdk/Lepton_I2C.h \
    $$PWD/sdk/Palettes.h \
    $$PWD/sdk/SPI.h

SOURCES += \
    $$PWD/leptonSDKEmb32PUB/LEPTON_SDK.c \
    $$PWD/leptonSDKEmb32PUB/LEPTON_OEM.c \
    $$PWD/leptonSDKEmb32PUB/LEPTON_SYS.c \
    $$PWD/leptonSDKEmb32PUB/LEPTON_VID.c \
    $$PWD/leptonSDKEmb32PUB/LEPTON_AGC.c \
    $$PWD/leptonSDKEmb32PUB/LEPTON_I2C_Protocol.c \
    $$PWD/leptonSDKEmb32PUB/LEPTON_I2C_Service.c \
    $$PWD/leptonSDKEmb32PUB/raspi_I2C.c \
    $$PWD/leptonSDKEmb32PUB/crc16fast.c \
    $$PWD/sdk/Lepton_I2C.cpp \
    $$PWD/sdk/Palettes.cpp \
    $$PWD/sdk/SPI.cpp

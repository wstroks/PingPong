QT += core
QT -= gui

TARGET = untitled3
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
           Ball.cpp \
           Bat.cpp \
            gameSystem.cpp \
            OpencvProcessing.cpp

win32 {
    INCLUDEPATH += C:\opencv\build\include

    LIBS += -LC:\opencv\build\lib\
    -llibopencv_core320 \
    -llibopencv_highgui320 \
    -llibopencv_imgproc320 \
    -llibopencv_features2d320 \
    -llibopencv_calib3d320 \
    -llibopencv_ml320 \
    -llibopencv_features2d320 \
    -llibopencv_objdetect320\
    -llibopencv_videoio320\
    -llibopencv_imgcodecs320

}


unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += opencv

}

HEADERS += \
           Ball.h \
           Bat.h \
            gameSystem.h \
            OpencvProcessing.h

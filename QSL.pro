TEMPLATE = app
TARGET = testApp
QT += widgets

HEADERS += \
    qsl_global.h \
    qsl_vector.h \
    qsl_chart.h \
    qsl_scale.h \
    qsl_plot.h \
    qsl_rectscale.h \
    qsl_rectplot.h \
    qsl_xyplot.h \
    qsl_chartview.h \
    qsl_rectframe.h

SOURCES += \
    qsl_chart.cpp \
    qsl_scale.cpp \
    main.cpp \
    qsl_plot.cpp \
    qsl_rectscale.cpp \
    qsl_rectplot.cpp \
    qsl_xyplot.cpp \
    qsl_chartview.cpp \
    qsl_rectframe.cpp

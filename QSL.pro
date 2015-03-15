TEMPLATE = app
TARGET = qslTest
QT += widgets

HEADERS += \
    qsl_global.h \
    qsl_chart.h \
    qsl_scale.h \
    qsl_plotable.h \
    qsl_chartitem.h \
    qsl_rectscale.h \
    qsl_rectplotable.h \
    qsl_xyplot.h \
    qsl_vector.h

SOURCES += \
    qsl_chart.cpp \
    qsl_scale.cpp \
    qsl_plotable.cpp \
    qsl_chartitem.cpp \
    main.cpp \
    qsl_rectscale.cpp \
    qsl_rectplotable.cpp \
    qsl_xyplot.cpp

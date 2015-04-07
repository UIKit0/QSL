project(QSL)
cmake_minimum_required(VERSION 2.8.11)

add_definitions(-DQSL_BUILD)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

set(QSL_PUB_HDRS
    headers/QslWorldView
    headers/QslChartView
)

set(QSL_HDRS
    QSL/qsl_global.h
    QSL/qsl_vec.h
    QSL/qsl_vector.h
    QSL/qsl_rectscale.h
    QSL/qsl_scale.h
    QSL/qsl_worldview.h
    QSL/qsl_chart.h
    QSL/qsl_chartview.h
    QSL/qsl_plot.h
    QSL/qsl_rectplot.h
    QSL/qsl_xyaxis.h
    QSL/qsl_xyplot.h
    QSL/qsl_chartlegend.h
)

set(QSL_SRCS
    QSL/qsl_worldview.cpp
    QSL/qsl_chart.cpp
    QSL/qsl_chartview.cpp
    QSL/qsl_plot.cpp
    QSL/qsl_rectplot.cpp
    QSL/qsl_rectscale.cpp
    QSL/qsl_scale.cpp
    QSL/qsl_xyaxis.cpp
    QSL/qsl_xyplot.cpp
    QSL/qsl_chartlegend.cpp
)

add_library(QSL SHARED ${QSL_SRCS} ${QSL_MOC_SRCS})
target_link_libraries(QSL ${QT_LIBRARIES})

add_executable(qslTest test.cpp)
target_link_libraries(qslTest QSL)

install(TARGETS QSL DESTINATION /usr/lib)
install(FILES ${QSL_HDRS} DESTINATION /usr/include/QSL)
install(FILES ${QSL_PUB_HDRS} DESTINATION /usr/include/QSL)

project(Qsl)
cmake_minimum_required(VERSION 2.8)

add_definitions(-DQSL_BUILD)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

include_directories(
    ./Qsl
    ./headers
    ./build/
)

set(QSL_PUB_HDRS
    headers/QslVector
    headers/QslWorldView
    headers/QslChartView
    headers/QslChart
)

set(QSL_HDRS
    Qsl/qsl_global.h
    Qsl/qsl_vec.h
    Qsl/qsl_vector.h
    Qsl/qsl_rectscale.h
    Qsl/qsl_scale.h
    Qsl/qsl_worldview.h
    Qsl/qsl_chart.h
    Qsl/qsl_chartview.h
    Qsl/qsl_plot.h
    Qsl/qsl_rectplot.h
    Qsl/qsl_rectaxis.h
    Qsl/qsl_graphplot.h
    Qsl/qsl_chartlegend.h
    Qsl/qsl_rectlabel.h
)

set(QSL_SRCS
    Qsl/qsl_worldview.cpp
    Qsl/qsl_chart.cpp
    Qsl/qsl_chartview.cpp
    Qsl/qsl_plot.cpp
    Qsl/qsl_rectplot.cpp
    Qsl/qsl_rectscale.cpp
    Qsl/qsl_scale.cpp
    Qsl/qsl_rectaxis.cpp
    Qsl/qsl_graphplot.cpp
    Qsl/qsl_chartlegend.cpp
    Qsl/qsl_rectlabel.cpp
)

add_library(Qsl SHARED ${QSL_SRCS} ${QSL_MOC_SRCS})
target_link_libraries(Qsl ${QT_LIBRARIES})

add_executable(qslTest test.cpp)
target_link_libraries(qslTest Qsl)

install(TARGETS Qsl DESTINATION /usr/lib)
install(FILES ${QSL_HDRS} DESTINATION /usr/include/Qsl)
install(FILES ${QSL_PUB_HDRS} DESTINATION /usr/include/Qsl)

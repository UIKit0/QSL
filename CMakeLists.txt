project(QSL)
cmake_minimum_required(VERSION 2.6)

find_package(Qt4 REQUIRED)
add_definitions(${QT_DEFINITIONS})
add_definitions(-DQSL_BUILD)
include(${QT_USE_FILE})
include_directories(${CMAKE_SOURCE_DIR})

set(QSL_HDRS
    QSL/qsl_global.h
    QSL/qsl_vector.h
    QSL/qsl_rectscale.h
    QSL/qsl_scale.h
)

set(QSL_QOBJ_HDRS
    QSL/qsl_chart.h
    QSL/qsl_chartview.h
    QSL/qsl_plot.h
    QSL/qsl_rectplot.h
    QSL/qsl_xyaxis.h
    QSL/qsl_xyplot.h
)

set(QSL_SRCS
    QSL/qsl_chart.cpp
    QSL/qsl_chartview.cpp
    QSL/qsl_plot.cpp
    QSL/qsl_rectplot.cpp
    QSL/qsl_rectscale.cpp
    QSL/qsl_scale.cpp
    QSL/qsl_xyaxis.cpp
    QSL/qsl_xyplot.cpp
)

qt4_wrap_cpp(QSL_MOC_SRCS ${QSL_QOBJ_HDRS})

add_library(QSL SHARED ${QSL_SRCS} ${QSL_MOC_SRCS})
target_link_libraries(QSL ${QT_LIBRARIES})

add_executable(qslTest test.cpp)
target_link_libraries(qslTest QSL)

install(TARGETS QSL DESTINATION /usr/lib)
install(FILES ${QSL_HDRS} DESTINATION /usr/include/QSL)
install(FILES ${QSL_QOBJ_HDRS} DESTINATION /usr/include/QSL)

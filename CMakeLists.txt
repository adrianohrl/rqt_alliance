cmake_minimum_required(VERSION 2.8.3)
project(rqt_alliance)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  roslint
  rqt_gui
  rqt_gui_cpp
  std_msgs
)

find_package(alliance REQUIRED COMPONENTS
  alliance_msgs
  ruler
  ruler_msgs
)

find_package(rqt_multiplot REQUIRED)

if("${qt_gui_cpp_USE_QT_MAJOR_VERSION} " STREQUAL "5 ")
  find_package(Qt5Widgets REQUIRED)
else()
  find_package(Qt4 COMPONENTS QtCore QtGui REQUIRED)
  include(${QT_USE_FILE})
endif()

catkin_python_setup()

roslint_cpp()

catkin_package(
  INCLUDE_DIRS ${rqt_alliance_INCLUDE_DIRS}
  LIBRARIES
    ${PROJECT_NAME}
    alliance
    rqt_multiplot
  CATKIN_DEPENDS
    alliance
    alliance_msgs
    roscpp
    rqt_gui_cpp
    rqt_multiplot
    ruler
    ruler_msgs
    std_msgs
#  DEPENDS system_lib
)

set (rqt_alliance_SRCS
  src/rqt_alliance/alliance_plugin.cpp
)

set(rqt_alliance_HDRS
  include/rqt_alliance/alliance_plugin.h
)

set(rqt_alliance_UIS
  src/rqt_alliance/alliance_monitor_widget.ui
)

if("${qt_gui_cpp_USE_QT_MAJOR_VERSION} " STREQUAL "5 ")
  qt5_wrap_cpp(rqt_alliance_MOCS ${rqt_alliance_HDRS})
  qt5_wrap_ui(rqt_alliance_UIS_H ${rqt_alliance_UIS})
else()
  qt4_wrap_cpp(rqt_alliance_MOCS ${rqt_alliance_HDRS})
  qt4_wrap_ui(rqt_alliance_UIS_H ${rqt_alliance_UIS})
endif()

include_directories(
  include
  ${CMAKE_CURRENT_BINARY_DIR}/..
  ${alliance_INCLUDE_DIRS}
  ${catkin_INCLUDE_DIRS}
  ${rqt_multiplot_INCLUDE_DIRS}
)

add_library(${PROJECT_NAME}
  ${rqt_alliance_SRCS}
  ${rqt_alliance_MOCS}
  ${rqt_alliance_UIS_H}
)

add_dependencies(${PROJECT_NAME}
  ${alliance_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS}
  ${rqt_multiplot_EXPORTED_TARGETS}
)

target_link_libraries(${PROJECT_NAME}
  ${alliance_LIBRARIES}
  ${catkin_LIBRARIES}
  ${rqt_multiplot_LIBRARIES}
)

if("${qt_gui_cpp_USE_QT_MAJOR_VERSION} " STREQUAL "5 ")
  target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
else()
  target_link_libraries(${PROJECT_NAME} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
endif()

install(FILES plugin.xml
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

install(TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION})

install(PROGRAMS scripts/rqt_alliance
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)

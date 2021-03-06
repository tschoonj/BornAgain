############################################################################
# CMakeLists.txt file for building libBornAgainGUI library
############################################################################
if(POLICY CMP0020)
    cmake_policy(SET CMP0020 NEW)
endif()
if(POLICY CMP0043)
    cmake_policy(SET CMP0043 NEW)
endif()
if(POLICY CMP0042)
    cmake_policy(SET CMP0042 NEW)
endif()
if(POLICY CMP0028)
    cmake_policy(SET CMP0028 NEW)
endif()

set(library_name BornAgainGUI)

# --- source and include files ---
set(include_dirs
    ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow
    ${CMAKE_CURRENT_SOURCE_DIR}/utils
    ${CMAKE_CURRENT_SOURCE_DIR}/Models
    ${CMAKE_CURRENT_SOURCE_DIR}/Views
    ${CMAKE_CURRENT_SOURCE_DIR}/Views/SampleDesigner
    ${CMAKE_CURRENT_SOURCE_DIR}/Views/JobWidgets
    ${CMAKE_CURRENT_SOURCE_DIR}/Views/IntensityDataWidgets
    ${CMAKE_CURRENT_SOURCE_DIR}/Views/InfoWidgets
    ${CMAKE_CURRENT_SOURCE_DIR}/Views/MaterialEditor
    ${CMAKE_CURRENT_SOURCE_DIR}/Views/InstrumentWidgets
    ${CMAKE_CURRENT_SOURCE_DIR}/Views/SimulationWidgets
    ${CMAKE_CURRENT_SOURCE_DIR}/Views/FitWidgets
    ${CMAKE_CURRENT_SOURCE_DIR}/Views/PropertyEditor
    ${CMAKE_CURRENT_SOURCE_DIR}/Views/MaskWidgets
    ${CMAKE_CURRENT_SOURCE_DIR}/Views/AccordionWidget
    ${CMAKE_CURRENT_SOURCE_DIR}/Views/ImportDataWidgets
    ${CMAKE_CURRENT_SOURCE_DIR}/Views/CommonWidgets
)

if(BORNAGAIN_OPENGL)
    list(APPEND include_dirs ${CMAKE_CURRENT_SOURCE_DIR}/Views/RealSpaceWidgets)
endif()

set(source_files)
set(include_files)

foreach(dir ${include_dirs})
    file(GLOB source ${dir}/*.cpp)
    file(GLOB include ${dir}/*.h)
    list(APPEND source_files ${source})
    list(APPEND include_files ${include})
endforeach()

set(source_widgetbox
    "Views/widgetbox/widgetboxcategorylistview.cpp"
    "Views/widgetbox/widgetboxtreewidget.cpp"
    "Views/widgetbox/widgetbox.cpp"
    "Views/widgetbox/widgetbox_dnditem.cpp"
)
list(APPEND source_files ${source_widgetbox})

set(include_widgetbox
    "Views/widgetbox/widgetboxcategorylistview.h"
    "Views/widgetbox/widgetboxtreewidget.h"
    "Views/widgetbox/widgetbox.h"
    "Views/widgetbox/widgetbox_dnditem.h"
    "Views/widgetbox/widgetbox_global.h"
)
list(APPEND include_files ${include_widgetbox})

list(APPEND include_dirs ${CMAKE_CURRENT_SOURCE_DIR}/Views/widgetbox)
include_directories(${include_dirs})

set(resource_files
    "coregui.qrc"
    "Views/SampleDesigner/SampleDesigner.qrc"
    "Views/MaskWidgets/MaskWidgets.qrc"
    "Views/widgetbox/widgetbox.qrc"
    "Views/AccordionWidget/accordionwidgeticons.qrc"
)

# --- Qt configuration ---------
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
qt5_add_resources(RC_SRCS ${resource_files})

# --- definitions ------
if(BORNAGAIN_CRASHHANDLER)
    add_definitions(-DBORNAGAIN_CRASHHANDLER)
endif()

if(BORNAGAIN_TIFF_SUPPORT)
    add_definitions(-DBORNAGAIN_TIFF_SUPPORT)
endif()

if(WIN32)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBA_CORE_BUILD_DLL")
endif()


# --- making library ---------

add_library(
    ${library_name}
    SHARED
    ${source_files} ${RC_SRCS} ${include_files}
)
set_Target_properties(${library_name} PROPERTIES PREFIX ${libprefix} SUFFIX ${libsuffix})
set(${library_name}_LIBRARY_TYPE SHARED)
# exposing library name and list of include directories outside
set(${library_name}_INCLUDE_DIRS ${include_dirs} PARENT_SCOPE)
set(${library_name}_LIBRARY ${library_name} PARENT_SCOPE)


# --- dependencies ---------
include_directories(
    ${QtAddOn_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
    ${GSL_INCLUDE_DIR}
    ${BornAgainCore_INCLUDE_DIRS}
    ${BornAgainFit_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
    ${PYTHON_INCLUDE_DIRS}
    ${ba3d_INCLUDE_DIRS}
)

target_link_libraries(${library_name}
    ${QtAddOn_LIBRARIES}
    ${PYTHON_LIBRARIES}
    ${Boost_LIBRARIES}
    ${BornAgainFit_LIBRARY}
    ${BornAgainCore_LIBRARY}
    ${ba3d_LIBRARY}
)

target_link_libraries(${library_name}
    Qt5::Widgets
    Qt5::Core
    Qt5::Gui
    Qt5::Designer
    Qt5::PrintSupport
    Qt5::Network
)


# --- Installation ---------
install (TARGETS ${library_name} DESTINATION ${destination_lib} COMPONENT Libraries)

if(WIN32)
    # --- Qt ---
    STRING(REGEX REPLACE "\\\\" "/" QTDIR $ENV{QTDIR} ) # Convert C:\Qt\ to C:/Qt/
    install(FILES
    ${QTDIR}/bin/Qt5Widgets.DLL
    ${QTDIR}/bin/Qt5Core.dll
    ${QTDIR}/bin/Qt5Gui.dll
    ${QTDIR}/bin/Qt5Designer.dll
    ${QTDIR}/bin/Qt5Xml.dll
    ${QTDIR}/bin/Qt5Svg.dll
    ${QTDIR}/bin/Qt5Network.dll
    ${QTDIR}/bin/Qt5PrintSupport.dll
    DESTINATION ${destination_lib} COMPONENT Libraries)

    install(FILES
    ${QTDIR}/plugins/platforms/qwindows.dll
    DESTINATION bin/platforms COMPONENT Libraries)

    install(FILES
    ${QTDIR}/plugins/iconengines/qsvgicon.dll
    DESTINATION bin/iconengines COMPONENT Libraries)

    install(FILES
    ${QTDIR}/plugins/imageformats/qjpeg.dll
    DESTINATION bin/imageformats COMPONENT Libraries)

endif()

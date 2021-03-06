############################################################################
# CMakeLists.txt file for building libBornAgainCore library
############################################################################

set(library_name BornAgainTestMachinery)

if(POLICY CMP0042)
    cmake_policy(SET CMP0042 NEW)
endif()

# --- source and include files ---------
set(include_dirs
    ${EIGEN3_INCLUDE_DIR}
    ${Boost_INCLUDE_DIRS}
    ${GSL_INCLUDE_DIR}
    ${BornAgainCore_INCLUDE_DIRS}
    )

include_directories(${include_dirs})

file(GLOB source_files "*.cpp")
file(GLOB include_files "*.h")

if(WIN32)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBA_CORE_BUILD_DLL")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DPYTHON_EXECUTABLE=\\\"${PYTHON_EXECUTABLE}\\\"")

# --- making library ---------
add_library(
    ${library_name}
    SHARED
    ${source_files} ${include_files}
    )

set_Target_properties(${library_name} PROPERTIES PREFIX ${libprefix} SUFFIX ${libsuffix})
set(${library_name}_LIBRARY_TYPE SHARED)

# exposing library name and list of include directories outside
set(${library_name}_INCLUDE_DIRS ${include_dirs} PARENT_SCOPE)
set(${library_name}_LIBRARY ${library_name} PARENT_SCOPE)


# --- external dependencies ---------

target_link_libraries(${library_name}
    ${BornAgainCore_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT}
    ${YAMLCPP_LIBRARY}
    )

if(APPLE AND BORNAGAIN_APPLE_BUNDLE)
    set(link_flags "-Wl,-rpath,@loader_path/../../Frameworks")
    set_target_properties(${library_name} PROPERTIES LINK_FLAGS ${link_flags})
endif()

# --- installation ---------

#install (TARGETS ${library_name} DESTINATION ${destination_lib} COMPONENT Libraries)
#install (FILES ${include_files} DESTINATION ${destination_include} COMPONENT Headers)

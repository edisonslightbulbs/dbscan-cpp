project(2D-detect-tabletop-objects)

set(ROOT ${CMAKE_SOURCE_DIR})
set(SRC_DIR ${ROOT}/src)
set(LIB_DIR ${ROOT}/libs)
set(BUILD_DIR ${ROOT}/build)
set(EXT_DIR ${ROOT}/external)
set(INCLUDE_DIR ${ROOT}/include)

find_package(glog REQUIRED)
find_package(OpenCV REQUIRED)
find_package(gflags REQUIRED)
find_package(Pangolin REQUIRED)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

set(K4A_SDK ${EXT_DIR}/Azure-Kinect-Sensor-SDK)
set(K4A_LIBRARY ${K4A_SDK}/build)
set(K4A_INCLUDE ${K4A_SDK}/include)
set(K4A_VERSION ${K4A_SDK}/build/src/sdk/include)

set(CMAKE_PREFIX_PATH ${EXT_DIR}/libtorch)
set(CMAKE_CXX_FLAGS
    ${CMAKE_CXX_FLAGS}
    ${TORCH_CXX_FLAGS}
    )
find_package(Torch REQUIRED)

set (INCLUDE_DIRS "")
file(GLOB_RECURSE HEADERS
    ${LIB_DIR}/*.h
    ${EXT_DIR}/nanoflann/examples/*.h
    ${EXT_DIR}/nanoflann/include/*.hpp
    )
foreach (HEADER ${HEADERS})
    get_filename_component(DIR ${HEADER} PATH)
    list (APPEND INCLUDE_DIRS ${DIR})
endforeach()
list(REMOVE_DUPLICATES INCLUDE_DIRS)

file(GLOB_RECURSE LIBS_SRC
    ${LIB_DIR}/*.cpp
    )

option(BUILD_OBJECT_DETECTION_EXAMPLE "Build 2D-detect-tabletop-objects example" ON) # default OFF
if(BUILD_OBJECT_DETECTION_EXAMPLE)

    add_executable(2D-detect-tabletop-objects
        ${EXT_SRC}
        ${LIBS_SRC}
        main.cpp
        )

    target_include_directories(2D-detect-tabletop-objects PRIVATE
        ${K4A_VERSION}
        ${K4A_INCLUDE}
        ${INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS}
        )

    target_link_libraries(2D-detect-tabletop-objects
        glog
        gflags
        Eigen3::Eigen
        ${OpenCV_LIBS}
        ${Pangolin_LIBRARIES}
        ${K4A_LIBRARY}/bin/libk4a.so
        ${TORCH_LIBRARIES}
        )

    option(EXECUTE_TARGET "Execute 2D-detect-tabletop-objects example" ON) # default OFF
    if(EXECUTE_TARGET)
        add_custom_command(TARGET 2D-detect-tabletop-objects
            POST_BUILD
            COMMAND ./scripts/run_2D_detect_tabletop_objects_example.sh
            WORKING_DIRECTORY ${ROOT})
    endif()
endif()

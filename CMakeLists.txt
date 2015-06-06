# CMakeLists.txt has to be located in the project folder and cmake has to be
# executed from 'project/build' with 'cmake ../'.
cmake_minimum_required(VERSION 2.6)
find_package(Rock)

set(Python_ADDITIONAL_VERSIONS 2.7)
find_package(Boost COMPONENTS filesystem system date_time python REQUIRED)
message(STATUS "Include dirs of boost: " ${Boost_INCLUDE_DIRS} )
message(STATUS "Libs of boost: " ${Boost_LIBRARIES} )

find_package(PythonLibs REQUIRED)
message(STATUS "Include dirs of Python: " ${PYTHON_INCLUDE_PATH} )
message(STATUS "Libs of Python: " ${PYTHON_LIBRARIES} )

include_directories(${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_PATH})


rock_init(gp_odometry 0.1)
rock_standard_layout()

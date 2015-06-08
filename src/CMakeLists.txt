

rock_library(gp_odometry
    SOURCES Sklearn.cpp
    DEPS_PKGCONFIG python
    DEPS_CMAKE Boost
    HEADERS Sklearn.hpp)


#target_link_libraries(gp_odometry ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})

rock_executable(gp_odometry_test main.cpp
	DEPS gp_odometry)


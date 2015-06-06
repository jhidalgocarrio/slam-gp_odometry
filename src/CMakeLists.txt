
rock_library(gp_odometry
    SOURCES Sklearn.cpp
    HEADERS Sklearn.hpp)


target_link_libraries(gp_odometry ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})

rock_executable(gp_odometry_test main.cpp
	DEPS gp_odometry)




rock_library(gp_odometry
    SOURCES Sklearn.cpp
            Gpy.cpp
    DEPS_PKGCONFIG python
    DEPS_PLAIN
        Boost_SYSTEM
        Boost_FILESYSTEM
        Boost_DATE_TIME
        Boost_PYTHON
    HEADERS GPModel.hpp
            Sklearn.hpp
            Gpy.hpp)


#target_link_libraries(gp_odometry ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})

rock_executable(gp_odometry_test main.cpp
	DEPS gp_odometry)


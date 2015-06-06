rock_library(gp_odometry
    SOURCES Dummy.cpp
    HEADERS Dummy.hpp)

rock_executable(gp_odometry_bin Main.cpp
    DEPS gp_odometry)


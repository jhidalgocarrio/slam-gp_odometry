#include <boost/test/unit_test.hpp>
#include <gp_odometry/Sklearn.hpp>

using namespace gp_odometry;

BOOST_AUTO_TEST_CASE(it_should_not_crash_when_welcome_is_called)
{
    gp_odometry::Sklearn gp_odo;
    gp_odo.welcome();
    gp_odo.init("./data/gp_sklearn.out");
}

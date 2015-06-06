#include <boost/test/unit_test.hpp>
#include <gp_odometry/Dummy.hpp>

using namespace gp_odometry;

BOOST_AUTO_TEST_CASE(it_should_not_crash_when_welcome_is_called)
{
    gp_odometry::DummyClass dummy;
    dummy.welcome();
}

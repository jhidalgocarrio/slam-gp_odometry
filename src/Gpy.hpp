#ifndef _GP_ODOMETRY_GPY_HPP_
#define _GP_ODOMETRY_GPY_HPP_

#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <python2.7/Python.h>
#include <boost/python.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/python/extract.hpp>
#include <boost/python/numeric.hpp>

namespace gp_odometry
{
    class Gpy
    {
        protected:
             boost::python::object main_namespace;

        public:

            /**
             */
            void init(const std::string &file_to_load, const std::string &object_name);

            /**
             */
            void print(const std::string &object_name);

            /**@brief Get Kernel parameters names
             *
             */
            std::vector<std::string> parameterNames(const std::string &object_name);

            /**
             */
            std::vector<double> predict(const std::string &object_name, const std::vector<double> &new_input, std::vector<double> &prediction_var);
    };
} // end namespace gp_odometry

#endif

#ifndef _GP_ODOMETRY_GPMODEL_HPP_
#define _GP_ODOMETRY_GPMODEL_HPP_

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

    class GPModel
    {
    protected:
        boost::python::object main_namespace;

    public:
        virtual ~GPModel() {  };

        virtual void init(const std::string &file_to_load, const std::string &object_name) = 0;

        virtual std::vector<double> predict(const std::string &object_name, const std::vector<double> &new_input, std::vector<double> &prediction_var) = 0;
    };
}

#endif

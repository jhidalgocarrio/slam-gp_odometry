#ifndef _GP_ODOMETRY_SKLEARN_HPP_
#define _GP_ODOMETRY_SKLEARN_HPP_

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <python2.7/Python.h>
#include <boost/python.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/python/extract.hpp>
#include <boost/python/numeric.hpp>

namespace gp_odometry
{
	class Sklearn
	{
        protected:
             boost::python::object main_namespace;

		public:

            /**
             */
            void init(const std::string &file_to_load);

            /**
             */
            void getParams();

            /**
             */
            std::vector<double> kernel_();

            /**
             */
            std::vector<double> predict(const std::vector<double> &new_input);


			/**
			* Print a welcome to stdout
			* \return nothing
			*/
			void welcome();
	};

} // end namespace gp_odometry

#endif

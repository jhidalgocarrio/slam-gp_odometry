#ifndef _GP_ODOMETRY_GPY_HPP_
#define _GP_ODOMETRY_GPY_HPP_

#include <gp_odometry/GPModel.hpp>

namespace gp_odometry
{
    class Gpy: public GPModel
    {
        protected:
             boost::python::object main_namespace;

        public:

            ~Gpy() {};

            /**
             */
            void init(const std::string &path_to_init);

            /**
             */
            void load(const std::string &file_to_load, const std::string &object_name);

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

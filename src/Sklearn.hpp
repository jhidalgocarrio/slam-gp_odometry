#ifndef _GP_ODOMETRY_SKLEARN_HPP_
#define _GP_ODOMETRY_SKLEARN_HPP_

#include <gp_odometry/GPModel.hpp>

namespace gp_odometry
{
    class Sklearn: public GPModel
    {
    public:

        ~Sklearn(){};

        /**
         */
        void init(const std::string &file_to_load, const std::string &object_name);

        /**
         */
        void getParams(const std::string &object_name);

        /**@brief Get Kernel parameters
         *
         * When using the DFKI gp module
         *
         */
        std::vector<double> kernel_(const std::string &object_name);

        /**@brief Get Kernel parameters
         *
         * When using the Sklearn alone
         *
         */
        std::vector<double> theta_(const std::string &object_name);


        /**
         */
        std::vector<double> predict(const std::string &object_name, const std::vector<double> &new_input, std::vector<double> &prediction_var);


        /**
        * Print a welcome to stdout
        * \return nothing
        */
        void welcome();
    };

} // end namespace gp_odometry

#endif

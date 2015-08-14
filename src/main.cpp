#include <gp_odometry/Sklearn.hpp>

int main()
{
    gp_odometry::Sklearn gp;

    gp.init("./data/gp_sklearn_x_delta_pose.data");
    gp.getParams();
    //std::vector<double> kernel_params = gp.kernel_();
    //std::cout<<"Kernel parameters: ";
    //for (std::vector<double>::const_iterator i = kernel_params.begin(); i != kernel_params.end(); ++i)
    //{
    //    std::cout << *i << ' ';
    //}
    //std::cout<<"\n";

     static const double arr[] = {9.93707217e-03,   1.01112053e-02,   9.95999202e-03,
                         1.01173632e-02,   9.95666254e-03,   1.00015244e-02,
                        -1.29177342e-05,  -7.75063527e-05,  -3.55237920e-04,
                         4.52120694e-05,  -1.22847661e-04,  -5.16709370e-05,
                        -2.04100197e-05,  -4.28868589e-05,  -7.63954769e-04,
                        -2.97462996e-02,   1.04754493e-01,  -7.75860772e-02,
                         5.71624078e-02,  -2.03379073e-03,   4.21097697e-04,
                        -1.73008403e-03,  -1.05434945e-01,  -2.72711140e-01};

    std::vector<double> input_vector(arr, arr + sizeof(arr) / sizeof(arr[0]));

    double output_var = 0.00;
    double output = gp.predict(input_vector, output_var);
    std::cout<<"Predict: "<<output<<" +-"<<output_var<<"\n";
}


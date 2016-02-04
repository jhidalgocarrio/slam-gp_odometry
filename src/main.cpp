#include <gp_odometry/Sklearn.hpp>

int main()
{
    gp_odometry::Sklearn gp;

    gp.init("./data/gp_sklearn_x_delta_pose.data", "gp_x");
    gp.getParams("gp_x");
    std::vector<double> kernel_params = gp.theta_("gp_x");
    std::cout<<"Kernel parameters: ";
    for (std::vector<double>::const_iterator i = kernel_params.begin(); i != kernel_params.end(); ++i)
    {
        std::cout << *i << ' ';
    }
    std::cout<<"\n";

    static const double arr[] = {3.54864560e-02,   3.48025449e-02,   3.48598845e-02,
         3.42543200e-02,   3.43560986e-02,   3.38060819e-02,
        -8.38438328e-03,  -1.46967657e-02,   8.38503335e-03,
         1.47102010e-02,   0.00000000e+00,   0.00000000e+00,
         0.00000000e+00,   5.16709349e-07,   0.00000000e+00,
        -1.16259562e-05,   1.00195929e-02,   3.70861366e-02,
        -7.05398992e-02,   1.56287136e-03,   1.10743524e-02,
        -4.02362763e-03,   7.95247861e-02,   3.11162212e-02};

    std::vector<double> input_vector(arr, arr + sizeof(arr) / sizeof(arr[0]));

    std::cout<<"Input vector: ";
    for (std::vector<double>::const_iterator i = input_vector.begin(); i != input_vector.end(); ++i)
    {
        std::cout << *i << ' ';
    }
    std::cout<<"\n";

    double output_var = 0.00;
    double output = gp.predict("gp_x", input_vector, output_var);
    std::cout<<"Predict: "<<output<<" +-"<<output_var<<"\n";
}


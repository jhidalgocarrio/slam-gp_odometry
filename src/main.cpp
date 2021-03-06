#include <gp_odometry/Sklearn.hpp>
#include <gp_odometry/Gpy.hpp>

int main()
{
    /** Gaussian Process with Sklearn **/
    gp_odometry::Sklearn gp_sklearn;

    std::cout<<"################# SKLEARN ######################\n";
    gp_sklearn.init("./scripts");
    gp_sklearn.load("./data/gp_sklearn_x_delta_pose.data", "gp_x");
    gp_sklearn.getParams("gp_x");
    std::vector<double> kernel_params = gp_sklearn.theta_("gp_x");
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

    std::cout<<"Input vector["<<input_vector.size()<<"]: ";
    for (std::vector<double>::const_iterator i = input_vector.begin(); i != input_vector.end(); ++i)
    {
        std::cout << *i << ' ';
    }
    std::cout<<"\n";

    std::vector<double> output_var(1);
    std::vector<double> output = gp_sklearn.predict("gp_x", input_vector, output_var);
    std::cout<<"Predict: "<<output[0]<<" +-"<<output_var[0]<<"\n";

    /** Gaussian Process with GPy **/
    gp_odometry::Gpy gp_gpy;
    std::cout<<"\n################# GPy ######################\n";

    gp_gpy.init("./scripts");
    gp_gpy.load("./data/SparseGP_RBF_NL_xyz_velocities_train_at_1s_normalized.data", "m");
    gp_gpy.print("m.model");

    std::vector<std::string> param_names = gp_gpy.parameterNames("m");
    std::cout<<"Param names["<<param_names.size()<<"]: ";
    for (std::vector<std::string>::const_iterator it = param_names.begin(); it != param_names.end(); ++it)
    {
        std::cout<<*it<<' ';
    }
    std::cout<<"\n";

    if (gp_gpy.isNormalized("m"))
        std::cout<<"m.model is normalized!\n";
    else
        std::cout<<"m.model is unnormalized!\n";

    static const double arr_gpy[] = {
        1.76003e-05, 2.44038e-05, -0.000522802, 3.44524e-05,
        0.000168296, 0, 0, 0, 0, -0.00366936, -0.000348695, 0.00102758,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -0.00990667, 0.025905, -0.01899,
        7.72695e-05, 9.96615e-05, -1.74269e-05};


       // {3.54864560e-02,   3.48025449e-02,   3.48598845e-02,
       //  3.42543200e-02,   3.43560986e-02,   3.38060819e-02,
       // -8.38438328e-03,  -1.46967657e-02,   8.38503335e-03,
       //  1.47102010e-02,   0.00000000e+00,   0.00000000e+00,
       //  0.00000000e+00,   5.16709349e-07,   0.00000000e+00,
       // -1.16259562e-05,   1.00195929e-02,   3.70861366e-02,
       // -1.16259562e-05,   1.00195929e-02,   3.70861366e-02,
       // -7.05398992e-02,   1.56287136e-03,   1.10743524e-02,
       // -4.02362763e-03,   7.95247861e-02,   3.11162212e-02, 3.11162212e-02};

    std::vector<double> input_vector_gpy(arr_gpy, arr_gpy + sizeof(arr_gpy) / sizeof(arr_gpy[0]));

    std::cout<<"Input vector["<<input_vector_gpy.size()<<"]: ";
    for (std::vector<double>::const_iterator i = input_vector_gpy.begin(); i != input_vector_gpy.end(); ++i)
    {
        std::cout << *i << ' ';
    }
    std::cout<<"\n";

    std::vector<double> pred_var(1);

    for (register int i = 0; i<3; ++i)
    {
        std::cout<<"["<<i<<"]\n";
        std::vector<double> pred_mean = gp_gpy.predict("m", input_vector_gpy, pred_var);

        std::cout<<"Predict["<<pred_mean.size()<<"]: ";
        for (std::vector<double>::const_iterator it = pred_mean.begin(); it != pred_mean.end(); ++it)
        {
            std::cout << *it << ' ';
        }
        std::cout<<"\n";
        std::cout<<"Predict var: "<<pred_var[0]<<"\n";
    }
}


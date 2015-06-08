#include <gp_odometry/Sklearn.hpp>

int main()
{
    gp_odometry::Sklearn gp;

    gp.init("./data/gp_sklearn_x_axis.data");
    gp.getParams();
    std::vector<double> kernel_params = gp.kernel_();
    std::cout<<"Kernel parameters: ";
    for (std::vector<double>::const_iterator i = kernel_params.begin(); i != kernel_params.end(); ++i)
    {
        std::cout << *i << ' ';
    }
    std::cout<<"\n";

    static const double arr[] = {7.01420605e-02,   6.99417815e-02,   6.95102736e-02,
                         7.01882914e-02,   7.01712891e-02,   6.98699653e-02,
                         2.91940616e-03,   2.90003303e-03,  -2.91940616e-03,
                        -2.90003303e-03,   0.00000000e+00,   0.00000000e+00,
                         0.00000000e+00,   0.00000000e+00,   0.00000000e+00,
                         1.29177342e-05,   1.56891756e-02,  -2.69636717e-02,
                         2.85652373e-02,  -7.36935056e-04,  -5.79455977e-03,
                        -6.13527879e-04,   4.31049256e-02,   2.56755739e-02};

    std::vector<double> input_vector(arr, arr + sizeof(arr) / sizeof(arr[0]));

    double output = gp.predict(input_vector);
    std::cout<<"Predict: "<<output<<"\n";
}


#include "Sklearn.hpp"

namespace gp_odometry
{
    void Sklearn::init(const std::string &path_to_init)
    {
        Py_Initialize();
        this->main_namespace = boost::python::import("__main__").attr("__dict__");

        std::string expression;
        expression = "import numpy as np\nfrom pylab import *\nimport pickle\n";
        expression += "from sklearn.gaussian_process import GaussianProcessRegressor\n";
        expression += "from sklearn.gaussian_process.kernels import RBF, WhiteKernel\n";
        expression += "def save_object(obj, filename):\n";
        expression += "\twith open(filename, 'wb') as output:\n";
        expression += "\t\tpickle.dump(obj, output, pickle.HIGHEST_PROTOCOL)\n";
        expression += "def open_object(filename):\n";
        expression += "\twith open(filename, 'rb') as input:\n";
        expression += "\t\treturn pickle.load(input)\n";
        boost::python::str str_expression(expression);

        try
        {
            boost::python::object ignored = boost::python::exec(str_expression, this->main_namespace);
        }
        catch(boost::python::error_already_set &)
        {
            PyObject *ptype, *pvalue, *ptraceback;
            PyErr_Fetch(&ptype, &pvalue, &ptraceback);

            boost::python::handle<> hType(ptype);
            boost::python::object extype(hType);
            boost::python::handle<> hTraceback(ptraceback);
            boost::python::object traceback(hTraceback);

            //Extract error message
            std::string strErrorMessage = boost::python::extract<std::string>(pvalue);
            std::cout<<strErrorMessage<<"\n";
        }

        return;
    }

    void Sklearn::load(const std::string &file_to_load, const std::string &object_name)
    {

        std::string expression;
        expression = object_name + " = open_object('";
        expression += file_to_load;
        expression += "')\n";
        boost::python::str str_expression(expression);

        try
        {
            boost::python::object ignored = boost::python::exec(str_expression, this->main_namespace);
        }
        catch(boost::python::error_already_set &)
        {
            PyObject *ptype, *pvalue, *ptraceback;
            PyErr_Fetch(&ptype, &pvalue, &ptraceback);

            boost::python::handle<> hType(ptype);
            boost::python::object extype(hType);
            boost::python::handle<> hTraceback(ptraceback);
            boost::python::object traceback(hTraceback);

            //Extract error message
            std::string strErrorMessage = boost::python::extract<std::string>(pvalue);
            std::cout<<strErrorMessage<<"\n";
        }

        return;
    }

    void Sklearn::getParams(const std::string &object_name)
    {
        std::string expression;
        expression = "print "+object_name+".get_params\n";
        boost::python::str str_expression(expression);
        boost::python::object ignored = boost::python::exec(str_expression, this->main_namespace);
    }

    std::vector<double> Sklearn::kernel_(const std::string &object_name)
    {
        std::string expression;
        expression = "out = "+object_name+".kernel_.theta\n";
        boost::python::str str_expression(expression);
        boost::python::object ignored = boost::python::exec(str_expression, this->main_namespace);
        boost::python::object out = this->main_namespace["out"];
        std::vector<double> vector_out(3);
        for (register int i = 0; i<3; ++i)
        {
            vector_out[i] = boost::python::extract<double>(out[i]);

        }
        std::string object_classname = boost::python::extract<std::string>(out.attr("__class__").attr("__name__"));
        //std::cout<<"this is an Object: "<<object_classname<<std::endl;
        //boost::python::numeric::array a = boost::python::extract<boost::python::numeric::array>(out);


        return vector_out;
    }

     std::vector<double> Sklearn::theta_(const std::string &object_name)
    {
        std::string expression;
        expression = "parameters = "+object_name+".theta_\n";
        boost::python::str str_expression(expression);
        boost::python::object ignored = boost::python::exec(str_expression, this->main_namespace);
        boost::python::object out = this->main_namespace["parameters"];
        std::vector<double> vector_out(1);
        vector_out[0] = boost::python::extract< double >(out[0][0]);
        return vector_out;
    }


    std::vector<double> Sklearn::predict(const std::string &object_name, const std::vector<double> &new_input, std::vector<double> &prediction_var)
    {
        std::string expression;
        expression = "Xp = np.array([";
        for (std::vector<double>::const_iterator i = new_input.begin(); i != new_input.end(); ++i)
        {
            expression += boost::lexical_cast<std::string>(*i)+", ";
        }
        expression += "])\n";
        expression += "mean_out, var_out = "+object_name+".predict(Xp, eval_MSE=True)\n";
        boost::python::str str_expression(expression);
        boost::python::object ignored = boost::python::exec(str_expression, this->main_namespace);
        boost::python::object mean_out = this->main_namespace["mean_out"];
        boost::python::object var_out = this->main_namespace["var_out"];
        std::vector<double> prediction(1);
        prediction[0] = boost::python::extract<double>(mean_out[0]);
        prediction_var[0] = boost::python::extract<double>(var_out[0]);

        return prediction;
    }


    void Sklearn::welcome()
    {
        std::cout << "You successfully compiled and executed Sklearn C++ interface. Welcome!" << std::endl;
    }
}

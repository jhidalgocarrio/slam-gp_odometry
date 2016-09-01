#include "Gpy.hpp"

using namespace gp_odometry;

void Gpy::init(const std::string &path_to_init)
{
    Py_Initialize();

    this->main_namespace = boost::python::import("__main__").attr("__dict__");
    std::string expression;
    expression = "import numpy as np\nfrom pylab import *\nimport pickle\n";
    expression += "import abc\nimport GPy\nimport sys\n";
    expression += "sys.path.insert(0,'";
    expression += path_to_init;
    expression += "')\n";
    expression += "from methods import GP_RBF, SVIGP_RBF, SparseGP_RBF, SparseGP_RBF_NL, GP_MAT32, SparseGP_MAT32, GP_MAT52, SparseGP_MAT52\n";
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

void Gpy::load(const std::string &file_to_load, const std::string &object_name)
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

void Gpy::print(const std::string &object_name)
{
    std::string expression;
    expression = "print "+object_name+"\n";
    boost::python::str str_expression(expression);
    boost::python::object ignored = boost::python::exec(str_expression, this->main_namespace);
}

std::vector<std::string> Gpy::parameterNames(const std::string &object_name)
{
    std::string expression;
    expression = "param_out = "+object_name+".parameter_names()\n";
    boost::python::str gpy_str_expression(expression);
    boost::python::object gpy_ignored = boost::python::exec(gpy_str_expression, this->main_namespace);
    boost::python::object param_out = this->main_namespace["param_out"];
    std::vector<std::string> vector_out(5);
    for (register size_t i = 0; i<vector_out.size(); ++i)
    {
        vector_out[i] = boost::python::extract<std::string>(param_out[i]);
    }

    return vector_out;
}

std::vector<double> Gpy::predict(const std::string &object_name, const std::vector<double> &new_input, std::vector<double> &prediction_var)
{
    std::string expression;
    expression = "Xp = np.array([";
    for (std::vector<double>::const_iterator i = new_input.begin(); i != new_input.end(); ++i)
    {
        expression += boost::lexical_cast<std::string>(*i)+", ";
    }
    expression += "])\n";
    expression += "Xp = np.column_stack(Xp)\n";
    expression += "[pred_mean, pred_var] = "+object_name+".predict(Xp)\n";
    boost::python::str str_expression(expression);
    boost::python::object ignored = boost::python::exec(str_expression, this->main_namespace);
    boost::python::object pred_mean = this->main_namespace["pred_mean"];
    boost::python::object pred_var = this->main_namespace["pred_var"];

    /** Get the results **/
    std::vector<double> prediction(3);
    for (register size_t i = 0; i<prediction.size(); ++i)
    {
        prediction[i] = boost::python::extract<double>(pred_mean[0][i]);
    }

    prediction_var[0] = boost::python::extract<double>(pred_var[0][0]);

    return prediction;
}


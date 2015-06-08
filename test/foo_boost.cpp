#include <python2.7/Python.h>
#include <boost/python.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <stdlib.h>
#include <assert.h>

//compile with: g++ foo_boost.cpp -I /usr/include/python2.7/ -lpython2.7  -lboost_python -lboost_system


int main()
{
    Py_Initialize();

    boost::python::object main_namespace = boost::python::import("__main__").attr("__dict__");
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
    expression += "gp = open_object('./gp_sklearn.out')\n";
    expression += "print gp.kernel_\n";
    boost::python::str str_expression(expression);

    try
    {
        boost::python::object ignored = boost::python::exec(str_expression, main_namespace);
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

        //Extract line number (top entry of call stack)
        // if you want to extract another levels of call stack
        // also process traceback.attr("tb_next") recurently
        //long lineno = boost::python::extract<long> (traceback.attr("tb_lineno"));
        //std::string filename = boost::python::extract<std::string>(traceback.attr("tb_frame").attr("f_code").attr("co_filename"));
        //std::string funcname = boost::python::extract<std::string>(traceback.attr("tb_frame").attr("f_code").attr("co_name"));
    }

    //std::string result = boost::python::extract<std::string>(main_namespace["result"]);
    //std::cout<<"result is: "<<result<<"\n";

    //boost::python::str numpy_expression(expression);
    //boost::python::object numpy_ignored = boost::python::exec(numpy_expression, numpy_namespace);
}

#include <python2.7/Python.h>
#include <iostream>
#include <stdlib.h>
#include <assert.h>

//compile with: g++ foo.cpp -lpython2.7

int main()
{
    PyObject *name, *module, *kernels, *gp, *rbf, *white, *kernel;
    PyObject *pArgs, *pArgs2, *pValue;

    Py_Initialize();

    PyRun_SimpleString("from time import time,ctime\n"
                     "print 'Today is',ctime(time())\n");

    name = PyString_FromString("sklearn.gaussian_process");
    module = PyImport_Import(name);
    Py_DECREF(name);

    name = PyString_FromString("sklearn.gaussian_process.kernels");
    kernels = PyImport_Import(name);
    Py_DECREF(name);

    if (module != NULL)
    {
        gp = PyObject_GetAttrString(module, "GaussianProcessRegressor");
        rbf = PyObject_GetAttrString(kernels, "RBF");
        white = PyObject_GetAttrString(kernels, "WhiteKernel");

        pArgs = PyTuple_New(1);
        pValue = PyInt_FromLong(1);
        PyTuple_SetItem(pArgs, 0, pValue);

        rbf = PyObject_CallObject(rbf, pArgs);

        pArgs2 = PyTuple_New(3);
        pValue = PyFloat_FromDouble(1e-06);
        PyTuple_SetItem(pArgs2, 0, pValue);

        pValue = PyFloat_FromDouble(1e-10);
        PyTuple_SetItem(pArgs2, 1, pValue);

        pValue = PyFloat_FromDouble(1e-1);
        PyTuple_SetItem(pArgs2, 2, pValue);

        white = PyObject_CallObject(white, pArgs);

        PyObject *kernels = PyTuple_New(1);
        PyTuple_SetItem(kernels, 0, white);

        gp = PyObject_CallObject(gp, kernels);
        if (gp == NULL)
        {
            std::cout<<"Call failed\n";
        }

        PyObject *fit =  PyObject_GetAttrString(gp, "fit");
        if (fit == NULL)
        {
            std::cout<<"Method failed\n";
        }

        pArgs2 = PyTuple_New(3);



        PyObject *predict =  PyObject_GetAttrString(gp, "predict");
        if (predict == NULL)
        {
            std::cout<<"Method failed\n";
        }


    }
    else
    {
        PyErr_Print();
        std::cout<<"stderr Failed to load \n";
        return 1;
    }


    Py_Finalize();

    return 0;
}

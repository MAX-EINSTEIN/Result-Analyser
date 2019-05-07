#include "pythread.h"
#include "Utils/pyhelper.hpp"
#include <iostream>

PyThread::PyThread()
{

}

void PyThread::run(){
    py::CPyObject _module;
    py::CPyObject _class;
    py::CPyObject _method;
    py::CPyObject _args;
    py::CPyObject _inst;
    py::CPyObject _result;

    py::CPyInstance initializer;

    _module = PyImport_ImportModule("xlanalyser");
    _class = PyObject_GetAttrString(_module,"XlAnalyser");
    _args = Py_BuildValue("(ss)","sample.xls","E:/Computer Science/Python/Programs/Resources");
    std::cout << "In Init_Class  k" << std::endl;
    _inst = PyObject_CallObject(_class,_args);
    _method = PyObject_GetAttrString(_inst,"print_sheet");
    _args = Py_BuildValue("()");
    PyEval_CallObject(_method,_args);
}



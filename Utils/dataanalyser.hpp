#ifndef DATAANALYSER_HPP
#define DATAANALYSER_HPP
#include <list>
#include <string>
#include <cstdarg>
#include <iostream>
#include "pyhelper.hpp"



class DataAnalyser{
private:
    py::CPyObject _module;
    py::CPyObject _class;
    py::CPyObject _method;
    py::CPyObject _args;
    py::CPyObject _inst;
    py::CPyObject _result;

    bool InitModule(std::string module_name){
        _module = PyImport_ImportModule(module_name.c_str());
        if(!_module)
            return false;
        return true;
    }

    bool InitClass(std::string class_name,std::string filename, std::string filepath){
        _class = PyObject_GetAttrString(_module,class_name.c_str());
        _args = Py_BuildValue("(ss)",filename.c_str(),filepath.c_str());
        std::cout << "In Init_Class  k" << std::endl;
        _inst = PyObject_CallObject(_class,_args);
        std::cout << "In Init_Class" << std::endl;
        if(!_inst)
            return false;
        return true;
    }

public:

    DataAnalyser(){
        py::CPyInstance initializer;
        if(!InitModule("xlanalyser")){
            std::cout << "Module Import Error!" << std::endl;
        }
    }


    bool Select_File(std::string file, std::string path){
        if(!InitClass("XlAnalyser",file.c_str(),path.c_str()))
            return false;
        std::cout << "In Select_File" << std::endl;
        return true;
    }

    void Print_Sheet(){
        _method = PyObject_GetAttrString(_inst,"print_sheet");
        _args = Py_BuildValue("()");
        PyEval_CallObject(_method,_args);
    }


};

































//#include "3rdparty/pybind11/embed.h"

//namespace py = pybind11;
//typedef std::list<std::list<std::string> > SheetData;

//class DataAnalyser
//{
//private:
//    py::module _module;
//    py::object _tool;

//public:
//    DataAnalyser()
//    {
//        _module = py::module::import("xlanalyser");
//    }

//    void Print_Sheet(std::string filename,std::string filepath)
//    {
//        _tool = _module.attr("XlAnalyser")(filename.c_str(),filepath.c_str());
//        _tool.attr("print_sheet")();
//    }

//    SheetData Return_Sheet(std::string filename,std::string filepath)
//    {
//        SheetData data;
//        _tool = _module.attr("XlAnalyser")(filename.c_str(),filepath.c_str());

////        PyObject * pTool = _tool.ptr();
////        qDebug("here 1");

//        PyObject * pFunc = PyObject_GetAttrString(_module.ptr(),"XlAnalyser.return_sheet");
//        qDebug("here 2");

//        PyObject * rawData = PyObject_CallObject(pFunc,NULL);
//        qDebug("here 3");

//        data = CastToSheetData(rawData);

////        qDebug("here 1");

////        py::object sheet = _tool.attr("return_sheet")();

////        qDebug("here 2");

////        data = CastToSheetData(sheet.ptr());

////        qDebug("here 3");

//        return  data;
//    }

//    SheetData CastToSheetData(PyObject *obj)
//    {
//        SheetData data;
//        PyObject *iter = PyObject_GetIter(obj);

//        if (!iter)
//            return data;
//        while (true) {
//            std::list<std::string> aux_list;
//            PyObject *next = PyIter_Next(iter);
//            if (!next) {
//                // nothing left in the iterator
//                break;
//            }
//            PyObject *iter2 = PyObject_GetIter(next);
//            if (!iter2)
//                continue;
//            while(true) {
//                PyObject *next2 = PyIter_Next(iter2);
//                if (!next2) {
//                    // nothing left in the iterator
//                    break;
//                }
//                PyObject* pyStrObj = PyUnicode_AsUTF8String(next2);
//                char* zStr = PyBytes_AsString(pyStrObj);
//                std::string foo(strdup(zStr));
//                aux_list.push_back(foo);
//                Py_DECREF(pyStrObj);
//            }
//            data.push_back(aux_list);
//        }

//        return data;
//    }



//    void Find_Field_Index(std::string fieldname)
//    {
//        py::print(_tool.attr("find_field_index")(fieldname.c_str()));
//    }

//    ~DataAnalyser()
//    {
//        //py::finalize_interpreter();
//    }
//    py::object tool() const;
//};

#endif // DATAANALYSER_HPP


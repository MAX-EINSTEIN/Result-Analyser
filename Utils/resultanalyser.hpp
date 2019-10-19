#ifndef RESULTANALYSER_H
#define RESULTANALYSER_H

#include <string>
#include <vector>
#include <map>
#include <utility>
#include "Utils/exceltool.hpp"

using FieldBinding = std::pair<std::string, std::string>;
using FieldMap = std::vector<FieldBinding>;

class ResultAnalyser
{
private:
    SheetData _analysisData;
    FieldMap _bindings;

public:
    ResultAnalyser(SheetData data, FieldMap bindings);

};

#endif // SCOREANALYSER_H

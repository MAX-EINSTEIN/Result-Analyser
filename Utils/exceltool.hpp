#ifndef EXCELTOOL_H
#define EXCELTOOL_H

#include <xlnt/xlnt.hpp>
#include <QtDebug>

using SheetData = std::vector<std::vector<std::string> >;
using SheetRow = std::vector<std::string>;

class ExcelTool final
{
public:
    ExcelTool();
    static SheetData processFile(std::string t_file);
};

#endif // EXCELTOOL_H

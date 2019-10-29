#ifndef EXCELTOOL_H
#define EXCELTOOL_H

#include <xlnt/xlnt.hpp>
#include <QtDebug>

using SheetData = std::vector<std::vector<std::string> >;
using SheetRow = std::vector<std::string>;

class ExcelTool final
{
public:
    static SheetData read(std::string t_file);
    static SheetRow readHeaders(std::string t_file);
};

#endif // EXCELTOOL_H

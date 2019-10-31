#include "exceltool.hpp"

SheetData ExcelTool::read(std::string t_file)
{
    qDebug("_processFile : Okay ! I m in here");
    xlnt::workbook wb;
    try {
     wb.load(t_file);
    } catch (std::exception &e) {
        qDebug(e.what());
    }
    xlnt::worksheet file = wb.active_sheet();
    qDebug("_processFile : Now I got my file");
    SheetData theWholeSpreadSheet;
    try {
        for (auto row : file.rows())
        {
            SheetRow aSingleRow;
            for (auto cell : row)
            {
                aSingleRow.push_back(cell.to_string());
            }

            theWholeSpreadSheet.push_back(aSingleRow);
        }
    } catch (std::exception e) {
        qDebug(e.what());
    }
    qDebug("_processFile : Now I got out");
    return theWholeSpreadSheet;
}

SheetRow ExcelTool::readHeaders(std::string t_file)
{
    qDebug("_processFile : Okay ! I m in here");
    xlnt::workbook wb;
    try {
     wb.load(t_file);
    } catch (std::exception &e) {
        qDebug(e.what());
    }
    xlnt::worksheet file = wb.active_sheet();
    qDebug("_processFile : Now I got my file");
    SheetRow row;
    try {
        for(auto first_row:file.rows()){
            for(auto cell:first_row){
                row.push_back(cell.to_string());
            }
            break;
        }
    } catch (std::exception e) {
        qDebug(e.what());
    }
    qDebug("_processFile : Now I got out");
    return row;
}


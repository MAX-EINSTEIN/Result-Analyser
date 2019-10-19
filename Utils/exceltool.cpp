#include "exceltool.hpp"

ExcelTool::ExcelTool()
{

}


SheetData ExcelTool::_processFile(std::string t_fileName,std::string t_filePath)
{
    qDebug("_processFile : Okay ! I m in here");
    xlnt::workbook wb;
    try {
     wb.load(t_filePath + "/" + t_fileName);
    } catch (std::exception &e) {
        qDebug(e.what());
    }
    xlnt::worksheet file = wb.active_sheet();
    qDebug("_processFile : Now I got my file");
    SheetData theWholeSpreadSheet;
    try {
        for (auto row : file.rows(false))
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


    qDebug("_processFile : processed it and now Printing");

    for (unsigned int rowInt = 0; rowInt < theWholeSpreadSheet.size(); rowInt++)
    {
        for (unsigned int colInt = 0; colInt < theWholeSpreadSheet.at(rowInt).size(); colInt++)
        {
            std::cout << theWholeSpreadSheet.at(rowInt).at(colInt) << std::endl;
        }
    }

    qDebug("_processFile : Now just returning back from here");

    return theWholeSpreadSheet;
}


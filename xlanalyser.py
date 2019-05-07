"""Reads, writes, analyses data present in an excel file (.xls or .xlsx)

Usage:
    python xlanalyser.py <filename><filepath = optional>
        filename:   Name of the excel document you want to open
        filepath:   Location of the excel document
"""

import sys,xlrd,xlwt

class XlAnalyser():
    """Reads, writes, analyses data present in an excel file"""
    def __init__(self,filename,filepath = ''):
        """Initialises data of the class

        Args:
            filename:   Name of the excel document you want to open
            filepath:   Location of the excel document
        """
        self._filename =  filename
        if filepath != '':
            self._iworkbook = xlrd.open_workbook(filepath + '/' + filename)
        else:
            self._iworkbook = xlrd.open_workbook(filename)
        self._isheet = self._iworkbook.sheet_by_index(0)
        self._oworkbook = xlwt.Workbook()
        self._osheet = self._oworkbook.add_sheet(filename)
        self._fieldindex = 0


    def print_sheet(self):
        """Prints the sheet in a tabular format
        """
        for r in range(self._isheet.nrows):
            for c in range(self._isheet.ncols):
                print(self._isheet.cell_value(r,c), end = '\t')
            print('')


    def return_sheet(self):
        """Returns the sheet in a list of lists
        """
        dataTable = []
        for r in range(self._isheet.nrows):
            datalist = []
            for c in range(self._isheet.ncols):
                datalist.append(str(self._isheet.cell_value(r,c)))
            dataTable.append(datalist)
        return dataTable


    def copy_sheet(self,new_filename):
        """Makes a copy of sheet removing the styles prensent in the sheet
        """
        for r in range(self._isheet.nrows):
            for c in range(self._isheet.ncols):
                self._osheet.write(r,c,self._isheet.cell_value(r,c))
        self._oworkbook.save(new_filename)


    def find_field_index(self,fieldname):
        """Finds the column number of the fieldname passed

        Returns:
            The column number of the fieldname passed
        """
        for c in range(self._isheet.ncols):
            if(fieldname.lower() == self._isheet.cell_value(0,c).lower()):
                self._fieldindex = c
        return self._fieldindex


    def calc_perct(self, fieldname, criteria, relation):
        """Shows the percentage of records that meet the given criteria in the given fieldname

        Returns:
            The percentage of records that meet the given criteria in the given fieldname
        """
        perct = 0.0
        count = 0
        fieldindex = self.find_field_index(self._filename)
        for  r in range(1,self._isheet.nrows):
            if relation == '=':
                if(float(self._isheet.cell_value(r,fieldindex)) == criteria):
                    count += 1;
            elif relation == '>=':
                if(float(self._isheet.cell_value(r,fieldindex)) >= criteria):
                    count += 1;
            elif relation == '<=':
                if(float(self._isheet.cell_value(r,fieldindex)) <= criteria):
                    count += 1;
            elif relation == '>':
                if(float(self._isheet.cell_value(r,fieldindex)) > criteria):
                    count += 1;
            elif relation == '<':
                if(float(self._isheet.cell_value(r,fieldindex)) < criteria):
                    count += 1;
            else:
                raise ValueError("{} relation not defined".format(relation))
        perct = (count/(self._isheet.nrows-1)) * 100
        return perct

if(__name__ == '__main__'):
    tool = XlAnalyser(sys.argv[1],sys.argv[2])
    tool.print_sheet()
    print(tool.find_field_index('Cost'))
    print(tool.calc_perct('Cost',120.00,'>='))

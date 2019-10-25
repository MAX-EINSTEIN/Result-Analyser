#include "sheetdatatablemodel.hpp"

SheetDataTableModel::SheetDataTableModel(QObject *parent, std::unique_ptr<SheetData> t_data)
    : QAbstractTableModel(parent), _data(std::move(t_data))
{
}

QVariant SheetDataTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole){
        if(orientation==Qt::Horizontal){
            auto titles = _data->at(0);
            for(size_t i=0; i<titles.size(); i++){
                if(section == i) return QString(titles.at(i).c_str());
            }
        }
    }
    return QVariant{};
}

int SheetDataTableModel::rowCount(const QModelIndex &parent) const
{
    if(_data==nullptr && !parent.isValid()){
        return 0;
    }
    return static_cast<int>(_data->size()-1);
}

int SheetDataTableModel::columnCount(const QModelIndex &parent) const
{
    if(_data==nullptr && !parent.isValid()){
        return 0;
    }
    auto row = _data->at(0);
    return (row.size()-1);
}

QVariant SheetDataTableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole && index.isValid())
        return QString(_data->at(index.row()+1) .at(index.column()+1).c_str());

    return QVariant();
}

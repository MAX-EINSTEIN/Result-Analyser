#ifndef SHEETDATATABLEMODEL_H
#define SHEETDATATABLEMODEL_H

#include <QAbstractTableModel>
#include <memory>
#include "Utils/exceltool.hpp"

class SheetDataTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit SheetDataTableModel(QObject *parent = nullptr, std::unique_ptr<SheetData> t_data = nullptr);

    // Headers:
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
   std::unique_ptr<SheetData> _data;
};

#endif // SHEETDATATABLEMODEL_H

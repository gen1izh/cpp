#ifndef GROUP_MODEL_H
#define GROUP_MODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QtSql/QSqlDatabase>

class GroupItem;

class GroupModel : public QAbstractItemModel
{
    Q_OBJECT

public:

    GroupModel(const QStringList &headers, QObject *parent = 0);
    ~GroupModel();

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;

    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) Q_DECL_OVERRIDE;
    bool setHeaderData(int section, Qt::Orientation orientation,
                       const QVariant &value, int role = Qt::EditRole) Q_DECL_OVERRIDE;

    bool insertRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;
    bool removeRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;

    void addGroup(QString name, QString parent, QString role, QString description);

    void deleteGroup(const QModelIndex &index);

    void updateModel();

private:
    void setupModelData(GroupItem *parent);
    GroupItem *getItem(const QModelIndex &index) const;

    GroupItem *m_rootItem;

    QSqlDatabase m_db;

};

#endif // GROUP_MODEL_H

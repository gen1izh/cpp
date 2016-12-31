#include "groupmodel.h"

#include <QtWidgets>

#include "groupitem.h"
#include "groupmodel.h"
#include "groupqdjangomodel.h"

#include <QDebug>
#include <library/orm/db/QDjango.h>
#include <library/orm/db/QDjangoQuerySet.h>


GroupModel::GroupModel(const QStringList &headers, QObject *parent)
    : QAbstractItemModel(parent)
{
    QVector<QVariant> rootData;
    foreach (QString header, headers)
        rootData << header;

    m_rootItem = new GroupItem(rootData);

    m_db = QSqlDatabase::addDatabase("QSQLITE", "autorization");
    QString path = QString("%1/%2").arg(QCoreApplication::applicationDirPath()).arg("__autorization");
    m_db.setDatabaseName(path);
    m_db.open();

    QDjango::setDatabase(m_db);
    QDjango::registerModel<Group>();

    QDjango::createTables();

    setupModelData(m_rootItem);
}

GroupModel::~GroupModel()
{
    m_db.close();
    delete m_rootItem;
}


int GroupModel::columnCount(const QModelIndex & /* parent */) const
{
    return m_rootItem->columnCount();
}


QVariant GroupModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    GroupItem *item = getItem(index);

    return item->data(index.column());
}


Qt::ItemFlags GroupModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

GroupItem *GroupModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        GroupItem *item = static_cast<GroupItem*>(index.internalPointer());
        if (item)
            return item;
    }
    return m_rootItem;
}

QVariant GroupModel::getName(const QModelIndex &index) const
{
    if (!index.isValid())
        return QVariant();

    GroupItem *item = getItem(index);
    return item->data(0);
}

QVariant GroupModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return m_rootItem->data(section);

    return QVariant();
}

QModelIndex GroupModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return QModelIndex();

    GroupItem *parentItem = getItem(parent);

    GroupItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

bool GroupModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    GroupItem *parentItem = getItem(parent);
    bool success;

    beginInsertRows(parent, position, position + rows - 1);
    success = parentItem->insertChildren(position, rows, m_rootItem->columnCount());
    endInsertRows();

    return success;
}


QModelIndex GroupModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    GroupItem *childItem = getItem(index);
    GroupItem *parentItem = childItem->parent();

    if (parentItem == m_rootItem)
        return QModelIndex();

    return createIndex(parentItem->childNumber(), 0, parentItem);
}

bool GroupModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    GroupItem *parentItem = getItem(parent);
    bool success = true;

    beginRemoveRows(parent, position, position + rows - 1);
    success = parentItem->removeChildren(position, rows);
    endRemoveRows();

    return success;
}

void GroupModel::addGroup(QString name, QString parent, QString role, QString description)
{
    Group *group = new Group;
    group->setName(name);
    group->setDescription(description);
    group->setRole(role);
    group->setParent(parent);
    group->save();
}

void GroupModel::deleteRecursiveGroup(const QModelIndex &index)
{
    QStringList groupsList;
    groupsList.clear();

    QString name = data(index, Qt::DisplayRole).toString();
    // Удаляем все дочерние группы
    if (getItem(index)->childCount()!=0/*TODO: Hack, без него сигфолт*/) {
        removeRows(0, getItem(index)->childCount(), index);
    }

    QDjangoQuerySet<Group> groups;
    QDjangoQuerySet<Group> someGroups;
    someGroups = groups.filter(QDjangoWhere("name", QDjangoWhere::Equals, name));
    someGroups.remove();

    groupsList << name;

    bool isDeleteProceed = true;

    while (isDeleteProceed) {
        someGroups = groups.filter(QDjangoWhere("parent", QDjangoWhere::Equals, groupsList.first()));

        foreach (const Group &group, someGroups) {
          groupsList << group.name();
        }

        someGroups.remove();
        groupsList.pop_front();

        if (groupsList.isEmpty()) {
           isDeleteProceed = false;
        }
    }
}

void GroupModel::deleteGroup(const QModelIndex &index)
{
    QStringList groupsList;
    groupsList.clear();

    QString name = data(index, Qt::DisplayRole).toString();
    // Удаляем группу
    if (getItem(index)->childCount()>0) {
        removeRows(0, 1, index);
    }

    QDjangoQuerySet<Group> groups;
    QDjangoQuerySet<Group> someGroups;
    someGroups = groups.filter(QDjangoWhere("name", QDjangoWhere::Equals, name));
    someGroups.remove();
}

void GroupModel::updateModel()
{
    // Удаляем все дерево
    if (m_rootItem->childCount()!=0/*TODO: Hack, без него сигфолт*/) {
        if (!removeRows(0, m_rootItem->childCount())) {
          qDebug() << "Can not delete rows!";
        }
    }

    QStringList headers;
    headers << tr("Группа")<< tr("Описание");

    QVector<QVariant> rootData;
    foreach (QString header, headers)
        rootData << header;

    m_rootItem = new GroupItem(rootData);

    setupModelData(m_rootItem);

}


int GroupModel::rowCount(const QModelIndex &parent) const
{
    GroupItem *parentItem = getItem(parent);

    return parentItem->childCount();
}

bool GroupModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole)
        return false;

    GroupItem *item = getItem(index);
    bool result = item->setData(index.column(), value);

    if (result)
        emit dataChanged(index, index);

    return result;
}

bool GroupModel::setHeaderData(int section, Qt::Orientation orientation,
                              const QVariant &value, int role)
{
    if (role != Qt::EditRole || orientation != Qt::Horizontal)
        return false;

    bool result = m_rootItem->setData(section, value);

    if (result)
        emit headerDataChanged(orientation, section, section);

    return result;
}

void GroupModel::setupModelData(GroupItem *parent) {

    GroupItem *item = parent;

    QList<QString> parents;
    parents << "";

    QList<GroupItem *> items;
    item->setIdentify(0);
    items << item;

    bool isNeedScan = true;
    while (isNeedScan) {
        QDjangoQuerySet<Group> groups;

        QDjangoQuerySet<Group> filtredGroup;
        filtredGroup = groups.filter(QDjangoWhere("parent", QDjangoWhere::Equals, parents.first()));

        foreach(GroupItem *_item, items) {
          if (_item->data(0/*column name*/).toString() == parents.first()) {
            item = _item;
            break;
          }
        }

        QList<QVariantMap> propertyMaps = filtredGroup.values(QStringList() << "name" << "description" << "id");
        foreach (const QVariantMap &propertyMap, propertyMaps) {
          item->insertChildren(item->childCount(), 1, m_rootItem->columnCount());
          item->child(item->childCount() - 1)->setData(0, propertyMap["name"]);
          item->child(item->childCount() - 1)->setData(1, propertyMap["description"]);

          bool ok;
          parents << propertyMap["name"].toString();
          item->child(item->childCount() - 1)->setIdentify(propertyMap["id"].toInt(&ok));

          items << (item->child(item->childCount() - 1));
        }

        parents.pop_front();

        if (parents.isEmpty()) {
          isNeedScan = false;
        }

    }

}



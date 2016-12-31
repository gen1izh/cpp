/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

/*
    GroupItem.cpp

    A container for items of data supplied by the simple tree model.
*/

#include "groupitem.h"

#include <QStringList>

#include <QDebug>

//! [0]
GroupItem::GroupItem(const QVector<QVariant> &data, GroupItem *parent)
{
    parentItem = parent;
    itemData = data;
}
//! [0]

//! [1]
GroupItem::~GroupItem()
{
    for (int i = 0; i < childItems.size(); i++) {
      delete childItems.at(i);
    }
}
//! [1]

//! [2]
GroupItem *GroupItem::child(int number)
{
    return childItems.value(number);
}
//! [2]

//! [3]
int GroupItem::childCount() const
{
    return childItems.count();
}
//! [3]

//! [4]
int GroupItem::childNumber() const
{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<GroupItem*>(this));

    return 0;
}
//! [4]

//! [5]
int GroupItem::columnCount() const
{
    return itemData.count();
}
//! [5]

//! [6]
QVariant GroupItem::data(int column) const
{
    return itemData.value(column);
}
//! [6]

//! [7]
bool GroupItem::insertChildren(int position, int count, int columns)
{
    if (position < 0 || position > childItems.size())
        return false;

    for (int row = 0; row < count; ++row) {
        QVector<QVariant> data(columns);
        GroupItem *item = new GroupItem(data, this);
        childItems.insert(position, item);
    }

    return true;
}
//! [7]

//! [8]
bool GroupItem::insertColumns(int position, int columns)
{
    if (position < 0 || position > itemData.size())
        return false;

    for (int column = 0; column < columns; ++column)
        itemData.insert(position, QVariant());

    foreach (GroupItem *child, childItems)
        child->insertColumns(position, columns);

    return true;
}
//! [8]

//! [9]
GroupItem *GroupItem::parent()
{
    return parentItem;
}
//! [9]

//! [10]
bool GroupItem::removeChildren(int position, int count)
{
    if (position < 0 || position + count > childItems.size())
        return false;

    for (int row = 0; row < count; ++row)
        delete childItems.takeAt(position);

    return true;
}
//! [10]

bool GroupItem::removeColumns(int position, int columns)
{
    if (position < 0 || position + columns > itemData.size())
        return false;

    for (int column = 0; column < columns; ++column)
        itemData.remove(position);

    foreach (GroupItem *child, childItems)
        child->removeColumns(position, columns);

    return true;
}

//! [11]
bool GroupItem::setData(int column, const QVariant &value)
{
    if (column < 0 || column >= itemData.size())
        return false;

    itemData[column] = value;
    return true;
}
int GroupItem::getIdentify() const
{
  return identify;
}

void GroupItem::setIdentify(int value)
{
  identify = value;
}

//! [11]

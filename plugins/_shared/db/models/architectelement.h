#ifndef ARCHITECTELEMENT_H
#define ARCHITECTELEMENT_H

#include <library/orm/db/QDjangoModel.h>

class ArchitectElement : public QDjangoModel
{
    Q_OBJECT
    Q_PROPERTY(int parentId READ parentId WRITE setParentId)
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString type READ type WRITE setType)

    Q_CLASSINFO("parentId", "none")
    Q_CLASSINFO("name", "max_length=255")
    Q_CLASSINFO("type", "max_length=255")

public:

    ArchitectElement(QObject *parent = 0);

    int parentId() const;
    void setParentId(int parentId);

    QString type() const;
    void setType(const QString &type);

    QString name() const;
    void setName(const QString &name);

private:
    int m_parentId;
    QString m_name;
    QString m_type;

};

#endif // ARCHITECTELEMENT_H

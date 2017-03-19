#ifndef GROUP_QDJANGO_MODEL_H
#define GROUP_QDJANGO_MODEL_H

#include <library/orm/db/QDjangoModel.h>

class Group : public QDjangoModel
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString description READ description WRITE setDescription)
    Q_PROPERTY(QString parent READ parent WRITE setParent)

    Q_CLASSINFO("name", "max_length=64")
    Q_CLASSINFO("description", "max_length=255")
    Q_CLASSINFO("parent", "max_length=64")

public:
    Group(QObject *parent = 0);

    QString name() const;
    void setName(const QString &name);

    QString description() const;
    void setDescription(const QString &description);

    QString parent() const;
    void setParent(const QString &parent);

private:
    QString m_parent;
    QString m_name;
    QString m_description;

};

#endif // GROUP_QDJANGO_MODEL_H

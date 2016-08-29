#ifndef GROUP_QDJANGO_MODEL_H
#define GROUP_QDJANGO_MODEL_H

#include <library/orm/db/QDjangoModel.h>

class Group : public QDjangoModel
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString description READ description WRITE setDescription)
    Q_PROPERTY(QString parent READ parent WRITE setParent)
    Q_PROPERTY(QString role READ role WRITE setRole)

    Q_CLASSINFO("name", "max_length=64")
    Q_CLASSINFO("description", "max_length=255")
    Q_CLASSINFO("parent", "null=true")
    Q_CLASSINFO("role", "max_length=255")


public:

    QString name() const;
    void setName(const QString &name);

    QString description() const;
    void setDescription(const QString &description);

    QString parent() const;
    void setParent(const QString &parent);

    QString role() const;
    void setRole(const QString &role);

private:
    QString m_parent;
    QString m_name;
    QString m_description;
    QString m_role;
};

#endif // GROUP_QDJANGO_MODEL_H

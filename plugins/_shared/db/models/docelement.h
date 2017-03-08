#ifndef DOCELEMENT_H
#define DOCELEMENT_H

#include <library/orm/db/QDjangoModel.h>

class DocElement : public QDjangoModel
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString type READ type WRITE setType)
    Q_PROPERTY(QString description READ description WRITE setDescription)

    Q_CLASSINFO("name", "max_length=255")
    Q_CLASSINFO("type", "max_length=255")
    Q_CLASSINFO("description", "max_length=1048576")

public:

    QString name() const;
    void setName(const QString &name);

    QString description() const;
    void setDescription(const QString &description);

    QString type() const;
    void setType(const QString &type);

private:
    QString m_name;
    QString m_type;
    QString m_description;
};

#endif // DOCELEMENT_H

#ifndef ARCHITECTTYPEALIAS_H
#define ARCHITECTTYPEALIAS_H

#include <library/orm/db/QDjangoModel.h>

class ArchitectTypeAlias : public QDjangoModel
{
    Q_OBJECT
    Q_PROPERTY(QString type READ type WRITE setType)
    Q_PROPERTY(QString alias READ alias WRITE setAlias)

    Q_CLASSINFO("type", "max_length=255")
    Q_CLASSINFO("alias", "max_length=255")
public:

    QString type() const;
    void setType(const QString &type);

    QString alias() const;
    void setAlias(const QString &alias);

private:
    QString m_type;
    QString m_alias;
};

#endif // ARCHITECTTYPEALIAS_H

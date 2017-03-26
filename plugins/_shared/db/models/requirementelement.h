#ifndef REQUIREMENTELEMENT_H
#define REQUIREMENTELEMENT_H

#include <library/orm/db/QDjangoModel.h>

#include "architectelement.h"

class RequirementElement : public QDjangoModel
{
    Q_OBJECT
    // тип требования ФТ, ПТ
    Q_PROPERTY(QString type READ type WRITE setType)
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(ArchitectElement *component READ component WRITE setComponent)

    Q_CLASSINFO("type", "max_length=255")
    Q_CLASSINFO("name", "max_length=255")
    Q_CLASSINFO("component", "on_delete=cascade")

public:

    RequirementElement(QObject *parent = 0);

    QString type() const;
    void setType(const QString &type);

    QString name() const;
    void setName(const QString &name);

    ArchitectElement *component() const;
    void setComponent(ArchitectElement *component);

private:

    QString m_type;
    QString m_name;

};

#endif // REQUIREMENTELEMENT_H

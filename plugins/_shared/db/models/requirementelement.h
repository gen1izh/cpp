#ifndef REQUIREMENTELEMENT_H
#define REQUIREMENTELEMENT_H

#include <library/orm/db/QDjangoModel.h>

class RequirementElement : public QDjangoModel
{
    Q_OBJECT
    // тип требования ФТ, ПТ
    Q_PROPERTY(QString rtype READ rtype WRITE setRType)
    Q_PROPERTY(int identificator READ identificator WRITE setIdentificator)
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString component READ component WRITE setComponent)
    Q_PROPERTY(QString module READ module WRITE setModule)

    Q_CLASSINFO("rtype", "max_length=255")
    Q_CLASSINFO("identificator", "")
    Q_CLASSINFO("name", "max_length=255")
    Q_CLASSINFO("component", "max_length=255")
    Q_CLASSINFO("module", "max_length=255")

public:

    QString rtype() const;
    void setRType(const QString &rtype);

    int identificator() const;
    void setIdentificator(const int &identificator);

    QString name() const;
    void setName(const QString &name);

    QString component() const;
    void setComponent(const QString &component);

    QString module() const;
    void setModule(const QString &module);

private:
    QString m_rtype;
    int m_identificator;
    QString m_name;
    QString m_component;
    QString m_module;
};

#endif // REQUIREMENTELEMENT_H

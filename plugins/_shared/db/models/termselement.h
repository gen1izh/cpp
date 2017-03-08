#ifndef TERMSELEMENT_H
#define TERMSELEMENT_H

#include <library/orm/db/QDjangoModel.h>

class TermsElement : public QDjangoModel
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString description READ description WRITE setDescription)

    Q_CLASSINFO("name", "max_length=255")
    Q_CLASSINFO("description", "max_length=512")

public:

    QString name() const;
    void setName(const QString &name);

    QString description() const;
    void setDescription(const QString &description);

private:
    QString m_name;
    QString m_description;
};

#endif // TERMSELEMENT_H

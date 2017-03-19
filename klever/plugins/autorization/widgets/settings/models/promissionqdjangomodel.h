#ifndef PROMISSION_QDJANGO_MODEL_H
#define PROMISSION_QDJANGO_MODEL_H

#include <library/orm/db/QDjangoModel.h>
#include "roleqdjangomodel.h"

class Promission : public QDjangoModel
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString signature READ signature WRITE setSignature)
    Q_PROPERTY(QString constant READ constant WRITE setConstant)
    Q_PROPERTY(Role *role READ role WRITE setRole)

    Q_CLASSINFO("name", "max_length=255")
    Q_CLASSINFO("signature", "max_length=128")
    Q_CLASSINFO("constant", "max_length=32")
    Q_CLASSINFO("role", "on_delete=cascade")

public:
    Promission(QObject *parent = 0);

    QString name() const;
    void setName(const QString &name);

    QString signature() const;
    void setSignature(const QString &signature);

    QString constant() const;
    void setConstant(const QString &constant);

    Role *role() const;
    void setRole(Role *role);
private:
    QString m_name;
    QString m_signature;
    QString m_constant;
};

#endif // PROMISSION_QDJANGO_MODEL_H

#ifndef PROMISSION_QDJANGO_MODEL_H
#define PROMISSION_QDJANGO_MODEL_H

#include <library/orm/db/QDjangoModel.h>

class Promission : public QDjangoModel
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString signature READ signature WRITE setSignature)
    Q_PROPERTY(QString constant READ constant WRITE setConstant)

    Q_CLASSINFO("name", "max_length=255")
    Q_CLASSINFO("signature", "max_length=128")
    Q_CLASSINFO("constant", "max_length=32")

public:
    QString name() const;
    void setName(const QString &name);

    QString signature() const;
    void setSignature(const QString &signature);

    QString constant() const;
    void setConstant(const QString &constant);

private:
    QString m_name;
    QString m_signature;
    QString m_constant;
};

#endif // PROMISSION_QDJANGO_MODEL_H

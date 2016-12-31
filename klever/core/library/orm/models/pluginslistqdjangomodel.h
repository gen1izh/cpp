#ifndef PLUGINS_LIST_QDJANGO_MODEL_H
#define PLUGINS_LIST_QDJANGO_MODEL_H

#include "../db/QDjangoModel.h"

class PluginsQDjangoModel : public QDjangoModel
{

    Q_OBJECT

    Q_PROPERTY(QString type READ type WRITE setType)
    Q_CLASSINFO("type", "max_length=255")

    Q_PROPERTY(QString name READ name WRITE setName)
    Q_CLASSINFO("name", "max_length=255")

    Q_PROPERTY(QString state READ state WRITE setState)
    Q_CLASSINFO("state", "max_length=255")

    Q_PROPERTY(QString objectsCount READ objectsCount WRITE setObjectsCount)
    Q_CLASSINFO("objectsCount", "max_length=255")

public:

    QString type() const;
    void setType(const QString &type);

    QString name() const;
    void setName(const QString &name);

    QString state() const;
    void setState(const QString &state);

    QString objectsCount() const;
    void setObjectsCount(const QString &objectsCount);

private:
    QString m_type;
    QString m_name;
    QString m_state;
    QString m_objectsCount;
};

#endif // PLUGINS_LIST_QDJANGO_MODEL_H

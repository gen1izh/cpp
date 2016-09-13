#ifndef PLUGINS_LIST_QDJANGO_MODEL_H
#define PLUGINS_LIST_QDJANGO_MODEL_H

#include "../db/QDjangoModel.h"

class PluginsQDjangoModel : public QDjangoModel
{

    Q_OBJECT

    QString m_type;  // manager or module
    QString m_name;
    bool m_state;
    int m_objectsCount;

    Q_PROPERTY(QString type READ type WRITE setType)
    Q_CLASSINFO("type", "max_length=255")

    Q_PROPERTY(QString name READ name WRITE setName)
    Q_CLASSINFO("name", "max_length=255")

    Q_PROPERTY(bool state READ state WRITE setState)
    Q_CLASSINFO("state", "max_length=3")

    Q_PROPERTY(int objectsCount READ objectsCount WRITE setObjectsCount)
    Q_CLASSINFO("objectsCount", "")

public:

    QString type() const;
    void setType(const QString &type);

    QString name() const;
    void setName(const QString &name);

    bool state() const;
    void setState(bool state);

    int objectsCount() const;
    void setObjectsCount(int objectsCount);
};

#endif // PLUGINS_LIST_QDJANGO_MODEL_H

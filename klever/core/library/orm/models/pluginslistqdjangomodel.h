#ifndef PLUGINS_LIST_QDJANGO_MODEL_H
#define PLUGINS_LIST_QDJANGO_MODEL_H

#include "../db/QDjangoModel.h"

class PluginsQDjangoModel : public QDjangoModel
{

    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName)
    Q_CLASSINFO("name", "max_length=255")

public:

    QString name() const;
    void setName(const QString &name);

private:
    QString m_name;
};

#endif // PLUGINS_LIST_QDJANGO_MODEL_H

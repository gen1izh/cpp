#ifndef ARCHITECTLINKS_H
#define ARCHITECTLINKS_H

#include <library/orm/db/QDjangoModel.h>

class ArchitectLinks : public QDjangoModel
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString description READ description WRITE setDescription)
    Q_PROPERTY(QString linkA READ linkA WRITE setLinkA)
    Q_PROPERTY(QString linkB READ linkB WRITE setLinkB)

    // обеспечение связи 1-1, 1 ко многим и тд
    Q_PROPERTY(QString linkACount READ linkACount WRITE setLinkACount)
    Q_PROPERTY(QString linkBCount READ linkBCount WRITE setLinkBCount)

    // Наследование, ассоциация, агрегация и т.д.
    Q_PROPERTY(QString type READ type WRITE setType)



    Q_CLASSINFO("name", "max_length=255")
    Q_CLASSINFO("description", "max_length=2048")
    Q_CLASSINFO("linkA", "max_length=64")
    Q_CLASSINFO("linkB", "max_length=64")
    Q_CLASSINFO("linkACount", "max_length=64")
    Q_CLASSINFO("linkBCount", "max_length=64")
    Q_CLASSINFO("type", "max_length=64")

public:

    QString name() const;
    void setName(const QString &name);

    QString linkA() const;
    void setLinkA(const QString &linkA);

    QString linkB() const;
    void setLinkB(const QString &linkB);

    QString linkACount() const;
    void setLinkACount(const QString &linkACount);

    QString linkBCount() const;
    void setLinkBCount(const QString &linkBCount);

    QString type() const;
    void setType(const QString &type);

    QString description() const;
    void setDescription(const QString &description);

private:
    QString m_name;
    QString m_description;
    QString m_linkA;
    QString m_linkB;
    QString m_linkACount;
    QString m_linkBCount;
    QString m_type;

};

#endif // ARCHITECTLINKS_H

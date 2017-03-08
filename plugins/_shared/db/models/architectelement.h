#ifndef ARCHITECTELEMENT_H
#define ARCHITECTELEMENT_H

#include <library/orm/db/QDjangoModel.h>

class ArchitectElement : public QDjangoModel
{
    Q_OBJECT
    Q_PROPERTY(QString article READ article WRITE setArticle)
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString description READ description WRITE setDescription)
    Q_PROPERTY(QString parentElementType READ parentElementType WRITE setParentElementType)
    Q_PROPERTY(QString parentElementArticle READ parentElementArticle WRITE setParentElementArticle)
    Q_PROPERTY(QString type READ type WRITE setType)

    Q_CLASSINFO("article", "max_length=255")
    Q_CLASSINFO("name", "max_length=255")
    Q_CLASSINFO("description", "max_length=10000")
    Q_CLASSINFO("parentElementType", "max_length=255")
    Q_CLASSINFO("parentElementArticle", "max_length=255")
    Q_CLASSINFO("type", "max_length=255")

public:

    QString article() const;
    void setArticle(const QString &article);

    QString name() const;
    void setName(const QString &name);

    QString description() const;
    void setDescription(const QString &description);

    QString parentElementType() const;
    void setParentElementType(const QString &parentElementType);

    QString parentElementArticle() const;
    void setParentElementArticle(const QString &parentElementArticle);

    QString type() const;
    void setType(const QString &type);

private:
    QString m_article;
    QString m_name;
    QString m_description;
    QString m_parentElementType;
    QString m_parentElementArticle;
    QString m_type;

};

#endif // ARCHITECTELEMENT_H

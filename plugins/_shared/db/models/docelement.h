#ifndef DOCELEMENT_H
#define DOCELEMENT_H

#include <library/orm/db/QDjangoModel.h>

class DocElement : public QDjangoModel
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString uid READ uid WRITE setUid)
    Q_PROPERTY(QString type READ type WRITE setType)
    Q_PROPERTY(QString content READ content WRITE setContent)
	Q_PROPERTY(QString author READ author WRITE setAuthor)
	Q_PROPERTY(QString datetime READ datetime WRITE setDatetime)
	Q_PROPERTY(int version READ version WRITE setVersion)
	Q_PROPERTY(QString comment READ comment WRITE setComment)
	
    Q_CLASSINFO("name", "max_length=255")
    Q_CLASSINFO("uid", "max_length=255")
    Q_CLASSINFO("type", "max_length=255")
    Q_CLASSINFO("content", "")
    Q_CLASSINFO("author", "max_length=255")
	Q_CLASSINFO("datetime", "max_length=255")
	Q_CLASSINFO("version", "")
	Q_CLASSINFO("comment", "max_length=1024")

public:
    QString name() const;
    void setName(const QString &name);

    QString type() const;
    void setType(const QString &type);

    QString content() const;
    void setContent(const QString &content);

    QString author() const;
    void setAuthor(const QString &author);

    QString datetime() const;
    void setDatetime(const QString &datetime);

    int version() const;
    void setVersion(int version);

    QString comment() const;
    void setComment(const QString &comment);

    DocElement(QObject *parent = 0);

    QString uid() const;
    void setUid(const QString &uid);

private:
    QString m_name;
    QString m_uid;
    QString m_type;
    QString m_content;
	QString m_author;
	QString m_datetime;
	int m_version;
    QString m_comment;
	
};

#endif // DOCELEMENT_H

#ifndef IMAGESELEMENT_H
#define IMAGESELEMENT_H

#include <library/orm/db/QDjangoModel.h>

class ImagesElement : public QDjangoModel
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString filename READ filename WRITE setFilename)

    Q_CLASSINFO("name", "max_length=255")
    Q_CLASSINFO("filename", "max_length=255")

public:


    QString filename() const;
    void setFilename(const QString &filename);

    QString name() const;
    void setName(const QString &name);

private:
    QString m_name;
    QString m_filename;
};


#endif // IMAGESELEMENT_H

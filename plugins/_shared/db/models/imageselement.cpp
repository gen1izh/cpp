#include "imageselement.h"



QString ImagesElement::filename() const
{
    return m_filename;
}

void ImagesElement::setFilename(const QString &filename)
{
    m_filename = filename;
}

QString ImagesElement::name() const
{
    return m_name;
}

void ImagesElement::setName(const QString &name)
{
    m_name = name;
}

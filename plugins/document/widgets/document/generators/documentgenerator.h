#ifndef DOCUMENTGENERATOR_H
#define DOCUMENTGENERATOR_H

#include <QString>
#include <QFile>
#include <QTextStream>

class DocumentGenerator
{

public:
    DocumentGenerator();

    QString generate();



private:
    QString createBody(const QString &specification, const QString &description, const QString &user_usage);
    QString createHeader();
    QString createFooter();
    QString createDocContent();


    QString loadText(const QString& txt);
    QString parse(const QString& txt);

    QString parseRequirement(const QString& txt, const QString &type);
    QString parseAnchor(const QString& txt);
    QString parseGotoAnchor(const QString& txt);

    QString parseFilename(const QString& txt);
    QString parseName(const QString& txt);

    QString parseSpecification();
    QString parseDescription();
    QString parseUserUsage();


};

#endif // DOCUMENTGENERATOR_H

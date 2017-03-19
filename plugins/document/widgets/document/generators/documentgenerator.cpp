#include "documentgenerator.h"
#include <frameWork/base.h>
#include <QDateTime>
#include <QDir>
#include <QDebug>
#include <QRegularExpressionMatch>

#include <library/orm/db/QDjangoQuerySet.h>
#include "../../../../_shared/db/models/docelement.h"
#include "../../../../_shared/db/models/glossaryelement.h"
#include "../../../../_shared/db/models/termselement.h"

QString DocumentGenerator::createHeader()
{
    QString header = "<!DOCTYPE html>"\
            "<html>"\
            "<head>"\
            "    <title>Документация по системе</title>"\
            "    <!--Подключение необходимых файлов-->"\
            "    <link href=\"../Bootstrap/styles/bootstrap.min.css\" rel=\"stylesheet\" />"\
            "    <script src=\"../Bootstrap/js/jquery-1.11.1.min.js\"></script>"\
            "    <script src=\"../Bootstrap/js/bootstrap.min.js\"></script>"\
            "    <style>'"\
            "        .container {"\
            "            margin-top: 40px;"\
            "        }'"\
            "        table, .table {"\
            "            width: 300px;"\
            "            margin: 20px auto;"\
            "        }"\
            "        .p1 {"\
            "            text-indent: 20px;"\
            "        }"\
            "        .p2 {"\
            "            text-indent: 40px;"\
            "        }"\
            "        .p3 {"\
            "            text-indent: 60px;"\
            "        }"\
            "        .p4 {"\
            "            text-indent: 80px;"\
            "        }"\
            "    </style>"\
            "</head>";

    return header;
}



QString DocumentGenerator::createBody(const QString& specification,
                                      const QString& description,
                                      const QString& user_usage)
{
    QString body = QString("   <body><div class=\"container\">"\
                           "        <div class=\"row\">"\
                           "            <div class=\"col-md-2\">"\
                           "                <p>Название системы:</p>"\
                           "            </div>"\
                           "            <div class=\"col-md-3\">"\
                           "                <p> %1 </p> </div>"\
                           "            <div class=\"col-md-6\">"\
                           "            </div>'"\
                           "        </div>"\
                           "        <div class=\"row\">"\
                           "            <div class=\"col-md-2\">"\
                           "                <p>Дата и время генерации:</p>"\
                           "            </div>"\
                           "            <div class=\"col-md-3\">"\
                           "                <p> %2 </p></div>"\
                           "            <div class=\"col-md-6\">"\
                           "            </div>"\
                           "        </div>"\
                           "        <!-- Контейнер с закладками -->"\
                           "        <ul class=\"nav nav-tabs\" role=\"tablist\">"\
                           "            <li class=\"active\"><a href=\"#specification\" role=\"tab\" data-toggle=\"tab\">Спецификация требований</a></li>"\
                           "            <li><a href=\"#description\" role=\"tab\" data-toggle=\"tab\">Описание ПО</a></li>"\
                           "            <li><a href=\"#user_usage\" role=\"tab\" data-toggle=\"tab\">Руководство пользователя</a></li>"\
                           "        </ul>"\
                           "        <!-- Контейнер с панелями -->"\
                           "        <div class=\"tab-content\">"\
                           "            <div class=\"tab-pane fade in active\" id=\"specification\">"\
                           "                <p>%3</p> "\
                           "            </div>"\
                           "            <div class=\"tab-pane fade\" id=\"description\"> "\
                           "                <p>%4</p> "\
                           "            </div>"\
                           "            <div class=\"tab-pane fade\" id=\"user_usage\">"\
                           "                <p>%5</p>"\
                           "            </div>"\
                           "        </div>"\
                           "    </div>")
                        .arg(Core::Base::instance().getParameterValue(QString("[Session]Name"), QString("")))
                        .arg(QDateTime::currentDateTime().toString("ddd MMMM d yy hh:mm:ss.zzz"))
                        .arg(specification)
                        .arg(description)
                        .arg(user_usage);
    return body;
}

QString DocumentGenerator::createFooter()
{
    QString footer ="</body></html>";
    return footer;
}

DocumentGenerator::DocumentGenerator()
{

}

QString DocumentGenerator::generate()
{

    QString path = QString("%1%2")
            .arg(Core::Base::instance().getParameterValue(QString("[Session]Folder"), QString("")))
            .arg("/document/doc/document.html");

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return QString("None");

    QTextStream out(&file);
    QString tmp = createDocContent();
    out << tmp;

    return path;

}

QString DocumentGenerator::createDocContent()
{
    QString tmp = QString("%1%2%3")
            .arg(createHeader())
            .arg(createBody(parseSpecification(),
                            parseDescription(),
                            parseUserUsage()))
            .arg(createFooter());

    return tmp;
}

QString DocumentGenerator::loadText(const QString &txt)
{
    QDjangoQuerySet<DocElement> someDocElements;

    someDocElements = someDocElements.filter(QDjangoWhere("name", QDjangoWhere::Equals, txt));

    DocElement de;
    for (int i = 0; i < someDocElements.size(); ++i) {
        if (someDocElements.at(i, &de)) {
            if (de.name() == txt) {
                return de.description();
            }
        }
    }

    return QString("");

}

QString DocumentGenerator::parse(const QString &txt)
{

    QString tmp = txt;

    if (tmp.indexOf("[BODY_CR:Бизнес-правила]")!=-1)
        tmp = tmp.replace(QString("[BODY_CR:Бизнес-правила]"), loadText("Бизнес-правила"));

    if (tmp.indexOf("[BODY_CR:Системные требования]")!=-1)
        tmp = tmp.replace(QString("[BODY_CR:Системные требования]"), loadText("Системные требования"));

    if (tmp.indexOf("[BODY_CR:Требования к документированию]")!=-1)
        tmp = tmp.replace(QString("[BODY_CR:Требования к документированию]"), loadText("Требования к документированию"));

    if (tmp.indexOf("[BODY_CR:Требования к дизаину ГИП]")!=-1)
        tmp = tmp.replace(QString("[BODY_CR:Требования к дизаину ГИП]"), loadText("Требования к дизаину ГИП"));

    if (tmp.indexOf("[BODY_CR:Требования к безопасности и надежности]")!=-1)
        tmp = tmp.replace(QString("[BODY_CR:Требования к безопасности и надежности]"), loadText("Требования к безопасности и надежности"));

    if (tmp.indexOf("[BODY_CR:Бизнес-правила]")!=-1)
        tmp = tmp.replace(QString("[BODY_CR:Бизнес-правила]"), loadText("Бизнес-правила"));

    if (tmp.indexOf("[BODY_CR:Требования к производительности]")!=-1)
        tmp = tmp.replace(QString("[BODY_CR:Требования к производительности]"), loadText("Требования к производительности"));

    if (tmp.indexOf("[BODY_CR:Требования к устойчивости к сбоям]")!=-1)
        tmp = tmp.replace(QString("[BODY_CR:Требования к устойчивости к сбоям]"), loadText("Требования к устойчивости к сбоям"));

    if (tmp.indexOf("[BODY_CR:Требования к эксплуатации и персоналу]")!=-1)
        tmp = tmp.replace(QString("[BODY_CR:Требования к эксплуатации и персоналу]"), loadText("Требования к эксплуатации и персоналу"));

    if (tmp.indexOf("[BODY_CR:Требования к внутреннему состоянию]")!=-1)
        tmp = tmp.replace(QString("[BODY_CR:Требования к внутреннему состоянию]"), loadText("Требования к внутреннему состоянию"));

    if (tmp.indexOf("[BODY_CR:Требования к отладке]")!=-1)
        tmp = tmp.replace(QString("[BODY_CR:Требования к отладке]"), loadText("Требования к отладке"));

    if (tmp.indexOf("[BODY_CR:Требования использования ПО]")!=-1)
        tmp = tmp.replace(QString("[BODY_CR:Требования использования ПО]"), loadText("Требования использования ПО"));

    if (tmp.indexOf("[BODY_INFO:Общие сведения]")!=-1)
        tmp = tmp.replace(QString("[BODY_INFO:Общие сведения]"), loadText("Общие сведения"));

    if (tmp.indexOf("[BODY_INFO:Назначение ПО]")!=-1)
        tmp = tmp.replace(QString("[BODY_INFO:Назначение ПО]"), loadText("Назначение ПО"));

    if (tmp.indexOf("[BODY_INFO:Язык программирования]")!=-1)
        tmp = tmp.replace(QString("[BODY_INFO:Язык программирования]"), loadText("Язык программирования"));

    if (tmp.indexOf("[BODY_INFO:Средства компиляции и сборки проекта]")!=-1)
        tmp = tmp.replace(QString("[BODY_INFO:Средства компиляции и сборки проекта]"), loadText("Средства компиляции и сборки проекта"));

    if (tmp.indexOf("[BODY_INFO:Перечень ссылочных документов]")!=-1)
        tmp = tmp.replace(QString("[BODY_INFO:Перечень ссылочных документов]"), loadText("Перечень ссылочных документов"));

    if (tmp.indexOf("[BODY_INFO:Функциональные ограничения на применение]")!=-1)
        tmp = tmp.replace(QString("[BODY_INFO:Функциональные ограничения на применение]"), loadText("Функциональные ограничения на применение"));

    if (tmp.indexOf("[BODY_INFO:Необходимые и достаточные условия эксплуатации ПО]")!=-1)
        tmp = tmp.replace(QString("[BODY_INFO:Необходимые и достаточные условия эксплуатации ПО]"), loadText("Необходимые и достаточные условия эксплуатации ПО"));



    if (tmp.indexOf("[BODY_BR:Видение]")!=-1)
        tmp = tmp.replace(QString("[BODY_BR:Видение]"), loadText("Видение"));

    if (tmp.indexOf("[BODY_BR:Предметная область]")!=-1)
        tmp = tmp.replace(QString("[BODY_BR:Предметная область]"), loadText("Предметная область"));


    tmp = parseRequirement(tmp, QString("BODY_NFR"));
    tmp = parseRequirement(tmp, QString("BODY_FR"));

    ///
    if (tmp.isEmpty()) tmp = "<br/>";

    tmp = tmp.replace(QString("[H1]"),QString("<h1>"));
    tmp = tmp.replace(QString("[H2]"),QString("<h2>"));
    tmp = tmp.replace(QString("[H3]"),QString("<h3>"));
    tmp = tmp.replace(QString("[H4]"),QString("<h4>"));

    tmp = tmp.replace(QString("[/H1]"),QString("</h1>"));
    tmp = tmp.replace(QString("[/H2]"),QString("</h2>"));
    tmp = tmp.replace(QString("[/H3]"),QString("</h3>"));
    tmp = tmp.replace(QString("[/H4]"),QString("</h4>"));

    tmp = tmp.replace(QString("[/UL]"),QString("</ul>"));
    tmp = tmp.replace(QString("[/LI]"),QString("</li>"));
    tmp = tmp.replace(QString("[UL]"),QString("<ul>"));
    tmp = tmp.replace(QString("[LI]"),QString("<li>"));

    tmp = tmp.replace(QString("[B]"),QString("<b>"));
    tmp = tmp.replace(QString("[/B]"),QString("</b>"));

    tmp = tmp.replace(QString("[I]"),QString("<i>"));
    tmp = tmp.replace(QString("[/I]"),QString("</i>"));

    tmp = tmp.replace(QString("[U]"),QString("<u>"));
    tmp = tmp.replace(QString("[/U]"),QString("</u>"));

    tmp = tmp.replace(QString("[P1]"),QString("<p class=\"p1\">"));
    tmp = tmp.replace(QString("[/P1]"),QString("</p>"));

    tmp = tmp.replace(QString("[P2]"),QString("<p class=\"p2\">"));
    tmp = tmp.replace(QString("[/P2]"),QString("</p>"));

    tmp = tmp.replace(QString("[P3]"),QString("<p class=\"p3\">"));
    tmp = tmp.replace(QString("[/P3]"),QString("</p>"));

    tmp = tmp.replace(QString("[P4]"),QString("<p class=\"p4\">"));
    tmp = tmp.replace(QString("[/P4]"),QString("</p>"));


    tmp = tmp.replace(QString("[PRE]"), QString("<pre>"));
    tmp = tmp.replace(QString("[/PRE]"), QString("</pre>"));

    /// IMAGE
    tmp = tmp.replace(QString("[IMG]"), QString("<center>"));
    tmp = tmp.replace(QString("[/IMG]"), QString("</center>"));



    tmp = parseFilename(tmp);
    tmp = parseName(tmp);


    tmp = parseAnchor(tmp);
    tmp = parseGotoAnchor(tmp);



    /// Термины проставляем

    QDjangoQuerySet<TermsElement> someTermsElements;


    QList<QString> abbrList;
    QList<QString> descList;

    TermsElement m_re;
    for (int i = 0; i < someTermsElements.size(); ++i) {
        if (someTermsElements.at(i, &m_re)) {
            abbrList.append(m_re.name());
            descList.append(m_re.description());
        }
    }


    for(int i = 0; i < abbrList.size(); i++) {
        if (tmp.indexOf(QString("[TERM]%1[/TERM]").arg(abbrList.at(i)))!=-1) {
            tmp.replace(QString("[TERM]%1[/TERM]").arg(abbrList.at(i)),
                        QString("<abbr title=\"%1\">%2</abbr>  ").arg(descList.at(i)).arg(abbrList.at(i)));
        }
    }

    QDjangoQuerySet<GlossaryElement> someGlossaryElements;
    GlossaryElement m_ge;
    for (int i = 0; i < someGlossaryElements.size(); ++i) {
        if (someGlossaryElements.at(i, &m_ge)) {
            abbrList.append(m_ge.name());
            descList.append(m_ge.description());
        }
    }

    for(int i = 0; i < abbrList.size(); i++) {
        if (tmp.indexOf(QString("[DEFINE]%1[/DEFINE]").arg(abbrList.at(i)))!=-1) {
            tmp.replace(QString("[DEFINE]%1[/DEFINE]").arg(abbrList.at(i)),
                        QString("<abbr title=\"%1\">%2</abbr>  ").arg(descList.at(i)).arg(abbrList.at(i)));
        }
    }


    ///

    if (tmp.indexOf("[GLOSSARY]Глоссарий[/GLOSSARY]")!=-1) {

        QString table = "<h1>Глоссарий</h1><br/><dl>";
        QDjangoQuerySet<GlossaryElement> someGlossaryElements;
        GlossaryElement m_re;
        for (int i = 0; i < someGlossaryElements.size(); ++i) {
            if (someGlossaryElements.at(i, &m_re)) {
                 table += QString("<dt>%1</dt>").arg(m_re.name());
                 table += QString("<dd>%2</dd>").arg(m_re.description());
            }
        }
        table += "</dl>";
        tmp = tmp.replace(QString("[GLOSSARY]Глоссарий[/GLOSSARY]"), table);
    }

    if (tmp.indexOf("[TERMINS]Термины[/TERMINS]")!=-1) {

        QString table = "<h1>Термины</h1><br/><dl class=\"dl-horizontal\">";
        QDjangoQuerySet<TermsElement> someTerminsElements;

        TermsElement m_re;
        for (int i = 0; i < someTerminsElements.size(); ++i) {
            if (someTerminsElements.at(i, &m_re)) {
                  table += QString("<dt>%1</dt>").arg(m_re.name());
                  table += QString("<dd>%2</dd>").arg(m_re.description());

            }
        }
        table += "</dl>";
        tmp = tmp.replace(QString("[TERMINS]Термины[/TERMINS]"), table);
    }
    return tmp;

}


QString DocumentGenerator::parseRequirement(const QString &txt, const QString &type)
{


    QStringList lst = txt.split("\n");
    for (int i = 0; i < lst.size(); i++) {
        QString tmp = lst.at(i);
        QRegularExpressionMatch match;
        if (tmp.indexOf(QRegularExpression(QString("\\[%1:.+\\]").arg(type)), 0, &match) != -1) {
            if (match.hasMatch()) {
                QString find = match.captured(0);
                find = find.replace(QString("["),"");
                find = find.replace(QString("]"),"");
                QStringList tmp2 = find.split(":");
                if (tmp2.size()==2) {
                    QString nfrid = (QString)tmp2.at(1);
                    QString nfrarticle = find;

                    tmp = tmp.replace(QString("[%1]").arg(nfrarticle),
                                      loadText(nfrid));
                }
            }
        }
        lst.removeAt(i);
        lst.insert(i, tmp);
    }



    return lst.join("\n");
}

QString DocumentGenerator::parseAnchor(const QString &txt)
{
    QStringList lst = txt.split("\n");
    for (int i = 0; i < lst.size(); i++) {
        QString tmp = lst.at(i);
        QRegularExpressionMatch match;
        if (tmp.indexOf(QRegularExpression("\\[ANCHOR.+ANCHOR\\]"), 0, &match) != -1) {

            if (match.hasMatch()) {
                QString find = match.captured(0);

                find = find.replace("[ANCHOR]", "");
                find = find.replace("[/ANCHOR]", "");
                find = find.trimmed();

                QString t = QString("<a name=\"%1\"></a>").arg(find);

                tmp = tmp.replace(QString("[ANCHOR]%1[/ANCHOR]").arg(find), t);
            }
        }
        lst.removeAt(i);
        lst.insert(i, tmp);
    }

    return lst.join("\n");
}

QString DocumentGenerator::parseGotoAnchor(const QString &txt)
{
    QStringList lst = txt.split("\n");
    for (int i = 0; i < lst.size(); i++) {
        QString tmp = lst.at(i);
        QRegularExpressionMatch match;
        if (tmp.indexOf(QRegularExpression("\\[GOTO_ANCHR.+GOTO_ANCHR\\]"), 0, &match) != -1) {

            if (match.hasMatch()) {
                QString find = match.captured(0);

                find = find.replace("[GOTO_ANCHR]", "");
                find = find.replace("[/GOTO_ANCHR]", "");
                find = find.trimmed();

                QStringList res = find.split(",");
                QString txt, anchr;
                if (res.size()==2) {
                    txt     = res.at(0);
                    anchr   = res.at(1);

                    txt = txt.replace("{","");
                    txt = txt.replace("}","");

                    anchr = anchr.replace("{","");
                    anchr = anchr.replace("}","");


                    QString t = QString("<a href=\"#%1\">%2</a>").arg(anchr).arg(txt);
                    tmp = tmp.replace(QString("[GOTO_ANCHR]%1[/GOTO_ANCHR]").arg(find), t);
                }
                else {
                }
            }

            lst.removeAt(i);
            lst.insert(i, tmp);
        }
    }

    return lst.join("\n");
}

QString DocumentGenerator::parseFilename(const QString &txt)
{
    QStringList lst = txt.split("\n");
    for (int i = 0; i < lst.size(); i++) {
        QString tmp = lst.takeAt(i);
        QRegularExpressionMatch match;
        if (tmp.indexOf(QRegularExpression("\\[FILENAME.+FILENAME\\]"), 0, &match) != -1) {

            if (match.hasMatch()) {
                QString find = match.captured(0);
                find = find.replace("[FILENAME]", "");
                find = find.replace("[/FILENAME]", "");
                find = find.trimmed();

                QString t = QString("<img src=\"../../images/%1\" class=\"img-rounded\">").arg(find);
                tmp = tmp.replace(QString("[FILENAME]%1[/FILENAME]").arg(find), t);
            }
        }
        lst.insert(i, tmp);
    }

    return lst.join("\n");


}

QString DocumentGenerator::parseName(const QString &txt)
{
    QStringList lst = txt.split("\n");
    for (int i = 0; i < lst.size(); i++) {
        QString tmp = lst.takeAt(i);
        QRegularExpressionMatch match;
        if (tmp.indexOf(QRegularExpression("\\[NAME.+NAME\\]"), 0, &match) != -1) {
            if (match.hasMatch()) {
                QString find = match.captured(0);
                find = find.replace("[NAME]", "");
                find = find.replace("[/NAME]", "");
                find = find.trimmed();

                QString t = QString("<p>%1</p>").arg(find);
                tmp = tmp.replace(QString("[NAME]%1[/NAME]").arg(find), t);
            }
        }
        lst.insert(i, tmp);
    }
    return lst.join("\n");
}







QString DocumentGenerator::parseSpecification()
{
    return parse(loadText("Спецификация требований"));
}

QString DocumentGenerator::parseDescription()
{
    return parse(loadText("Описание ПО"));
}

QString DocumentGenerator::parseUserUsage()
{
    return parse(loadText("Руководство пользователя"));
}



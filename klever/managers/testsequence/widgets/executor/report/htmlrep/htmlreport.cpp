#include "htmlreport.h"
#include <QDebug>
#include <frameWork/cveManager.h>
#include <frameWork/gui/cvegui.h>
#include <frameWork/cve.h>

void HtmlReport::changeLevel(int level)
{
  if (level < 1) current = 1;
  else if (level > current) current++;
  else if (level < current) {
    for (int i = level; i < current; i++)
      counters[i] = 0;
    current = level;
  }
  if (current >= COUNTER_SIZE ) current = COUNTER_SIZE-1;
  counters[current-1]++;
}

QString HtmlReport::getNumber()
{
  QString number;
  for (int i = 0; i < current; i++) {
    number += QString::number(counters[i]) + ".";
  }
  number += "    ";
  return number;
}

HtmlReport::HtmlReport(Type type, QObject *parent) : QObject(parent)
{
  this->type = type;
  Q_UNUSED(parent);
  current = 0;
  for (int i = 0; i < COUNTER_SIZE; i++)
    counters[i] = 0;

  data.appendPlainText("<!DOCTYPE html>\n<html>\n<head>");
  data.appendPlainText("<meta charset='UTF-8'>");

  //стили отображения
  data.appendPlainText("<link rel='stylesheet' href='resources/style.css' "
                       "type='text/css' media='screen'>");
  //стили для подробного отчета.
  data.appendPlainText("<link rel='stylesheet' href='resources/tree.css' "
                       "type='text/css' media='screen'>");;
  //jquery
  data.appendPlainText("<script src='resources/jquery-2.1.4.js'> </script>");
  //jquery-ui
  data.appendPlainText("<script src='resources/jquery-ui.js'> </script>");
  data.appendPlainText("<link rel='stylesheet' href='resources/jquery-ui.css' "
                       "type='text/css'>");
  //скрипт для подробного отчета.
  data.appendPlainText("<script src='resources/tree.js'> </script></head>");

  data.appendPlainText("<body><div class='PageContainer'>");
}

void HtmlReport::addElement(QString result, QString text, QString duration)
{
  data.appendPlainText("<tr>");
  if (result == "Информация")
    data.appendPlainText("<td class='result " + infoClass + "'><nobr><img src='resources/images/info.png'>Успешно</nobr></td>");
  else if (result == "Ошибка")
    data.appendPlainText("<td class='result " + errorClass + "'><nobr><img src='resources/images/error.png'>Ошибка</nobr></td>");
  else if (result == "Предупреждение")
    data.appendPlainText("<td class='result " + warnClass + "'><nobr><img src='resources/images/warn.png'>Предупреждение</nobr></td>");
  data.appendPlainText("<td class='text'>" + text + "</td>");
  data.appendPlainText("<td class='date'>" + duration + "</td>");

  data.insertPlainText("</tr>");
}

void HtmlReport::createDocument(QString filename, bool isNeedOpen, bool isNeedCopyJsFiles)
{
  if (!filename.endsWith(".html")) {
    filename += ".html";
  }

  QFileInfo fileinfo(filename);
  QString filepath = fileinfo.absolutePath();

  if (type==SHORT_REPORT) {
    data.appendPlainText("</table>");
  }
  if (type==FULL_REPORT) {

    while (current) {
      data.appendPlainText("</li></ul>\n");
      current--;
    }

    data.appendPlainText("</div>");
  }
  data.appendPlainText("<br><hr class='Footer'><p class='Footer'>АО Ижевский Радиозавод</p>");
  data.appendPlainText("</div></body>\n</html>");

  QFile file(filename);
  if (!file.open(QIODevice::WriteOnly)) {
    return;
  }
  QTextStream out(&file);

  out << data.toPlainText();

  if (isNeedOpen) {
    QDesktopServices::openUrl(QUrl(QUrl::fromLocalFile(fileinfo.absoluteFilePath())));
  }

  if (isNeedCopyJsFiles) {
    bool writeCheck = true;
    //.css and .js
    writeCheck &= writeFile(filepath, "/resources/style.css");
    writeCheck &= writeFile(filepath, "/resources/jquery-ui.css");
    writeCheck &= writeFile(filepath, "/resources/jquery-ui.js");
    writeCheck &= writeFile(filepath, "/resources/tree.js");
    writeCheck &= writeFile(filepath, "/resources/tree.css");
    writeCheck &= writeFile(filepath,"/resources/jquery-2.1.4.js");

    //images
    writeCheck &= writeFile(filepath, "/resources/images/ui-bg_highlight-soft_75_ffe45c_1x100.png");
    writeCheck &= writeFile(filepath, "/resources/images/ui-bg_diagonals-thick_18_b81900_40x40.png");
    writeCheck &= writeFile(filepath, "/resources/images/expand_leaf.gif");
    writeCheck &= writeFile(filepath, "/resources/images/expand_plus.gif");
    writeCheck &= writeFile(filepath, "/resources/images/expand_minus.gif");
    writeCheck &= writeFile(filepath, "/resources/images/expand_loading.gif");
    writeCheck &= writeFile(filepath, "/resources/images/i.gif");
    writeCheck &= writeFile(filepath, "/resources/images/i_half.gif");
    writeCheck &= writeFile(filepath, "/resources/images/warn.png");
    writeCheck &= writeFile(filepath, "/resources/images/error.png");
    writeCheck &= writeFile(filepath, "/resources/images/info.png");
    writeCheck &= writeFile(filepath, "/resources/images/logo.png");

    if (!writeCheck) {
      logWarning(this,QString("Ошибка при копировании файлов"));
    }
  }

  file.close();
}

void HtmlReport::addHeader(QString text)
{
  if (type == SHORT_REPORT) {
    data.appendPlainText("<p></p><center><table width='100%'>");
    data.appendPlainText("<tr><td class='header' colspan='" +
                         QString::number(COLNUM) + "'>" + text + "<hr></td></tr>");
    data.appendPlainText("<tr>");
    data.appendPlainText("<th class='TableHeader ui-corner-all'>Результат</th>");
    data.appendPlainText("<th class='TableHeader ui-corner-all'>Название теста</th>");
//    data.appendPlainText("<th class='TableHeader ui-corner-all' width='15%'>Описание</th>");
    data.appendPlainText("<th class='TableHeader ui-corner-all'>Длительность</th>");
    data.appendPlainText("</tr>");
  }
  if (type == FULL_REPORT) {
    data.appendPlainText("<p class='header'>" + text + "<hr></p>");
    data.appendPlainText("<table width='100%'><tr>");
    data.appendPlainText("<th class='TableHeader ui-corner-all' width='15%'>Результат</th>");
    data.appendPlainText("<th class='TableHeader ui-corner-all' colspan='2'>Название теста</th>");
    data.appendPlainText("<th class='TableHeader ui-corner-all' width='15%'>Описание</th>");
    data.appendPlainText("<th class='TableHeader ui-corner-all' width='15%'>Длительность</th>");
    data.appendPlainText("</tr></table>");
    data.appendPlainText("<div onclick='tree_toggle(arguments[0])'>");

  }
}

void HtmlReport::addInformation(QString testname, QString project, QString reciever, QString date)
{
  QString sn = Cve::instance().getParameterValue(QString("/serialNumber"), QString("999999"));

  data.appendPlainText("<table align='center' class='info'>");
  data.appendPlainText("<tr class='logo'><td rowspan='6'><img src='resources/images/logo.png'></td></tr>");
  data.appendPlainText("<tr class='info'><td>Название тестовой последовательности: </td><td>" + testname + "</td></tr>\n");
  data.appendPlainText("<tr class='info'><td>Изделие: </td><td>" + project + "</td></tr>\n");
  data.appendPlainText("<tr class='info'><td>Название сессии: </td><td>" + reciever + "</td></tr>\n");
  data.appendPlainText("<tr class='info'><td>Время проведения испытания: </td><td>" + date + "</td><td></td></tr>\n");
  data.appendPlainText("<tr class='info'><td>Серийный номер изделия: </td><td>" + sn + "</td><td></td></tr>\n");
  data.appendPlainText("</table>");
}

void HtmlReport::addToTree(int level, QString result, QString text, QString description, QString duration, bool hasChilds)
{
  //старый уровень вложенности.
  int old = current;
  changeLevel(level);

  //закрываем <li> и <ul>, если идем на уровень выше.
  if (current < old ) {
    for (int i = 0; i < old-current; i++) {
      data.appendPlainText("</li></ul>");
    }
  }

  //закрываем <li>, если не углубляемся в списке.
  if (current == old ) {
    data.appendPlainText("</li>");
  }

  //если углубляемся, создаем новый список, добавлением <ul>
  if (current > old) {
    data.appendPlainText("<ul class='Container'>\n");
  }
  //создаем элемент списка
  data.appendPlainText("<li class='Node ");

  //добавляем класс IsRoot, если относится к верхнему уровню.
  if (current == 1) {
    data.appendPlainText("IsRoot ");
  }

  //если есть элементы, то будет свернут.
  if (hasChilds) {
    data.appendPlainText("ExpandClosed'>");
  }
  //если не имеет потомков, помечаем как лист.
  else {
    data.appendPlainText("ExpandLeaf'>");
  }
  data.appendPlainText("<div class='Expand'></div>");

  //добавляем данные.
  data.appendPlainText("<div class='Content'>");
  data.appendPlainText("<table table width='100%'><tr>");

  if (result == "Информация")
    data.appendPlainText("<td class='result " + infoClass + "'><nobr><img src='resources/images/info.png'>Успешно</nobr></td>");
  else if (result == "Ошибка")
    data.appendPlainText("<td class='result " + errorClass + "'><nobr><img src='resources/images/error.png'>Ошибка</nobr></td>");
  else if (result == "Предупреждение")
    data.appendPlainText("<td class='result " + warnClass + "'><nobr><img src='resources/images/warn.png'>Предупреждение</nobr></td>");

  data.appendPlainText("<td class='text'>" + text + "</td>");
  data.appendPlainText("<td class='text'>" + description + "</td>");
  data.appendPlainText("<td class='date'>" + duration + "</td>");
  data.appendPlainText("</tr></table>");

  data.appendPlainText("</div>");
}

bool HtmlReport::writeFile(QString filepath, QString filename)
{
  QDir dir;
  dir.mkpath(filepath + "/resources/images");
  bool success = true;

  QFile sourceFile(":htmlrep/htmlrep/" + filename);
  QFile destFile(filepath + filename);
  success &= sourceFile.open(QFile::ReadOnly);
  success &= destFile.open(QFile::WriteOnly);
  success &= destFile.write( sourceFile.readAll() ) >= 0;
  sourceFile.close();
  destFile.close();

  return success;
}

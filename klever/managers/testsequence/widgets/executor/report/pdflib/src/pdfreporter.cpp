#include "pdfreporter.h"

void PdfReporter::changeLevel(int level)
{
  if (level < 1) current = 1;
  else if (level > current) current++;
  else if (level < current) {
    for (int i = level; i < current; i++)
      counters[i] = 0;
    current = level;
  }
  counters[current-1]++;
}

QString PdfReporter::getNumber()
{
  QString number;
  for (int i = 0; i < current; i++) {
    number += QString::number(counters[i]) + ".";
  }
  number += "    ";
  return number;
}

PdfReporter::PdfReporter()
{
  //default values
  report = new QtRPT(this);
  current = 0;
  for (int i = 0; i < 50; i++)
    counters[i] = 0;

  //Make a report page
  RptPageObject *page = new RptPageObject();
  page->pageNo=0;
  report->pageList.append(page); //Append page to the report

  createDataFields();

  //connectors
  connect(report, SIGNAL(setField(RptFieldObject &)), SLOT(setField(RptFieldObject &)));
}

PdfReporter::~PdfReporter()
{

}

void PdfReporter::createDataFields()
{
  //Make a report page
  RptPageObject *dataPage = new RptPageObject();
  dataPage->pageNo=1;
  report->pageList.append(dataPage); //Append page to the report

  //Make a DataBand
  RptBandObject *dataBand = new RptBandObject();
  dataBand->name = "DataBand";
//  dataBand->height = 30;
  dataBand->type = MasterData;
  //Append band to the page
  dataPage->addBand(dataBand);

  RptFieldObject *text = new RptFieldObject();
  text->fieldType = Text;
  text->font.setPointSize(12);
  text->aligment  = Qt::AlignLeft;
  text->name = "BodyText";

  dataBand->addField(text);

  //Make a PageFooterBand
  RptBandObject *footer = new RptBandObject();
  footer->name = "PageFooterBand";
  footer->height = 50;
  footer->type = PageFooter;
  dataPage->addBand(footer); //Append band to the page

  RptFieldObject *pf = new RptFieldObject();
  pf->name = "PageFooter";
  pf->fieldType = Text;
  pf->aligment  = Qt::AlignRight | Qt::AlignBottom;
  pf->font.setBold(true);
  pf->rect.setTop(0);
  pf->rect.setLeft(570);
  pf->rect.setHeight(30);
  pf->rect.setWidth(150);
  pf->value = "<Page>";
  footer->addField(pf);  //Append field to the PageFooterBand
}

void PdfReporter::createTitle(QString test, QString sender, QString reciever)
{
  //Make a ReportTitleBand
  RptBandObject *titleBand = new RptBandObject();
  titleBand->name = "ReportBand";
  titleBand->height = 1400;
  titleBand->type = ReportTitle;
  report->pageList.at(0)->addBand(titleBand); //Append band to the page

  //make a field
  RptFieldObject *title = new RptFieldObject();
  title->name = "title";
  title->fieldType = Text;
  title->font.setBold(true);
  title->font.setPointSize(14);
  title->rect.setTop(0);
  title->rect.setLeft(0);
  title->rect.setHeight(350);
  title->rect.setWidth(700);
  title->aligment = Qt::AlignCenter | Qt::AlignBottom;
  title->value    = "ОТЧЁТ";
  title->textWrap = 1;
  titleBand->addField(title);

  //Make a field
  RptFieldObject *testname = new RptFieldObject();
  testname->name = "TestName";
  testname->fieldType = Text;
  testname->rect.setTop(0);
  testname->rect.setLeft(0);
  testname->rect.setHeight(390);
  testname->rect.setWidth(700);
  testname->font.setBold(false);
  testname->font.setPointSize(12);
  testname->aligment = Qt::AlignCenter | Qt::AlignBottom;
  testname->value = "Выполнения теста: " + test;
  titleBand->addField(testname); //Append field to the ReportTitleBand

  //Make a field
  RptFieldObject *senderName = new RptFieldObject();
  senderName->name = "SenderName";
  senderName->fieldType = Text;
  senderName->rect.setTop(300);
  senderName->rect.setLeft(500);
  senderName->rect.setHeight(450);
  senderName->rect.setWidth(700);
  senderName->font.setBold(false);
  senderName->font.setPointSize(12);
  senderName->aligment = Qt::AlignLeft | Qt::AlignBottom;
  senderName->value = "Отправитель " + sender;
  titleBand->addField(senderName); //Append field to the ReportTitleBand

  //Make a field
  RptFieldObject *recieverName = new RptFieldObject();
  recieverName->name = "RecieverName";
  recieverName->fieldType = Text;
  recieverName->rect.setTop(300);
  recieverName->rect.setLeft(500);
  recieverName->rect.setHeight(480);
  recieverName->rect.setWidth(700);
  recieverName->font.setBold(false);
  recieverName->font.setPointSize(12);
  recieverName->aligment = Qt::AlignLeft | Qt::AlignBottom;
  recieverName->value = "Приёмщик " + reciever;
  titleBand->addField(recieverName); //Append field to the ReportTitleBand

  //Make a field
  RptFieldObject *footer = new RptFieldObject();
  footer->name = "TitleFooter";
  footer->fieldType = Text;
  footer->rect.setTop(1000);
  footer->rect.setLeft(0);
  footer->rect.setHeight(100);
  footer->rect.setWidth(700);
  footer->font.setBold(false);
  footer->font.setPointSize(12);
  footer->aligment = Qt::AlignCenter | Qt::AlignBottom;
  footer->value = "Ижевск\n2015";
  titleBand->addField(footer); //Append field to the ReportTitleBand
}

void PdfReporter::addElement(int level, QString text)
{
  // изменяем уровень
  changeLevel(level);
  // добавляем элемент в список.
  data.append(qMakePair(level, getNumber() + text));
}

void PdfReporter::createDocument(QString filename)
{
  if (!filename.endsWith(".pdf")) {
    filename += ".pdf";
  }
  report->recordCount << 1;
  report->recordCount << data.size();
//  report->printExec(); // предпросмотр печати.
  report->printPDF(filename, true);
}

void PdfReporter::setField(RptFieldObject &fieldObject)
{
  // Установка прозрачного фона для полей.
  fieldObject.setDefaultBackgroundColor(QColor(0, 0, 0, 0));

  // Установка белых рамок вокруг полей.
  fieldObject.borderLeft = Qt::white;
  fieldObject.borderRight = Qt::white;
  fieldObject.borderBottom = Qt::white;
  fieldObject.borderTop = Qt::white;

  // Заполнение отчета.
  if (fieldObject.name == "BodyText") {
    fieldObject.autoHeight = 1;
    fieldObject.textWrap = 1;
    fieldObject.rect.setWidth(750 - 20*data.at(fieldObject.recNo()).first);
    fieldObject.parentBand->width = 800;
    fieldObject.rect.setLeft(20*data.at(fieldObject.recNo()).first);
    fieldObject.value = data.at(fieldObject.recNo()).second;
  }
}


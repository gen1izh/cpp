#include "loggerform.h"
#include "ui_loggerform.h"

LoggerForm::LoggerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoggerForm)
{
    ui->setupUi(this);

}

LoggerForm::~LoggerForm()
{
    delete ui;
}

void LoggerForm::appendText(const QString &txt)
{

    if (ui->logBrowser->document()->lineCount() > 100) {
        QTextCursor cur(ui->logBrowser->document());
        cur.movePosition(QTextCursor::Start);
        cur.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
        cur.removeSelectedText();
    }

    ui->logBrowser->append(txt);
}

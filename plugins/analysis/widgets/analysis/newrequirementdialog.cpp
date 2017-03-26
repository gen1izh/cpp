#include "newrequirementdialog.h"
#include "ui_newrequirementdialog.h"
#include "../../../_shared/db/models/requirementelement.h"
#include "../../../_shared/db/models/architectelement.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QBuffer>
#include <QDir>
#include <QClipboard>

#include <frameWork/base.h>
#include <library/orm/db/QDjangoQuerySet.h>


NewRequirementDialog::NewRequirementDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewRequirementDialog)
{
    ui->setupUi(this);
}

NewRequirementDialog::~NewRequirementDialog()
{
    delete ui;
}

/*
 *
 */
void NewRequirementDialog::showEvent(QShowEvent *event)
{
    Q_UNUSED(event)

//    QDjango::setDatabase(*Core::Base::instance().sessionDatabase());
//    QDjango::registerModel<ArchitectElement>();
//    QDjango::createTables();

    ui->componentBox->clear();
    QDjango::setDatabase(*Core::Base::instance().sessionDatabase());
    QDjangoQuerySet<ArchitectElement> someArchitectElements;

    ui->componentBox->clear();
    // retrieve usernames and passwords for matching users as maps
    QList<QVariantMap> propertyMaps = someArchitectElements.values(QStringList() << "id" << "type" << "name");
    foreach (const QVariantMap &propertyList, propertyMaps) {
        QString tmp = QString("%1:%2%3-%4").arg(propertyList["id"].toString())
                .arg(propertyList["type"].toString())
                .arg(propertyList["id"].toString())
                .arg(propertyList["name"].toString());
        ui->componentBox->addItem(tmp);
    }
}

void NewRequirementDialog::on_componentBox_currentTextChanged(const QString &arg1)
{
}

/*
 * Создание нового требования
 */
void NewRequirementDialog::on_buttonBox_accepted()
{
    // Получаем идентификатор элемента архитектуры
    QString architectElementId = ui->componentBox->currentText().split(":").at(0);

    bool ok;
    QDjango::setDatabase(*Core::Base::instance().sessionDatabase());
    QDjangoQuerySet<ArchitectElement> someArchitectElements;
    someArchitectElements = someArchitectElements.filter(QDjangoWhere("id", QDjangoWhere::Equals, architectElementId.toInt(&ok,10)));
    ArchitectElement architectElementCurrent;
    if (someArchitectElements.size()>0) {
        someArchitectElements.at(0, &architectElementCurrent);
    }

    RequirementElement requirementElement;
    requirementElement.setType(ui->requirementComboBox->currentText());
    requirementElement.setName(ui->nameEdit->text());
    requirementElement.setComponent(&architectElementCurrent);

    requirementElement.save();
}



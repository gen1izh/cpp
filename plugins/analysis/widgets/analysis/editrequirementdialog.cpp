#include "editrequirementdialog.h"
#include "ui_editrequirementdialog.h"

#include <frameWork/base.h>

#include <library/orm/db/QDjangoQuerySet.h>
#include "../../../_shared/db/models/requirementelement.h"
#include "../../../_shared/db/models/architectelement.h"

EditRequirementDialog::EditRequirementDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditRequirementDialog)
{
    ui->setupUi(this);
}

EditRequirementDialog::~EditRequirementDialog()
{
    delete ui;
}

/*
 *
 */
void EditRequirementDialog::showEvent(QShowEvent *event)
{
    Q_UNUSED(event)

    QString id = Core::Base::instance().getParameterValue("EDIT_REQUIEREMENT_ID",QString(""));

    bool ok;

    QDjango::setDatabase(*Core::Base::instance().sessionDatabase());

    ui->componentBox->clear();
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


    QDjangoQuerySet<RequirementElement> someRequirementElements;

    someRequirementElements = someRequirementElements.filter(QDjangoWhere("id", QDjangoWhere::Equals,
                                                                          id.toInt(&ok,10)));
    RequirementElement requirementElementCurrent;
    if (someRequirementElements.size()>0) {
        someRequirementElements.at(0, &requirementElementCurrent);

        ui->requirementComboBox->setCurrentText(requirementElementCurrent.type());
        ui->requirementComboBox->setEnabled(false);
        ui->nameEdit->setText(requirementElementCurrent.name());
    }

}


/*
 *
 */
void EditRequirementDialog::on_buttonBox_accepted()
{
    QDjango::setDatabase(*Core::Base::instance().sessionDatabase());
    QDjangoQuerySet<RequirementElement> someRequirementElements;
    QString id = Core::Base::instance().getParameterValue("EDIT_REQUIEREMENT_ID",QString(""));
    bool ok;
    someRequirementElements = someRequirementElements.filter(QDjangoWhere("id", QDjangoWhere::Equals,
                                                                          id.toInt(&ok,10)));
    RequirementElement requirementElementCurrent;
    if (someRequirementElements.size()>0) {
        someRequirementElements.at(0, &requirementElementCurrent);

        requirementElementCurrent.setType(ui->requirementComboBox->currentText());
        requirementElementCurrent.setName(ui->nameEdit->text());
        requirementElementCurrent.setComponent(NULL); // TODOЖ Сделать поиск

        requirementElementCurrent.save();

    }

}

void EditRequirementDialog::on_buttonBox_rejected()
{
    // ...
}

void EditRequirementDialog::on_componentBox_currentTextChanged(const QString &arg1)
{
}

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

    QDjango::setDatabase(*Core::Base::instance().database());
    QDjango::registerModel<ArchitectElement>();
    QDjango::createTables();

    ui->requirementComboBox->setCurrentText(
                Core::Base::instance().getParameterValue("EDIT_REQUIEREMENT_TYPE",QString("")));
    ui->requirementComboBox->setEnabled(false);
    ui->nameEdit->setText(
                Core::Base::instance().getParameterValue("EDIT_REQUIEREMENT_ARTICLE",QString("")));

    ui->componentBox->clear();
    ArchitectElement ae;
    QDjangoQuerySet<ArchitectElement> someArchitectElements;

    // Поиск системы
    for (int i = 0; i < someArchitectElements.size(); ++i) {
        if (someArchitectElements.at(i, &ae)) {

            if (ae.type() == "Компонент") {
                ui->componentBox->addItem(ae.article());
            }
        }
    }

}


/*
 *
 */
void EditRequirementDialog::on_buttonBox_accepted()
{
    QDjango::setDatabase(*Core::Base::instance().database());
    QDjango::registerModel<RequirementElement>();
    QDjango::createTables();
    QDjangoQuerySet<RequirementElement> someRequirementElements;

    bool ok;
    int value = QString(Core::Base::instance().getParameterValue("EDIT_REQUIEREMENT_ID",QString("0"))).toInt(&ok,10);

    RequirementElement m_re;
    for (int i = 0; i < someRequirementElements.size(); ++i) {
        if (someRequirementElements.at(i, &m_re)) {
            if (m_re.rtype() == Core::Base::instance().getParameterValue("EDIT_REQUIEREMENT_TYPE",QString(""))) {
                if (m_re.identificator() == value) {
                    m_re.setName(ui->nameEdit->text());
                    m_re.setComponent(ui->componentBox->currentText());
                    m_re.setModule(ui->moduleBox->currentText());

                    m_re.save();
                    break;
                }
            }
        }
    }

}

void EditRequirementDialog::on_buttonBox_rejected()
{
    // ...
}

void EditRequirementDialog::on_componentBox_currentTextChanged(const QString &arg1)
{
    QDjango::setDatabase(*Core::Base::instance().database());
    QDjango::registerModel<ArchitectElement>();
    QDjango::createTables();
    ui->moduleBox->clear();

    ArchitectElement ae;
    QDjangoQuerySet<ArchitectElement> someArchitectElements;

    // Поиск системы
    for (int i = 0; i < someArchitectElements.size(); ++i) {
        if (someArchitectElements.at(i, &ae)) {
            if (ae.type() == "Модуль") {
                if (ae.parentElementArticle()== arg1) {
                    ui->moduleBox->addItem(ae.article());
                }
            }
        }
    }
}

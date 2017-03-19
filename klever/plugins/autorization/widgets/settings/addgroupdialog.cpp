#include "addgroupdialog.h"
#include "ui_addgroupdialog.h"
#include <QRegExp>
#include <QRegExpValidator>
#include <library/orm/db/QDjangoQuerySet.h>
#include <frameWork/base.h>
#include <library/message/messagelibrary.h>

AddGroupDialog::AddGroupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addGroupDialog)
{
    ui->setupUi(this);
}

void AddGroupDialog::showEvent(QShowEvent *) {

    QRegExp rx("^(\\w+\\s+)$");
    QValidator *validator = new QRegExpValidator(rx, this);

    ui->groupEdit->setValidator(validator);

    // Заполнение раскрывающегося списка групп всеми возможными группами
    ui->parentBox->clear();

    QDjango::setDatabase(*Core::Base::instance().database());
    QDjango::registerModel<Group>();
    QDjango::createTables();
    QDjangoQuerySet<Group> groups;
    ui->parentBox->addItem("");
    QList<QVariantMap> propertyMaps = groups.values(QStringList() << "name" << "role"<< "description" << "parent");
    foreach (const QVariantMap &propertyMap, propertyMaps) {
        ui->parentBox->addItem(propertyMap["name"].toString());
    }

}

AddGroupDialog::~AddGroupDialog()
{
    delete ui;
}

QString AddGroupDialog::name() const
{
    return ui->groupEdit->text();
}

QString AddGroupDialog::parent() const
{
    return ui->parentBox->currentText();
}

QString AddGroupDialog::description() const
{
    return ui->descriptionEdit->toPlainText();
}

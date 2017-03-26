#include "bf_analizeform.h"
#include "ui_bf_analizeform.h"

#include <QDebug>
#include <QMenu>
#include <QMessageBox>

#include <QCryptographicHash>

#include <QTimer>

#include <library/orm/db/QDjangoQuerySet.h>
#include "../../../_shared/db/models/requirementelement.h"
#include <library/message/messagelibrary.h>

#include <frameWork/base.h>

#include "QtSql/QSqlDatabase"
#include "QSqlError"


BF_AnalizeForm::BF_AnalizeForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BF_AnalizeForm)
{
    ui->setupUi(this);

    createActions();
    createDialogs();
    createConnectors();

    Core::Base::instance().setParameterValue("NAME", QString(""));
}

void BF_AnalizeForm::showEvent(QShowEvent *event) {
    on_updateButton_clicked();
}


BF_AnalizeForm::~BF_AnalizeForm()
{
    delete ui;
}

/*
 *  Создает соединения.
 */
void BF_AnalizeForm::createConnectors()
{
    QObject::connect( m_openEditorAction,
                      SIGNAL(triggered(bool)),
                      this,
                      SLOT(on_onEditorButton_clicked()));
}

/*
 * Создает действия.
 */
void BF_AnalizeForm::createActions()
{
    // анализ
    m_openEditorAction = new QAction("Открыть редактор");
}

/*
 * Создание диалоговых окон создания и редактирования элемента требования.
 */
void BF_AnalizeForm::createDialogs()
{
    m_requirementDialog     = new NewRequirementDialog();
    m_editRequirementDialog = new EditRequirementDialog();
}

/*
 * Чтение всех требований.
 */
void BF_AnalizeForm::readRequirements() {
    fillRequirements(QString("UR"), ui->userRequirementListWidget);
    fillRequirements(QString("FR"), ui->funcRequirementListWidget);
    fillRequirements(QString("NFR"), ui->nofuncRequirementListWidget);
}

/*
 * Обновить перечень требований.
 */
void BF_AnalizeForm::on_updateButton_clicked()
{
    readRequirements();
}

/*
 * Чтение и подгрузка из БД требований.
 */
void BF_AnalizeForm::fillRequirements(const QString &type, QListWidget *lwgt) {

    lwgt->clear();

    QDjango::setDatabase(*Core::Base::instance().sessionDatabase());
    QDjangoQuerySet<RequirementElement> someRequirementElements;
    someRequirementElements = someRequirementElements.filter(
                QDjangoWhere("type", QDjangoWhere::Equals, type));

    // retrieve usernames and passwords for matching users as maps
    QList<QVariantMap> propertyMaps = someRequirementElements.values(
                QStringList() << "id" << "type" << "name");
    foreach (const QVariantMap &propertyList, propertyMaps) {
      QString tmp = QString("%1:%2%3-%4")
              .arg(propertyList["id"].toString())
              .arg(propertyList["type"].toString())
              .arg(propertyList["id"].toString())
              .arg(propertyList["name"].toString());
      lwgt->addItem(tmp);
    }
}

/*
 * Создание нового требования.
 */
void BF_AnalizeForm::openRequirementDialog()
{
    if (m_requirementDialog->exec() == QDialog::Accepted) {
        readRequirements();
    }
}

/*
 * Слот открытия редактора.
 */
void BF_AnalizeForm::on_onEditorButton_clicked()
{
    QString requirementName = Core::Base::instance().getParameterValue("NAME", QString(""));

    if (requirementName.isEmpty()) {
        messageLibrary msg;
        msg.createWarnMessage("Предупреждение", "Не выбран ни один элемент. Выберите что хотите отредактировать!");
    }
    else {
        Core::Base::instance().setParameterValue("DOCTYPE", "ТРЕБОВАНИЕ");
        emit openTexteditor();
    }
}

void BF_AnalizeForm::on_requirementsTab_currentChanged(int index)
{
    controlAccess(DEFAULT);

    QString text = ui->requirementsTab->tabText(index);

    if (text=="Видение") {
        controlAccess(VISION);
    }

    if (text=="Общие требования") {
        controlAccess(COMMON_REQUIREMENTS);
    }

    if (text=="Пользовательские требования"){
        controlAccess(USER_REQUIREMENTS);
    }

    if (text=="Функциональные требования"){
        controlAccess(FUNC_REQUIREMENTS);
    }

    if (text=="Нефункциональные требования"){
        controlAccess(NOFUNC_REQUIREMENTS);
    }
}

/*
 *
 */
void BF_AnalizeForm::controlAccess(ANALYZE_TYPE val) {

    switch (val) {
        case VISION:
        case COMMON_REQUIREMENTS:
            if (Core::Base::instance().getParameterValue("NAME", QString(""))!="") {
                ui->onEditorButton->setEnabled(true);
            }
            else {
                ui->onEditorButton->setEnabled(false);
            }

            ui->updateButton->setEnabled(true);
            ui->editButton->setEnabled(false);
            ui->deleteButton->setEnabled(false);
            ui->addButton->setEnabled(true);
            break;

        case USER_REQUIREMENTS:
        case FUNC_REQUIREMENTS:
        case NOFUNC_REQUIREMENTS:
            if (Core::Base::instance().getParameterValue("NAME", QString(""))!="") {
                ui->onEditorButton->setEnabled(true);
            }
            else {
                ui->onEditorButton->setEnabled(false);
            }

            ui->updateButton->setEnabled(true);
            ui->editButton->setEnabled(true);
            ui->deleteButton->setEnabled(true);
            ui->addButton->setEnabled(true);
            break;

        default:
            if (Core::Base::instance().getParameterValue("NAME", QString(""))!="") {
                ui->onEditorButton->setEnabled(true);
            }
            else {
                ui->onEditorButton->setEnabled(false);
            }
            ui->onEditorButton->setEnabled(false);
            ui->updateButton->setEnabled(false);
            ui->editButton->setEnabled(false);
            ui->deleteButton->setEnabled(false);
            ui->addButton->setEnabled(true);
            break;
    }
}

/*
 *
 */
void BF_AnalizeForm::on_addButton_clicked()
{
    openRequirementDialog();
}

/*
 *
 */
void BF_AnalizeForm::on_deleteButton_clicked()
{
    QString requirementName = Core::Base::instance().getParameterValue("NAME", QString(""));

    if (requirementName.isEmpty()) {
        messageLibrary msg;
        msg.createWarnMessage("Предупреждение", "Не выбран ни один элемент. Выберите что хотите удалить!");
    }
    else {
        // Получаем идентификатор элемента требования
        QString requirementElementId = requirementName.split(":").at(0);

        QDjango::setDatabase(*Core::Base::instance().sessionDatabase());


        bool ok;
        QDjangoQuerySet<RequirementElement> someRequirementElements;
        someRequirementElements = someRequirementElements.filter(
                    QDjangoWhere("id", QDjangoWhere::Equals, requirementElementId.toInt(&ok,10)));

        RequirementElement requirementElement;

        if (someRequirementElements.size() > 0) {
            someRequirementElements.at(0, &requirementElement);
            requirementElement.remove();
        }

        readRequirements();
    }
}

/*
 *
 */
void BF_AnalizeForm::on_editButton_clicked()
{
    QString requirementName = Core::Base::instance().getParameterValue("NAME", QString(""));

    if (requirementName.isEmpty()) {
        messageLibrary msg;
        msg.createWarnMessage("Предупреждение", "Не выбран ни один элемент. Выберите что хотите редактировать!");
    }
    else {
        // Получаем идентификатор элемента требования
        QString requirementElementId = requirementName.split(":").at(0);
        Core::Base::instance().setParameterValue("EDIT_REQUIEREMENT_ID", requirementElementId);
        int result = m_editRequirementDialog->exec();
        if (result == QDialog::Accepted) {
            readRequirements();
        }
    }
}

void BF_AnalizeForm::on_visionListWidget_clicked(const QModelIndex &index)
{
    QString hash = QString(QCryptographicHash::hash(index.data().toByteArray(), QCryptographicHash::Sha1).toHex());
    Core::Base::instance().setParameterValue("UID", hash);
    Core::Base::instance().setParameterValue("NAME", index.data().toString());
    ui->onEditorButton->setEnabled(true);
}

void BF_AnalizeForm::on_userRequirementListWidget_clicked(const QModelIndex &index)
{
    QString hash = QString(QCryptographicHash::hash(index.data().toByteArray(), QCryptographicHash::Sha1).toHex());
    Core::Base::instance().setParameterValue("UID", hash);
    Core::Base::instance().setParameterValue("NAME", index.data().toString());
    ui->onEditorButton->setEnabled(true);
}

void BF_AnalizeForm::on_funcRequirementListWidget_clicked(const QModelIndex &index)
{
    QString hash = QString(QCryptographicHash::hash(index.data().toByteArray(), QCryptographicHash::Sha1).toHex());
    Core::Base::instance().setParameterValue("UID", hash);
    Core::Base::instance().setParameterValue("NAME", index.data().toString());
    ui->onEditorButton->setEnabled(true);
}

void BF_AnalizeForm::on_nofuncRequirementListWidget_clicked(const QModelIndex &index)
{
    QString hash = QString(QCryptographicHash::hash(index.data().toByteArray(), QCryptographicHash::Sha1).toHex());
    Core::Base::instance().setParameterValue("UID", hash);
    Core::Base::instance().setParameterValue("NAME", index.data().toString());
    ui->onEditorButton->setEnabled(true);
}

void BF_AnalizeForm::on_commonRequirementListWidget_clicked(const QModelIndex &index)
{
    QString hash = QString(QCryptographicHash::hash(index.data().toByteArray(), QCryptographicHash::Sha1).toHex());
    Core::Base::instance().setParameterValue("UID", hash);
    Core::Base::instance().setParameterValue("NAME", index.data().toString());
    ui->onEditorButton->setEnabled(true);
}

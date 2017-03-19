#include "bf_analizeform.h"
#include "ui_bf_analizeform.h"

#include <QDebug>
#include <QMenu>
#include <QMessageBox>

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

    QTimer::singleShot(1000, this, SLOT(on_updateButton_clicked()));

    ui->analyzeTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->analyzeTreeWidget->setColumnWidth(0, 300);
}

BF_AnalizeForm::~BF_AnalizeForm()
{
    delete ui;
}

void BF_AnalizeForm::createConnectors()
{
    // анализ
    QObject::connect( ui->analyzeTreeWidget,
                      SIGNAL(customContextMenuRequested(QPoint)),
                      this,
                      SLOT(onContextAnalyzeTreeMenuRequest(QPoint)));

    QObject::connect( m_openEditorAction,
                      SIGNAL(triggered(bool)),
                      this,
                      SLOT(on_onEditorButton_clicked()));
}

void BF_AnalizeForm::createActions()
{
    // анализ
    m_openEditorAction = new QAction("Открыть редактор");
}


/*
 * Создание контекстного меню для дерева Анализ.
 */
void BF_AnalizeForm::onContextAnalyzeTreeMenuRequest(QPoint point)
{
}


void BF_AnalizeForm::on_updateButton_clicked()
{
    QList<QTreeWidgetItem*> reqItem;
    reqItem = ui->analyzeTreeWidget->findItems("Пользовательские требования",
                                               Qt::MatchRecursive);
    fillRequirements(QString("ПТ"), reqItem.at(0));
    reqItem = ui->analyzeTreeWidget->findItems("Функциональные требования",
                                               Qt::MatchRecursive);
    fillRequirements(QString("ФТ"), reqItem.at(0));
    reqItem = ui->analyzeTreeWidget->findItems("Нефункциональные требования",
                                          Qt::MatchRecursive);
    fillRequirements(QString("НФТ"), reqItem.at(0));
}


/*
 *
 */
void BF_AnalizeForm::openRequirementDialog()
{

    QTreeWidgetItem *reqItem;

    QString currItem = ui->analyzeTreeWidget->currentItem()->text(0);

    if (currItem == "Пользовательские требования") {
        Core::Base::instance().setParameterValue("RTYPE","ПТ");
    }
    else if (currItem == "Функциональные требования") {
        Core::Base::instance().setParameterValue("RTYPE","ФТ");
    }
    else if (currItem == "Нефункциональные требования") {
        Core::Base::instance().setParameterValue("RTYPE","НФТ");
    }
    else {
        QMessageBox msgBox;
        msgBox.setText("Тип требования неверен!");
        msgBox.exec();
    }

    // reqItem = ui->analyzeTreeWidget->findItems(currItem, Qt::MatchRecursive);

    reqItem = ui->analyzeTreeWidget->currentItem();

    if (m_requirementDialog->exec() == QDialog::Accepted) {
        // Считать список требований
        if (fillRequirements(
                    Core::Base::instance().getParameterValue("RTYPE", QString("")),
                    reqItem) ) {
             // ...
        }
    }
}


/*
 *
 */
bool BF_AnalizeForm::fillRequirements(const QString &rtype,
                                               QTreeWidgetItem *reqItem) {

    bool isFind;


    QDjango::setDatabase(*Core::Base::instance().database());
    QDjango::registerModel<RequirementElement>();
    QDjango::createTables();
    QDjangoQuerySet<RequirementElement> someRequirementElements;
    someRequirementElements = someRequirementElements.filter(
                QDjangoWhere("rtype", QDjangoWhere::Equals, rtype));

    RequirementElement re;
    isFind = false;
    bool ok; // TODO: Сделать проверку.
    for (int i = 0; i < someRequirementElements.size(); ++i) {
        if (someRequirementElements.at(i, &re)) {

            for (int j = 0; j < reqItem->childCount(); j++) {
                // ФТ001.Компонент.Модуль - Название
                QString rid = QString(reqItem->child(j)->text(0).split(".").at(0)).right(3);
                if (re.identificator() == rid.toInt(&ok,10)) {
                    isFind = true;
                    break;
                }
            }

            if (!isFind) {
                QTreeWidgetItem *item = new QTreeWidgetItem();
                QString tmp = QString("%1%2.%3.%4 - %5")
                        .arg(rtype)
                        .arg(re.identificator(), 3, 10, QLatin1Char('0'))
                        .arg(re.component())
                        .arg(re.module())
                        .arg(re.name());
                item->setText(0, tmp);

                reqItem->addChild(item);
            }

            isFind = false;
        }
    }

    return isFind;
}

/*
 * Создание диалоговых окон.
 */
void BF_AnalizeForm::createDialogs()
{
    m_requirementDialog = new NewRequirementDialog();
    m_editRequirementDialog = new EditRequirementDialog();

}

/*
 * Слот открытия редактора.
 */
void BF_AnalizeForm::on_onEditorButton_clicked()
{
    if (ui->analyzeTreeWidget->selectedItems().count() > 0 ) {
        QString s = ui->analyzeTreeWidget->selectedItems().at(0)->text(0);
        Core::Base::instance().setParameterValue("NAME", s.split(".").at(0));
        Core::Base::instance().setParameterValue("DOCTYPE", "ТРЕБОВАНИЕ");
    }

    emit openTexteditor();
    // TODO: сделат открытие окна редактора
    // m_editorDialog->show();
}

/*!
 * \brief Нажатие на дерево нажатия
 * \param[in] index индекс
 */
void BF_AnalizeForm::on_analyzeTreeWidget_clicked(const QModelIndex &index)
{
    controlAccess(DEFAULT);

    if (index.parent()!=QModelIndex()) {
        if (index.parent().data().toString()=="Бизнес-требования") {
            if (index.data().toString()=="Предметная область") {
                controlAccess(DOMAIN_AREA);
            }
        }
    }

    if (index.parent()!=QModelIndex()) {
        if (index.parent().data().toString()=="Бизнес-требования") {
            if (index.data().toString()=="Видение") {
                controlAccess(VISION);
            }
        }
    }

    if (index.parent()==QModelIndex()) {
        if (index.data().toString()=="Общие требования") {
            controlAccess(COMMON_REQUIREMENTS);
        }
    }

    if (index.parent()==QModelIndex()) {
        if (index.data().toString()=="Пользовательские требования"){
            controlAccess(USER_REQUIREMENTS);
        }
    }

    if (index.parent()==QModelIndex()) {
        if (index.data().toString()=="Функциональные требования"){
            controlAccess(FUNC_REQUIREMENTS);
        }
    }

    if (index.parent()==QModelIndex()) {
        if (index.data().toString()=="Нефункциональные требования"){
            controlAccess(NOFUNC_REQUIREMENTS);
        }
    }

    if (index.parent()!=QModelIndex()) {
        if (index.parent().data().toString()=="Общие требования") {
            controlAccess(SUB_COMMON_REQUIREMENTS);
        }
    }

    if (index.parent()!=QModelIndex()) {
        if (index.parent().data().toString()=="Пользовательские требования"){
            controlAccess(SUB_USER_REQUIREMENTS);
        }
    }

    if (index.parent()!=QModelIndex()) {
        if (index.parent().data().toString()=="Функциональные требования"){
            controlAccess(SUB_FUNC_REQUIREMENTS);
        }
    }

    if (index.parent()!=QModelIndex()) {
        if (index.parent().data().toString()=="Нефункциональные требования"){
            controlAccess(SUB_NOFUNC_REQUIREMENTS);
        }
    }

    if (index.parent()!=QModelIndex()) {
        if (index.parent().data().toString()=="Дополнительно"){
            controlAccess(OTHER);
        }
    }
}

/*
 *
 */
void BF_AnalizeForm::controlAccess(ANALYZE_TYPE val) {

    switch (val) {
    case DOMAIN_AREA:
    case VISION:
    case OTHER:
    case SUB_COMMON_REQUIREMENTS:
        ui->onEditorButton->setEnabled(true);
        ui->updateButton->setEnabled(true);
        ui->editButton->setEnabled(false);
        ui->deleteButton->setEnabled(false);
        ui->addButton->setEnabled(false);
        break;
    case USER_REQUIREMENTS:
    case FUNC_REQUIREMENTS:
    case NOFUNC_REQUIREMENTS:
        ui->onEditorButton->setEnabled(false);
        ui->updateButton->setEnabled(true);
        ui->editButton->setEnabled(false);
        ui->deleteButton->setEnabled(false);
        ui->addButton->setEnabled(true);
        break;
    case SUB_USER_REQUIREMENTS:
    case SUB_FUNC_REQUIREMENTS:
    case SUB_NOFUNC_REQUIREMENTS:
        ui->onEditorButton->setEnabled(true);
        ui->updateButton->setEnabled(true);
        ui->editButton->setEnabled(true);
        ui->deleteButton->setEnabled(true);
        ui->addButton->setEnabled(false);
        break;

    case COMMON_REQUIREMENTS:
        ui->onEditorButton->setEnabled(false);
        ui->updateButton->setEnabled(true);
        ui->editButton->setEnabled(false);
        ui->deleteButton->setEnabled(false);
        ui->addButton->setEnabled(false);
        break;
    default:
        ui->onEditorButton->setEnabled(false);
        ui->updateButton->setEnabled(false);
        ui->editButton->setEnabled(false);
        ui->deleteButton->setEnabled(false);
        ui->addButton->setEnabled(false);
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

    QString tmp = ui->analyzeTreeWidget->currentItem()->text(0).split(".").at(0);

    bool ok;

    int rid   = (QString(tmp).right(3)).toInt(&ok, 10);
    QString rtype = QString(tmp).left(2);

    QDjango::setDatabase(*Core::Base::instance().database());
    QDjango::registerModel<RequirementElement>();
    QDjango::createTables();

    QDjangoQuerySet<RequirementElement> someRequirementElements;
    someRequirementElements = someRequirementElements.filter(
                QDjangoWhere("rtype", QDjangoWhere::Equals, rtype));

    RequirementElement m_re;

    for (int i = 0; i < someRequirementElements.size(); ++i) {
        if (someRequirementElements.at(i, &m_re)) {
            if (m_re.identificator() == rid) {
                m_re.remove();
                break;
            }
        }
    }

    QList<QTreeWidgetItem*> reqItem;

    QString currItem = ui->analyzeTreeWidget->currentItem()->parent()->text(0);

    if (currItem == "Пользовательские требования") {
        reqItem = ui->analyzeTreeWidget->findItems(currItem,
                                                   Qt::MatchRecursive);
        ui->analyzeTreeWidget->currentItem()->parent()->removeChild(ui->analyzeTreeWidget->currentItem());

        fillRequirements(QString("ПТ"), reqItem.at(0));
    }
    if (currItem == "Функциональные требования") {
        reqItem = ui->analyzeTreeWidget->findItems(currItem,
                                                   Qt::MatchRecursive);
        ui->analyzeTreeWidget->currentItem()->parent()->removeChild(ui->analyzeTreeWidget->currentItem());


        fillRequirements(QString("ФТ"), reqItem.at(0));
    }
    if (currItem == "Нефункциональные требования") {
        reqItem = ui->analyzeTreeWidget->findItems(currItem,
                                                   Qt::MatchRecursive);
        ui->analyzeTreeWidget->currentItem()->parent()->removeChild(ui->analyzeTreeWidget->currentItem());


        fillRequirements(QString("НФТ"), reqItem.at(0));
    }
    else {
        QMessageBox msgBox;
        msgBox.setText("Тип требования неверен!");
        msgBox.exec();
    }
}

/*
 *
 */
void BF_AnalizeForm::on_editButton_clicked()
{

    QString tmp = ui->analyzeTreeWidget->currentItem()->text(0).split(".").at(0);

    QString rid   = QString(tmp).right(3);
    QString rtype = QString(tmp).left(2);

    Core::Base::instance().setParameterValue("EDIT_REQUIEREMENT_ID", rid);
    Core::Base::instance().setParameterValue("EDIT_REQUIEREMENT_TYPE", rtype);
    Core::Base::instance().setParameterValue("EDIT_REQUIEREMENT_ARTICLE",
                                             QString(ui->analyzeTreeWidget->
                                                     currentItem()->text(0).split("-").at(1)).trimmed());

    int result = m_editRequirementDialog->exec();

    if (result == QDialog::Accepted) {

        QList<QTreeWidgetItem*> reqItem;

        QString currItem = ui->analyzeTreeWidget->currentItem()->parent()->text(0);

        if (currItem == "Пользовательские требования") {
            reqItem = ui->analyzeTreeWidget->findItems(currItem,
                                                       Qt::MatchRecursive);
            ui->analyzeTreeWidget->currentItem()->parent()->removeChild(ui->analyzeTreeWidget->currentItem());

            fillRequirements(QString("ПТ"), reqItem.at(0));
        }
        if (currItem == "Функциональные требования") {
            reqItem = ui->analyzeTreeWidget->findItems(currItem,
                                                       Qt::MatchRecursive);
            ui->analyzeTreeWidget->currentItem()->parent()->removeChild(ui->analyzeTreeWidget->currentItem());


            fillRequirements(QString("ФТ"), reqItem.at(0));
        }
        if (currItem == "Нефункциональные требования") {
            reqItem = ui->analyzeTreeWidget->findItems(currItem,
                                                       Qt::MatchRecursive);
            ui->analyzeTreeWidget->currentItem()->parent()->removeChild(ui->analyzeTreeWidget->currentItem());


            fillRequirements(QString("НФТ"), reqItem.at(0));
        }
        else {
            QMessageBox msgBox;
            msgBox.setText("Тип требования неверен!");
            msgBox.exec();
        }
    }

}




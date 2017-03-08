#include "bf_architectform.h"
#include "ui_bf_architectform.h"

#include <QTimer>
#include <QDebug>

#include <library/orm/db/QDjangoQuerySet.h>
#include "../../../_shared/db/models/architectelement.h"
#include "../../../_shared/db/models/architectlinks.h"
#include "../../../_shared/db/models/architecttypealias.h"

#include <frameWork/base.h>

BF_ArchitectForm::BF_ArchitectForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BF_ArchitectForm)
{
    ui->setupUi(this);

    m_currentArchitectTreeItem   = NULL;
    QTimer::singleShot(100, this, SLOT(openArchitect()));
    // TODO: Заменить на название сессии
    Core::Base::instance().setParameterValue("SessionName", "Унифицированный комплекс");
    ui->sysNameEdit->setText(Core::Base::instance().getParameterValue("SessionName", QString("")));
    on_updateButton_clicked();
}

BF_ArchitectForm::~BF_ArchitectForm()
{
    delete ui;
}

void BF_ArchitectForm::on_editArchitectElementButton_clicked()
{
    EditArchitectElementDialog editArchitectElementDialog;
    Core::Base::instance().setParameterValue("Architect_Edit_Article",
            QString(m_currentArchitectTreeItem->text(0).split("|").at(1)).trimmed());


    if (editArchitectElementDialog.exec() == QDialog::Accepted) {
        ui->architectTreeWidget->clear();
        openArchitect();
    }
}

void BF_ArchitectForm::on_addArchitectElementButton_clicked()
{
    NewArhitectElementDialog newArchitectDialog;
    Core::Base::instance().setParameterValue("Architect_ParentName", m_currentArchitectTreeItem->text(0).split("|").at(1));
    Core::Base::instance().setParameterValue("Architect_ParentSmallText", m_currentArchitectTreeItem->text(0).split("|").at(0));

    if (newArchitectDialog.exec() == QDialog::Accepted) {

        if (m_currentArchitectTreeItem) {
            QString word = Core::Base::instance().getParameterValue("Arhitect_Type",QString(""));
            QTreeWidgetItem *newItem = new QTreeWidgetItem(m_currentArchitectTreeItem,
                                                           ui->architectTreeWidget->currentItem());

            if (word == "Подсистема") {
                newItem->setIcon(0, QIcon(":/img/img/subsystem.png"));
            }
            else if (word == "Компонент") {
                newItem->setIcon(0, QIcon(":/img/img/component.png"));
            }
            else if (word == "Модуль") {
                newItem->setIcon(0, QIcon(":/img/img/module.png"));
            }

            newItem->setText(m_currentArchitectTreeColumn, word + " | " +
                             Core::Base::instance().getParameterValue("Arhitect_SmallName", QString("")));
            newItem->setExpanded(true);
        }
        else {
            QTreeWidgetItem *newItem = new QTreeWidgetItem(ui->architectTreeWidget->currentItem());
            newItem->setText(m_currentArchitectTreeColumn, " | " +
                             Core::Base::instance().getParameterValue("Arhitect_SmallName", QString("")));
            newItem->setExpanded(true);
        }

    }
}

void BF_ArchitectForm::on_deleteArchitectElementButton_clicked()
{
    if (m_currentArchitectTreeItem)  {
        QString article1 = m_currentArchitectTreeItem->text(0).split("|").at(1);
        QTreeWidgetItem *parent = m_currentArchitectTreeItem->parent();
        int index;
        if (parent) {
            index = parent->indexOfChild(ui->architectTreeWidget->currentItem());
            delete parent->takeChild(index);
        }
        else {
            index = ui->architectTreeWidget->indexOfTopLevelItem(ui->architectTreeWidget->currentItem());
            delete ui->architectTreeWidget->takeTopLevelItem(index);
        }

        QSqlDatabase m_db = QSqlDatabase::addDatabase("QSQLITE", "pm");
        QString path = QString("%1/%2").arg(QCoreApplication::applicationDirPath()).arg("__pm");
        m_db.setDatabaseName(path);
        if (!m_db.open()) {
            messageLibrary msg;
            QString text;
            text = QString("%1. %2").arg("Не удалось открыть БД").arg(m_db.lastError().text());

            msg.createErrorMessage("Ошибка", text);

        }
        else {

            QDjango::setDatabase(m_db);
            QDjango::registerModel<ArchitectElement>();
            QDjango::createTables();
            QDjangoQuerySet<ArchitectElement> someArchitectElements;
            ArchitectElement ae;
            article1 = article1.trimmed();

            for (int i = 0; i < someArchitectElements.size(); ++i) {
                if (someArchitectElements.at(i, &ae)) {

                    QString article2 = ae.article().trimmed();

                    if (article1 == article2) {
                        ae.remove();

                        ui->architectTreeWidget->clear();
                        openArchitect();

                        break;
                    }
                }
            }
        }
        m_db.close();
    }

    m_currentArchitectTreeItem = NULL;
}



/*
 *
 */
QTreeWidgetItem *BF_ArchitectForm::findItemByTypeAndOrArticle(const QString &type,
                                                                   const QString &article) {
    if (type == "Система") {
        QList<QTreeWidgetItem *> lst = ui->architectTreeWidget->findItems(type + " | ",
                                                                         Qt::MatchContains);
        if (lst.size()>0) {
            return lst.at(0);
        }
        else {
            return NULL;
        }
    }
    else{
        QString findText = type + " | " + article;
        QList<QTreeWidgetItem *> lst = ui->architectTreeWidget->findItems(findText,
                                                                          Qt::MatchRecursive);
        if (lst.size()>0) {
            return lst.at(0);
        }
        else {
            return NULL;
        }
    }

    return NULL;
}


/*
 * Открыть архитектуру
 */
void BF_ArchitectForm::openArchitect()
{
    ui->architectTreeWidget->selectAll();

    QSqlDatabase m_db = QSqlDatabase::addDatabase("QSQLITE", "pm");
    QString path = QString("%1/%2").arg(QCoreApplication::applicationDirPath()).arg("__pm");
    m_db.setDatabaseName(path);
    if (!m_db.open()) {
        messageLibrary msg;
        QString text;
        text = QString("%1. %2").arg("Не удалось открыть БД").arg(m_db.lastError().text());

        msg.createErrorMessage("Ошибка", text);

    }
    else {

        QDjango::setDatabase(m_db);
        QDjango::registerModel<ArchitectElement>();
        QDjango::createTables();
        ArchitectElement ae;
        QDjangoQuerySet<ArchitectElement> someArchitectElements;

        bool isSystem = false;

        QTreeWidgetItem *unusedElementsItem = new QTreeWidgetItem(ui->architectTreeWidget);
        unusedElementsItem->setIcon(0, QIcon(":/img/img/unused.png"));
        unusedElementsItem->setText(0, "Не используемые");

        QList<int> usedElements;

        // Поиск системы
        for (int i = 0; i < someArchitectElements.size(); ++i) {
            if (someArchitectElements.at(i, &ae)) {

                QString parentType = ae.parentElementType();
                QString type = ae.type();
                if ((parentType == "") && (type == "Система")) {

                    QTreeWidgetItem *newItem = new QTreeWidgetItem(ui->architectTreeWidget);
                    newItem->setIcon(0, QIcon(":/img/img/system.png"));
                    newItem->setText(0, "Система | " + ae.article());
                    newItem->setExpanded(true);
                    isSystem = true;

                    usedElements.append(i);

                    break;
                }
            }
        }

        // Если система не найдена, то создаем ее сами
        // имя сессии = имя системы
        if (!isSystem) {
            ae.setArticle(Core::Base::instance().getParameterValue("SessionName", QString("")));
            ae.setName("");
            ae.setDescription("");
            ae.setType("Система");
            ae.setParentElementType("");
            ae.setParentElementArticle("");
            ae.save();

            QTreeWidgetItem *newItem = new QTreeWidgetItem(ui->architectTreeWidget);
            newItem->setIcon(0, QIcon(":/img/img/system.png"));
            newItem->setText(0, "Система | " + ae.article());
            newItem->setExpanded(true);
        }


        for (int i = 0; i < someArchitectElements.size(); ++i) {
            if (someArchitectElements.at(i, &ae)) {

                QString text = ae.parentElementType();
                if (text == "Система") {
                    if (findItemByTypeAndOrArticle(QString("Система"))) {
                        QTreeWidgetItem *newItem = new QTreeWidgetItem(findItemByTypeAndOrArticle(QString("Система")),
                                                                       ui->architectTreeWidget->currentItem());
                        newItem->setIcon(0, QIcon(":/img/img/subsystem.png"));
                        newItem->setText(0, "Подсистема | " + ae.article());
                        newItem->setExpanded(true);
                        usedElements.append(i);
                    }
                    else {
                        QTreeWidgetItem *newItem = new QTreeWidgetItem(ui->architectTreeWidget->currentItem());
                        newItem->setText(0, " | " + ae.article());
                        newItem->setExpanded(true);
                    }
                }
            }
        }

        for (int i = 0; i < someArchitectElements.size(); ++i) {
            if (someArchitectElements.at(i, &ae)) {
                QString text = ae.parentElementType();
                if (text == "Подсистема") {
                    if (findItemByTypeAndOrArticle(QString("Подсистема"), ae.parentElementArticle())) {
                        QTreeWidgetItem *newItem = new QTreeWidgetItem(
                                    findItemByTypeAndOrArticle(QString("Подсистема"),
                                                               ae.parentElementArticle()),
                                                               ui->architectTreeWidget->currentItem());
                        newItem->setIcon(0, QIcon(":/img/img/component.png"));
                        newItem->setText(0, "Компонент | " + ae.article());
                        newItem->setExpanded(true);
                        usedElements.append(i);
                    }
                    else {
                        QTreeWidgetItem *newItem = new QTreeWidgetItem(ui->architectTreeWidget->currentItem());
                        newItem->setText(0, " | " + ae.article());
                        newItem->setExpanded(true);
                    }
                }
            }
        }


        for (int i = 0; i < someArchitectElements.size(); ++i) {
            if (someArchitectElements.at(i, &ae)) {
                QString text = ae.parentElementType();
                if (text == "Компонент") {
                    if (findItemByTypeAndOrArticle(QString("Компонент"), ae.parentElementArticle())) {
                        QTreeWidgetItem *newItem = new QTreeWidgetItem(findItemByTypeAndOrArticle(
                                                                           QString("Компонент"),
                                                                           ae.parentElementArticle()),
                                                                       ui->architectTreeWidget->currentItem());
                        newItem->setIcon(0, QIcon(":/img/img/module.png"));
                        newItem->setText(0, "Модуль | " + ae.article());
                        newItem->setExpanded(true);
                        usedElements.append(i);
                    }
                    else {
                        QTreeWidgetItem *newItem = new QTreeWidgetItem(ui->architectTreeWidget->currentItem());
                        newItem->setText(0, " | " + ae.article());
                        newItem->setExpanded(true);
                    }
                }
            }
        }


        for (int i = 0; i < someArchitectElements.size(); ++i) {
            if (someArchitectElements.at(i, &ae)) {
                if (!usedElements.contains(i)) {
                    QTreeWidgetItem *newItem = new QTreeWidgetItem(unusedElementsItem,
                                                                   ui->architectTreeWidget->currentItem());
                    newItem->setIcon(0, QIcon(":/img/img/unused.png"));
                    newItem->setText(0, ae.type() + " | " + ae.article());
                    newItem->setExpanded(true);
                }
            }
        }
    }

    m_db.close();
}

void BF_ArchitectForm::on_architectTreeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    m_currentArchitectTreeItem   = item;
    m_currentArchitectTreeColumn = column;

    ui->addArchitectElementButton->setEnabled(true);
    ui->deleteArchitectElementButton->setEnabled(true);
    ui->editArchitectElementButton->setEnabled(true);

    // Выбираем элементы для связи
    if (ui->linkAEdit->text().isEmpty()) {
        ui->linkAEdit->setText(item->text(0));
        return;
    }
    // Выбираем элементы для связи
    else if (ui->linkBEdit->text().isEmpty()) {
        ui->linkBEdit->setText(item->text(0));
    }

}


void BF_ArchitectForm::on_resetButton_clicked()
{
    ui->linkAEdit->clear();
    ui->linkBEdit->clear();
    ui->nameLineEdit->clear();
    ui->linkDescriptionEdit->clear();
}

void BF_ArchitectForm::on_setLinkButton_clicked()
{
    QSqlDatabase m_db = QSqlDatabase::addDatabase("QSQLITE", "pm");
    QString path = QString("%1/%2").arg(QCoreApplication::applicationDirPath()).arg("__pm");
    m_db.setDatabaseName(path);
    if (!m_db.open()) {
        messageLibrary msg;
        QString text;
        text = QString("%1. %2").arg("Не удалось открыть БД").arg(m_db.lastError().text());

        msg.createErrorMessage("Ошибка", text);

    }
    else {

        QDjango::setDatabase(m_db);
        QDjango::registerModel<ArchitectLinks>();
        QDjango::createTables();
        ArchitectLinks al;
        al.setDescription(ui->linkDescriptionEdit->toPlainText());
        al.setLinkA(ui->linkAEdit->text());
        al.setLinkACount(QString("%1").arg(ui->linkASpinBox->value()));
        al.setLinkB(ui->linkBEdit->text());
        al.setLinkBCount(QString("%1").arg(ui->linkBSpinBox->value()));
        al.setName(ui->nameLineEdit->text());
        al.setType(ui->linkTypeBox->currentText());
        al.save();
    }
    m_db.close();

    on_resetButton_clicked();

}

void BF_ArchitectForm::on_updateButton_clicked()
{

    ui->linkListWidget->clear();

    QSqlDatabase m_db = QSqlDatabase::addDatabase("QSQLITE", "pm");
    QString path = QString("%1/%2").arg(QCoreApplication::applicationDirPath()).arg("__pm");
    m_db.setDatabaseName(path);
    if (!m_db.open()) {
        messageLibrary msg;
        QString text;
        text = QString("%1. %2").arg("Не удалось открыть БД").arg(m_db.lastError().text());

        msg.createErrorMessage("Ошибка", text);

    }
    else {

        QDjango::setDatabase(m_db);
        QDjango::registerModel<ArchitectLinks>();
        QDjango::createTables();
        QDjangoQuerySet<ArchitectLinks> someArchitectLinksElements;


        QList<QVariantMap> propertyMaps = someArchitectLinksElements.values(QStringList() << "id"
                                                                            << "name"
                                                                            << "type"
                                                                            << "linkA"
                                                                            << "linkB");
        foreach (const QVariantMap &propertyMap, propertyMaps) {
            ui->linkListWidget->addItem(QString("%1 | Название=%2 Тип=%3 A=%4 B=%5")
                                      .arg(propertyMap["id"].toString())
                                      .arg(propertyMap["name"].toString())
                                      .arg(propertyMap["type"].toString())
                                      .arg(propertyMap["linkA"].toString())
                                      .arg(propertyMap["linkB"].toString()));
        }
    }
    m_db.close();
}

void BF_ArchitectForm::on_linkListWidget_currentTextChanged(const QString &currentText)
{
    ui->idEdit->setText(QString(currentText.split("|").at(0)).trimmed());
}

void BF_ArchitectForm::on_deleteLinkButton_clicked()
{
    bool ok;
    int id = ui->idEdit->text().toInt(&ok,10);

    QSqlDatabase m_db = QSqlDatabase::addDatabase("QSQLITE", "pm");
    QString path = QString("%1/%2").arg(QCoreApplication::applicationDirPath()).arg("__pm");
    m_db.setDatabaseName(path);
    if (!m_db.open()) {
        messageLibrary msg;
        QString text;
        text = QString("%1. %2").arg("Не удалось открыть БД").arg(m_db.lastError().text());

        msg.createErrorMessage("Ошибка", text);

    }
    else {

        QDjango::setDatabase(m_db);
        QDjango::registerModel<ArchitectLinks>();
        QDjango::createTables();
        QDjangoQuerySet<ArchitectLinks> someArchitectLinksElements;
        someArchitectLinksElements = someArchitectLinksElements.filter(
                    QDjangoWhere("id", QDjangoWhere::Equals, id));

        someArchitectLinksElements.remove();
    }

    m_db.close();

    on_updateButton_clicked();
}



void BF_ArchitectForm::on_changeButton_clicked()
{
    QSqlDatabase m_db = QSqlDatabase::addDatabase("QSQLITE", "pm");
    QString path = QString("%1/%2").arg(QCoreApplication::applicationDirPath()).arg("__pm");
    m_db.setDatabaseName(path);
    if (!m_db.open()) {
        messageLibrary msg;
        QString text;
        text = QString("%1. %2").arg("Не удалось открыть БД").arg(m_db.lastError().text());

        msg.createErrorMessage("Ошибка", text);

    }
    else {

        QDjango::setDatabase(m_db);
        QDjango::registerModel<ArchitectElement>();
        QDjango::createTables();
        ArchitectElement ae;
        QDjangoQuerySet<ArchitectElement> someArchitectElements;

        // Поиск системы
        for (int i = 0; i < someArchitectElements.size(); ++i) {
            if (someArchitectElements.at(i, &ae)) {

                QString parentType = ae.parentElementType();
                QString type = ae.type();
                if ((parentType == "") && (type == "Система")) {
                    ae.setArticle(ui->sysNameEdit->text());
                    ae.save();
                    break;
                }
            }
        }
    }
    m_db.close();
}

void BF_ArchitectForm::on_saveAliasButton_clicked()
{
    QSqlDatabase m_db = QSqlDatabase::addDatabase("QSQLITE", "pm");
    QString path = QString("%1/%2").arg(QCoreApplication::applicationDirPath()).arg("__pm");
    m_db.setDatabaseName(path);
    if (!m_db.open()) {
        messageLibrary msg;
        QString text;
        text = QString("%1. %2").arg("Не удалось открыть БД").arg(m_db.lastError().text());

        msg.createErrorMessage("Ошибка", text);

    }
    else {

        QDjango::setDatabase(m_db);
        QDjango::registerModel<ArchitectTypeAlias>();
        QDjango::createTables();
        QDjangoQuerySet<ArchitectTypeAlias> someArchitectElements;

        someArchitectElements.remove();

        ArchitectTypeAlias ae;

        ae.setType("Система");
        ae.setAlias(ui->systemAliasEdit->text());
        ae.setType("Подсистема");
        ae.setAlias(ui->subsystemAliasEdit->text());
        ae.setType("Компонент");
        ae.setAlias(ui->componentAliasEdit->text());
        ae.setType("Модуль");
        ae.setAlias(ui->moduleAliasEdit->text());

        ae.save();
    }
    m_db.close();
}

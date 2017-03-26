#include "bf_architectform.h"
#include "ui_bf_architectform.h"

#include <QTimer>
#include <QDebug>
#include <QList>

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
}

BF_ArchitectForm::~BF_ArchitectForm()
{
    delete ui;
}


void BF_ArchitectForm::showEvent(QShowEvent *event) {
    Q_UNUSED(event)
    readArchitecture();
    on_updateButton_clicked();
}

/*
 * Открыть структуру системы
 */
void BF_ArchitectForm::readArchitecture()
{
    // Очищаем все дерево
    ui->architectTreeWidget->clear();

    // Устанавливаем корневой элемент
    QTreeWidgetItem *rootItem = new QTreeWidgetItem(ui->architectTreeWidget);
    //rootItem->setIcon(0, QIcon(":/img/img/system.png"));
    rootItem->setText(0, QString("0:Корень"));
    rootItem->setExpanded(true);


    // Заполняем список архитектурных элементов
    QDjango::setDatabase(*Core::Base::instance().sessionDatabase());

    QDjangoQuerySet<ArchitectElement> someArchitectElements;
    QList<architectElementListItem> _architectElementListItem;

    // retrieve usernames and passwords for matching users as maps
    QList<QVariantMap> propertyMaps = someArchitectElements.values(QStringList() << "id"
                                                                   << "type" << "name" << "parentId");
    foreach (const QVariantMap &propertyList, propertyMaps) {
      architectElementListItem tmp;
      tmp.id = propertyList["id"].toInt();
      tmp.name = propertyList["name"].toString();
      tmp.type = propertyList["type"].toString();
      tmp.parentId = propertyList["parentId"].toInt();

      _architectElementListItem.append(tmp);
    }

    int searchParentId = 0;
    QList<QPair<int,QTreeWidgetItem *> > ids;

    QTreeWidgetItem *searchItem = rootItem;
    // Заполняем дерево архитектуры
    while(!_architectElementListItem.isEmpty()) {

        if (!ids.isEmpty()) {
            QPair<int,QTreeWidgetItem *> t = ids.takeAt(0);
            searchParentId = t.first;
            searchItem = t.second;
        }

        for(int i = 0; i < _architectElementListItem.size(); i++) {

            // Находим первый элемент
            if (_architectElementListItem.at(i).parentId == searchParentId) {
                QTreeWidgetItem *newItem = new QTreeWidgetItem(searchItem);
                //newItem->setIcon(0, QIcon(":/img/img/system.png"));
                newItem->setText(0, QString("%1:%2 - %3").arg(_architectElementListItem.at(i).id)
                                               .arg(_architectElementListItem.at(i).type)
                                               .arg(_architectElementListItem.at(i).name));
                newItem->setExpanded(true);
                // Ищем новые элементы по новому идентификатору и продолжаем заполнять дерево
                QPair<int,QTreeWidgetItem *> t;
                t.first  = _architectElementListItem.at(i).id;
                t.second =  newItem;
                ids.append(t);

                _architectElementListItem.takeAt(i);
                i = -1;
            }
        }

    }
}


/*
 * Обновить связи
 */
void BF_ArchitectForm::on_updateButton_clicked()
{
    ui->linkListWidget->clear();

    QDjango::setDatabase(*Core::Base::instance().sessionDatabase());
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

/*
 * Редактирование архитектурного элемента
 */
void BF_ArchitectForm::on_editArchitectElementButton_clicked()
{
    if (m_currentArchitectTreeItem) {
        // Получаем идентификатор элемента
        Core::Base::instance().setParameterValue("ArchitectElement_Id",
                QString(m_currentArchitectTreeItem->text(0).split(":").at(0)).trimmed());

        // Открываем окно редактирования
        EditArchitectElementDialog editArchitectElementDialog;
        if (editArchitectElementDialog.exec() == QDialog::Accepted) {
            readArchitecture();
            m_currentArchitectTreeItem = NULL;
        }
    }
    else {
        messageLibrary msg;
        msg.createInfoMessage("Информация", "Не выбран никакой элемент структуры системы.");
    }
}

/*
 * Добавляем новый элемент
 */
void BF_ArchitectForm::on_addArchitectElementButton_clicked()
{
    if (m_currentArchitectTreeItem) {
        // Получение идентификатора элемента
        Core::Base::instance().setParameterValue("ArchitectElement_ParentId",
                                                 m_currentArchitectTreeItem->text(0).split(":").at(0));

        NewArhitectElementDialog newArchitectDialog;
        if (newArchitectDialog.exec() == QDialog::Accepted) {
            readArchitecture();
            m_currentArchitectTreeItem = NULL;
        }
    }
    else {
        messageLibrary msg;
        msg.createInfoMessage("Информация", "Не выбран никакой элемент структуры системы.");
    }
}

/*
 *
 */
void BF_ArchitectForm::recursiveDeleteElements(QTreeWidgetItem *item, int id)
{
    QDjango::setDatabase(*Core::Base::instance().sessionDatabase());
    QDjangoQuerySet<ArchitectElement> someArchitectElements;
    ArchitectElement architectElement;
    bool ok;

    someArchitectElements = someArchitectElements.filter(QDjangoWhere("id", QDjangoWhere::Equals, id));
    if (someArchitectElements.size()>0) {
        someArchitectElements.at(0, &architectElement);
        architectElement.remove();

        for (int i=0; i <item->childCount(); i++) {
            QString id = item->child(i)->text(0).split(":").at(0);
            recursiveDeleteElements(item->child(i), id.toInt(&ok, 10));
        }
    }

    // TODO Сделать удаление связей
}

/*
 * Удаляем элемент
 */
void BF_ArchitectForm::on_deleteArchitectElementButton_clicked()
{
    if (m_currentArchitectTreeItem) {
        bool ok;
        QString id = m_currentArchitectTreeItem->text(0).split(":").at(0);
        recursiveDeleteElements(m_currentArchitectTreeItem, id.toInt(&ok, 10));
        readArchitecture();
        m_currentArchitectTreeItem = NULL;
    }
    else {
        messageLibrary msg;
        msg.createInfoMessage("Информация", "Не выбран никакой элемент структуры системы.");
    }
}


/*
 * Обработчик нажатия на элемент структуры дерева.
 */
void BF_ArchitectForm::on_architectTreeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    m_currentArchitectTreeItem   = item;
    m_currentArchitectTreeColumn = column;

    ui->editorButton->setEnabled(true);
    ui->addArchitectElementButton->setEnabled(true);
    ui->deleteArchitectElementButton->setEnabled(true);
    ui->editArchitectElementButton->setEnabled(true);

}

/*
 * Установка связи
 */
void BF_ArchitectForm::on_setLinkButton_clicked()
{

    QDjango::setDatabase(*Core::Base::instance().sessionDatabase());
    ArchitectLinks al;

    al.setDescription(ui->linkDescriptionEdit->toPlainText());
    al.setLinkA(ui->linkAEdit->text());
    al.setLinkACount(QString("%1").arg(ui->linkACountBox->currentText()));
    al.setLinkB(ui->linkBEdit->text());
    al.setLinkBCount(QString("%1").arg(ui->linkBCountBox->currentText()));
    al.setName(ui->nameLineEdit->text());
    al.setType(ui->linkTypeBox->currentText());
    al.save();

    on_resetLinkBButton_clicked();
    on_resetLinkBButton_clicked();

    ui->nameLineEdit->clear();
    ui->linkDescriptionEdit->clear();
    ui->linkTypeBox->setCurrentIndex(0);

    on_updateButton_clicked();
}

/*
 *  Установка ID
 */
void BF_ArchitectForm::on_linkListWidget_currentTextChanged(const QString &currentText)
{
    ui->idLabel->setText(QString(currentText.split(":").at(0)).trimmed());
}


/*
 * Удаление связи
 */
void BF_ArchitectForm::on_deleteLinkButton_clicked()
{
    bool ok;
    int id = ui->idLabel->text().toInt(&ok,10);

    QDjango::setDatabase(*Core::Base::instance().sessionDatabase());
    QDjangoQuerySet<ArchitectLinks> someArchitectLinksElements;
    someArchitectLinksElements = someArchitectLinksElements.filter(
                QDjangoWhere("id", QDjangoWhere::Equals, id));

    someArchitectLinksElements.remove();
    on_updateButton_clicked();
}

/*
 *  Открытие текстового редактора
 */
void BF_ArchitectForm::on_editorButton_clicked()
{
    if (ui->architectTreeWidget->selectedItems().count() > 0 ) {
        QByteArray ba;
        ba.append(ui->architectTreeWidget->selectedItems().at(0)->text(0));
        QString hash = QString(QCryptographicHash::hash(ba,
                               QCryptographicHash::Sha1).toHex());

        Core::Base::instance().setParameterValue("UID", hash);
        Core::Base::instance().setParameterValue("NAME", ui->architectTreeWidget->selectedItems().at(0)->text(0));

        Core::Base::instance().setParameterValue("DOCTYPE", "АРХИТЕКТУРА");
    }

    emit openTexteditor();
}

void BF_ArchitectForm::on_resetLinkBButton_clicked()
{
    ui->linkBEdit->clear();
    ui->linkBCountBox->setItemText(0, "1");
}

void BF_ArchitectForm::on_resetLinkAButton_clicked()
{
    ui->linkAEdit->clear();
    ui->linkACountBox->setItemText(0, "1");
}

void BF_ArchitectForm::on_setLinkAButton_clicked()
{
    ui->linkAEdit->setText(ui->architectTreeWidget->currentItem()->text(0).split(":").at(0));
}

void BF_ArchitectForm::on_setLinkBButton_clicked()
{
    ui->linkBEdit->setText(ui->architectTreeWidget->currentItem()->text(0).split(":").at(0));
}


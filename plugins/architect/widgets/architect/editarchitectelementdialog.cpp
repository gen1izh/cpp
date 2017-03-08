#include "editarchitectelementdialog.h"
#include "ui_editarchitectelementdialog.h"
#include <frameWork/base.h>
#include <library/orm/db/QDjangoQuerySet.h>
#include "../../../_shared/db/models/architectelement.h"

#include <QDebug>

EditArchitectElementDialog::EditArchitectElementDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditArchitectElementDialog)
{
    ui->setupUi(this);
}

EditArchitectElementDialog::~EditArchitectElementDialog()
{
    delete ui;
}

/*
 * Открываем окно редактирования элемента архитектуры
 */
void EditArchitectElementDialog::showEvent(QShowEvent *event)
{
    Q_UNUSED(event)
    ui->articleEdit->setText(Core::Base::instance().getParameterValue("Architect_Edit_Article", QString()));


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

        // Проходим по БД и ищем нужный элемент по его идентификатору article
        QDjangoQuerySet<ArchitectElement> someArchitectElements;

        QString parentType;
        ArchitectElement ae;
        QString excludeParentArticle = "";

        for (int i = 0; i < someArchitectElements.size(); ++i) {
            if (someArchitectElements.at(i, &ae)) {
                QString text = ae.article();

                // Если нашли текущий элемент для редактирования в БД
                if (text ==  ui->articleEdit->text().trimmed()) {
                    ui->nameEdit->setText(ae.name().trimmed());            // Имя элемента (н-р MSDOS)
                    ui->descriptionEdit->setText(ae.description());        // Описание элемента
                    ui->parentTypeBox->addItem(ae.parentElementType());    // Тип родительского элемента (н-р Подсистема)
                    ui->elementTypeLabel->setText(ae.type().trimmed());    // Тип самого компонента

                    parentType = ae.parentElementType().trimmed();
                    excludeParentArticle = ae.parentElementArticle().trimmed();
                    break;
                }
            }
        }

        // Заполняем список идентификаторов следующим уровнем элементов архитекутры.
        for (int i = 0; i < someArchitectElements.size(); ++i) {
            if (someArchitectElements.at(i, &ae)) {

                QString type = ae.type().trimmed();
                QString article = ae.article().trimmed();


                if ((type == parentType) && (excludeParentArticle != article)) {
                    ui->parentNameBox->addItem(ae.article());
                }
            }
        }
    }

    m_db.close();
}

/*
 * Обработчик кнопки Accept диалогового окна.
 */
void EditArchitectElementDialog::on_buttonBox_accepted()
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

        QDjangoQuerySet<ArchitectElement> someArchitectElements;
        ArchitectElement ae;

        for (int i = 0; i < someArchitectElements.size(); ++i) {
            if (someArchitectElements.at(i, &ae)) {

                QString article1 = Core::Base::instance().getParameterValue("Architect_Edit_Article", QString(""));
                QString article2 = ae.article().trimmed();

                // Нашли элемент, который редактируем и удаляем его.
                if (article1 == article2) {
                    ae.remove();
                    break;
                }
            }
        }

        // Добавить новый элемент
        ae.setArticle(ui->articleEdit->text().trimmed());
        ae.setName(ui->nameEdit->text().trimmed());
        ae.setDescription(ui->descriptionEdit->toPlainText());
        ae.setType(ui->elementTypeLabel->text().trimmed());
        ae.setParentElementType(ui->parentTypeBox->currentText());
        ae.setParentElementArticle(ui->parentNameBox->currentText());

        ae.save();

    }

    m_db.close();
}

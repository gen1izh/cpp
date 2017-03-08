#include "editordialog.h"
#include "ui_editordialog.h"
#include <frameWork/base.h>

#include <library/orm/db/QDjangoQuerySet.h>

#include "../../../_shared/db/models/docelement.h"
#include "../../../_shared/db/models/imageselement.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QBuffer>
#include <QDir>
#include <QClipboard>

#include "../../../_shared/db/models/glossaryelement.h"
#include "../../../_shared/db/models/termselement.h"
#include "../../../_shared/db/models/requirementelement.h"

#include <QDebug>

EditorDialog::EditorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditorDialog)
{
    ui->setupUi(this);

     m_highlighter = new Highlighter(ui->descriptionEdit->document());
     m_highlighter->setDocument(ui->descriptionEdit->document());
}

EditorDialog::~EditorDialog()
{
    delete ui;
}

/*
 *
 */
void EditorDialog::loadDescription() {

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
        QDjango::registerModel<DocElement>();
        QDjango::createTables();

        QDjangoQuerySet<DocElement> someDocElements;

        someDocElements = someDocElements.filter(QDjangoWhere("name", QDjangoWhere::Equals, ui->nameEdit->text()));

        if (someDocElements.count() > 1) {
            QMessageBox msgBox;
             msgBox.setText("Элемент с именем " +  ui->nameEdit->text() + " создан несколько раз!"\
                            "Должен быть только один элемент!");
             msgBox.exec();
        }
        else if (someDocElements.count() == 1) {
            // Находим нужный элемент и меняем его.
            DocElement de;
            for (int i = 0; i < someDocElements.size(); ++i) {
                if (someDocElements.at(i, &de)) {
                    if (de.name() == ui->nameEdit->text()) {
                        ui->descriptionEdit->setText(de.description());
                    }
                }
            }
        }
        else {
            ui->descriptionEdit->setText("");
        }
    }
    m_db.close();

}


/*
 * Загрузка картинок.
 */
bool EditorDialog::loadImage(const QString &fullPath, const QString &fileName) {
    QImage image;
    image.load(fullPath);

    if (image.height() > 2*image.width()) {
        QMessageBox msgBox;
        msgBox.setText("Пропорции картинки выбраны не удачно."
                       "Высота больше чем в 2 раза ширины."
                       "Масштабирование картинки будет не удачным."
                       "Поэтому вручную измените пропорции картинки. ");
        msgBox.exec();
        return false;
    }


    QDir dir = QDir::currentPath() + "//images";
    if (dir.exists()) {
        if (image.width() > DEFAULT_IMAGE_WIDTH) {
           image = image.scaledToWidth(DEFAULT_IMAGE_WIDTH);
        }
        image.save(QString("images//%1").arg(fileName));
        return true;
    }
    else {
        QMessageBox msgBox;
        msgBox.setText("Каталог images не создан. "
                       "Сейчас создам его и сохраню картинку.");
        msgBox.exec();
        dir.mkdir(QDir::currentPath() + "//images");
        if (dir.exists()) {
            if (image.width() > DEFAULT_IMAGE_WIDTH) {
               image = image.scaledToWidth(DEFAULT_IMAGE_WIDTH);
            }
            image.save(QString("images//%1").arg(fileName));
            return true;
        }
        else {
            QMessageBox msgBox;
            msgBox.setText("Каталог images не создан. "
                           "Возможно проблемы с правами доступа.");
            msgBox.exec();
            return false;
        }
    }
    return false;
}

/*
 * Обновление списка картинок.
 */
void EditorDialog::refreshImagesList(){

    ui->picturesList->clear();

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
        QDjango::registerModel<ImagesElement>();
        QDjango::createTables();

        QDjangoQuerySet<ImagesElement> someImagesElements;

        ImagesElement ie;
        for (int i = 0; i < someImagesElements.size(); ++i) {
            if (someImagesElements.at(i, &ie)) {

                ui->picturesList->addItem(
                            QString("%1 || %2").arg(ie.filename())
                                           .arg(ie.name()));
            }
        }

    }

    m_db.close();
}

/*
 *
 */
void EditorDialog::showEvent(QShowEvent *event)
{
    Q_UNUSED(event)
    ui->nameEdit->setText(Core::Base::instance().getParameterValue("NAME", QString("")));
    ui->docTypeLabel->setText(Core::Base::instance().getParameterValue("DOCTYPE", QString("")));

    loadDescription();
    refreshImagesList();

    ui->EditorlBox->setCurrentIndex(0);

    ui->terminBox->clear();
    ui->glossaryBox->clear();
    ui->frBox->clear();
    ui->nfrBox->clear();

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
        QDjango::registerModel<TermsElement>();
        QDjango::createTables();

        QDjangoQuerySet<TermsElement> someTermsElements;

        TermsElement m_re;
        for (int i = 0; i < someTermsElements.size(); ++i) {
            if (someTermsElements.at(i, &m_re)) {
                ui->terminBox->addItem(m_re.name());
            }
        }

        QDjangoQuerySet<GlossaryElement> someGlossaryElementElements;

        GlossaryElement m_ge;
        for (int i = 0; i < someGlossaryElementElements.size(); ++i) {
            if (someGlossaryElementElements.at(i, &m_ge)) {
                ui->glossaryBox->addItem(m_ge.name());
            }
        }


        QDjangoQuerySet<RequirementElement> someRequirementElements;
        someRequirementElements = someRequirementElements.filter(
                    QDjangoWhere("rtype", QDjangoWhere::Equals, QString("ФТ")));

        RequirementElement re;
        for (int i = 0; i < someRequirementElements.size(); ++i) {
            if (someRequirementElements.at(i, &re)) {

                QString tmp = QString("%1%2")
                        .arg(re.rtype())
                        .arg(re.identificator(), 3, 10, QLatin1Char('0'));

                ui->frBox->addItem(tmp);
            }
        }


        QDjangoQuerySet<RequirementElement> someNoFunctionalRequirementElements;
        someNoFunctionalRequirementElements = someNoFunctionalRequirementElements.filter(
                    QDjangoWhere("rtype", QDjangoWhere::Equals, QString("НФТ")));

        RequirementElement nfre;
        for (int i = 0; i < someNoFunctionalRequirementElements.size(); ++i) {
            if (someNoFunctionalRequirementElements.at(i, &nfre)) {

                QString tmp = QString("%1%2")
                        .arg(nfre.rtype())
                        .arg(nfre.identificator(), 3, 10, QLatin1Char('0'));

                ui->nfrBox->addItem(tmp);
            }
        }



        QDjangoQuerySet<DocElement> someDocElements;

        DocElement de;
        for (int i = 0; i < someDocElements.size(); ++i) {
            if (someDocElements.at(i, &de)) {
                if (de.type() == QString("ПРИЛОЖЕНИЕ")) {
                    ui->appendixBox->addItem(de.name());
                }
            }
        }

    }
    m_db.close();

}

/*
 *
 */
void EditorDialog::on_dialogButtonBox_accepted()
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
        QDjango::registerModel<DocElement>();
        QDjango::createTables();

        QDjangoQuerySet<DocElement> someDocElements;
        someDocElements = someDocElements.filter(QDjangoWhere("name", QDjangoWhere::Equals, ui->nameEdit->text()));

        if (someDocElements.count() > 1) {
            QMessageBox msgBox;
             msgBox.setText("Элемент с именем " +  ui->nameEdit->text() + " создан несколько раз!"\
                            "Должен быть только один элемент!");
             msgBox.exec();
        }
        else if (someDocElements.count() == 1) {
            // Находим нужный элемент и меняем его.
            DocElement de;
            for (int i = 0; i < someDocElements.size(); ++i) {
                if (someDocElements.at(i, &de)) {
                    if (de.name() == ui->nameEdit->text()) {
                        de.setName(ui->nameEdit->text());
                        de.setType(ui->docTypeLabel->text());
                        de.setDescription(ui->descriptionEdit->toPlainText());
                        de.save();
                    }
                }
            }
        }
        else {
            DocElement de;
            de.setName(ui->nameEdit->text());
            de.setType(ui->docTypeLabel->text());
            de.setDescription(ui->descriptionEdit->toPlainText());
            de.save();
        }

    }

    m_db.close();
}

/*
 *
 */
void EditorDialog::on_browselButton_clicked()
{
    ui->pathEdit->setText(
                QFileDialog::getOpenFileName(this,
                                             tr("Выбрать картинку"),
                                             "",
                                             tr("Image Files (*.png)"))
                );
}


/*
 * Добавление картинки.
 */
void EditorDialog::on_addImageButton_clicked()
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
        QDjango::registerModel<ImagesElement>();
        QDjango::createTables();

        if (ui->nameImageEdit->text().isEmpty()) {
            QMessageBox msgBox;
             msgBox.setText("Введите название!");
             msgBox.exec();
             return;
        }

        if (ui->pathEdit->text().isEmpty()) {
            QMessageBox msgBox;
             msgBox.setText("Выберите файл!");
             msgBox.exec();
             return;
        }

        QFileInfo file(ui->pathEdit->text());

        QString filename = file.fileName();


        QDjangoQuerySet<ImagesElement> someImagesElements;
        someImagesElements = someImagesElements.filter(QDjangoWhere("filename",
                                                                    QDjangoWhere::Equals,
                                                                    filename));

        if (someImagesElements.count() > 1) {
            QMessageBox msgBox;
             msgBox.setText("Картинка с именем " +  ui->pathEdit->text() + " создана несколько раз!"\
                            "Должен быть только один элемент картинки с таким именем!");
             msgBox.exec();
             return;
        }
        else if (someImagesElements.count() == 1) {
            QMessageBox msgBox;
             msgBox.setText("Картинка с именем " +  ui->pathEdit->text() + " уже создана!"\
                            "Должен быть только один элемент картинки с таким именем!"\
                            "Если хотите заменить картинку, то сначала удалите старую, а затем закачайте новую.");
             msgBox.exec();
             return;
        }
        else {

            //
            // Картинки до этого момента с таким именем не существовало.
            //

            // Проверяем загружена ли картинка.
            if (loadImage(ui->pathEdit->text(), filename) == true) {

                ImagesElement ie;
                ie.setName(ui->nameImageEdit->text());
                ie.setFilename(filename);
                ie.save();
            }
        }

        // Обновить список картинок в редакторе.
        refreshImagesList();
    }

    m_db.close();
}

/*
 * Удаление картинки.
 */
void EditorDialog::on_deleteImageButton_clicked()
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
        QDjango::registerModel<ImagesElement>();
        QDjango::createTables();


        QString imageName = (ui->picturesList->currentItem()->text().split("||")).at(0);

        imageName = imageName.trimmed(); // удаляем пробелы вначале строки в конце.

        QDjangoQuerySet<ImagesElement> someImagesElements;
        someImagesElements = someImagesElements.filter(QDjangoWhere("filename",
                                                                    QDjangoWhere::Equals,
                                                                    imageName));

        if (someImagesElements.count() > 1) {
            QMessageBox msgBox;
             msgBox.setText("Картинка с именем " +  imageName + " создана несколько раз!"\
                            "Должен быть только один элемент картинки с таким именем!");
             msgBox.exec();
             return;
        }
        else if (someImagesElements.count() == 1) {
            QMessageBox msgBox;
              msgBox.setText("Удаление картинки");
              msgBox.setInformativeText("Вы точно хотите удалить картинку?");
              msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
              msgBox.setDefaultButton(QMessageBox::Cancel);
              int ret = msgBox.exec();

              switch (ret) {
                  case QMessageBox::Ok:
                      someImagesElements.at(0)->remove();
                      break;
                  case QMessageBox::Cancel:
                      // Cancel was clicked
                      break;
                  default:
                      // should never be reached
                      break;
                }

             // Обновить список картинок в редакторе.
             refreshImagesList();

             return;
        }
        else {
            QMessageBox msgBox;
            msgBox.setText("Картинка с именем " +  imageName + " отсутствует!");
            msgBox.exec();
        }
    }
    m_db.close();

}

/*
 * Обработка двойного щелчка.
 */
void EditorDialog::on_picturesList_doubleClicked(const QModelIndex &index)
{
    Q_UNUSED(index)
    QClipboard *clipboard = QApplication::clipboard();
    QString imageFileName = (ui->picturesList->currentItem()->text().split("||")).at(0);
    imageFileName = imageFileName.trimmed(); // удаляем пробелы вначале строки в конце.

    QString imageName = (ui->picturesList->currentItem()->text().split("||")).at(1);
    imageName = imageName.trimmed(); // удаляем пробелы вначале строки в конце.

    imageFileName = "[IMG]\n\t[FILENAME]" + imageFileName +
            "[/FILENAME]\n\t[NAME]" + imageName + "[/NAME]\n[/IMG]\n";

    clipboard->setText(imageFileName);

    QMessageBox msgBox;
    msgBox.setText("Тег картинки скопирован в буфер.");
    msgBox.exec();
}

/*
 * Добавление курсива
 */
void EditorDialog::on_italicButton_clicked()
{
    QString result =
            "[I]" + ui->descriptionEdit->textCursor().selectedText() + "[/I]";


    ui->descriptionEdit->textCursor().insertText(result);
}

/*
 * Добавление жирного текста
 */
void EditorDialog::on_boldButton_clicked()
{
    QString result =
            "[B]" + ui->descriptionEdit->textCursor().selectedText() + "[/B]";


    ui->descriptionEdit->textCursor().insertText(result);
}

/*
 * Добавление подчеркнутного текста
 */
void EditorDialog::on_understrikeButton_clicked()
{
    QString result =
            "[U]" + ui->descriptionEdit->textCursor().selectedText() + "[/U]";


    ui->descriptionEdit->textCursor().insertText(result);
}

/*
 * Добавление не отформатированного текста
 */
void EditorDialog::on_preButton_clicked()
{
    QString result =
            "[PRE]" + ui->descriptionEdit->textCursor().selectedText() + "[/PRE]";


    ui->descriptionEdit->textCursor().insertText(result);
}

/*
 * Добавление заголовка
 */
void EditorDialog::on_titlesBox_currentTextChanged(const QString &arg1)
{
Q_UNUSED(arg1)
}

/*
 * Вставить перечисление.
 */
void EditorDialog::on_enumButton_clicked()
{
    QString result =
            "[UL] \n \t[LI] [/LI] \n \t[LI] [/LI] \n \t[LI] [/LI] \n[/UL] \n";

    ui->descriptionEdit->textCursor().insertText(result);
}

/*
 *
 */
void EditorDialog::on_picturesList_clicked(const QModelIndex &index)
{
    Q_UNUSED(index)
    QString imageName = (ui->picturesList->currentItem()->text().split("||")).at(1);
    imageName = imageName.trimmed(); // удаляем пробелы вначале строки в конце.

    ui->newNameEdit->setText(imageName);
}

/*
 *
 */
void EditorDialog::on_editNameButton_clicked()
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
        QDjango::registerModel<ImagesElement>();
        QDjango::createTables();

        if (ui->editNameButton->isChecked()) {
            ui->newNameEdit->setEnabled(true);
        }
        else {
                    QString imageFileName = (ui->picturesList->currentItem()->text().split("||")).at(0);

                    imageFileName = imageFileName.trimmed(); // удаляем пробелы вначале строки в конце.

                    QDjangoQuerySet<ImagesElement> someImagesElements;
                    someImagesElements = someImagesElements.filter(QDjangoWhere("filename",
                                                                                QDjangoWhere::Equals,
                                                                                imageFileName));

                    if (someImagesElements.count() > 1) {
                        QMessageBox msgBox;
                        msgBox.setText("Картинок " +  imageFileName + " создано больше одной."\
                                       "Должен быть только один элемент картинки с таким именем!");
                        msgBox.exec();

                        ui->newNameEdit->setEnabled(false);
                        return;
                    }
                    else if (someImagesElements.count() == 1) {

                        QDjangoQuerySet<ImagesElement> someImagesElements;

                        ImagesElement ie;
                        for (int i = 0; i < someImagesElements.size(); ++i) {
                            if (someImagesElements.at(i, &ie)->filename() == imageFileName) {
                                ie.setName(ui->newNameEdit->text());
                                ie.save();
                            }
                        }

                        // Обновить список картинок в редакторе.
                        refreshImagesList();

                        ui->newNameEdit->setEnabled(false);

                        return;
                    }
                    else {
                        QMessageBox msgBox;
                        msgBox.setText("Картинка с именем " +  imageFileName + " отсутствует!");
                        msgBox.exec();
                    }

            ui->newNameEdit->setEnabled(false);

        }
    }

    m_db.close();

}

/*
 *
 */
void EditorDialog::on_titlesBox_activated(const QString &arg1)
{
    if (arg1 == "Заголовок 1") {
        QString result =
                "[H1]" + ui->descriptionEdit->textCursor().selectedText() + "[/H1]";


        ui->descriptionEdit->textCursor().insertText(result);
    }
    else if (arg1 == "Заголовок 2") {
        QString result =
                "[H2]" + ui->descriptionEdit->textCursor().selectedText() + "[/H2]";


        ui->descriptionEdit->textCursor().insertText(result);
    }
    else if (arg1 == "Заголовок 3") {
        QString result =
                "[H3]" + ui->descriptionEdit->textCursor().selectedText() + "[/H3]";


        ui->descriptionEdit->textCursor().insertText(result);
    }
    else if (arg1 == "Заголовок 4") {
        QString result =
                "[H4]" + ui->descriptionEdit->textCursor().selectedText() + "[/H4]";


        ui->descriptionEdit->textCursor().insertText(result);
    }
}

/*
 *
 */
void EditorDialog::on_paragraphBox_activated(const QString &arg1)
{
    if (arg1 == "Пункт уровня 1") {
        QString result =
                "[P1]" + ui->descriptionEdit->textCursor().selectedText() + "[/P1]";


        ui->descriptionEdit->textCursor().insertText(result);
    }
    else if (arg1 == "Пункт уровня 2") {
        QString result =
                "[P2]" + ui->descriptionEdit->textCursor().selectedText() + "[/P2]";


        ui->descriptionEdit->textCursor().insertText(result);
    }
    else if (arg1 == "Пункт уровня 3") {
        QString result =
                "[P3]" + ui->descriptionEdit->textCursor().selectedText() + "[/P3]";


        ui->descriptionEdit->textCursor().insertText(result);
    }
    else if (arg1 == "Пункт уровня 4") {
        QString result =
                "[P4]" + ui->descriptionEdit->textCursor().selectedText() + "[/P4]";


        ui->descriptionEdit->textCursor().insertText(result);
    }
}

/*
 *
 */
void EditorDialog::on_tableButton_clicked()
{
    QString result =
            "[TABLE] \n\n\t[TR HEADER]\n\t\t[TD][/TD]\n\t[/TR] "
            "\n\n\t[TR]\n\t\t[TD][/TD]\n\t[/TR] "
            "\n\n\t[TR]\n\t\t[TD][/TD]\n\t[/TR]\n\n[/TABLE] \n";

    ui->descriptionEdit->textCursor().insertText(result);
}

/*
 *
 */
void EditorDialog::on_codeButton_clicked()
{
    QString result =
            "[CODE]" + ui->descriptionEdit->textCursor().selectedText() + "[/CODE]";


    ui->descriptionEdit->textCursor().insertText(result);
}

/*
 *
 */
void EditorDialog::on_noteButton_clicked()
{
    QString result =
            "[NOTE]" + ui->descriptionEdit->textCursor().selectedText() + "[/NOTE]";


    ui->descriptionEdit->textCursor().insertText(result);
}



void EditorDialog::on_terminBox_activated(const QString &arg1)
{
    QString result = "[TERM]" + arg1 + "[/TERM]";

    ui->descriptionEdit->textCursor().insertText(result);
}

void EditorDialog::on_pasteTemplateButton_clicked()
{
    QString result = "";
    if (ui->nameEdit->text() == "Спецификация требований") {
        result += "[H1]Введение[/H1] \n";
        result += "[H1]Основания для разработки[/H1]\n";
        result += "\n";
        result += "[H1]Назначение ПО[/H1]\n";
        result += "[BODY_INFO:Назначение ПО]\n";
        result += "\n";
        result += "[H1]Cостав ПО[/H1]\n";
        result += "<!-- Состав ПО -->\n";
        result += "\n";
        result += "[H1]Язык программирования[/H1] \n";
        result += "[BODY_INFO:Язык программирования]\n";
        result += "\n";
        result += "[H1]Аппаратная зависимость[/H1]\n";
        result += "<!-- Аппаратная зависимость -->\n";
        result += "\n";
        result += "[H1]Необходимые и достаточные условия эксплуатации ПО[/H1]\n";
        result += "\t[H2]Требования к эксплуатации и персоналу[/H2] \n";
        result += "[BODY_CR:Требования к эксплуатации и персоналу]\n";
        result += "\n";
        result += "[H1]Обеспечение надежности и безопасности ПО[/H1]\n";
        result += "\t[H2]Требования к безопасности и надежности[/H2]\n";
        result += "[BODY_CR:Требования к безопасности и надежности]\n";
        result += "\t[H2]Требования к устойчивости к сбоям[/H2]\n";
        result += "[BODY_CR:Требования к устойчивости к сбоям]\n";
        result += "\n";
        result += "\t[H2]Требования к производительности[/H2]\n";
        result += "[BODY_CR:Требования к производительности]\n";
        result += "\n";
        result += "[H1]Функциональные требования[/H1]\n";
        result += "\n";
        result += "<!-- Функциональные требования системы -->\n";
        result += "[H1]Нефункциональные требования к ПО[/H1]\n";
        result += "\n";
        result += "<!-- Нефункциональные требования системы -->\n";
        result += "\n";
        result += "[H1]Общие требования[/H1]\n";
        result += "\n";
        result += "\t[H2]Требования к внутреннему состоянию[/H2]\n";
        result += "[BODY_CR:Требования к внутреннему состоянию]\n";
        result += "\n";
        result += "\t[H2]Требования к отладке[/H2]\n";
        result += "[BODY_CR:Требования к отладке]\n";
        result += "\n";
        result += "[H2]Требования использования ПО[/H2]\n";
        result += "[BODY_CR:Требования использования ПО]\n";
        result += "\n";
        result += "\t[H2]Требования к документированию[/H2]\n";
        result += "[BODY_CR:Требования к документированию]\n";
        result += "\n";
        result += "[H1]Перечень ссылочных документов[/H1]\n";
        result += "[BODY_INFO:Перечень ссылочных документов]\n";
        result += "\n";
        result += "[GLOSSARY]Глоссарий[/GLOSSARY]\n";
        result += "[TERMINS]Термины[/TERMINS]\n";
        result += "[H1]Приложения[/H1]\n";
    }
    else if (ui->nameEdit->text() == "Описание ПО") {
        result += "[H1]Общие сведения[/H1]\n";
        result += "[BODY_INFO:Общие сведения]\n";
        result += "\n";
        result += "[H1]Язык программирования[/H1]\n";
        result += "[BODY_INFO:Язык программирования]\n";
        result += "<!-- Программное обеспечение, необходимое для функционирования программы -->\n";
        result += "\n";
        result += "[H1]Назначение ПО[/H1]\n";
        result += "[BODY_INFO:Назначение ПО]\n";
        result += "\n";
        result += "[H1]Функциональные ограничения на применение[/H1]\n";
        result += "[BODY_INFO:Функциональные ограничения на применение]\n";
        result += "\n";
        result += "[H1]Вызов и загрузка ПО[/H1]\n";
        result += "\n";
        result += "[H1]Предметная область[/H1]\n";
        result += " [BODY_BR:Предметная область]";
        result += " [H1]Алгоритмы ПО[/H1]\n";
        result += "\n";
        result += "    [H2]Жизненный цикл ПО[/H2]\n";
        result += "\n";
        result += "    <!-- Другие алгоритмы ПО -->\n";
        result += "\n";
        result += "[H1]Описание структуры ПО[/H1]\n";
        result += "<!-- Описание структуры ПО -->\n";
        result += "\n";
        result += "[GLOSSARY]Глоссарий[/GLOSSARY]\n";
        result += "\n";
        result += "[TERMINS]Термины[/TERMINS]\n";
        result += "\n";
        result += "[H1]Приложения[/H1]\n";
    }
    else if (ui->nameEdit->text() == "Руководство пользователя") {
        result += "[H1]Назначение ПО[/H1]\n";
        result += "[BODY_INFO:Назначение ПО]\n";
        result += "\n";
        result += "[H1]Предметная область[/H1]\n";
        result += "[BODY_BR:Предметная область]\n";
        result += "\n";
        result += "[H1]Функции ПО[/H1]\n";
        result += "<--! Основные функции ПО -->\n";
        result += "\n";
        result += "[H1]Условия выполнения программы[/H1]\n";
        result += "\n";
        result += "[H1]Требования к эксплуатации и персоналу[/H1]\n";
        result += "[BODY_CR:Требования к эксплуатации и персоналу]\n";
        result += "\n";
        result += "[H2]Требования к аппаратному обеспечению[/H2]\n";
        result += "<--! Какие требования к ПО совместно-работающего с нашим ПО -->\n";
        result += "[H2]Требования к программному обеспечению[/H2]\n";
        result += "<--! Какие требования к аппаратуре, на которой будет работать наше ПО -->\n";
        result += "\n";
        result += "[H1]Разграничение прав пользователей[/H1]\n";
        result += "\n";
        result += "[H1]Выполнение ПО[/H1]\n";
        result += "[H2]Установка ПО[/H2]\n";
        result += "<--! Демонстрация установки ПО -->\n";
        result += "[H2]Запуск ПО[/H2]\n";
        result += "<--! Демонстрация запуска ПО -->\n";
        result += "[H2]Интерфейс ПО[/H2]\n";
        result += "<--! Демонстрация интерфейса ПО -->\n";
        result += "[H2]Работа с ПО[/H2]\n";
        result += "<--! Демонстрация выполнения функциональных требований -->\n";
        result += "\n";
        result += "[H1]Завершение работы ПО[/H1]\n";
        result += "<--! Завершение работы ПО -->\n";
        result += "\n";
        result += "[H1]Сообщения пользователю [/H1]\n";
        result += "<--! Сообщения пользователю -->\n";
        result += "\n";
        result += "[GLOSSARY]Глоссарий[/GLOSSARY]\n";
        result += "[TERMINS]Термины[/TERMINS]\n";
        result += "[H1]Приложения[/H1]\n";
    }
    else {
        QMessageBox msgBox;
        msgBox.setText("Шаблон [" +  ui->nameEdit->text() + "] отсутствует!");
        msgBox.exec();
    }


    ui->descriptionEdit->textCursor().insertText(result);

//    result += "[H1]Структура ПО[/H1] \n\n";
//    result += "\t[H2]Описание системы[/H2] \n\n";
//    result += "\t\t[H3]Назначение[/H3] \n\n";
//    result += "\t[H2]Описание подсистем[/H2] \n\n";
//    result += "\t\t[H3]Назначение[/H3] \n\n";
//    result += "\t[H2]Описание компонента А[/H2] \n\n";
//    result += "\t\t[H3]Назначение[/H3] \n\n";
//    result += "\t\t[H3]Описание модуля А1[/H3] \n\n";
//    result += "\t\t\t\t[H4]Назначение[/H4] \n\n";
//    result += "\t\t\t\t[H4]Контекст применения[/H4] \n\n";
//    result += "\t\t\t\t[H4]Описание ГИП[/H4] \n\n";
//    result += "\t\t\t\t[H4]Входные данные[/H4] \n\n";
//    result += "\t\t\t\t[H4]Выходные данные[/H4] \n\n";
//    result += "\t\t\t\t[H4]Диаграмма классов[/H4] \n\n";
//    result += "\t\t\t\t[H4]Файловая структура[/H4] \n\n";
//    result += "\t\t\t\t[H4]Данные[/H4] \n\n";
//    result += "\t\t\t[H3]Описание модуля А2[/H3] \n\n";
//    result += "\t\t\t\t[H4]Назначение[/H4] \n\n";
//    result += "\t\t\t\t[H4]Контекст применения[/H4] \n\n";
//    result += "\t\t\t\t[H4]Описание ГИП[/H4] \n\n";
//    result += "\t\t\t\t[H4]Входные данные[/H4] \n\n";
//    result += "\t\t\t\t[H4]Выходные данные[/H4] \n\n";
//    result += "\t\t\t\t[H4]Диаграмма классов[/H4] \n\n";
//    result += "\t\t\t\t[H4]Файловая структура[/H4] \n\n";
//    result += "\t\t\t\t[H4]Данные[/H4] \n\n";
//    result += "\t\t\t[H3]Описание модуля А3[/H3] \n\n";
//    result += "\t\t\t\t[H4]Назначение[/H4] \n\n";
//    result += "\t\t\t\t[H4]Контекст применения[/H4] \n\n";
//    result += "\t\t\t\t[H4]Описание ГИП[/H4] \n\n";
//    result += "\t\t\t\t[H4]Входные данные[/H4] \n\n";
//    result += "\t\t\t\t[H4]Выходные данные[/H4] \n\n";
//    result += "\t\t\t\t[H4]Диаграмма классов[/H4] \n\n";
//    result += "\t\t\t\t[H4]Файловая структура[/H4] \n\n";
//    result += "\t\t\t\t[H4]Данные[/H4] \n\n";
//    result += "\t\t[H2]Связи между компонентами[/H2] \n\n";
}



void EditorDialog::on_appendixBox_activated(const QString &arg1)
{
    Q_UNUSED(arg1)
    QString result = "";

    result = "[APPENDIX]" + ui->appendixBox->currentText() + "[/APPENDIX] \n";
    result += "[BODY_APPENDIX:"+ ui->appendixBox->currentText()+"]\n";

    ui->descriptionEdit->textCursor().insertText(result);
}

void EditorDialog::on_frBox_activated(const QString &arg1)
{
Q_UNUSED(arg1)
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
        QDjango::registerModel<RequirementElement>();
        QDjango::createTables();

        QString result = "";

        QDjangoQuerySet<RequirementElement> someRequirementElements;
        someRequirementElements = someRequirementElements.filter(
                    QDjangoWhere("rtype", QDjangoWhere::Equals, QString("ФТ")));

        QString name;

        RequirementElement nfre;
        for (int i = 0; i < someRequirementElements.size(); ++i) {
            if (someRequirementElements.at(i, &nfre)) {

                QString tmp = QString("%1%2")
                        .arg(nfre.rtype())
                        .arg(nfre.identificator(), 3, 10, QLatin1Char('0'));

                if ( ui->frBox->currentText() == tmp) {
                    name =  QString("%1%2.%3.%5 - %6")
                            .arg(nfre.rtype())
                            .arg(nfre.identificator(), 3, 10, QLatin1Char('0'))
                            .arg(nfre.component())
                            .arg(nfre.module())
                            .arg(nfre.name());
                    break;
                }
            }
        }

        result = "[H2]" + name + "[/H2] \n";
        result += "[BODY_FR:"+ ui->frBox->currentText()+"]\n";

        ui->descriptionEdit->textCursor().insertText(result);
    }

    m_db.close();
}

void EditorDialog::on_crBox_activated(const QString &arg1)
{
    Q_UNUSED(arg1)
    QString result = "";

    if (ui->crBox->currentText()=="ВСЕ") {

        for( int i=0; i < ui->crBox->count(); i++ ) {
            if ((ui->crBox->itemText(i)!="")&&(ui->crBox->itemText(i)!="ВСЕ")) {
            result += "[H2]" + ui->crBox->itemText(i) + "[/H2] \n";
            result += "[BODY_CR:"+ ui->crBox->itemText(i)+"]\n";
            }
        }
    }
    else {
        if (ui->crBox->currentText()!="") {
            result = "[H2]" + ui->crBox->currentText() + "[/H2] \n";
            result += "[BODY_CR:"+ ui->crBox->currentText()+"]\n";
        }
    }

    ui->descriptionEdit->textCursor().insertText(result);
}

void EditorDialog::on_nfrBox_activated(const QString &arg1)
{
    Q_UNUSED(arg1)
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
        QDjango::registerModel<RequirementElement>();
        QDjango::createTables();

        QString result = "";

        QDjangoQuerySet<RequirementElement> someRequirementElements;
        someRequirementElements = someRequirementElements.filter(
                    QDjangoWhere("rtype", QDjangoWhere::Equals, QString("НФТ")));

        QString name;

        RequirementElement nfre;
        for (int i = 0; i < someRequirementElements.size(); ++i) {
            if (someRequirementElements.at(i, &nfre)) {

                QString tmp = QString("%1%2")
                        .arg(nfre.rtype())
                        .arg(nfre.identificator(), 3, 10, QLatin1Char('0'));

                if ( ui->nfrBox->currentText() == tmp) {
                    name =  QString("%1%2.%3.%5 - %6")
                            .arg(nfre.rtype())
                            .arg(nfre.identificator(), 3, 10, QLatin1Char('0'))
                            .arg(nfre.component())
                            .arg(nfre.module())
                            .arg(nfre.name());
                    break;
                }
            }
        }

        result = "[H2]" + name + "[/H2] \n";
        result += "[BODY_NFR:"+ ui->nfrBox->currentText()+"]\n";

        ui->descriptionEdit->textCursor().insertText(result);
    }

    m_db.close();
}

void EditorDialog::on_brBox_activated(const QString &arg1)
{
    Q_UNUSED(arg1)
    QString result = "";

    result = "[H1]" + ui->brBox->currentText() + "[/H1] \n";
    result += "[BODY_BR:"+ ui->brBox->currentText()+"]\n";

    ui->descriptionEdit->textCursor().insertText(result);
}

void EditorDialog::on_infoBox_activated(const QString &arg1)
{
    QString result = "";

    result = "[H1]" + ui->infoBox->currentText() + "[/H1] \n";
    result += "[BODY_INFO:"+ ui->infoBox->currentText()+"]\n";

    ui->descriptionEdit->textCursor().insertText(result);
}

void EditorDialog::on_glossaryBox_activated(const QString &arg1)
{
    QString result = "[GLOSSARY_TERM]" + arg1 + "[/GLOSSARY_TERM]";

    ui->descriptionEdit->textCursor().insertText(result);
}

void EditorDialog::on_scanTermsButton_clicked()
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
        QDjango::registerModel<TermsElement>();
        QDjango::createTables();

        QDjangoQuerySet<TermsElement> someTermsElements;

        QList<QString> abbrList;

        TermsElement m_re;
        for (int i = 0; i < someTermsElements.size(); ++i) {
            if (someTermsElements.at(i, &m_re)) {
                abbrList.append(m_re.name());
            }
        }

        QString tmp = ui->descriptionEdit->toPlainText();

        foreach(const QString& abbr, abbrList) {

            int result = tmp.indexOf(abbr);
            if (result!=-1) {
                QChar chStart;
                QChar chEnd;

                chStart = chEnd = QChar(0);

                if (result>0) {
                    chStart = tmp.at(result-1);
                }

                if (abbr.length()+result < tmp.length()) {
                    chEnd = tmp.at(result+abbr.length());
                }

                if ((!chStart.isLetterOrNumber()) && (!chEnd.isLetterOrNumber())) {
                    if ((chEnd!='[') && (chStart!=']') ) {
                        tmp.replace(abbr, QString("[TERM]%1[/TERM]").arg(abbr));
                    }
                }
            }
        }
        ui->descriptionEdit->setText(tmp);
    }

    m_db.close();

}

void EditorDialog::on_scanGlossaryButton_clicked()
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
        QDjango::registerModel<GlossaryElement>();
        QDjango::createTables();

        QDjangoQuerySet<GlossaryElement> someGlossaryElements;

        QList<QString> abbrList;

        GlossaryElement m_re;
        for (int i = 0; i < someGlossaryElements.size(); ++i) {
            if (someGlossaryElements.at(i, &m_re)) {
                abbrList.append(m_re.name());
            }
        }

        QString tmp = ui->descriptionEdit->toPlainText();

        foreach(const QString& abbr, abbrList) {

            int result = tmp.indexOf(abbr);
            if (result!=-1) {
                QChar chStart;
                QChar chEnd;

                chStart = chEnd = QChar(0);

                if (result>0) {
                    chStart = tmp.at(result-1);
                }

                if (abbr.length()+result < tmp.length()) {
                    chEnd = tmp.at(result+abbr.length());
                }

                if ((!chStart.isLetterOrNumber()) && (!chEnd.isLetterOrNumber())) {
                    if ((chEnd!='[') && (chStart!=']') ) {
                        tmp.replace(abbr, QString("[DEFINE]%1[/DEFINE]").arg(abbr));
                    }
                }
            }
        }
        ui->descriptionEdit->setText(tmp);
    }

    m_db.close();
}

void EditorDialog::on_anchorButton_clicked()
{
    QString result = "";

    result = "[ANCHOR]" + ui->brBox->currentText() + "[/ANCHOR] \n";

    ui->descriptionEdit->textCursor().insertText(result);
}

void EditorDialog::on_gotoAnchorButton_clicked()
{
    QString result =
                "[GOTO_ANCHR] \n \t{Текст ссылки}, \n \t{anchor_tag} \n[/GOTO_ANCHR] \n";

    ui->descriptionEdit->textCursor().insertText(result);
}

#include "messagelibrary.h"

void messageLibrary::setButtonText(QMessageBox &message)
{
  //Изменение текста кнопок.
  message.setButtonText(QMessageBox::Cancel, "Отмена");
  message.setButtonText(QMessageBox::Save, "Сохранить");
  message.setButtonText(QMessageBox::Discard, "Не сохранять");
  message.setButtonText(QMessageBox::Yes, "Да");
  message.setButtonText(QMessageBox::No, "Нет");
}

messageLibrary::messageLibrary(QObject *parent) : QObject(parent)
{

}

void messageLibrary::createInfoMessage(QString title, QString text)
{
  QMessageBox message;
  message.setText(text);
  message.setIcon(QMessageBox::Information);
  message.setWindowTitle(title);
  message.exec();
}

void messageLibrary::createErrorMessage(QString title, QString text)
{
  QMessageBox message;
  message.setText(text);
  message.setIcon(QMessageBox::Critical);
  message.setWindowTitle(title);
  message.exec();
}

void messageLibrary::createWarnMessage(QString title, QString text)
{
  QMessageBox message;
  message.setWindowTitle(title);
  message.setIcon(QMessageBox::Warning);
  message.setText(text);
  message.addButton(QMessageBox::Ok);
  message.exec();
}

int messageLibrary::createQuestionMessage(QString title, QString text)
{
  QMessageBox message;
  message.setWindowTitle(title);
  message.setIcon(QMessageBox::Question);
  message.setText(text);
  message.addButton(QMessageBox::Yes);
  message.addButton(QMessageBox::No);
  message.setDefaultButton(QMessageBox::No);

  setButtonText(message);

  message.exec();

  if (message.clickedButton() == message.button(QMessageBox::Yes)) {
    return QMessageBox::Yes;
  }
  if (message.clickedButton() == message.button(QMessageBox::No)) {
    return QMessageBox::No;
  }
  return false;
}

int messageLibrary::createSaveDialog(QString title, QString text)
{
  QMessageBox message;
  message.setWindowTitle(title);
  message.setText(text);

  //Иконка сообщения
  message.setIcon(QMessageBox::Question);

  //Кнопки
  message.addButton(QMessageBox::Save);
  message.addButton(QMessageBox::Discard);
  message.addButton(QMessageBox::Cancel);
  message.setDefaultButton(QMessageBox::Cancel);

  setButtonText(message);

  message.exec();

  //Возвращаем результат.
  if (message.clickedButton() == message.button(QMessageBox::Save)) {
    return QMessageBox::Save;
  }
  if (message.clickedButton() == message.button(QMessageBox::Discard)) {
    return QMessageBox::Discard;
  }
  if (message.clickedButton() == message.button(QMessageBox::Cancel)) {
    return QMessageBox::Cancel;
  }
  return QMessageBox::Cancel;
}

void messageLibrary::createAboutMessage(QString title, QString text)
{
  QMessageBox message;
  message.setWindowTitle(title);
  message.setText(text);
  message.exec();
}

int messageLibrary::createWarnDialog(QString title, QString text)
{
  QMessageBox message;
  message.setWindowTitle(title);
  message.setText(text);
  message.setIcon(QMessageBox::Warning);

  message.addButton(QMessageBox::Yes);
  message.addButton(QMessageBox::Cancel);
  message.setDefaultButton(QMessageBox::Cancel);

  setButtonText(message);

  message.exec();
  if (message.clickedButton() == message.button(QMessageBox::Yes)) {
    return QMessageBox::Yes;
  }
  return QMessageBox::Cancel;
}


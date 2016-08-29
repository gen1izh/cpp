#ifndef MESSAGELIBRARY_H
#define MESSAGELIBRARY_H

#include <QObject>
#include <QMessageBox>
#include <QDebug>
#include <QPushButton>

/*!
 * Перечисление возрващаемых значений.
 */
enum {
  MessageLibrary_Cancel  = 0x0,
  MessageLibrary_Save    = 0x1,
  MessageLibrary_Discard = 0x2,
  MessageLibrary_Yes     = 0x4,
  MessageLibrary_No      = 0x8,
};

class messageLibrary : public QObject
{
  Q_OBJECT
private:
  /*!
   * \brief Установка русского языка для кнопок.
   */
  void setButtonText(QMessageBox &message);
public:
  explicit messageLibrary(QObject *parent = 0);

  /*!
   * \brief Создает информационное сообщение
   * \param title - заголовок окна сообщения.
   * \param text - текст сообщения.
   */
  void createInfoMessage(QString title, QString text);

  /*!
   * \brief Создает сообщение об ошибке.
   * \param title - заголовок окна сообщения.
   * \param text - текст сообщения.
   */
  void createErrorMessage(QString title, QString text);

  /*!
   * \brief Создает предупреждающее сообщение.
   * \param title - заголовок окна сообщения.
   * \param text - текст сообщения.
   */
  void createWarnMessage(QString title, QString text);

  /*!
   * \brief Создает сообщение с вопросом. В окне сообщения создаются
   * кнопки "Yes" и "No".
   * \param title - заголовок окна сообщения.
   * \param text - текст сообщения.
   * \return при нажатии кнопки "Yes" возвращается MessageLibrary_Yes,
   * при нажатии кнопки "No" возвращается MessageLibrary_No.
   */
  int createQuestionMessage(QString title, QString text);

  /*!
   * \brief Создает сообщение с вопросом. В окне сообщения создаются
   * кнопки "Save", "Discard", "Cancel".
   * \param title - заголовок окна сообщения.
   * \param text - текст сообщения.
   * \return при нажатии кнопки "Save" возвращается MessageLibrary_Save,
   * при нажатии кнопки "Discard" - MessageLibrary_Discard,
   * при нажатии кнопки "Отмена" - MessageLibrary_Cancel.
   */
  int createSaveDialog(QString title, QString text);

  /*!
   * \brief Создает сообщение без иконок.
   * \param title - заголовок окна сообщения.
   * \param text - текст сообщения.
   */
  void createAboutMessage(QString title, QString text);

  /*!
   * \brief Создает предупреждающее сообщение с вопросом и кнопками "Да", "Отмена".
   * \param title - заголовок окна.
   * \param text - текст сообщения.
   * \return при нажатии кнопки "Да" возвращается MessageLibrary_Yes,
   * при нажатии кнопки "Отмена" - MessageLibrary_No.
   */
  int createWarnDialog(QString title, QString text);
signals:

public slots:
};

#endif // MESSAGELIBRARY_H

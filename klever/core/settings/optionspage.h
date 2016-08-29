#ifndef OPTIONSPAGE_H
#define OPTIONSPAGE_H

/*!
 * \brief   Класс реализующий страницу настроек внешнего вида приложения.
 * \details Описание класса...
 * \date      2015
 */

#include <QWidget>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

/*!
 * \brief Класс настроек приложения
 */
class OptionsPage : public QWidget {
    Q_OBJECT

    /*!
     * \brief Указатель на метку для поля названия ПО
     */
    QLabel     *_textLabel;
    /*!
     * \brief Указатель на метку стелей внешнего вида ПО
     */
    QLabel     *_styleLabel;
    /*!
     * \brief Указатель на поле названия ПО
     */
    QLineEdit  *_textEdit;
    /*!
     * \brief Указатель на всплывающий список стилей внешнего вида ПО
     */
    QComboBox  *_styleCombo;

    QPushButton *_acceptButton;

  public:
    OptionsPage(QWidget *parent = 0);

    /*!
     * \brief Функция создания коннекторов
     */
    void createConnectors();

  public slots:
    /*!
     * \brief Слот на изменение внешнего стиля приложения
     * \param[in] index индексный номер стиля
     */
    void styleComboBoxChanged(int index);

    /*!
     * \brief Слот на изменение имени приложения в заголовке главнго окна.
     * \param[in] text текст названия главного окна
     */
    void acceptButton_onClicked();
};

#endif // OPTIONSPAGE_H

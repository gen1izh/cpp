#ifndef QLAMPWIDGET_H
#define QLAMPWIDGET_H

/*!
 * \page lampwidget Библиотека светодиодов
 * \latexonly
 * \endlatexonly
 */

#include <QFrame>
#include <QLabel>
#include <QIcon>
#include <QGridLayout>

/*!
 * \brief Класс светодиодов
 */
class QLampWidget : public QFrame {

  Q_OBJECT

  /*!
   * \brief Свойство класса
   * \todo расписать подробней
   */
  Q_PROPERTY(QString text READ text WRITE setText USER true)

public:
  enum States {
    IS_LAMP_ON,             /*! Признак включения */
    IS_LAMP_OFF,            /*! Признак выключенности */
    IS_LAMP_DISABLE,        /*! Признак неактивного состояния */
    IS_LAMP_FAIL,           /*! Признак ошибки */
    IS_LAMP_PING,           /*! Признак сигнализации процесса */
    IS_LAMP_TRAFFIC,        /*! Признак передачи трафика */
    IS_LAMP_READY           /*! Признак готовности */
  };

private:
  /*!
   * \brief Состояние светодиода
   */
  States   _state;

  /*!
   * \brief Иконка светодиода
   */
  QLabel        *_iconLabel;

  /*!
   * \brief Текст слева светодиода
   */
  QLabel        *_txtLabel;

  public:
    /*!
     * \brief Инициализация виджета
     * \param[in] parent - указатель на родительский класс
     * \todo  Возможно папраметр не нужен, необходимо решить это.
     */
    explicit QLampWidget( QWidget *parent = 0 );
  /*!
     * \brief QLampWidget Перегруженный конструктор QLampWidget
     * \param parent[in]  Указатель на родительский класс
     * \param label       Текст рядом с виджетом
     * \param colorIndex  Индекс цвета
     */
    explicit QLampWidget(QString label, int colorIndex, int rowIndex, QWidget *parent = 0);

    /*!
     * \brief Деструктор класса
     */
    ~QLampWidget(){
      delete _iconLabel;
      delete _txtLabel;
    }

    /*!
     * \brief Установка текста светодиода
     * \param[in] txt - текст светодиода
     */
    void setText(QString txt) {
      _txtLabel->setText( txt );
    }

    /*!
     * \brief Запрос текста светодиода
     * \return Текст светодиода
     */
    QString text() const {
      return _txtLabel->text();
    }

    States state() const {
        return _state;
    }

  public slots:

    /*!
     * \brief Включение светодиода
     */
    void setOnLamp();

    /*!
     * \brief Отключение светодиода
     */
    void setOffLamp();

    /*!
     * \brief Сигнализация недоступности светодиода
     */
    void setDisableLamp();

    /*!
     * \brief Сигнализация ошибки
     */
    void setFailLamp();

    /*!
     * \brief Сигнализация процесса
     */
    void setPingLamp();

    /*!
     * \brief Сигнализация трафика
     */
    void setTrafficLamp();

    /*!
     * \brief Ожидание готовности
     */
    void setReadyLamp();

};

#endif // QLAMPWIDGET_H

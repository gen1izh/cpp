#ifndef LOGGERSSETTINGSPAGE_H
#define LOGGERSSETTINGSPAGE_H

#include "loggerdata.h"
#include <QScrollArea>

class LoggersSettingsPage : public QWidget {

  Q_OBJECT

  public:

    /*!
     * \todo На данный момент сейчсас сделано не больше 4 журналов в приложении
     */
    enum {
      COUNT = 4
    };

    /*!
     * \brief Возвращает в качестве ссылок аргументов функции имя и состояние журнала
     * \param[in] type - тип журнала
     * \param[in] name - название журнала
     * \param[in] enabled - состояние журнала
     */
    void getLoggerProperty(int type, QString &name, QString &enabled);

    /*!
     * \brief LoggersSettingsPage
     * \param parent
     */
    LoggersSettingsPage(QWidget *parent = 0);
    ~LoggersSettingsPage();

    /*!
     * \brief Создание коннекторов по изменению каждого поля
     * \param Индекс журнала (1,2,3,4)
     */
    void createConnections();

    /*!
     * \brief Лейбл для типов логгеров
     */
    QLabel *loggerTypeLabel;

    /*!
     * \brief Список типов логгеров
     */
    QComboBox *loggerTypeBox;

    /*!
     * \brief Лейбл для названия логгера
     */
    QLabel *loggerTextNameLabel;

    /*!
     * \brief Поле ввода имени журнала
     */
    QLineEdit *loggerTextNameEdit;

    /*!
     * \brief Флаг состояни журнала
     */
    QCheckBox *loggerEnabledCheckBox;

    /*!
     * \brief Указатель на текущий номер журнала
     */
    int currentLogger;

  public slots:
    /*!
     * \brief Слот изменения типа журнала
     */
    void loggerType_onChanged(const QString &type);

    /*!
     * \brief Устанавливает тестовое название логгера
     * \details  для отображения на табе нижнего дока
     * \param[in] type - тип журнала
     * \param[in] name - название журнала
     */
    void setLoggerTextName(const QString &name);

    /*!
     * \brief Устанавливает состояние логгера
     * \param[in] type - тип журнала
     * \param[in] enabled - состояние журнала (true - включен, false - выключен)
     */
    void setLoggerEnabled(int checked);

};


#endif // LOGGERSSETTINGSPAGE_H

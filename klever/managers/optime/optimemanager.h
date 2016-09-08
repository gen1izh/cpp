#ifndef OPTIME_MANAGER_H
#define OPTIME_MANAGER_H

/*!
 * brief   Наработка
 * details %{ModuleDescription}
 * author  Петров Г.Г., gen.izh@ya.ru
 * date
 */
class OptimeManager;

#include <frameWork/base.h>
#include "widgets/settings/optimesettingswidget.h"

#include <QTime>
#include <QTimer>

class OptimeManager : public QObject, public ManagerInterface {

  Q_OBJECT

  Q_PLUGIN_METADATA(IID ManagerInterface_iid FILE "optime.json")
  Q_INTERFACES(ManagerInterface)

  /*!
   * brief Виджет настроек
   */
  OptimeSettings *_settings;

  /*!
   * \brief Время наработки КПА
   */
  QTime *_cveOperationTime;

  /*!
   * \brief Таймер для рассчета наработки КПА
   */
  QTimer *_cveOperationTimer;

  /*!
   * \brief Время наработки изделия
   */
  QTime *_productOperationTime;

  /*!
   * \brief Таймер для рассчета наработки изделия
   */
  QTimer *_productOperationTimer;

  /*!
   * \brief Таймер опроса состояния флагов опроса
   */
  QTimer *_pollingOptimesFlagsTimer;

  bool _cveOperationTimeAccumulateFlag;
  bool _productOperationTimeAccumulateFlag;

public:

  OptimeManager();

  ~OptimeManager() {
    writeCveAndProductOperationTime();
    finalize();
  }

  /*!
   * brief Создание виджетов модуля
   */
  void createWidgets();

  /*!
   * brief Возвращает виджет настроек менеджера
   * return
   */
  QWidget *getSettingPage();

  /*!
   * brief Возвращает иконку для настроек
   * return
   */
  QIcon settingIcon();

  /*!
   * \brief Создание действий
   */
  void createActions() {}

  /*!
   * \brief Созданией коннекторов
   */
  void createConnectors();


  /*!
   * brief Деинициализация элементов менеджера
   */
  void finalize();

public slots:
  /*!
   * \brief Чтение значения времени наработки из реестра
   */
  void writeCveAndProductOperationTime();

  /*!
   * \brief Запись значения времени наработки
   */
  void readCveAndProductOperationTime();

  /*!
   * \brief
   */
  void cveOperationTimerTick();

  /*!
   * \brief
   */
  void productOperationTimerTick();

  /*!
   * \brief
   */
  void pollingOptimesFlagsTimerTick();
};


#endif // OPTIME_MANAGER_H


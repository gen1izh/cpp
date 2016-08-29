#ifndef TESTSEQUENCE_EXECUTOR_TREE_MODEL_H
#define TESTSEQUENCE_EXECUTOR_TREE_MODEL_H

#include <QAbstractItemModel>
#include <QDir>
#include <QFile>
#include <QDebug>
#include <QSqlRecord>
#include <QSqlQuery>

#include <library/databasesapi/mysql/mysqldatabaseapi.h>
#include <library/message/messagelibrary.h>
#include <library/loggerapi/loggerapi.h>

#include "testsequenceexecutortreeitem.h"
#include <library/processDialog/processdialog.h>

#include "../../testsequencescriptapi.h"

class TestsequenceExecutorTreeModel : public QAbstractItemModel {

    Q_OBJECT

  TestsequenceScriptApi *_scripts;

  void createConnectors();

  /*!
   * \brief Название тестовой последовательности открытой для редактирования(внешнее представление)
   * Если создаем тест, то первоначально это поле будет пустым
   */
  QString *_testExternalName;

  /*!
   * \brief Название тестовой последовательности открытой для редактирования(внутреннее представление)
   * Если создаем тест, то первоначально это поле будет пустым
   */
  QString *_testInternalName;

  /*!
   * \brief Процесс загрузки тестовой последовательности
   */
  ProcessDialog _process;

  /*!
   * \brief Чтение тестовой последовательности из файла
   * \param[in] task -тест-кейс
   */
  void readTestSequenceTreeFromDatabase(TestsequenceExecutorTreeItem *task);

  /*!
   * \brief Запись всех узлов дерева проверок в базу данных
   * \param[in] id   - идентификатор
   * \param[in] task - тест-кейс
   */
  void writeTestcaseTreeToDatabase(int id, TestsequenceExecutorTreeItem *testcase ) /*const*/;

  /*!
   * \brief Проставить идентификаторы узлов
   * \param[in] testcase - тест-кейс
   */
  void rewriteTestcaseTreeNodesIds(TestsequenceExecutorTreeItem *testcase);

  /*!
   * \brief Возвращает index по путю тест-кейса
   * \param[in] parent - модельный индекс на родительский элемент
   * \param[in] path - путь
   * \return
   */
  QModelIndex indexForPath( const QModelIndex &parent,
                            const QStringList &path ) const;

  /*!
   * \brief Хеш состояний тест-кейсов
   */
  QHash<int, QString> _statusHash;

  /*!
   * \brief Список уровней в дереве тестовой последовательности
   */
  QList<int>  _level;

  /*!
   * \brief Признак запуска исполнителя тестовой последовательности
   */
  bool _isStarted;

  /*!
   * \brief Корневой тест-кейс
   */
  TestsequenceExecutorTreeItem *_rootItem;

  /*!
   * \brief addParams
   * \param item
   * \param idnode
   */
  void addParams(TestsequenceExecutorTreeItem *item, int idnode);

  /*!
   * \brief readTestsequenceStructure
   * \param testcase
   * \param name
   */
  void readTestsequenceStructure(TestsequenceExecutorTreeItem *testcase, QString name);

public:

    /*!
     * \brief Роль
     */
    enum Roles
    {
        DebugRole = Qt::UserRole
    };

    /*!
     *  Состояния тест-кейсов в тестовой последовательности
     */
    enum {
      TS_EXEC_FAIL = -1,
      TS_EXEC_SUCCESS,
      TS_EXECUTING,
      TS_PAUSED,
      TS_EXECUTED_EARLY,
      TS_ABORTING,
      TS_SKIPED,
      TS_LOADED,
      TS_DEBUG,
      TC_FAIL,
      TC_SUCCESS,
    };

    /*!
     * Нумерация колонок редактора тестовой последовательности
     */
    enum {
      Name = 0,
      DebugBreak,
      Status,
      ExecTime,
      AvarageTime,
      TestSequencesTableColumnsCount
    };

    explicit TestsequenceExecutorTreeModel(QObject *parent = 0);

    ~TestsequenceExecutorTreeModel() {
      delete _rootItem;
    }

    void setScripts(TestsequenceScriptApi *scripts) {
      _scripts = scripts;
    }

    TestsequenceScriptApi *script() {
      return _scripts;
    }

    /*!
     * \brief getTestsequenceStructureName
     * \return
     */
    QString getTestsequenceStructureName();

    /*!
     * \brief Установка указателя на внешнее имя тестовой последовательности
     * \param[in] name - название
     */
    void setTestsequenceExternalName(QString *name) { _testExternalName = name; }

    /*!
     * \brief Установка указателя на внутреннее имя тестовой последовательности
     * \param[in] name - название
     */
    void setTestsequenceInternalName(QString *name) { _testInternalName = name; }

    /*!
     * \brief Возвращает состояние тест-кейса
     * \param[in] state - индекс состояния
     * \return
     */
    QString getStatusString(int state) const;

    /*!
     * \brief Возвращает item по индексу
     * \paramin] index - модельный индекс
     * \return
     */
    TestsequenceExecutorTreeItem *itemForIndex(const QModelIndex &index) const;

    /*!
     * \brief Возвращает флаги
     * \param[in] index - модельный индекс
     * \return
     */
    Qt::ItemFlags flags(const QModelIndex &index) const;

    /*!
     * \brief Прорисовка тестовой последовательности в представлении
     * \param[in] index - модельный индекс
     * \param[in] role - роль
     * \return
     */
    QVariant data(const QModelIndex &index,
                  int role=Qt::DisplayRole) const;

    /*!
     * \brief Вовзращает главную строку таблицы
     * \param[in] section - секция
     * \param[in] orientation - ориентация
     * \param[in] role - роль
     * \return
     */
    QVariant headerData( int section, Qt::Orientation orientation,
                         int role=Qt::DisplayRole ) const;

    /*!
     * \brief Возвращает количество строк модели
     * \param[in] parent - модельный индекс на родителя
     * \return
     */
    int rowCount( const QModelIndex &parent = QModelIndex() ) const;

    /*!
     * \brief Возвращает количество колонок
     * \param[in] parent - модельный индекс на родителя
     * \return
     */
    int columnCount( const QModelIndex &parent = QModelIndex() ) const;

    /*!
     * \brief Вовращает модельный индекс по строке и колонке таблицы
     * \param[in] row - строка
     * \param[in] column - колонка
     * \param[in] parent - модельный индекс на родителя
     * \return
     */
    QModelIndex index( int row, int column,
                       const QModelIndex &parent = QModelIndex() ) const;

    /*!
     * \brief Возвращает родителя по модельному индексу
     * \param[in] index - модельный индекс
     * \return
     */
    QModelIndex parent(const QModelIndex &index) const;

    /*!
     * \brief Устанавливает главную строку таблицы
     * \return
     */
    bool setHeaderData( int, Qt::Orientation, const QVariant&,
                        int = Qt::EditRole ) {
      return false;
    }

    /*!
     * \brief Установка среднего времени на исполнение скрипта рекурсивно
     * \param[in] in - модельный индекс
     */
    void treewalkSetAvarageTimeTestSequence(const QModelIndex &in);

    /*!
     * \brief Верификация дерева тестовой последовательности
     * \param[in] in - модельный индекс
     * \return
     */
    QString treewalkVerify(const QModelIndex &in);

    /*!
     * \brief Обход всего дерева на наличие установленных флажков
     * \param[in] index - модельный индекс
     * \return
     */
    bool treewalkCheckBox(const QModelIndex &index);

    /*!
     * \brief Обход всего дерева. Очистка поля времени исполнения
     * \param[in] index - модельный индекс
     */
    void treewalkExecTimeClear(const QModelIndex &index);

    /*!
     * \brief Устанавливает данные в модель
     * \param[in] index - модельный индекс
     * \param[in] value - значение
     * \param[in] role  - роль
     * \return
     */
    bool setData( const QModelIndex &index, const QVariant &value,
                  int role=Qt::EditRole );

    /*!
     * \brief Вставка тест-кейса в модель
     * \param[in] row - строка
     * \param[in] count -счетчик
     * \param[in] parent - модельный индекс на родителя
     * \return
     */
    bool insertRows( int row, int count,
                     const QModelIndex &parent=QModelIndex() );

    /*!
     * \brief Удаляет тест-кейсы из модели
     * \param[in] row - строка
     * \param[in] count -счетчик
     * \param[in] parent - модельный индекс на родителя
     * \return
     */
    bool removeRows( int row, int count,
                     const QModelIndex &parent=QModelIndex() );

    /*!
     * \brief Установка иконки для определенного состояния таймера
     * \param[in] icon - иконка
     */
    void setIconForTimedItem(const QIcon &icon = QIcon());

    /*!
     * \brief Очистка модели
     */
    void clearModel();

    /*!
     * \brief Загрузить файл тестовой последовательности в модель
     */
    void load();

    /*!
     * \brief Возвращает путь до тест-кейса по индексу
     * \param[in] index - модельный индекс
     * \return
     */
    QStringList pathForIndex(const QModelIndex &index) const;

    /*!
     * \brief Возвращает индекс по путю к тест-кейсу
     * \param[in] path - путь
     * \return
     */
    QModelIndex indexForPath(const QStringList &path) const;

    /*!
     * \brief Возвращает корневой item тест-кейса
     * \return
     */
    TestsequenceExecutorTreeItem *getRootItem() {
      return _rootItem;
    }

    /*!
     * \brief Текущий, исполяемый item тест-кейса
     */
    TestsequenceExecutorTreeItem *currentExecItem;

    /*!
     * \brief Текущий, исполяемый index тест-кейса
     */
    QModelIndex            currentExecIndex;

    /*!
     * \brief Обновление состояния внешнего вида тест-кейса
     * \param[in] item - тест-кейс
     */
    void announceItemChanged(TestsequenceExecutorTreeItem *item);


  public slots:

    void loadInConcurrent(TestsequenceExecutorTreeItem *testcase);
    void testsequenceLoaded();
signals:

    /*!
     * \brief Изменение установки данных
     */
    void setDataChanged();

    void loaded();
};


#endif // TESTSEQUENCE_EXECUTOR_TREE_MODEL_H

#ifndef TESTSEQUENCE_EDITOR_TREE_MODEL_H
#define TESTSEQUENCE_EDITOR_TREE_MODEL_H

#include <library/databasesapi/mysql/mysqldatabaseapi.h>
#include <library/loggerapi/loggerapi.h>

#include "testsequenceeditortreeitem.h"


class TestSequencesEditorTreeModel : public QAbstractItemModel {

    Q_OBJECT

  void createConnectors();

  /*!
   *Нумерация колонок редактора тестовой последовательности
   */
  enum {
    Name = 0,
    Path,
    Description,
    TestSequencesTableColumnsCount
  };

  /*!
   * \brief Список уровней
   */
  QList<int> _level;

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
   * \brief Вырезанный тест-кейс
   */
  TestSequencesEditorTreeItem *_cutItem;

  /*!
   * \brief Объект процесса исполнения загрузки тестовой последовательности
   */
  ProcessDialog _process;

  /*!
   * \brief Корневой тест-кейс
   */
  TestSequencesEditorTreeItem *_rootItem;

  /*!
   * \brief Загрузка тестовой последовательности через поток
   * \param[in] testcase - тест-кейс
   */
  void loadInConcurrent(TestSequencesEditorTreeItem *testcase);

  /*!
   * \brief Добавление параметров в тест-кейс
   * \param[in] item - элемент тест-кейса
   * \param[in] idnode - идентификатор узла
   */
  void addParams(TestSequencesEditorTreeItem *item, int idnode);

  /*!
   * \brief Чтение структуры тестовой последовательности
   * \param[in] testcase - тест-кейс
   * \param[in] name - название
   */
  void readTestsequenceStructure(TestSequencesEditorTreeItem *testcase, QString name);


  /*!
   * \brief Запись всех узлов дерева проверок в базу данных
   * \param[in] id - идентификатор
   * \param[in] testcase - тест-кейс
   */
  void writeTestcaseTreeToDatabase(int id, TestSequencesEditorTreeItem *testcase) /*const*/;

  /*!
   * \brief Проставить идентификаторы узлов
   * \param[in] testcase - тест-кейс
   */
  void rewriteTestcaseTreeNodesIds(TestSequencesEditorTreeItem *testcase);

  /*!
   * \brief Возвращает название таблицы структуры тестовой последовательности выбранной
   * пользователем
   * \return
   */
  QString getTestsequenceStructureName();

  /*!
   * \brief Возвращает index по путю тест-кейса
   * \param[in] parent - родительский индекс
   * \param[in] path - путь
   * \return
   */
  QModelIndex indexForPath(const QModelIndex &parent,
                           const QStringList &path ) const;

  /*!
   * \brief Перемещение тест-кейса
   * \param[in] parent - родительский индекс
   * \param[in] oldRow - старая строка
   * \param[in] newRow - новая строка
   * \return
   */
  QModelIndex moveItem(TestSequencesEditorTreeItem *parent, int oldRow, int newRow);

  /*!
   * \brief Снимает рекурсивно исполнение всех элементов теста
   * \param[in] item Элемент
   * \return
   */
  void unsetChilds(TestSequencesEditorTreeItem *item, int &offset);

  /*!
   * \brief Устанавливает рекурсивно исполнение всех элементов теста
   * \param[in] item Элемент
   * \return
   */
  void setChilds(TestSequencesEditorTreeItem *item);


  public:

    explicit TestSequencesEditorTreeModel(QObject *parent = 0);

    ~TestSequencesEditorTreeModel() {
      delete _rootItem;
      delete _cutItem;
    }

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
     * \brief Возвращает item по индексу
     * \param[in] index - индекс
     * \return
     */
    TestSequencesEditorTreeItem *itemForIndex(const QModelIndex &index) const;

    /*!
     * \brief Возвращает флаги
     * \param[in] index - индекс
     * \return
     */
    Qt::ItemFlags flags(const QModelIndex &index) const;

    /*!
     * \brief Прорисовка тестовой последовательности в представлении
     * \param[in] index - индекс
     * \param[in] role - роль
     * \return
     */
    QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const;

    /*!
     * \brief Вовзращает главную строку таблицы
     * \param[in] section - номер
     * \param[in] orientation - ориентация
     * \param[in] role - роль
     * \return
     */
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role=Qt::DisplayRole) const;

    /*!
     * \brief Возвращает количество строк модели
     * \param[in] parent - родительский элемент
     * \return
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    /*!
     * \brief Возвращает количество колонок
     * \param[in] parent - родительский элемент
     * \return
     */
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    /*!
     * \brief Вовращает модельный индекс по строке и колонке таблицы
     * \param[in] row - строка
     * \param[in] column - колонка
     * \param[in] parent - родительский элемент
     * \return
     */
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;

    /*!
     * \brief Возвращает родителя по модельному индексу
     * \param[in] index - индекс
     * \return
     */
    QModelIndex parent(const QModelIndex &index) const;

    /*!
     * \brief Устанавливает главную строку таблицы
     * \return
     */
    bool setHeaderData(int, Qt::Orientation, const QVariant&,
                       int = Qt::EditRole) {
      return false;
    }

    /*!
     * \brief Устанавливает данные в модель
     * \param[in] index - индекс
     * \param[in] value - значение
     * \param[in] role - роль
     * \return
     */
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role=Qt::EditRole );

    /*!
     * \brief Вставка тест-кейса в модель
     * \param[in] row - строка
     * \param[in] count -количество
     * \param[in] parent - родительский элемент
     * \return
     */
    bool insertRows( int row, int count,
                     const QModelIndex &parent=QModelIndex() );

    /*!
     * \brief Удаляет тест-кейсы из модели
     * \param[in] row - строка
     * \param[in] count -количество
     * \param[in] parent - родительский элемент
     * \return
     */
    bool removeRows( int row, int count,
                     const QModelIndex &parent=QModelIndex() );

    /*!
     * \brief Проверяется выделенный элемент или нет.
     * Если выделен, но будет исполняться.
     * \param[in] index - индекс
     * \return
     */
    bool isChecked(const QModelIndex &index) const;

    /*!
     * \brief Возвращает вырезанный тест-кейс
     * \return
     */
    bool hasCutItem() const {
      return _cutItem;
    }

    /*!
     * \brief Очистка модели
     */
    void clearModel();

    /*!
     * \brief Возвращает путь до тест-кейса по индексу
     * \param[in] index - индекс
     * \return
     */
    QStringList pathForIndex(const QModelIndex &index) const;

    /*!
     * \brief Вовзращает индекс по путю к тест-кейсу
     * \param path
     * \return
     */
    QModelIndex indexForPath(const QStringList &path) const;

    /*!
     * \brief Возвращает корневой item тест-кейса
     * \return
     */
    TestSequencesEditorTreeItem *getRootItem() {
      return _rootItem;
    }

    /*!
     * \brief Обновление состояния внешнего вида тест-кейса
     * \param item
     */
    void announceItemChanged( TestSequencesEditorTreeItem *item );

    /***********************************************************************************
     *                      Проход по дереву тестовой последовательности
     ***********************************************************************************/

    /*!
     * \brief Верификация дерева тестовой последовательности
     * \param[in] index - индекс
     * \return
     */
    QString treewalkVerify(const QModelIndex &_index);

    /*!
     * \brief Обход всего дерева на наличие установленных флажков
     * \param[in] index - индекс
     * \return
     */
    bool treewalkCheckBox(const QModelIndex &index);

    /*!
     * \brief Обход всего дерева. Очистка поля времени исполнения
     * \param[in] index - индекс
     */
    void treewalkExecTimeClear(const QModelIndex &index);

    /***********************************************************************************
     *                         Редактирование тестовой последовательности
     ***********************************************************************************/

    /*!
     * \brief Перемещение тест-кейса вверх
     * \param[in] index - индекс
     * \return
     */
    QModelIndex moveUp(const QModelIndex &index);

    /*!
     * \brief Перемещение тест-кейса вниз
     * \param[in] index - индекс
     * \return
     */
    QModelIndex moveDown(const QModelIndex &index);

    /*!
     * \brief Вырезание тест-кейса
     * \param[in] index - индекс
     * \return
     */
    QModelIndex cut(const QModelIndex &index);

    /*!
     * \brief Вставка тест-кейса
     * \param[in] index - индекс
     * \return
     */
    QModelIndex paste(const QModelIndex &index);

    /*!
     * \brief Продвижение тест-кейса вперед по дереву
     * \param[in] index - индекс
     * \return
     */
    QModelIndex promote(const QModelIndex &index);

    /*!
     * \brief Понижение тест-кейса вниз по дереву
     * \param[in] index - индекс
     * \return
     */
    QModelIndex demote(const QModelIndex &index);

    /*!
     * \brief Сохранить модель тестовой последовательности
     */
    void save();

    /*!
     * \brief Загрузка дерева тестовой последовательности в модель
     */
    void load();

  public slots:
    /*!
     * \brief Слот финиша загрузки тестовой последовательности
     */
    void testsequenceLoaded();

  signals:

    /*!
     * \brief Сигнал изменения модели
     */
    void change();

    /*!
     * \brief Сигнал того что тестовая последовательность загрузилась
     */
    void loaded();
};


#endif // TESTSEQUENCE_EDITOR_TREE_MODEL_H

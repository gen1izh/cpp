#ifndef TESTSEQUENCE_EXECUTOR_TREE_ITEM_H
#define TESTSEQUENCE_EXECUTOR_TREE_ITEM_H

#include <QList>
#include <QPair>
#include <QIcon>

class TestsequenceExecutorTreeItem {

  /*!
   * \brief Путь до скрипта
   */
  QString _path;

  /*!
   * \brief Признак необходимости исполнения тест-кейса
   */
  QString _exectable_flag;

  /*!
   * \brief Брейк-поинт
   */
  bool _debugBreak;

  /*!
   * \brief Имя тест-кейса
   */
  QString _name;

  /*!
   * \brief Статус тест-кейса
   */
  QString _status;

  /*!
   * \brief Среднее время исполнения тест-кейса
   */
  QString _avarage_time;

  /*!
   * \brief Время исполнения тест-кейса
   */
  QString _exec_time;

  /*!
   * \brief Идентификатор тест-кейса
   */
  int _id;

  /*!
   * \brief Иконка исполняемого процесса тест-кейса
   */
  QIcon _icon;

  /*!
   * \brief Список параметров для тест-кейса
   */
  QList< QPair < QString, QString > > _parameters;

  /*!
   * \brief Указатель на родительский тест-кейс
   */
  TestsequenceExecutorTreeItem *_parent;

  /*!
   * \brief Список указателей на дочернии тест-кейсы
   */
  QList< TestsequenceExecutorTreeItem* > _children;

  public:
    /*!
     * \brief Конструктор элемента дерева тестовой последовательности
     * \param[in] name       - название тестовой последовательности
     * \param[in] avarage    - среднее время исполнения тест-кейса
     * \param[in] debugBreak - брейк-поинт на тест-кейс
     * \param[in] parent     - указатель на родительский тест-кейс
     */
    explicit TestsequenceExecutorTreeItem(
      const QString &name    = QString(),
      const QString &avarage = QString(),
      const bool debugBreak  = false,
      TestsequenceExecutorTreeItem *parent = 0);


    ~TestsequenceExecutorTreeItem() {
       qDeleteAll(_children);
     }

    /*!
     * \brief Возвращает имя тест-кейса
     * \return
     */
      QString name() const { return _name; }

    /*!
     * \brief Устанавливает имя тест-кейса
     * \param[in] name - название тест-кейса
     */
      void setName(const QString &name) { _name = name; }

    /*!
     * \brief Возвращает статус тест-кейса
     * \return
     */
      QString status() const { return _status; }

  /*!
   * \brief  Устанавливает статус тест-кейса
   * \param[in] state - состояние тест-кейса
   */
    void setStatus(QString state) { _status = state; }

  /*!
   * \brief Возвращает время выполнения тестовой последовательности
   * \return
   */
    QString execTime() const { return _exec_time; }

  /*!
   * \brief Устанавливает время выполнения тестовой последовательности
   * \param[in] time - устанавливает текущее время исполнения скрипта
   */
    void setExecTime(QString time) { _exec_time = time; }

  /*!
   * \brief Возвращает среднее время выполнения тестовой последовательности
   * \return
   */
    QString avarageTime() const { return _avarage_time; }

  /*!
   * \brief Устанавливает среднее время выполнения тестовой последовательности
   * \param[in] time - устанавливает среднее время исполнения тест-кейса
   */
    void setAvarageTime( QString time ) { _avarage_time = time; }

  /*!
   * \brief Возвращает идентификатор тесткейса
   * \return
   */
    int id() const { return _id; }

  /*!
   * \brief Устанавливает идентификатор тесткейса
   * \param[in] id - идентификатор тест-кейса
   */
    void setId(const int id) { _id = id; }

  /*!
   * \brief Очистка параметра
   */
    void clearParam() { _parameters.clear(); }

  /*!
   * \brief Возвращает иконку исполнения тест-кейса
   * \return
   */
    QIcon icon() const { return _icon; }

    /*!
     * \brief Устанавливает иконку исполнения тест-кейса
     * \param[in] icon - иконка
     */
    void setIcon(QIcon icon) { _icon = icon; }

    /*!
     * \brief Добавляет параметры для скрипта тест-кейса
     * \param[in] p - пара параметров
     */
      void addParam(QPair<QString, QString> p) { _parameters.append(p); }

    /*!
     * \brief Возвращает параметры
     * \return
     */
    QList< QPair < QString, QString > > params() const { return _parameters; }

    /*!
     * \brief Возвращает признак необходимости исполнения тест-кейса
     * \return
     */
    QString isExectable() const { return _exectable_flag; }

    /*!
     * \brief Устанавливает признак необходимости исполнения тест-кейса
     * \param[in] flag - флаг исполнения
     */
    void setExectableFlag(bool flag) {
      if (flag) {
        _exectable_flag = "1";
      }
      else {
        _exectable_flag = "0";
      }
    }

    /*!
     * \brief Возвращает путь до скрипта тест-кейса
     * \return
     */
      QString path() { return _path; }

    /*!
     * \brief Устанавливает путь до скрипта тест-кейса
     * \param[in] path - путь до скрипта
     */
      void setPath( const QString &path ) { _path = path; }

    /*!
     * \brief Возвращает указатель на родителя
     * \return
     */
    TestsequenceExecutorTreeItem *parent() const { return _parent; }

    /*!
     * \brief Возвращает тест-кейс по номеру строки в дереве
     * \param[in] row - номер строки
     * \return
     */
    TestsequenceExecutorTreeItem *childAt(int row) const {
      return _children.value(row);
    }

    /*!
     * \brief Возвращает строку по элементу тест-кейса
     * \param[in] child - возвращает строки по тест-кейсу
     * \return
     */
    int rowOfChild(TestsequenceExecutorTreeItem *child) const {
      return _children.indexOf(child);
    }

    /*!
     * \brief Возвращает количество дочерних тест-кейсов
     * \return
     */
    int childCount() const {
      return _children.count();
    }

    /*!
     * \brief Проверка наличия дочерних тест-кейсов
     * \return
     */
    bool hasChildren() const {
      return !_children.isEmpty();
    }

    /*!
     * \brief Возвращает список указателей на тест-кейсы
     * \return
     */
    QList<TestsequenceExecutorTreeItem *> children() const {
      return _children;
    }

    /*!
     * \brief Вставляет тест-кейс в список дочерних
     * \param[in] row - номер стркои
     * \param[in] item - тест-кейс
     */
    void insertChild(int row, TestsequenceExecutorTreeItem *item) {
      item->_parent = this;
      _children.insert(row, item);
    }

    /*!
     * \brief Добавление дочернего тест-кейса
     * \param[in] item - тест-кейс
     */
    void addChild(TestsequenceExecutorTreeItem *item) {
      item->_parent = this;
      _children << item;
    }

    /*!
     * \brief Меняет местами два элемента тест-кейса
     * \param[in] oldRow - старый номер строки
     * \param[in] newRow - новый номер строки
     */
    void swapChildren(int oldRow, int newRow) {
      _children.swap(oldRow, newRow);
    }

    /*!
     * \brief Установка брейк-поинта
     * \param[in] value - установка точки останова
     */
    void setDebugBreak(bool value) { _debugBreak = value; }

    /*!
     * \brief брейк-поинт
     * \return
     */
    bool debugBreak() const { return _debugBreak; }

    /*!
     * \brief Изымает элемент тест-кейса из тестовой последовательности
     * \param[in] row - номер строки
     * \return
     */
    TestsequenceExecutorTreeItem* takeChild(int row);

};

Q_DECLARE_METATYPE(TestsequenceExecutorTreeItem)

#endif // TESTSEQUENCE_EXECUTOR_TREE_ITEM_H

#ifndef TESTSEQUENCE_EDITOR_TREE_ITEM_H
#define TESTSEQUENCE_EDITOR_TREE_ITEM_H

#include <QTableWidget>
#include <QTableWidgetItem>

#include <library/processDialog/processdialog.h>

class TestSequencesEditorTreeItem {

  /*!
   * \brief Отрадочный брейк-поинт
   */
  bool _debugBreak;

  /*!
   * \brief Имя тест-кейса
   */
  QString _name;

  /*!
   * \brief Признак необходимости исполнения тест-кейса
   */
  QString _exectable_flag;

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
   * \brief Описание тест-кейса
   */
  QString _desc;

  /*!
   * \brief Идентификатор тест-кейса
   */
  int _id;

  /*!
   * \brief Путь до скрипта тест-кейса
   */
  QString _path;

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
  TestSequencesEditorTreeItem *_parent;

  /*!
   * \brief Список указателей на дочернии тест-кейсы
   */
  QList< TestSequencesEditorTreeItem* > _children;

  public:
    /*!
     * \brief Конструктор элемента дерева тестовой последовательности
     * \param[in] name       - имя тест-кейса
     * \param[in] exectable  - признак исполнения
     * \param[in] avarage    - среднее время исполнения скрипта (TODO: Нет необходимости этого поля в редакторе)
     * \param[in] desc       - описание теста
     * \param[in] path       - путь до скрипта
     * \param[in] debugBreak - брейкпоинт (TODO: Нет необходимости этого поля в редакторе)
     * \param[in] parent     - указатель на родителя
     */
    explicit TestSequencesEditorTreeItem( const QString &name      = QString(),
                                          const QString &exectable = QString(),
                                          const QString &avarage   = QString(),
                                          const QString &desc      = QString(),
                                          const QString &path      = QString(),
                                          const bool debugBreak = false,
                                          TestSequencesEditorTreeItem *parent = 0 );

    ~TestSequencesEditorTreeItem() { qDeleteAll(_children); }

    /*!
     * \brief Возвращает имя тест-кейса
     * \return
     */
    QString name() const {
      return _name;
    }

    /*!
     * \brief Устанавливает имя тест-кейса
     * \param[in] name - название тест-кейса
     */
    void setName(const QString &name) {
      _name = name;
    }

    /*!
     * \brief Возвращает описание тест-кейса
     * \return
     */
    QString description() const {
      return _desc;
    }

    /*!
     * \brief Устанавливает описание тест-кейса
     * \param[in] desc - описание тест-кейса
     */
    void setDescription(const QString &desc) {
      _desc = desc;
    }

    /*!
     * \brief Возвращает идентификатор тесткейса
     * \return
     */
    int id() const {
      return _id;
    }

    /*!
     * \brief Устанавливает идентификатор тесткейса
     * \param[in] id - Установка идентификатора тест-кейса
     */
    void setId(const int id) {
      _id = id;
    }

    /*!
     * \brief Возвращает путь до скрипта тест-кейса
     * \return
     */
    QString path() {
      return _path;
    }

    /*!
     * \brief Устанавливает путь до скрипта тест-кейса
     * \param[in] path - путь до скрипта
     */
    void setPath( const QString &path ) {
      _path = path;
    }

    /*!
     * \brief Устанавливает параметры для скрипта тест-кейса
     * \param[in] t - элемент тест-кейса
     */
    void setParams(QTableWidget *t) {
      _parameters.clear();
      QTableWidgetItem *ptwItem1, *ptwItem2;
      for (int i = 0; i < 100 ; i++) {
        ptwItem1 = t->item( i,0 );
        ptwItem2 = t->item( i,1 );
        if ( !ptwItem1->text().isEmpty() ) {
          if ( ptwItem2->text().isEmpty() ) {
            break;
          } else {
            // записать
            QPair<QString, QString> p;
            p.first =  ptwItem1->text();
            p.second = ptwItem2->text();

            _parameters.append( p );
          }
        }
        else {
          break;
        }
      }
    }

    /*!
     * \brief Добавляет параметры для скрипта тест-кейса
     * \param[in] p - пара параметров
     */
    void addParam(QPair<QString, QString> p) {
      _parameters.append( p );
    }

    /*!
     * \brief Возвращает параметры
     * \return
     */
    QList< QPair < QString, QString > > params() const { return _parameters; }

    /*!
     * \brief Очистка параметра
     */
    void clearParam() { _parameters.clear(); }

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
     * \brief Возвращает иконку исполнения тест-кейса
     * \return
     */
    QIcon icon() const { return _icon; }

    /*!
     * \brief Устанавилвает иконку исполнения тест-кейса
     * \param[in] icon - установка иконки
     */
    void setIcon(QIcon icon) { _icon = icon; }

    /*!
     * \brief Возвращает указатель на родителя
     * \return
     */
    TestSequencesEditorTreeItem *parent() const { return _parent; }

    /*!
     * \brief Возвращает тест-кейс по номеру строки в дереве
     * \param[in] row - строка в дереве тестовой последовательности
     * \return
     */
    TestSequencesEditorTreeItem *childAt(int row) const { return _children.value(row); }

    /*!
     * \brief Возвращает строку по элементу тест-кейса
     * \param[in] child - тест-кейс тестовой последовательности
     * \return
     */
    int rowOfChild(TestSequencesEditorTreeItem *child) const { return _children.indexOf(child); }

    /*!
     * \brief Возвращает количество дочерних тест-кейсов
     * \return
     */
    int childCount() const { return _children.count(); }

    /*!
     * \brief Проверка наличия дочерних тест-кейсов
     * \return
     */
    bool hasChildren() const { return !_children.isEmpty(); }

    /*!
     * \brief Возвращает список указателей на тест-кейсы
     * \return
     */
    QList< TestSequencesEditorTreeItem* > children() const { return _children; }

    /*!
     * \brief Вставляет тест-кейс в список дочерних
     * \param[in] row -строка
     * \param[in] item - элемент
     */
    void insertChild(int row, TestSequencesEditorTreeItem *item) {
      item->_parent = this;
      _children.insert(row, item);
    }

    /*!
     * \brief Добавление дочернего тест-кейса
     * \param[in] item - элемент дерева
     */
    void addChild(TestSequencesEditorTreeItem *item) {
      item->_parent = this;
      _children << item;
    }

    /*!
     * \brief Меняет местами два элемента тест-кейса
     * \param[in] oldRow - старая строка
     * \param[in] newRow - новая строка
     */
    void swapChildren(int oldRow, int newRow) {_children.swap(oldRow, newRow);}

    /*!
     * \brief Установка брейкпоинта
     * \param[in] value - установка точки брейкпоинта
     */
    void setDebugBreak(bool value) { _debugBreak = value; }

    /*!
     * \brief Возвращает брейк-поинт
     * \return
     */
    bool debugBreak() const { return _debugBreak; }

    /*!
     * \brief Изымает элемент тест-кейса из тестовой последовательности
     * \param[in] row - строка
     * \return
     */
    TestSequencesEditorTreeItem* takeChild(int row);

};

Q_DECLARE_METATYPE(TestSequencesEditorTreeItem)

#endif // TESTSEQUENCE_EDITOR_TREE_ITEM_H

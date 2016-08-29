#ifndef REPORT_TREE_ITEM_H
#define REPORT_TREE_ITEM_H

#include <QString>
#include <QIcon>

class ReportTreeItem {

  /*!
   * \brief Идентификатор тест-кейса
   */
  int     _id;

  /*!
   * \brief Название элемента
   */
  QString _name;

  /*!
   * \brief Указатель на родительский
   */
  ReportTreeItem *_parent;

  /*!
   * \brief Состояние элемента
   */
  QString _status;

  /*!
   * \brief Иконка состояния тест-кейса
   */
  QIcon   _icon;

  /*!
   * \brief Описание элемента
   */
  QString _msg;

  /*!
   * \brief Длительность исполнения тестовой последовательности
   */
  QString _execTime;

  /*!
   * \brief Общее время
   */
  QString   _totaltime;

  /*!
   * \brief Список указателей на дочернии
   */
  QList< ReportTreeItem* > _children;

  public:

    /*!
     * \brief Конструктор элемента дерева отчета
     * \param[in] parent - указатель на родительский элемент
     */
    explicit ReportTreeItem(ReportTreeItem *parent = 0) : _parent(parent) {
      if (_parent != NULL) {
        _parent->addChild( this );
      }
    }

    /*!
     * Деструктор элемента дерева тестовой последовательности
     */
    ~ReportTreeItem() {
       qDeleteAll(_children);
     }

    /*!
     * \brief Устанавливает имя
     * \param[in] name - название
     */
    void setName(const QString &name) {
      _name = name;
    }

    /*!
     * \brief Возвращает имя
     * \return
     */
    QString name() const {
      return _name;
    }

    /*!
     * \brief Установка идентификатора
     * \param[in] id - идентификатор
     */
    void setId(int id) {
      _id = id;
    }

    /*!
     * \brief Получение идентификатора
     * \return
     */
    int id() {
      return _id;
    }

    /*!
     * \brief Устанавливает общее время исполнения
     * \param[in] time - время
     */
    void setTotaltime(QString time) {
      _totaltime = time;
    }

    /*!
     * \brief Возвращает общее время исполнения
     * \return
     */
    QString totaltime() const {
      return _totaltime;
    }

    /*!
     * \brief Устанавливает статус
     * \param[in] state - состояние
     */
    void setStatus(QString state) {
      _status = state;
    }

    /*!
     * \brief Возвращает статус
     * \return
     */
    QString status() const {
      return _status;
    }

    /*!
     * \brief Устанавливает текст сообщения
     * \param[in] msg - тесткт сообщения
     */
    void setMsg(QString msg) {
      _msg = msg;
    }

    /*!
     * \brief Возвращает текст сообщения
     * \return
     */
    QString msg() const {
      return _msg;
    }

    /*!
     * \brief Возвращает длительность исполнения
     * \return
     */
    QString execTime() const {
      return _execTime;
    }

    /*!
     * \brief Устанавливает длительность исполнения
     * \param[in] time - время
     */
    void setExecTime(QString time) {
      _execTime = time;
    }

    /*!
     * \brief Устанавливает иконку
     * \param[in] icon - иконка
     */
    void setIcon(QIcon icon) {
      _icon = icon;
    }

    /*!
     * \brief Возвращает иконку
     * \return
     */
    QIcon icon() const {
      return _icon;
    }

    /*!
     * \brief Устанавливает родителя
     */
    void setParent(ReportTreeItem *p) {
      _parent = p;
    }

    /*!
     * \brief Возвращает указатель на родителя
     * \return
     */
    ReportTreeItem *parent() const {
      return _parent;
    }

    /*!
     * \brief Возвращает элемент по номеру строки в дереве
     * \param[in] row - строка
     * \return
     */
    ReportTreeItem *childAt(int row) const {
      return _children.value(row);
    }

    /*!
     * \brief Возвращает строку по элементу
     * \param[in] child - указатель
     * \return
     */
    int rowOfChild(ReportTreeItem *child) const {
      return _children.indexOf(child);
    }

    /*!
     * \brief  Возвращает количество дочерних элементов
     * \return
     */
    int childCount() const {
      return _children.count();
    }

    /*!
     * \brief Проверка наличия дочерних
     * \return
     */
    bool hasChildren() const {
      return !_children.isEmpty();
    }

    /*!
     * \brief Возвращает список указателей на элемент
     * \return
     */
    QList< ReportTreeItem* > children() const {
      return _children;
    }

    /*!
     * \brief Вставляет элемент в список дочерних
     * \param[in] row - строка
     * \param[in] item - указатель на элемент
     */
    void insertChild(int row, ReportTreeItem *item);

    /*!
     * \brief Добавление дочернего элемента
     * \param[in] item - указатель на элемент
     */
    void addChild(ReportTreeItem *item);


    /*!
     * \brief Изымает элемент из отчета
     * \param[in] row - строка
     * \return
     */
    ReportTreeItem* takeChild(int row);

};



#endif // REPORT_TREE_ITEM_H

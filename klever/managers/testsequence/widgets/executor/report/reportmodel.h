#ifndef REPORT_MODEL_H
#define REPORT_MODEL_H

#include <QGridLayout>
#include <QWidget>
#include <QTreeView>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QFileInfo>
#include <QFile>
#include <QAbstractItemModel>
#include <QMenu>
#include <QSqlQuery>
#include <QSqlRecord>

#include <library/databasesapi/mysql/mysqldatabaseapi.h>
#include <managers/logger/cveLogger.h>

#include <library/processDialog/processdialog.h>

#include "reporttreeitem.h"


struct smallReportContentListStruct {
  int level;
  QString testName;
  QString description;
  QString result;
  QString time;
};

class ReportModel : public QAbstractItemModel {

    Q_OBJECT

  /*!
   * \brief Колонки представления отчета
   */
  enum Column {
    Name = 0,          // Название
    Status,            // Состояние
    Duration,          // Время исполнения
    Message,           // Сообщение
    ReportColumnCount  // Количество колонок
  };

  /*!
   * \brief Список уровней в дереве тестовой последовательности
   */
  QList<int>  _level;

  /*!
   * \brief Список пар идентификаторов сообщений и состояний этих сообщений
   */
  QList<QPair<int, QString> > _idStateList;

  /*!
   * \brief Список идентификаторов на тесткейсы
   */
  QList<QPair<int, QString> > _idTimeList;

  /*!
   * \brief Корневой элемент
   */
  QList<ReportTreeItem *> _items;

  /*!
   * \brief Корневой элемент
   */
  ReportTreeItem *_rootItem;

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
   * \brief Количество считанных строк
   */
  int _readRowsCount;

  /*!
   * \brief Проверка существовавния элемента по имени
   * \param[in] name - имя элемента
   * \return результат проверки
   */
  bool isItemByNameExist(QString name);

  /*!
   * \brief Возвращает индекс по путю элемента
   * \param[in] parent - родительский модельный индекс
   * \param[in] path - путь до элемента
   * \return модельный индекс
   */
  QModelIndex indexForPath( const QModelIndex &parent,
                            const QStringList &path );

  /*!
   * \brief Установка состояний у тесткейсов рекурсивно вверх
   * \param[in] id - идентификатор
   * \param[in] state - состояние
   */
  void setStateUp(int id, QString state);

  /*!
   * \brief Сложить два временных интервала
   * \param[in] t1 - первый временной интервал
   * \param[in] t2 - второй временной интервал
   * \return
   */
  QString addTime(QString t1, QString t2);

  /*!
   * \brief treewalkFindTestcaseByIDAndSetMessage
   * \param[in] in - модельный индекс
   * \param[in] parentIdVar - идентификатор родительского элемента
   * \return
   */
  ReportTreeItem *treewalkFindTestcaseByIDAndSetMessage(QModelIndex &in, int parentIdVar);

  /*!
   * \brief Установка времени исполнения тест-кейсов
   * \param[in] id - идентификатор
   */
  void setTestcasesTimeUp(int id, QString time);

public:

    explicit ReportModel(QObject *parent = 0): QAbstractItemModel(parent) {
      _rootItem          = NULL;
      _readRowsCount     = 0;
    }

    /*!
     * \brief Деструктор модели тестовой последовательности
     */
    ~ReportModel() {
      delete _rootItem;
    }

    /*!
     * \brief Возвращает item по индексу
     * \param[in] index - модельный индекс
     * \return
     */
    ReportTreeItem *itemForIndex( const QModelIndex &index ) const;

    /*!
     * \brief Возвращает флаги
     * \param[in] index - модельный индекс
     * \return
     */
    Qt::ItemFlags flags( const QModelIndex &index ) const;

    /*!
     * \brief Возвращает данные из модели
     * \param[in] index - модельный индекс
     * \param[in] role - роль
     * \return
     */
    QVariant data( const QModelIndex &index,
                   int role=Qt::DisplayRole ) const;

    /*!
     * \brief Возвращает главную строку таблицы
     * \param[in] section - колонка(в данном случае номер колонки)
     * \param[in] orientation - ориентация хидера
     * \param[in] role - роль
     * \return
     */
    QVariant headerData( int section, Qt::Orientation orientation,
                         int role=Qt::DisplayRole ) const;

    /*!
     * \brief Возвращает количество строк модели
     * \param[in] parent
     * \return
     */
    int rowCount( const QModelIndex &parent = QModelIndex() ) const;

    /*!
     * \brief Возвращает количество колонок
     * \param[in] parent - модельный индекс
     * \return
     */
    int columnCount( const QModelIndex &parent = QModelIndex() ) const;

    /*!
     * \brief Вовращает модельный индекс по строке и колонке таблицы
     * \param[in] row - строка
     * \param[in] column - колонка
     * \param[in] parent - указатель на родителя
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
     * \brief Устанавливает данные в модель
     * \param[in] index - модельный индекс
     * \param[in] value - значение
     * \param[in] role - роль
     * \return
     */
    bool setData( const QModelIndex &index, const QVariant &value,
                  int role=Qt::EditRole );

    /*!
     * \brief Очистка модели
     */
    void clear();

    /*!
     * \brief Создание root элемента
     */
    void createReportTreeItem() {
      _rootItem = new ReportTreeItem();
    }

    /*!
     * \brief Возвращает путь до элемента по индексу
     * \param[in] index - модельный индекс
     * \return
     */
    QStringList pathForIndex( const QModelIndex &index ) const;

    /*!
     * \brief Возвращает индекс по путю к элементу
     * \param[in] path - вовзращает индекс по путю к элементу
     * \return
     */
    QModelIndex indexForPath(const QStringList &path);

    /*!
     * \brief Возвращает корневой item тест-кейса
     * \return
     */
    ReportTreeItem *getRootItem() { return _rootItem; }

    /*!
     * \brief Устанавливает корневой item тест-кейса
     * \return
     */
    void setRootItem( ReportTreeItem *item) { _rootItem = item; }

    /*!
     * \brief Проходит по дереву отчета и создает отчет по основным элементам
     * помещает их в контейнер - с
     * \param[in] in - начальный модельный индекс
     * \param[in] deep - уровень, глубины вложений элементов
     * \param[in] c - контейнер
     */
    void treewalkGetMainResultsList(const QModelIndex &in, int deep, QList<smallReportContentListStruct> &c);

    /*!
     * \brief Установка времени по идентификатору
     * \param[in] id - идентификатор
     * \param[in] time - время исполнения тесткейса
     */
    void setExecTimeToReportById(int id, QString time);

    /*!
     * \brief Удаление корневого элемента
     */
    void deleteRootItem() {
      delete _rootItem;
      _rootItem = NULL;
      beginResetModel();
      endResetModel();;
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
     * \brief Финализация состояний тест-кейсов
     */
    void finalizeTestState();
  public slots:

    /*!
     * \brief Загрузка отчета тестовой последовательности
     * \param[in] testcase - Указатель на элемент дерева теста
     */
    void readReportTreeFromDatabase(ReportTreeItem *testcase);

    /*!
     * \brief Проход по дереву тестовых последовательностей для получания списка всех
     *  результатов тестирования
     * \param[in] in - начальный модельный индекс
     * \param[in] deep - уровень, глубины вложений элементов
     * \param[in] c - контейнер
     */
    void treewalkGetAllResultsList(const QModelIndex &in, int deep, QList<smallReportContentListStruct> &c);

};


#endif // REPORT_MODEL_H

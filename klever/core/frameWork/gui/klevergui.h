#ifndef _GUI_H
#define _GUI_H

#include <QMainWindow>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QObject>
#include <QSplashScreen>
#include <QToolBar>
#include <QCoreApplication>
#include <QDebug>
#include <QPluginLoader>

// Работа с формами модулей
#include "iformmanager.h"
// Работа с mdiarea
#include "mainwindow/mdiarea.h"
// Работа с журналом
#include <frameWork/managers.h>
#include <library/loggerapi/loggerapi.h>
#include <library/processDialog/processdialog.h>

#include <interfaces/itopmanager.h>


namespace Core {

    /*!
     * \brief Класс работы с графическим интерфейсом
     */
    class KleverGui : public QObject, public ITopManager {

      Q_OBJECT

      KleverGui();
      KleverGui(const KleverGui& root);
      KleverGui& operator=(const KleverGui&);

      /*!
       * \brief Хеш идентификаторов окон и иконок к ним
       */
      QHash< QString, QPointer<QWidget> > _froms;

      /*!
       * \brief Указатель на главную форму приложения
       */
      QMainWindow *_mainwindow;

      /*!
       * \brief Указатель на mdi area главной формы приложения
       */
      MdiArea     *_mdi;

      /*!
       * \brief Указатель на сплеш-скрин при запуске программы.
       */
      QSplashScreen *_splash;

      /*!
       * \brief Диалоговое окно процесса
       */
      ProcessDialog _procDialog;

      /*!
       * \brief Флаг ожидания окончания операции
       */
      bool          _waitingOperaion;


      public slots:
        /*!
         * \brief Функция блокирования MainWindow до окончания длительной операции
         * \param[in] msg - текст сообщения
         */
        void blockMainWindowByDialog(QString msg) {
          _waitingOperaion = true;
          emit blockMainWindowByDialogSignal(msg);
        }

        /*!
         * \brief Функция разблокирования MainWindow после окончания длительной операции
         */
        void unblockMainWindowByDialog() {
          _waitingOperaion = true;
          emit unblockMainWindowByDialogSignal();
        }

        /*!
         * \brief Функция блокирования MainWindow до окончания длительной операции
         * \param[in] msg - текст сообщения
         */
        void startDialog(QString msg);

        /*!
         * \brief Функция разблокирования MainWindow после окончания длительной операции
         */
        void closeDialog();

      public:

        /*!
         * \brief Инстанцирование класса
         * \return
         */
        static KleverGui& instance();

        /*!
         * \brief Загрузка ГИП
         * \return
         */
        int load();

        /*!
         * \brief Финализация работы ГИП
         */
        int finalize();

        /*!
         * \brief Панель активных окон
         */
        QToolBar *activWindowsListToolBar;

        /*!
         * \brief Указатель на интерфейс плагина форм
         */
        IFormManager *formManager;

        /*!
         * \brief Сплеш-скрин. Информирование о загрузке модуля.
         * \param[in] txt текст сообщения
         */
        void splashMessage(QString txt);

        /*!
         * \brief Инициализация сплеш скрина
         */
        void initializeSplashScreen();

        /*!
         * \brief Отключение сплеш-скрина
         * \param[in] w - указатель на главное окно
         */
        void finishSplashScreen();


        /*************************************************************************
         *                    Работа с указателями главного окна
         *************************************************************************/

        /*!
         * \brief Возвращает указатель главного окна
         * \return
         */
        QMainWindow *mainwindow() const { return _mainwindow; }

        /*!
         * \brief Возвращает указатель mdi area главного окна
         * \return
         */
        MdiArea *mdi() const { return _mdi; }

        /*!
         * \brief Инициализация плагина форм
         */
        void initializeFormManager();

        /*!
         * \brief Возвращает список форм
         * \return
         */
        QHash< QString, QPointer<QWidget> > forms() {
         return _froms;
       }

       /*!
        * \brief Добавление формы в список
        * \param id идентификатор формы (строковый)
        * \param h указатель на форму
        */
       void addForm( QString id, QPointer<QWidget> h ) {
         _froms[id] = h;
       }

       /*!
        * \brief Поиск SubWindow по идентификатору формы
        * \param[in] id идентификатор
        * \return указатель на SubWindow
        */
       QMdiSubWindow *findMdiChild(QString id);

        /*!
        * \brief Шаблон открытия окна с проверкой наличия данного окна в хеше окон.
        * Если такое окно уже существует, то оно не создается заново, а передает указатель
        * на существующее окно.
        */
        template <class T, class T2> void openWindow( QString id, QString title,
                                          QString msgPositiveResult,
                                          QString msgNegativeResult ) {

          QMdiSubWindow *existing = findMdiChild( id  );
          if ( existing ) {
            MdiArea *m;
            m = mdi();
            m->setActiveSubWindow( existing );
            existing->setVisible(true);

           ( (T2 *)mainwindow() )->statusBar()->showMessage(
                 msgPositiveResult, 2000 );

            Library::Logger::logInfo(this,msgPositiveResult);

           ((T2 *)mainwindow())->updateActivWindowsListOnToolBar();
           return;
         }

         QWidget *child = createMdiChild<T>( id );

         if ( child != NULL )  {

          ( (T2 *)mainwindow() )->statusBar()->showMessage(
                msgPositiveResult, 2000 );

           Library::Logger::logInfo(this,msgPositiveResult);

           child->setWindowTitle( title );
           child->show();
         }
         else {
           Library::Logger::logWarning(this,msgNegativeResult);
         }
         ((T2 *)mainwindow())->updateActivWindowsListOnToolBar();
        }


       /*!
        * \brief Шаблон открытия окна без проверкой наличия данного окна в хеше окон.
        * Если такое окно уже существует, то оно создается заново, а передает указатель
        * на новое окно.
        */
        template <class T, class T2> void openDinamicWindow(
           QString id, QString title,
           QString msgPositiveResult,
           QString msgNegativeResult ) {

          QWidget *child = createMdiChild<T>(id);

          if ( child != NULL )  {

           ((T2 *)mainwindow())->statusBar()->showMessage(
                 msgPositiveResult, 2000 );
            Library::Logger::logInfo(this,msgPositiveResult);

            child->setWindowTitle( title );
            child->show();
          }
          else {
            Library::Logger::logWarning(this,msgNegativeResult);
          }
          ((T2 *)mainwindow())->updateActivWindowsListOnToolBar();

        }

         /*!
          * \brief Создание mdi формы
          */
        template <class T> QWidget *createMdiChild(QString id) {
          QWidget       *child = NULL;
          QMdiSubWindow *ex    = NULL;

          child = new T();
          child->setObjectName(id);
          ex = new QMdiSubWindow();
          ex->setWidget(child);
          // Установка иконки на subwindow
          ex->setWindowIcon(child->windowIcon());

          // Добавление идентификатора и форму в хеш.
          addForm(id, child);

          QObject::connect(child, SIGNAL(setVisibleSignal(bool)),
                           ex, SLOT( setVisible(bool)));

          QObject::connect(child, SIGNAL(setVisibleSignal(bool)),mainwindow(),
                           SLOT( updateActivWindowsListOnToolBar()));

          ((MdiArea *)mdi())->addSubWindow(ex);

          if (ex) {
            ex->installEventFilter(this);
          }

          return child;
        }


       /*!
        * \brief Восстановить расположение элементов
        */
        void restoreDocksPosition();

       /*!
        * \brief Максимазация главного окна
        */
        void showMaximized();

       /*!
        * \brief Подготовка ГИП
        */
        void prepare();

       /*!
        * \brief Инициализация mainwindow и mdiarea
        */
        void initializeMainwindowAndMdi();

       /*!
        * \brief Проверка необходимости ожидания какой-либо операции
        * \return
        */
        bool isNeedWait() { return _waitingOperaion; }

      protected:

       /*!
        * \brief Обработчик события скрытия формы
        * \param[in] obj указатель на mdi subwindow
        * \param[in] event событие
        * \return
        */
        bool eventFilter(QObject *obj, QEvent *event);

      signals:
        /*!
         * \brief Функция блокирования MainWindow до окончания длительной операции
         * \param[in] msg - текст сообщения
         */
        void blockMainWindowByDialogSignal(QString msg);

        /*!
         * \brief Функция разблокирования MainWindow после окончания длительной операции
         */
        void unblockMainWindowByDialogSignal();
    };
}


#endif // _GUI_H

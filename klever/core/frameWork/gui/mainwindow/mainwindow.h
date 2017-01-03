#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QCloseEvent>
#include <QDockWidget>
#include <QListWidget>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QSettings>
#include <QSignalMapper>
#include <QStatusBar>
#include <QTextCodec>
#include <QTimer>
#include <QToolBar>
#include <QtWidgets>

/* Глобальные данные приложения */
#include <frameWork/base.h>
#include <frameWork/gui/klevergui.h>
#include <frameWork/managers.h>

#include <plugins/logger/logger.h>

#include <interfaces/ilogger.h>


class MainWindow : public QMainWindow {

    Q_OBJECT

protected:

    void closeEvent(QCloseEvent *event);

public:

    MainWindow( QWidget *parent = 0 );
    ~MainWindow();

    // Признак того что окно видимо и активно
    QWidget      *isVisibleAndActiveMdiChild();

    MdiArea       *mdiArea;

    QSignalMapper *windowMapper;

    QList<QPair<QDockWidget*,QPair<int,int> > > docksList;

    /*
                          Список пунктов главного меню
                                                                             */
    QMenu *settingMenu;
    QMenu *scriptsAndSequencesMenu;
    QMenu *panelMenu;
    QMenu *windowMenu;
    QMenu *devicesModulesMenu;


    /*
     * Инициализация mdi пространства
     */
    void initializeMdiArea() {
        mdiArea = new MdiArea(this);
        mdiArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAsNeeded );
        mdiArea->setVerticalScrollBarPolicy( Qt::ScrollBarAsNeeded );
    }

    /*
     * Установка маппа
     */
    void setMapper() {
        windowMapper = new QSignalMapper( this );
        QObject::connect( windowMapper, SIGNAL( mapped( QWidget* ) ),
                          this, SLOT( setActiveSubWindow( QWidget* ) ) );
    }

    /*
     * Настройка основных настроек приложения и стиля
     */
    void setupStyleAndMainSettings();

    QAction *appSettingAction() { return m_settingsAction; }

    QAction *moduleInfoAction() { return m_pluginInformationAction; }



public slots:
    // Слоты обновления списка активных окон
    void updateActivWindowsListOnMenu();
    void updateActivWindowsListOnToolBar();

    /*
     * Выделить активное окно приложения
     */
    void setActiveSubWindow( QWidget *window ) {
        if ( !window ) {
            return;
        }
        mdiArea->setActiveSubWindow( qobject_cast<QMdiSubWindow *>(window) );
    }

    /*
                          Создание элементов приложения
                                                                             */
    void createActions();
    void createConnectors();
    void createMenu();
    void createToolBars();
    void createDockWindows();
    void openDocument();
    void about();


private:

    void fillDocumentsActions();

    /*
                        Список пунктов меню быстрого запуска
                                                                             */

    QToolBar *windowToolBar;
    QToolBar *toolsToolBar;
    QToolBar *devicesModulesToolBar;

    /*
                                  Список действий
                                                                             */
    QAction *exitAppAct;
    QAction *closeWindowAct;
    QAction *closeAllWindowsAct;
    QAction *tileAct;
    QAction *cascadeAct;
    QAction *separatorAct;

    // Действие открытия окна Об
    QAction          *m_aboutAction;
    // Действие открытия окна с информацией о плагине
    QAction          *m_pluginInformationAction;
    // Действие открытия документации
    QList<QAction *>  m_documentsApi;
    // Действие открытия настроек приложения
    QAction          *m_settingsAction;

};

#endif // MAINWINDOW_H

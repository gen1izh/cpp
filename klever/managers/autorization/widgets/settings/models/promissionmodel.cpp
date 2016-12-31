#include "promissionmodel.h"
#include <library/orm/db/QDjango.h>
#include <library/orm/db/QDjangoQuerySet.h>

#include "promissionqdjangomodel.h"

#include <QMessageBox>
#include <QDebug>
#include <QCoreApplication>


PromissionModel::PromissionModel()
{

    m_db = QSqlDatabase::database("autorization");
    if (m_db.driverName()!="QSQLITE") {
        m_db = QSqlDatabase::addDatabase("QSQLITE", "autorization");
    }

    QString path = QString("%1/%2").arg(QCoreApplication::applicationDirPath()).arg("__autorization");
    m_db.setDatabaseName(path);
    m_db.open();

    QDjango::setDatabase(m_db);
    QDjango::registerModel<Promission>();

    QDjango::createTables();

    addPromission( tr("Возможность смотреть документацию приложения"),    "CAN_SEE_APP_DOCS",          "CONST" );
    addPromission( tr("Возможность смотреть настройки приложения"),       "CAN_SEE_APP_SETTINGS",      "CONST" );
    addPromission( tr("Возможность смотреть меню плагинов приложения"), "CAN_SEE_MANAGERS_MENU",     "CONST" );
    addPromission( tr("Возможность управлять настройками плагинов"),    "CAN_SEE_MANAGERS_SETTINGS", "CONST" );
    addPromission( tr("Возможность работать с панелями плагинов"),      "CAN_SEE_MANAGERS_TOOLBAR",  "CONST" );

    addPromission( tr("Возможность работать с элементами управления плагина на уровне 0"), "CAN_SEE_MANAGER_CONROLS_LEVEL_0",     "CONST" );
    addPromission( tr("Возможность работать с элементами управления плагина на уровне 1"), "CAN_SEE_MANAGER_CONROLS_LEVEL_1",     "CONST" );
    addPromission( tr("Возможность работать с элементами управления плагина на уровне 2"), "CAN_SEE_MANAGER_CONROLS_LEVEL_2",     "CONST" );

    addPromission( tr("Возможность работать с элементами управления плагина на уровне 0"), "CAN_SEE_MODULES_CONROLS_LEVEL_0",     "CONST" );
    addPromission( tr("Возможность работать с элементами управления плагина на уровне 1"), "CAN_SEE_MODULES_CONROLS_LEVEL_1",     "CONST" );
    addPromission( tr("Возможность работать с элементами управления плагина на уровне 2"), "CAN_SEE_MODULES_CONROLS_LEVEL_2",     "CONST" );

    addPromission( tr("Возможность смотреть меню модулей приложения"),      "CAN_SEE_MODULES_MENU",            "CONST" );
    addPromission( tr("Возможность смотреть настройки модулей приложения"), "CAN_SEE_MODULES_SETTINGS",        "CONST" );
    addPromission( tr("Возможность смотреть панели модулей приложения"),    "CAN_SEE_MODULES_TOOLBAR",         "CONST" );

    addPromission( tr("Возможность работать в отладочном режиме"), "DEBUG_MODE",                    "CONST" );

}

PromissionModel::~PromissionModel()
{
    m_db.close();
}

QStringList PromissionModel::selectAllPromission()
{
    QDjangoQuerySet<Promission> proms;
    QStringList tmp;

    tmp.clear();

    QList<QVariantMap> propertyMaps = proms.values(QStringList() << "name" << "signature" << "constant");
    foreach (const QVariantMap &propertyMap, propertyMaps) {
        tmp.append(propertyMap["name"].toString());
    }

    return tmp;
}

void PromissionModel::addPromission(QString name, QString signature, QString constant) {

    QDjangoQuerySet<Promission> proms;

    bool isFind = false;

    QList<QVariantMap> propertyMaps = proms.values(QStringList() << "name" << "signature" << "constant");
    foreach (const QVariantMap &propertyMap, propertyMaps) {
        if ((propertyMap["signature"].toString() == signature) &&
            (propertyMap["constant"].toString() == "CONST") &&
            (constant == "CONST")) {
          isFind = true;
        }
    }

    if (!isFind) {
      Promission *proms = new Promission;
      proms->setName(name);
      proms->setSignature(signature);
      proms->setConstant(constant);
      proms->save();
    }
}

void PromissionModel::updateModel()
{
    setStringList(selectAllPromission());
}

void PromissionModel::deletePromission(const QModelIndex &index)
{
    QStringList promsList;
    promsList.clear();

    QString name = data(index, Qt::DisplayRole).toString();
    removeRows(0, 1, index);

    QDjangoQuerySet<Promission> proms;
    QDjangoQuerySet<Promission> someProms;
    someProms = proms.filter(QDjangoWhere("name", QDjangoWhere::Equals, name));

    QList<QVariantMap> propertyMaps = someProms.values(QStringList() << "name" << "signature" << "constant");
    foreach (const QVariantMap &propertyMap, propertyMaps) {
        if (propertyMap["constant"].toString() != "CONST") {
          someProms.remove();
        }
        else {
          QMessageBox msgBox;
          msgBox.setText(tr("Вы пытаетесь удалить системное разрешение!"));
          msgBox.exec();
        }
    }

}

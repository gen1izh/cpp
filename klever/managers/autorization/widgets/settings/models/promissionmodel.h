#ifndef PROMISSION_MODEL_H
#define PROMISSION_MODEL_H
#include <QStringListModel>
#include <QtSql/QSqlDatabase>

class PromissionModel : public QStringListModel
{

  QSqlDatabase m_db;

public:
  PromissionModel();
  ~PromissionModel();

  QStringList selectAllPromission();

  void addPromission(QString name, QString signature, QString constant);

  void updateModel();

  void deletePromission(const QModelIndex &index);

};

#endif // PROMISSION_MODEL_H

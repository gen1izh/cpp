#ifndef SESSIONPROPERTYDIALOG_H
#define SESSIONPROPERTYDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>

class SessionPropertyDialog : public QDialog
{
    Q_OBJECT

    QLineEdit *_nameLineEdit;
    QLineEdit *_productTypeLineEdit;
    QComboBox *_rightsBox;
    QLineEdit *_serialNumberLineEdit;

    QGridLayout addNewSessionGridLayout;
    QPushButton acceptButton;

  public:
    explicit SessionPropertyDialog(QDialog *parent = 0);

    void execute();

  signals:

    /*!
     * \brief Добавление новой сессии
     * \param[in] name - название сессии
     * \param[in] product - продукт
     * \param[in] right - права доступа
     * \param[in] serial - серийный номер продукта
     */
    void insertNewSession(QString name, QString product, QString right, QString serial);

  public slots:
};

#endif // SESSIONPROPERTYDIALOG_H

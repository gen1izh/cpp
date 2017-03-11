#ifndef EDITORFORM_H
#define EDITORFORM_H

#include <QWidget>

#include <QShowEvent>

#include "highlight/highlighter.h"

#define DEFAULT_IMAGE_WIDTH 600
#define DEFAULT_IMAGE_HEIGHT 400

namespace Ui {
class EditorForm;
}

class EditorForm : public QWidget
{
    Q_OBJECT

public:
    explicit EditorForm(QWidget *parent = 0);
    ~EditorForm();

private slots:
    void on_scanGlossaryButton_clicked();
    void on_scanTermsButton_clicked();
    void on_browselButton_clicked();
    void on_addImageButton_clicked();
    void on_deleteImageButton_clicked();
    void on_picturesList_doubleClicked(const QModelIndex &index);
    void on_italicButton_clicked();
    void on_boldButton_clicked();
    void on_understrikeButton_clicked();
    void on_preButton_clicked();
    void on_titlesBox_currentTextChanged(const QString &arg1);
    void on_enumButton_clicked();
    void on_picturesList_clicked(const QModelIndex &index);
    void on_editNameButton_clicked();
    void on_titlesBox_activated(const QString &arg1);
    void on_paragraphBox_activated(const QString &arg1);
    void on_tableButton_clicked();
    void on_codeButton_clicked();
    void on_noteButton_clicked();
    void on_terminBox_activated(const QString &arg1);
    void on_pasteTemplateButton_clicked();
    void on_appendixBox_activated(const QString &arg1);
    void on_frBox_activated(const QString &arg1);
    void on_crBox_activated(const QString &arg1);
    void on_nfrBox_activated(const QString &arg1);
    void on_brBox_activated(const QString &arg1);
    void on_infoBox_activated(const QString &arg1);
    void on_glossaryBox_activated(const QString &arg1);
    void on_anchorButton_clicked();
    void on_gotoAnchorButton_clicked();
    void on_saveButton_clicked();
    void on_descriptionEdit_textChanged();

private:
    Ui::EditorForm *ui;
    Highlighter *m_highlighter;

    void loadDescription();
    void refreshImagesList();
    bool loadImage(const QString &fullPath, const QString &fileName);
protected:
     void showEvent(QShowEvent *event);
};

#endif // EDITORFORM_H

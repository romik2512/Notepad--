#ifndef TEXT_EDITOR_H
#define TEXT_EDITOR_H

#include <QMainWindow>

namespace Ui {
class Text_editor;
}

class Text_editor : public QMainWindow
{
    Q_OBJECT

public:
    explicit Text_editor(QWidget *parent = nullptr);
    ~Text_editor();

private slots:
    void OpenFile();
    void SaveAsFile();
    void SaveFile();
    void Quit();
    void NewFile();
    void SetFont();
    void SetFontColour();
    void SetBackgroundColour();


private:
    Ui::Text_editor *ui;

    QString File_name;
    QString Opened_file_name;
    QColor Pal;
    QPalette Bcolour;
    QColor fontColour;
};

#endif // TEXT_EDITOR_H

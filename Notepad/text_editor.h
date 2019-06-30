#ifndef TEXT_EDITOR_H
#define TEXT_EDITOR_H

#include <QMainWindow>
#include <QRegExp>
#include <QtQuick/QQuickTextDocument>
#include <QTextEdit>
#include "highlighter.h"

namespace Ui {
class Text_editor;
}

class Text_editor : public QMainWindow
{
    Q_OBJECT

public:
    explicit Text_editor(QWidget *parent = nullptr);
    enum codecType {
            UTF8 = 0,
            WINDOWS1251 = 1,
            IBM866 = 2,
            CP1251 = 3
        };
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
    void Undo();
    void Redo();
    void Paste();
    void Cut();
    void Copy();
    void codecWindows1251();
    void codecIBM866();
    void codecCP1251();
    void codecUTF8();
     void codecButton(codecType type);
    void HighOff();
    void HighOn();


private:
    Ui::Text_editor *ui;
   // Compiler* compiler;

    QString File_name, _str;
    QByteArray _strUTF8;

    QString Opened_file_name;
    QColor Pal;
    QPalette Bcolour;
    QColor fontColour;

    QShortcut *HotKeySave, *HotKeyOpen, *HotKeyUndo, *HotKeyRedo;

    Highlighter *highlighter;

    QTextEdit *editor;

    QTextCodec *codec;

};

#endif // TEXT_EDITOR_H

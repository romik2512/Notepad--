#include "text_editor.h"
#include "ui_text_editor.h"

#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QFontDialog>
#include <QPalette>
#include <QColorDialog>
#include <QShortcut>




Text_editor::Text_editor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Text_editor)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);

    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(OpenFile()));
    connect(ui->actionSave_as, SIGNAL(triggered()), this, SLOT(SaveAsFile()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(SaveFile()));
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(Quit()));
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(NewFile()));
    connect(ui->Font, SIGNAL(triggered()), this, SLOT(SetFont()));
    connect(ui->FontColour, SIGNAL(triggered()), this, SLOT(SetFontColour()));
    connect(ui->BackgroundColour, SIGNAL(triggered()), this, SLOT(SetBackgroundColour()));
    connect(ui->actionUndo, SIGNAL(triggered()), this, SLOT(Undo()));
    connect(ui->actionRedo, SIGNAL(triggered()), this, SLOT(Redo()));
    connect(ui->actionCut, SIGNAL(triggered()), this, SLOT(Cut()));
    connect(ui->actionPaste, SIGNAL(triggered()), this, SLOT(Paste()));
    connect(ui->actionCopy, SIGNAL(triggered()), this, SLOT(Copy()));


    HotKeySave = new QShortcut(this);
    HotKeySave->setKey(Qt::CTRL+Qt::Key_S);
    connect(HotKeySave, SIGNAL(activated()), this, SLOT(SaveFile()));

    HotKeyOpen = new QShortcut(this);
    HotKeyOpen->setKey(Qt::CTRL+Qt::Key_O);
    connect(HotKeyOpen, SIGNAL(activated()), this, SLOT(OpenFile()));

    HotKeyUndo = new QShortcut(this);
    HotKeyUndo->setKey(Qt::CTRL+Qt::Key_Z);
    connect(HotKeyUndo, SIGNAL(activated()), this, SLOT(Undo()));

    HotKeyRedo = new QShortcut(this);
    HotKeyRedo->setKey(Qt::CTRL+Qt::Key_U);
    connect(HotKeyRedo, SIGNAL(activated()), this, SLOT(Redo()));

}

Text_editor::~Text_editor()
{
    delete ui;

}

void Text_editor::SaveFile()
{
    QFile file(Opened_file_name);
      if(!file.open(QFile::WriteOnly | QFile::Text)) {
          QMessageBox::warning(this,"..","File was not saved!");
          return;
        }
      QTextStream out(&file);
      QString text = ui->textEdit->toPlainText();
      out << text;
      file.flush();
      file.close();
}

void Text_editor::SaveAsFile()
{
    Opened_file_name = QFileDialog::getSaveFileName();
        QFile out(Opened_file_name);
        if (out.open(QIODevice::WriteOnly)) {
            QTextStream stream(&out);
            QString text = ui->textEdit->toPlainText();
            stream << text;
            out.flush();
            out.close();
        }
}

void Text_editor::Quit()
{
    QApplication::quit();
}

void Text_editor::OpenFile()
{
    File_name = QFileDialog::getOpenFileName(this,"Open file");
      QFile file(File_name);
      Opened_file_name = File_name;
       if (File_name.isEmpty()) {return;}
        //if (!openTab(File_name)) {QMessageBox::warning(this,"ERROR","Файл уже открыт"); return;}
      if(!file.open(QFile::ReadOnly | QFile::Text)) {
          QMessageBox::warning(this,"..","I can't open this file!");
          return;
        }
      QTextStream in(&file);
      QString text = in.readAll();
      ui->textEdit->setText(text);
     // highlighter = new Highlighter(ui->textEdit->document());
      file.close();
}

void Text_editor::NewFile()
{
    Opened_file_name = "";
    ui->textEdit->setText("");
}

void Text_editor::SetFontColour()
{
    fontColour = QColorDialog::getColor();
    QPalette newPalette;
    newPalette.setColor(QPalette::Text,fontColour);
    ui->textEdit->setPalette(newPalette);
}

void Text_editor::SetFont()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);
    if (ok){
        ui->textEdit->setFont(font);
    }else return;
}

void Text_editor::SetBackgroundColour()
{
    Pal = QColorDialog::getColor();
    ui->textEdit->setStyleSheet("QTextEdit { background-color: "+Pal.name()+" }");
    ui->textEdit->show();
}

void Text_editor::Undo()
{
    ui->textEdit->undo();
}

void Text_editor::Redo()
{
    ui->textEdit->redo();
}

void Text_editor::Paste()
{
    ui->textEdit->paste();
}

void Text_editor::Cut()
{
    ui->textEdit->cut();
}

void Text_editor::Copy()
{
    ui->textEdit->copy();
}


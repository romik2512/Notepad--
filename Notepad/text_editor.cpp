#include "text_editor.h"
#include "ui_text_editor.h"

#include <QFileDialog>
#include <QTextStream>

#include <QMessageBox>


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
}

Text_editor::~Text_editor()
{
    delete ui;

}

void Text_editor::SaveFile()
{
    QFile file(Opened_file_name);
      if(!file.open(QFile::WriteOnly | QFile::Text)) {
          QMessageBox::warning(this,"..","I can't save file!");
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
      if(!file.open(QFile::ReadOnly | QFile::Text)) {
          QMessageBox::warning(this,"..","I can't open the file!");
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

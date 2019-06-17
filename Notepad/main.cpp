#include "text_editor.h"
#include "highlighter.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Text_editor w;
    w.show();

    return a.exec();
}

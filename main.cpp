#include <QApplication>
#include "fMenu.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    recongnizeWin reg;
    reg.show();


    return a.exec();
}




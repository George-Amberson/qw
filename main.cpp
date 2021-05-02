#include "QtWidgetsApplication1.h"
#include <QtWidgets/QApplication>
#include "View.h"
#include <fstream>
#include <iostream>
#pragma comment (lib,"opengl32.lib")

using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	View w;
	w.LoadData("C:\\Users\\George\\Desktop\\nv\\FOURDIX-1.bin");
	w.show();
    return a.exec();
}

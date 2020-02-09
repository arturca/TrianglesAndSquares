#include "src/triangles-and-squares.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	TrianglesAndSquares w;
	w.show();
	return a.exec();
}

#include "stdafx.h"
#include "gluttonous.h"
#include <QtWidgets/QApplication>
#include <QtPlugin>

Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin);

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Gluttonous w;
	w.show();
	return a.exec();
}

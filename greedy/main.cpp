#include "greedy.h"
#include <QtWidgets/QApplication>
#include <QtPlugin>

Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin);

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Greedy w;
	w.show();
	return a.exec();
}

#include <QApplication>
#include "weatherdashboard.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    WeatherDashboard w;
    w.show();
    return a.exec();
}

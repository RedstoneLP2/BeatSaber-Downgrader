#include "MainUI.h"
#include "common.h"
#include <QApplication>

int main(int argc, char** argv) {
    QApplication app (argc, argv);
    BeatsaberDowngraderWindow *window = new BeatsaberDowngraderWindow();
    return app.exec();
}


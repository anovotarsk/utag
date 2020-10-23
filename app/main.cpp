#include <iostream>
#include <tags.h>
#include <mainwindow.h>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    if (argc != 2) {
        MainWindow w("", nullptr, false);
        w.show();
        return a.exec();
    }
    MainWindow w(argv[1], nullptr, true);
    w.show();
    // MainWindow w(argv[1], nullptr, true);
    // w.show();
    return a.exec();
}


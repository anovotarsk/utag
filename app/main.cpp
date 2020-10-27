#include <iostream>
#include <tags.h>
#include <mainwindow.h>
#include <QMessageBox>

void check_arguments(int argc, char *argv[]) {
    DIR* d;
    std::string message = "";

    if (argc != 2) {
        QApplication a(argc, argv);
        QMessageBox b;
        b.setIcon(QMessageBox::Critical);
        b.setText("Invalid count of arguments!");
        b.show();
        exit(a.exec());
    }

    d = opendir(argv[1]);
    if (!d) {
        message += argv[1];
        message += ": ";
        message += strerror(errno);
        QApplication a(argc, argv);
        QMessageBox b;
        b.setIcon(QMessageBox::Critical);
        b.setText(message.c_str());
        b.show();
        exit(a.exec());
    }
    closedir(d);
}

int main(int argc, char *argv[]) {
    check_arguments(argc, argv);
    QApplication a(argc, argv);
    MainWindow w(argv[1]);
    w.show();
    return a.exec();
}

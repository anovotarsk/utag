#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QListWidgetItem>
#include <read_directory.h>
#include <tags.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(std::string dir, QWidget *parent = nullptr, bool status=true);
    ~MainWindow();

    void fill_listView();

private slots:
    void on_buttonEdit_clicked();
    void on_buttonSave_clicked();
    void on_listWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    std::vector<std::string> m_files;
    std::vector<std::string> m_pathes;
    bool m_status;

    void line_setEnable(bool flag);
    void fill_lines(std::string file);
};

#endif // MAINWINDOW_H

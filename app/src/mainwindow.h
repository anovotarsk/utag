#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QListWidgetItem>
#include <QMessageBox>
#include <read_directory.h>
#include <tags.h>
#include <algorithm>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(std::string dir, QWidget *parent = nullptr);
    ~MainWindow();

    void fill_listView();

private slots:
    void on_buttonEdit_clicked();
    void on_buttonSave_clicked();
    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_actionArtist_triggered();
    void on_actionAlbum_triggered();
    void on_actionTitle_triggered();
    void on_actionGenre_triggered();
    void on_actionReverse_triggered();
    void on_actionASCII_triggered();

private:
    Ui::MainWindow *ui;
    std::vector<std::string> m_pathes;

    void line_setEnable(bool flag);
    void fill_lines(std::string file);
    void clear_lines();
    std::string getName(std::string file); 
};

#endif // MAINWINDOW_H

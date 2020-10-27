#include "mainwindow.h"
#include "../resources/ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(std::string dir, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    line_setEnable(false);

    std::vector<std::pair<std::string, std::string>> files = read_directory(dir.c_str());
    for (auto i : files) {
        //m_files.push_back(i.second);
        m_pathes.push_back(i.first);
    }
    fill_listView();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::line_setEnable(bool flag) {
    ui->linePath->setEnabled(false);
    ui->lineArtist->setEnabled(flag);
    ui->lineAlbum->setEnabled(flag);
    ui->lineTitle->setEnabled(flag);
    ui->lineGenre->setEnabled(flag);
}

void MainWindow::on_buttonEdit_clicked()
{
    line_setEnable(true);
}

void MainWindow::on_buttonSave_clicked()
{
    int error;
    std::array <std::string, 4> tags;

    line_setEnable(false);

    if (ui->listWidget->currentRow() != -1) {
        errno = 0;
        tags[0] = ui->lineArtist->text().toStdString();
        tags[1] = ui->lineTitle->text().toStdString();
        tags[2] = ui->lineAlbum->text().toStdString();
        tags[3] = ui->lineGenre->text().toStdString();
        
        int index;
        for (; ui->listWidget->currentRow() != index && index < m_pathes.size(); index++);

        MP3File *mp3file = new MP3File(m_pathes[index]);
        error = mp3file->writeTags(tags);
        if (error != 0 && error != 22)
            QMessageBox::critical(nullptr, "", "This file is unwritable.\nPermission denied!");

        delete mp3file;
    }
}

void MainWindow::fill_listView() {
    for (auto i : m_pathes)
        ui->listWidget->addItem(getName(i).c_str());
}

void MainWindow::fill_lines(std::string file) {
    MP3File *mp3file = new MP3File(file);
    int error = mp3file->fileErrors(4);

    if (error == 0) {
        auto tags = mp3file->readTags();
        ui->linePath->clear();
        ui->lineArtist->clear();
        ui->lineTitle->clear();
        ui->lineAlbum->clear();
        ui->lineGenre->clear();

        ui->linePath->insert(file.c_str());
        ui->lineArtist->insert(tags[0].c_str());
        ui->lineTitle->insert(tags[1].c_str());
        ui->lineAlbum->insert(tags[2].c_str());
        ui->lineGenre->insert(tags[3].c_str());
    }
    else {
        QMessageBox::critical(nullptr, "", "This file is unreadable.\nPermission denied!");
    }

    delete mp3file;
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item) {
    int index = 0;

    line_setEnable(false);
    //QString::compare(item->text(), getName(m_pathes[index]).c_str()) != 0 &&
    for (; ui->listWidget->currentRow() != index && index < m_pathes.size(); index++);
    fill_lines(m_pathes[index]);
}

std::string MainWindow::getName(std::string file) {
    std::string name;

    int pos = file.rfind("/");
    if (pos != std::string::npos)
        for (int i = pos + 1; i < file.size(); i++)
            name += file[i];
    else
        name = file;
    return name;
}


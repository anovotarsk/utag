#include "mainwindow.h"
#include "../resources/ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(std::string dir, QWidget *parent, bool status) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_status(status)
{
    ui->setupUi(this);
    line_setEnable(false);

    if (m_status) {
        std::vector<std::pair<std::string, std::string>> files = read_directory(dir.c_str());
        for (auto i : files) {
            m_files.push_back(i.second);
            m_pathes.push_back(i.first);
        }
        fill_listView();
    }
    else
        ui->statusBar->showMessage("Invalid count of parameters!\nUsage: utag \"directory name\"");
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

    if (m_status) {
        errno = 0;
        tags[0] = ui->lineArtist->text().toStdString();
        tags[1] = ui->lineTitle->text().toStdString();
        tags[2] = ui->lineAlbum->text().toStdString();
        tags[3] = ui->lineGenre->text().toStdString();
        
        int index;
        for (; QString::compare(ui->listWidget->currentItem()->text(), m_files[index].c_str()) != 0; index++);

        MP3File *mp3file = new MP3File(m_pathes[index]);
        error = mp3file->writeTags(tags);
        if (error != 0)
            ui->statusBar->showMessage(strerror(error));

        delete mp3file;
    }
}

void MainWindow::fill_listView() {
    for (auto i : m_files)
        ui->listWidget->addItem(i.c_str());
}

void MainWindow::fill_lines(std::string file) {
    MP3File *mp3file = new MP3File(file);

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

    delete mp3file;
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item) {
    int index = 0;

    line_setEnable(false);
    
    for (; QString::compare(item->text(), m_files[index].c_str()) != 0; index++);
    fill_lines(m_pathes[index]);
}


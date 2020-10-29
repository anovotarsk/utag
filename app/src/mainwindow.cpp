#include "mainwindow.h"
#include "../resources/ui_mainwindow.h"


MainWindow::MainWindow(std::string dir, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    std::vector<std::pair<std::string, std::string>> files = read_directory(dir.c_str());

    ui->setupUi(this);
    line_setEnable(false);

    for (auto i : files)
        m_pathes.push_back(i.first);
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
        if (error == 2) {
            QMessageBox::critical(nullptr, "", "This file was deleted!");
            for (int i = index; i < m_pathes.size(); i++)
                m_pathes[i] =  m_pathes[i + 1];
            m_pathes.pop_back();
            fill_listView();
            clear_lines();
        }
        else
            if (error != 0 && error != 22)
                QMessageBox::critical(nullptr, "", "This file is unwritable.\nPermission denied!");
        delete mp3file;
    }
}

void MainWindow::fill_listView() {
    ui->listWidget->clear();
    for (auto i : m_pathes)
        ui->listWidget->addItem(getName(i).c_str());
}

void MainWindow::clear_lines() {
    ui->linePath->clear();
    ui->lineArtist->clear();
    ui->lineTitle->clear();
    ui->lineAlbum->clear();
    ui->lineGenre->clear();
}

void MainWindow::fill_lines(std::string file) {
    MP3File *mp3file = new MP3File(file);
    int error = mp3file->fileErrors(4);

    if (error == 0) {
        auto tags = mp3file->readTags();

        clear_lines();
        ui->linePath->insert(file.c_str());
        ui->lineArtist->insert(tags[0].c_str());
        ui->lineTitle->insert(tags[1].c_str());
        ui->lineAlbum->insert(tags[2].c_str());
        ui->lineGenre->insert(tags[3].c_str());
    }
    else {
        if (error == 2) {
            m_pathes.erase(m_pathes.begin() + ui->listWidget->currentRow());
            QMessageBox::critical(nullptr, "", "This file was deleted!");
            fill_listView();
            clear_lines();
        }
        else
            QMessageBox::critical(nullptr, "", "This file is unreadable.\nPermission denied!");
    }

    delete mp3file;
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item) {
    int index = 0;

    line_setEnable(false);
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

void MainWindow::on_actionArtist_triggered()
{
    std::sort(m_pathes.begin(), m_pathes.end(), compareArtist);
    fill_listView();
}


void MainWindow::on_actionAlbum_triggered()
{
    std::sort(m_pathes.begin(), m_pathes.end(), compareAlbum);
    fill_listView();
}


void MainWindow::on_actionTitle_triggered()
{
    std::sort(m_pathes.begin(), m_pathes.end(), compareTitle);
    fill_listView();
}

void MainWindow::on_actionGenre_triggered()
{
    std::sort(m_pathes.begin(), m_pathes.end(), compareGenre);
    fill_listView();
}

void MainWindow::on_actionReverse_triggered()
{
    std::reverse(m_pathes.begin(), m_pathes.end());
    fill_listView();
}

void MainWindow::on_actionASCII_triggered()
{
    std::sort(m_pathes.begin(), m_pathes.end());
    fill_listView();
}

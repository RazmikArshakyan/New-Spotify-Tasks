#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    player = new QMediaPlayer;
    audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);

    ui->pushButton_playPause->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->pushButton_seekBackward->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
    ui->pushButton_seekForward->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
    ui->pushButton_stop->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    ui->pushButton_volume->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));

    ui->horizontalSlider_volume->setMinimum(0);
    ui->horizontalSlider_volume->setMaximum(100);
    ui->horizontalSlider_volume->setValue(66);

    audioOutput->setVolume(ui->horizontalSlider_volume->value());

    connect(player, &QMediaPlayer::durationChanged, this, &MainWindow::durationChanged);
    connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::positionChanged);

    ui->horizontalSlider_duration->setRange(0, player->duration() / 1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::durationChanged(qint64 duration)
{
    mDuration = duration / 1000;
    ui->horizontalSlider_duration->setMaximum(mDuration);
}

void MainWindow::positionChanged(qint64 duration)
{
    if (!ui->horizontalSlider_duration->isSliderDown()) {
        ui->horizontalSlider_duration->setValue(duration / 1000);
    }
    updateDuration(duration / 1000);
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Select Video File"), "", tr("MP4 Files (*.mp4)"));

    video = new QVideoWidget();

    video->setGeometry(5, 5, ui->groupBox_video->width() - 10, ui->groupBox_video->height() - 10);
    video->setParent(ui->groupBox_video);

    player->setVideoOutput(video);

    player->setSource(QUrl::fromLocalFile(fileName));

    video->setVisible(true);
    video->show();
}

void MainWindow::on_pushButton_playPause_clicked()
{
    if (isPaused) {
        player->play();
        isPaused = false;
        ui->pushButton_playPause->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    }
    else {
        on_pushButton_stop_clicked();
    }
}

void MainWindow::on_pushButton_stop_clicked()
{
    player->pause();
    isPaused = true;
    ui->pushButton_playPause->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
}

void MainWindow::on_horizontalSlider_duration_valueChanged(int value)
{
    player->setPosition(value * 1000);
}

void MainWindow::on_pushButton_volume_clicked()
{
    if (!isMuted) {
        isMuted = true;
        ui->pushButton_volume->setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));
        audioOutput->setMuted(true);
    }
    else {
        isMuted = false;
        ui->pushButton_volume->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
        audioOutput->setMuted(false);
    }
}

void MainWindow::on_horizontalSlider_volume_valueChanged(int value)
{
    audioOutput->setVolume(value);
    if (value == 0) {
        isMuted = true;
        ui->pushButton_volume->setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));
    }
    else {
        isMuted = false;
        ui->pushButton_volume->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    }
}

void MainWindow::on_pushButton_seekBackward_clicked()
{
    ui->horizontalSlider_duration->setValue(ui->horizontalSlider_duration->value() - 10);
    player->setPosition(ui->horizontalSlider_duration->value() * 1000);
}

void MainWindow::on_pushButton_seekForward_clicked()
{
    ui->horizontalSlider_duration->setValue(ui->horizontalSlider_duration->value() + 10);
    player->setPosition(ui->horizontalSlider_duration->value() * 1000);
}

void MainWindow::updateDuration(qint64 duration)
{
    if (duration || mDuration) {
        QTime currentTime((duration / 3600) % 60, (duration / 60) % 60, duration % 10, (duration * 1000) % 1000);
        QTime totalTime((mDuration / 3600) % 60, (mDuration / 60) % 60, mDuration % 60, (mDuration * 1000) % 1000);

        QString format = "";
        if (mDuration > 3600) {
            format = "hh:mm:ss";
        }
        else {
            format = "mm:ss";
        }

        ui->label_currentTimer->setText(currentTime.toString(format));
        ui->label_totalTimer->setText(totalTime.toString(format));
    }
}

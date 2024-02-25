#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMultimedia>
#include <QtMultimediaWidgets>
#include <QtCore>
#include <QtWidgets>
#include <QtGui>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void durationChanged(qint64 duration);
    void positionChanged(qint64 duration);
    void on_actionOpen_triggered();
    void on_pushButton_playPause_clicked();
    void on_pushButton_stop_clicked();
    void on_horizontalSlider_duration_valueChanged(int value);
    void on_pushButton_volume_clicked();
    void on_horizontalSlider_volume_valueChanged(int value);
    void on_pushButton_seekBackward_clicked();
    void on_pushButton_seekForward_clicked();

private:
    void updateDuration(qint64 duration);

    Ui::MainWindow *ui;
    QAudioOutput* audioOutput;
    QMediaPlayer* player;
    QVideoWidget* video;
    qint64 mDuration;
    bool isPaused = true;
    bool isMuted = false;
};
#endif // MAINWINDOW_H

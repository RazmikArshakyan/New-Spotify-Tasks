#ifndef WEATHERDASHBOARD_H
#define WEATHERDASHBOARD_H

#include <QWidget>
#include <QNetworkReply>
#include <QLineEdit>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QVBoxLayout>
#include <QPushButton>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QTimer>

class WeatherDashboard : public QWidget {
    Q_OBJECT

public:
    explicit WeatherDashboard(QWidget *parent = nullptr);

private slots:
    void fetchWeather();
    void onWeatherResponse(QNetworkReply *reply);

private:
    QVBoxLayout *layout;
    QLabel *temperatureLabel;
    QLineEdit *locationInput;
    QNetworkAccessManager *manager;
    QTimer *timer;
};

#endif // WEATHERDASHBOARD_H

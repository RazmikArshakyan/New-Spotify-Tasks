#include "weatherdashboard.h"

WeatherDashboard::WeatherDashboard(QWidget *parent) : QWidget(parent) {
    layout = new QVBoxLayout();
    temperatureLabel = new QLabel("Temperature: N/A");
    locationInput = new QLineEdit();
    QPushButton *fetchButton = new QPushButton("Fetch Weather");

    layout->addWidget(temperatureLabel);
    layout->addWidget(locationInput);
    layout->addWidget(fetchButton);

    setLayout(layout);

    connect(fetchButton, &QPushButton::clicked, this, &WeatherDashboard::fetchWeather);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &WeatherDashboard::fetchWeather);
    timer->start(5 * 60 * 1000);

    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &WeatherDashboard::onWeatherResponse);
}

void WeatherDashboard::fetchWeather() {
    QString location = locationInput->text();
    QString url = "https://api.openweathermap.org/data/2.5/weather?q=" + location + "&appid=fecd42e455c70a537a3876cbd4b06d04";
    manager->get(QNetworkRequest(QUrl(url)));
}

void WeatherDashboard::onWeatherResponse(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonObject obj = doc.object();
        QJsonValue main = obj["main"];
        QJsonObject mainObj = main.toObject();
        double temp = mainObj["temp"].toDouble() - 273.15;
        QString temperature = QString::number(temp, 'f', 2) + "°C";
                                                              temperatureLabel->setText("Temperature: " + temperature);
    } else {
        temperatureLabel->setText("Error fetching weather data");
    }
    reply->deleteLater();
}

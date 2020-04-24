#include "authmanager.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>

AuthManager::AuthManager(QObject *parent) : QObject(parent)
{
    _isIndicatorRun = false;
}

void AuthManager::registering(const QString &login, const QString &passwod)
{
    _isIndicatorRun = true;

    QUrl url("http://127.0.0.1:50443/register");

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      "application/json");

    QJsonObject body;
    body["login"] = login;
    body["password"] = passwod;
    QByteArray bodyData = QJsonDocument(body).toJson();

    QNetworkReply *reply = _net.post(request, bodyData);

    connect(reply, &QNetworkReply::finished,
            [this, reply] {
                if (reply -> errorString() == "Неизвестная ошибка")
                    emit registerFinished();
                else
                    emit registerFailed(reply -> errorString());
                reply -> deleteLater();
    });

    _isIndicatorRun = false;
}

void AuthManager::authenticate(const QString &login, const QString &password)
{
    _isIndicatorRun = true;

    QUrl url("http://127.0.0.1:50443/auth");

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      "application/json");

    QJsonObject body;
    body["login"] = login;
    body["password"] = password;
    QByteArray bodyData = QJsonDocument(body).toJson();

    QNetworkReply *reply = _net.post(request, bodyData);

    connect(reply, &QNetworkReply::finished,
            [this, reply]{
                QString token = QJsonDocument::fromJson(reply -> readAll()).object().value("token").toString();
                emit authenticateRequestCompleted(reply -> errorString(), token);
                reply -> deleteLater();
    });

    _isIndicatorRun = false;
}

bool AuthManager::getindicatorRun()
{
    return _isIndicatorRun;
}

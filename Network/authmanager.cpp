#include "authmanager.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonObject>
#include <QJsonDocument>

AuthManager::AuthManager(QObject *parent) : QObject(parent)
{

}

void AuthManager::registering(const QString &login, const QString &passwod)
{
    QUrl url("http://127.0.0.1:59851/register");

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
                emit RegisterRequestCompleted(reply -> errorString());
                reply -> deleteLater();
    });
}

void AuthManager::authenticate(const QString &login, const QString &password)
{
    QUrl url("http://127.0.0.1:59851/auth");

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
                emit AuthenticateRequestCompleted(reply -> errorString(), token);
                reply -> deleteLater();
    });
}

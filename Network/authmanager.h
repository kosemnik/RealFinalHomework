#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QString>

class AuthManager : public QObject
{
    Q_OBJECT
public:
    explicit AuthManager(QObject *parent = nullptr);

    void registering (const QString &login,
                      const QString &passwod);
    void authenticate(const QString &login,
                      const QString &password);

private:
    QNetworkAccessManager _net;

signals:
    void RegisterRequestCompleted(QString);
    void AuthenticateRequestCompleted(QString, QString);
};
#endif // AUTHMANAGER_H

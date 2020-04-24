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

    Q_INVOKABLE void registering (const QString &login,
                      const QString &passwod);
    Q_INVOKABLE void authenticate(const QString &login,
                      const QString &password);

    Q_INVOKABLE bool getindicatorRun();

private:
    QNetworkAccessManager _net;
    bool _isIndicatorRun;

signals:
    void registerFinished();
    void registerFailed(QString error);
    void authenticateRequestCompleted(QString error, QString token);
};
#endif // AUTHMANAGER_H

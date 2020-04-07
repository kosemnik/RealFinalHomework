#include <QCoreApplication>
#include "authmanager.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    AuthManager auth;
    auth.registering("qwerty66612", "qwerty666");
    auth.authenticate("qwerty66612", "qwerty666");

    return a.exec();
}

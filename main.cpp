#include <QCoreApplication>
#include "Wallpaper.h"
#include "Client.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Client *client = new Client(QUrl(QStringLiteral("ws://ddns.mkacg.com:1996/sync")));
    QObject::connect(client, &Client::closed, &a, &QCoreApplication::quit);

    Wallpaper *w = new Wallpaper(client);
    return a.exec();
}

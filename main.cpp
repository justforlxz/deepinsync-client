#include <QCoreApplication>
#include "Wallpaper.h"
#include "Client.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("QtWebSockets example: echoclient");
    parser.addHelpOption();

    QCommandLineOption dbgOption(QStringList() << "d" << "debug",
            QCoreApplication::translate("main", "Debug output [default: off]."));
    parser.addOption(dbgOption);
    parser.process(a);
    bool debug = parser.isSet(dbgOption);

    Client *client = new Client(QUrl(QStringLiteral("ws://server.mkacg.com:1996")));
    QObject::connect(client, &Client::closed, &a, &QCoreApplication::quit);
    return a.exec();
}

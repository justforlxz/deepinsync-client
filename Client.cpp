#include "Client.h"
#include <QTimer>

Client::Client(const QUrl &url, QObject *parent) :
    QObject(parent),
    m_url(url)
{
    qDebug() << "WebSocket server:" << url;
    connect(&m_webSocket, &QWebSocket::connected, this, &Client::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &Client::closed);
    m_webSocket.open(QUrl(url));
}

void Client::onConnected()
{
    qDebug() << "WebSocket connected";
    connect(&m_webSocket, &QWebSocket::textMessageReceived,
            this, &Client::onTextMessageReceived);

    QTimer *t = new QTimer;
    t->start(1000);
    connect(t, &QTimer::timeout, this, [=]{
        m_webSocket.sendTextMessage(QStringLiteral("Hello, world!"));
    });
}

void Client::onTextMessageReceived(QString message)
{
    qDebug() << "Message received:" << message;
}

#include "Client.h"
#include <QJsonObject>
#include <QJsonDocument>

Client::Client(const QUrl &url, QObject *parent) :
    QObject(parent),
    m_url(url)
{
    m_webSocket = new QWebSocket;
    qDebug() << "WebSocket server:" << url;
//    connect(m_webSocket, &QWebSocket::connected, this, &Client::onConnected);
//    connect(&m_webSocket, &QWebSocket::disconnected, this, &Client::closed);
    m_webSocket->open(QUrl(url));
}

void Client::sendMessage(const QJsonObject &json)
{
    QJsonDocument doc(json);
    m_webSocket->sendTextMessage(QString(doc.toJson(QJsonDocument::Compact)));
}

QWebSocket *Client::websocket()
{
    return m_webSocket;
}

void Client::onConnected()
{
    qDebug() << "WebSocket connected";
//    connect(m_webSocket, &QWebSocket::textMessageReceived,\
            this, &Client::onTextMessageReceived);
}

void Client::onTextMessageReceived(QString message)
{
    qDebug() << "Message received:" << message;
}

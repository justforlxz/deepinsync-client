#include "Wallpaper.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QImage>
#include <QByteArray>
#include <QBuffer>
#include <QPixmap>

const QString Service = "com.deepin.daemon.Appearance";
const QString Path    = "/com/deepin/daemon/Appearance";

Wallpaper::Wallpaper(Client *client, QObject *parent) :
    QObject(parent),
    m_client(client),
    m_wallpaperDBus(new Appearance(Service, Path, QDBusConnection::sessionBus(), this))
{
    connect(m_client->websocket(), &QWebSocket::connected, this, &Wallpaper::bindingService);
}

void Wallpaper::bindingService()
{
    connect(m_wallpaperDBus, &Appearance::Changed, this, [=](const QString &in0, const QString &in1){
        if (in0 == "background") {
            QString f1 = in1;
            QFile file(f1.replace("file://", ""));
            if (!file.open(QIODevice::ReadOnly)) {
                qDebug() << file.error();
                return;
            }

            QFileInfo info(f1);
            QByteArray array = file.readAll();

            QJsonObject json;
            json.insert("background", array.toBase64().data());
            json.insert("filename", info.fileName());
            json.insert("type", info.completeSuffix());

            m_client->sendMessage(json);
        }
    });

    connect(m_client->websocket(), &QWebSocket::textMessageReceived, this,[=](const QString &message){
        qDebug() << "收到数据，正在设置...";
        QJsonDocument jsonDocument = QJsonDocument::fromJson(message.toLocal8Bit().data());
        QJsonObject obj = jsonDocument.object();
        QByteArray array = obj["background"].toString().toUtf8();
        array = QByteArray::fromBase64(array);

        QString path = "/tmp/" + obj["filename"].toString();

        QFile file(path);
        // Write contents of ba in file
        file.open(QIODevice::WriteOnly);
        qDebug() <<  file.write(array);
        // Close the file
        file.close();
        qDebug() << file.error();
        m_wallpaperDBus->Set("background", path);
    });
}

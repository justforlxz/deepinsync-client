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
            QString file = in1;
            QImage image(file.replace("file://", ""));
            QByteArray byteArray;
            QBuffer buffer(&byteArray);
            image.save(&buffer, "PNG");

            QJsonObject json;
            json.insert("background", byteArray.toBase64().data());
            m_client->sendMessage(json);
        }
    });

    connect(m_client->websocket(), &QWebSocket::textMessageReceived, this,[=](const QString &message){
        qDebug() << "收到数据，正在设置...";
        QJsonValue value(message);
        const QJsonObject obj = value.toObject();
        for (const QString &v : obj.keys()) {

            QByteArray byte_array = QJsonDocument(obj.value(v).toObject()).toJson();
            QByteArray Ret_bytearray;
            Ret_bytearray = QByteArray::fromBase64(byte_array);
            QBuffer buffer(&Ret_bytearray);
            buffer.open(QIODevice::WriteOnly);
            QPixmap imageresult;
            imageresult.loadFromData(Ret_bytearray);
            const QString path = "/tmp/1/1";
            imageresult.save(path);

            m_wallpaperDBus->Set(v, path);
        }
    });
}

#include "Wallpaper.h"

#include <QJsonObject>

const QString Service = "com.deepin.daemon.Appearance";
const QString Path    = "/com/deepin/daemon/Appearance";

Wallpaper::Wallpaper(Client *client, QObject *parent) :
    QObject(parent),
    m_client(client),
    m_wallpaperDBus(new Appearance(Service, Path, QDBusConnection::sessionBus(), this))
{
//    m_wallpaperDBus->setSync(false);
    connect(m_wallpaperDBus, &Appearance::Changed, this, [=](const QString &in0, const QString &in1){
        //构建json
        qDebug() << in0 << in1;
        if (in0 == "background") {
            QJsonObject json;
            json.insert("background", in1);
            m_client->sendMessage(json);
        }
    });
}

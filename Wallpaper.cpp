#include "Wallpaper.h"

const QString Service = "com.deepin.daemon.Appearance";
const QString Path    = "/com/deepin/daemon/Appearance";

Wallpaper::Wallpaper(QObject *parent) :
    QObject(parent),
    m_wallpaperDBus(new Appearance(Service, Path, QDBusConnection::sessionBus(), this))
{
    m_wallpaperDBus->setSync(false);
    connect(m_wallpaperDBus, &Appearance::Changed, this, [=](const QString &in0, const QString &in1){
          //个性化数据发生了改变，上传数据。
    });
}

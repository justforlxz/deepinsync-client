#ifndef WALLPAPER_H
#define WALLPAPER_H

#include <QObject>
#include <com_deepin_daemon_apperance.h>

using com::deepin::daemon::Appearance;

class Wallpaper : public QObject
{
    Q_OBJECT
public:
    explicit Wallpaper(QObject *parent = 0);

private:
    Appearance *m_wallpaperDBus;

};

#endif // WALLPAPER_H

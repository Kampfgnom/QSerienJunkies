#include "qserienjunkies.h"
#include <QSharedData>

#include "qserienjunkiesreply.h"

#include <QNetworkAccessManager>
#include <QRegularExpression>

static const QRegularExpression SEASON_NUMBER_REGEXP("(Season|Staffel) (\\d+)");
static const QString SEASON_LANGUAGE_ENGLISH("Season");
static const QString SEASON_LANGUAGE_GERMAN("Staffel");

QSerienJunkiesReply *QSerienJunkies::searchSeries(const QString &search)
{
    QSerienJunkiesReply *reply = new QSerienJunkiesReply;
    reply->searchSeries(search);
    return reply;
}

QSerienJunkiesReply *QSerienJunkies::searchSeasons(const QUrl &seriesUrl)
{
    QSerienJunkiesReply *reply = new QSerienJunkiesReply;
    reply->searchSeasons(seriesUrl);
    return reply;
}

QSerienJunkiesReply *QSerienJunkies::searchDownloads(const QUrl &seasonUrl)
{
    QSerienJunkiesReply *reply = new QSerienJunkiesReply;
    reply->searchDownloads(seasonUrl);
    return reply;
}

QSerienJunkiesReply *QSerienJunkies::decrypt(const QUrl &downloadLink)
{
    QSerienJunkiesReply *reply = new QSerienJunkiesReply;
    reply->decrypt(downloadLink);
    return reply;

}

static QNetworkAccessManager *nam = nullptr;

void QSerienJunkies::setNetworkAccessManager(QNetworkAccessManager *net)
{
    nam = net;
}

QNetworkAccessManager *QSerienJunkies::networkAccessManager()
{
    static QObject guard;

    if(!nam)
        nam = new QNetworkAccessManager(&guard);

    return nam;
}

int QSerienJunkies::seasonNumberFromTitle(const QString &title)
{
    QRegularExpressionMatch match = SEASON_NUMBER_REGEXP.match(title);
    if(!match.hasMatch())
        return -1;

    bool okay = false;
    int number = match.captured(2).toInt(&okay);

    if(!okay)
        return -1;

    return number;
}

QLocale::Language QSerienJunkies::seasonLanguageFromTitle(const QString &title)
{
    if(title.contains(SEASON_LANGUAGE_ENGLISH))
        return QLocale::English;

    if(title.contains(SEASON_LANGUAGE_GERMAN))
        return QLocale::German;

    return QLocale::AnyLanguage;
}

static QStringList episodeNumberRegExpList()
{
    // from XBMC: http://wiki.xbmc.org/index.php?title=Advancedsettings.xml#.3Ctvshowmatching.3E
    static QStringList list = QStringList()
            << QLatin1String("[Ss]([0-9]+)[][ ._-]*[Ee]([0-9]+)([^\\\\/]*)$") //  <!-- foo.s01.e01, foo.s01_e01, S01E02 foo, S01 - E02 -->
            << QLatin1String("[\\._ -]()[Ee][Pp]_?([0-9]+)([^\\\\/]*)$") //  <!-- foo.ep01, foo.EP_01 -->
            //<< "([0-9]{4})[\\.-]([0-9]{2})[\\.-]([0-9]{2})") //  <!-- foo.yyyy.mm.dd.* (byDate=true) -->
            //<< "([0-9]{2})[\\.-]([0-9]{2})[\\.-]([0-9]{4})") //  <!-- foo.mm.dd.yyyy.* (byDate=true) -->
            << QLatin1String("[\\\\/\\._ \\[\\(-]([0-9]+)x([0-9]+)([^\\\\/]*)$") //  <!-- foo.1x09* or just /1x09* -->
            << QLatin1String("[\\\\/\\._ -]([0-9]+)([0-9][0-9])([\\._ -][^\\\\/]*)$") //  <!-- foo.103*, 103 foo -->
            //<< "[\\/._ -]p(?:ar)?t[_. -]()([ivx]+)([._ -][^\\/]*)$") //  <!-- Part I, Pt.VI -->
            << QLatin1String("()[E|e]([0-9][0-9])")
            << QLatin1String("()([0-9][0-9])")
           ;

    return list;
}

int QSerienJunkies::episodeNumberFromName(const QString &name)
{
    foreach(QString exp, episodeNumberRegExpList()) {
        QRegularExpression regExp(exp);
        QRegularExpressionMatch match = regExp.match(name);
        if(match.hasMatch())
            return match.captured(2).toInt();
    }

    return -1;
}

int QSerienJunkies::seasonNumberFromName(const QString &name)
{
    foreach(QString exp, episodeNumberRegExpList()) {
        QRegularExpression regExp(exp);
        QRegularExpressionMatch match = regExp.match(name);
        if(match.hasMatch())
            return match.captured(1).toInt();
    }

    return -1;
}

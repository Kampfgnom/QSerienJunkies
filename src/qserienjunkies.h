#ifndef QSERIENJUNKIES_H
#define QSERIENJUNKIES_H

#include <QSharedDataPointer>

#include <qserienjunkiesreply.h>
#include <QLocale>

class QNetworkAccessManager;
class QUrl;

class QSerienJunkiesData;

class QSerienJunkies
{
public:
    static QSerienJunkiesReply *searchSeries(const QString &search);
    static QSerienJunkiesReply *searchSeasons(const QUrl &seriesUrl);
    static QSerienJunkiesReply *searchDownloads(const QUrl &seasonUrl);
    static QSerienJunkiesReply *decrypt(const QUrl &downloadLink);

    static void setNetworkAccessManager(QNetworkAccessManager *net);
    static QNetworkAccessManager *networkAccessManager();

    static int seasonNumberFromTitle(const QString &title);
    static QLocale::Language seasonLanguageFromTitle(const QString &title);

    static int seasonNumberFromName(const QString &name);
    static int episodeNumberFromName(const QString &name);
};

#endif // QSERIENJUNKIES_H

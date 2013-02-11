#include "qserienjunkies.h"
#include <QSharedData>

#include "qserienjunkiesreply.h"

#include <QNetworkAccessManager>

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

QNetworkAccessManager *QSerienJunkies::networkAccessManager()
{
    static QObject guard;
    static QNetworkAccessManager *nam = nullptr;

    if(!nam)
        nam = new QNetworkAccessManager(&guard);

    return nam;
}

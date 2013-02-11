#ifndef QSERIENJUNKIES_H
#define QSERIENJUNKIES_H

#include <QSharedDataPointer>

#include <qserienjunkiesreply.h>

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

    static QNetworkAccessManager *networkAccessManager();
};

#endif // QSERIENJUNKIES_H

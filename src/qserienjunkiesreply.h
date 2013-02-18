#ifndef QSERIENJUNKIESSEARCHRESULT_H
#define QSERIENJUNKIESSEARCHRESULT_H

#include <QObject>

#include <QSharedDataPointer>
#include <QStringList>
#include <QHash>
#include <QUrl>

class QSerienJunkiesReplyData;
class QNetworkReply;

class QSerienJunkiesReply : public QObject
{
    Q_OBJECT
public:
    struct Series {
        int id;
        QString name;
        QUrl url;
    };

    struct Season {
        QString title;
        QUrl url;
    };

    struct Format {
        QString description;
        QStringList mirrors;
    };

    struct DownloadLink {
        QString name;
        QUrl url;
    };

    ~QSerienJunkiesReply();

    QString errorString() const;

    // Series search
    QList<Series> series() const;

    // Seasons search
    QList<Season> seasons() const;

    // Downloads search
    QList<Format> formats() const;
    QList<DownloadLink> downloadLinks(const Format &format, const QStringList &mirrors) const;
    QList<DownloadLink> downloadLinks(const Format &format, const QString &mirror) const;

    // Decrypting
    QByteArray captcha() const;
    void solveCaptcha(const QString &captcha);
    QString packageName() const;
    QList<QUrl> urls() const;

Q_SIGNALS:
    void finished();
    void requiresCaptcha();
    void error();

private Q_SLOTS:
    void seriesSearchReplyFinished();
    void seriesLocationReplyFinished();
    void seasonSearchReplyFinished();
    void downloadSearchReplyFinished();
    void decryptLinkReplyFinished();
    void decryptedLinkReplyFinished();
    void onError();

private:
    friend class QSerienJunkies;
    QSerienJunkiesReply(QObject *parent = 0);

    void searchSeries(const QString &QString);
    void searchSeasons(const QUrl &seriesUrl);
    void searchDownloads(const QUrl &seasonUrl);
    void decrypt(const QUrl &url);
    void decryptLinkReplyFinishedHelper(const QString &page);

    QSharedDataPointer<QSerienJunkiesReplyData> data;

    Q_DISABLE_COPY(QSerienJunkiesReply)
};

#endif // QSERIENJUNKIESSEARCHRESULT_H

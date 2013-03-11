#include <QApplication>

#include "captchadialog.h"

#include <qserienjunkies.h>

#include <QUrl>
#include <QDebug>
#include <QFile>
#include <QPixmap>
#include <QLabel>
#include <QMainWindow>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //*
    {
        QSerienJunkiesReply *result = QSerienJunkies::searchSeries("White");

        QObject::connect(result, &QSerienJunkiesReply::finished, [&]() {
            qDebug() << "Series search finished";
            qDebug() << "Results:";
            foreach(QSerienJunkiesReply::Series r, result->series()) {
                qDebug() << r.id << r.name << r.url;
            }
            result->deleteLater();
            result = nullptr;
        });

        QObject::connect(result, &QSerienJunkiesReply::error, [&]() {
            qDebug() << "Error:" << result->errorString();
            result->deleteLater();
            result = nullptr;
        });
    }
    //*/

    //*
    {
        QSerienJunkiesReply *result = QSerienJunkies::searchSeasons(QUrl("http://serienjunkies.org/serie/white-collar/"));

        QObject::connect(result, &QSerienJunkiesReply::finished, [&]() {
            qDebug() << "Seasons search finished";
            qDebug() << "Results:";
            foreach(QSerienJunkiesReply::Season r, result->seasons()) {
                qDebug() << r.title << r.url;
            }
            result->deleteLater();
            result = nullptr;
        });

        QObject::connect(result, &QSerienJunkiesReply::error, [&]() {
            qDebug() << "Error:" << result->errorString();
            result->deleteLater();
            result = nullptr;
        });
    }
    //*/

    //*
    {
        QSerienJunkiesReply *result = QSerienJunkies::searchDownloads(QUrl("http://serienjunkies.org/white-collar/white-collar-season-4-hdtvweb-dl-xvid720p/"));

        QObject::connect(result, &QSerienJunkiesReply::finished, [&]() {
            qDebug() << "Downloads search finished";
            qDebug() << "Results:";

            foreach(auto format, result->formats()) {
                qDebug() << "Format:" << format.description;
                foreach(auto mirror, format.mirrors) {
                    qDebug() << "Mirror:" << mirror;
                    foreach(auto download, result->downloadLinks(format, mirror)) {
                        qDebug() << download.name << download.url;
                    }
                }
            }

            result->deleteLater();
            result = nullptr;
        });

        QObject::connect(result, &QSerienJunkiesReply::error, [&]() {
            qDebug() << "Error:" << result->errorString();
            result->deleteLater();
            result = nullptr;
        });
    }
    //*/

    // Create a mainwindow, so that accepting the captcha dialog does not close the application.
    QMainWindow window;
    window.show();

    CaptchaDialog dialog;
    {
        QSerienJunkiesReply *result = QSerienJunkies::decrypt(QUrl("http://download.serienjunkies.org/f-ae6c3e1b37fc9bac/ul_wc-xvid-S04E01.html"));

        QObject::connect(result, &QSerienJunkiesReply::requiresCaptcha, [&]() {
            dialog.setCaptcha(result->captcha());
            dialog.show();
        });

        QObject::connect(&dialog, &CaptchaDialog::solved, [&]() {
            result->solveCaptcha(dialog.solution());
        });

        QObject::connect(result, &QSerienJunkiesReply::finished, [&]() {
            qDebug() << "Decrypted:";
            qDebug() << result->urls();
            result->deleteLater();
            result = nullptr;
        });

        QObject::connect(result, &QSerienJunkiesReply::error, [&]() {
            qDebug() << "Error:" << result->errorString();
            result->deleteLater();
            result = nullptr;
        });
    }


    return a.exec();
}

#ifndef CAPTCHADIALOG_H
#define CAPTCHADIALOG_H

#include <QDialog>

namespace Ui {
class CaptchaDialog;
}

class CaptchaDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit CaptchaDialog(QWidget *parent = 0);
    ~CaptchaDialog();
    
    void setCaptcha(const QByteArray &captch);

    QString solution() const;

signals:
    void solved();

private:
    Ui::CaptchaDialog *ui;
};

#endif // CAPTCHADIALOG_H

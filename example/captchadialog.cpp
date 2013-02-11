#include "captchadialog.h"
#include "ui_captchadialog.h"

CaptchaDialog::CaptchaDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CaptchaDialog)
{
    ui->setupUi(this);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SIGNAL(solved()));
}

CaptchaDialog::~CaptchaDialog()
{
    delete ui;
}

void CaptchaDialog::setCaptcha(const QByteArray &captch)
{
    QImage image = QImage::fromData(captch);
    ui->captchaLabel->setPixmap(QPixmap::fromImage(image));
}

QString CaptchaDialog::solution() const
{
    return ui->lineEdit->text();
}

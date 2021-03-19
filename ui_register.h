/********************************************************************************
** Form generated from reading UI file 'register.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTER_H
#define UI_REGISTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_registerWin
{
public:
    QPushButton *cancelReg_bt;
    QGroupBox *userInfo_gb;
    QLabel *displayLabel;
    QPushButton *trainButton;
    QPushButton *samplerButton;
    QPushButton *returnButton;
    QLabel *noticeLabel;
    QLabel *serialNumLabel;
    QLabel *faceNumLabel;
    QLabel *detectResultLabel;
    QLabel *label_5;
    QLabel *label_2;
    QGroupBox *opsTips_gb;
    QGroupBox *realChan_gb;

    void setupUi(QWidget *registerWin)
    {
        if (registerWin->objectName().isEmpty())
            registerWin->setObjectName(QStringLiteral("registerWin"));
        registerWin->resize(1024, 600);
        registerWin->setStyleSheet(QStringLiteral("background-color: rgb(165, 206, 234);"));
        cancelReg_bt = new QPushButton(registerWin);
        cancelReg_bt->setObjectName(QStringLiteral("cancelReg_bt"));
        cancelReg_bt->setGeometry(QRect(80, 490, 151, 51));
        userInfo_gb = new QGroupBox(registerWin);
        userInfo_gb->setObjectName(QStringLiteral("userInfo_gb"));
        userInfo_gb->setGeometry(QRect(530, 60, 421, 251));
        displayLabel = new QLabel(registerWin);
        displayLabel->setObjectName(QStringLiteral("displayLabel"));
        displayLabel->setGeometry(QRect(80, 100, 371, 311));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(displayLabel->sizePolicy().hasHeightForWidth());
        displayLabel->setSizePolicy(sizePolicy);
        displayLabel->setMinimumSize(QSize(0, 0));
        displayLabel->setMaximumSize(QSize(16777215, 16777215));
        displayLabel->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        displayLabel->setAlignment(Qt::AlignCenter);
        trainButton = new QPushButton(registerWin);
        trainButton->setObjectName(QStringLiteral("trainButton"));
        trainButton->setGeometry(QRect(300, 430, 151, 51));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(trainButton->sizePolicy().hasHeightForWidth());
        trainButton->setSizePolicy(sizePolicy1);
        trainButton->setMinimumSize(QSize(151, 51));
        QFont font;
        font.setPointSize(8);
        trainButton->setFont(font);
        trainButton->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        samplerButton = new QPushButton(registerWin);
        samplerButton->setObjectName(QStringLiteral("samplerButton"));
        samplerButton->setGeometry(QRect(80, 430, 151, 51));
        sizePolicy1.setHeightForWidth(samplerButton->sizePolicy().hasHeightForWidth());
        samplerButton->setSizePolicy(sizePolicy1);
        samplerButton->setMinimumSize(QSize(151, 51));
        samplerButton->setFont(font);
        samplerButton->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        returnButton = new QPushButton(registerWin);
        returnButton->setObjectName(QStringLiteral("returnButton"));
        returnButton->setGeometry(QRect(300, 490, 151, 51));
        sizePolicy1.setHeightForWidth(returnButton->sizePolicy().hasHeightForWidth());
        returnButton->setSizePolicy(sizePolicy1);
        returnButton->setMinimumSize(QSize(151, 51));
        returnButton->setFont(font);
        returnButton->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        noticeLabel = new QLabel(registerWin);
        noticeLabel->setObjectName(QStringLiteral("noticeLabel"));
        noticeLabel->setGeometry(QRect(560, 360, 381, 161));
        sizePolicy.setHeightForWidth(noticeLabel->sizePolicy().hasHeightForWidth());
        noticeLabel->setSizePolicy(sizePolicy);
        noticeLabel->setMinimumSize(QSize(0, 0));
        noticeLabel->setFont(font);
        noticeLabel->setStyleSheet(QStringLiteral(""));
        noticeLabel->setAlignment(Qt::AlignCenter);
        serialNumLabel = new QLabel(registerWin);
        serialNumLabel->setObjectName(QStringLiteral("serialNumLabel"));
        serialNumLabel->setGeometry(QRect(850, 100, 81, 41));
        sizePolicy1.setHeightForWidth(serialNumLabel->sizePolicy().hasHeightForWidth());
        serialNumLabel->setSizePolicy(sizePolicy1);
        serialNumLabel->setMinimumSize(QSize(81, 41));
        serialNumLabel->setFont(font);
        serialNumLabel->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        serialNumLabel->setAlignment(Qt::AlignCenter);
        faceNumLabel = new QLabel(registerWin);
        faceNumLabel->setObjectName(QStringLiteral("faceNumLabel"));
        faceNumLabel->setGeometry(QRect(850, 150, 81, 41));
        sizePolicy1.setHeightForWidth(faceNumLabel->sizePolicy().hasHeightForWidth());
        faceNumLabel->setSizePolicy(sizePolicy1);
        faceNumLabel->setMinimumSize(QSize(81, 41));
        faceNumLabel->setFont(font);
        faceNumLabel->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        faceNumLabel->setAlignment(Qt::AlignCenter);
        detectResultLabel = new QLabel(registerWin);
        detectResultLabel->setObjectName(QStringLiteral("detectResultLabel"));
        detectResultLabel->setGeometry(QRect(570, 100, 221, 181));
        sizePolicy1.setHeightForWidth(detectResultLabel->sizePolicy().hasHeightForWidth());
        detectResultLabel->setSizePolicy(sizePolicy1);
        detectResultLabel->setMinimumSize(QSize(0, 0));
        detectResultLabel->setMaximumSize(QSize(16777215, 16777215));
        detectResultLabel->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        detectResultLabel->setAlignment(Qt::AlignCenter);
        label_5 = new QLabel(registerWin);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(800, 100, 51, 41));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);
        label_5->setMinimumSize(QSize(0, 0));
        label_5->setFont(font);
        label_5->setStyleSheet(QStringLiteral(""));
        label_5->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(registerWin);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(800, 150, 51, 41));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setMinimumSize(QSize(0, 0));
        label_2->setFont(font);
        label_2->setStyleSheet(QStringLiteral(""));
        label_2->setAlignment(Qt::AlignCenter);
        opsTips_gb = new QGroupBox(registerWin);
        opsTips_gb->setObjectName(QStringLiteral("opsTips_gb"));
        opsTips_gb->setGeometry(QRect(530, 320, 421, 231));
        realChan_gb = new QGroupBox(registerWin);
        realChan_gb->setObjectName(QStringLiteral("realChan_gb"));
        realChan_gb->setGeometry(QRect(60, 60, 421, 491));
        realChan_gb->raise();
        opsTips_gb->raise();
        displayLabel->raise();
        trainButton->raise();
        samplerButton->raise();
        returnButton->raise();
        noticeLabel->raise();
        userInfo_gb->raise();
        cancelReg_bt->raise();
        detectResultLabel->raise();
        label_5->raise();
        label_2->raise();
        serialNumLabel->raise();
        faceNumLabel->raise();

        retranslateUi(registerWin);

        QMetaObject::connectSlotsByName(registerWin);
    } // setupUi

    void retranslateUi(QWidget *registerWin)
    {
        registerWin->setWindowTitle(QApplication::translate("registerWin", "Form", 0));
        cancelReg_bt->setText(QApplication::translate("registerWin", "\345\217\226\346\266\210\346\263\250\345\206\214", 0));
        userInfo_gb->setTitle(QApplication::translate("registerWin", "\347\224\250\346\210\267\344\277\241\346\201\257", 0));
        displayLabel->setText(QString());
        trainButton->setText(QApplication::translate("registerWin", "\346\225\260\346\215\256\350\256\255\347\273\203", 0));
        samplerButton->setText(QApplication::translate("registerWin", "\344\272\272\350\204\270\351\207\207\346\240\267", 0));
        returnButton->setText(QApplication::translate("registerWin", "\350\277\224\345\233\236\344\270\273\351\241\265", 0));
        noticeLabel->setText(QString());
        serialNumLabel->setText(QString());
        faceNumLabel->setText(QString());
        detectResultLabel->setText(QString());
        label_5->setText(QApplication::translate("registerWin", "\347\274\226\345\217\267\357\274\232", 0));
        label_2->setText(QApplication::translate("registerWin", "\344\272\272\350\204\270\346\225\260\357\274\232", 0));
        opsTips_gb->setTitle(QApplication::translate("registerWin", "\346\223\215\344\275\234\346\217\220\347\244\272", 0));
        realChan_gb->setTitle(QApplication::translate("registerWin", "\345\256\236\346\227\266\351\200\232\351\201\223", 0));
    } // retranslateUi

};

namespace Ui {
    class registerWin: public Ui_registerWin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTER_H

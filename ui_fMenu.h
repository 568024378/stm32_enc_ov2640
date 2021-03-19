/********************************************************************************
** Form generated from reading UI file 'fMenu.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FMENU_H
#define UI_FMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_recongnizeWin
{
public:
    QWidget *centralwidget;
    QLabel *recResultLabel;
    QLabel *detectLabel;
    QPushButton *registerButton;
    QPushButton *settingButton;
    QPushButton *exitButton;
    QLabel *faceNumLabel;
    QLabel *label_2;
    QLabel *serialNumLabel;
    QLabel *label_3;
    QPushButton *takephotoButton;
    QLabel *camShow_lb;

    void setupUi(QMainWindow *recongnizeWin)
    {
        if (recongnizeWin->objectName().isEmpty())
            recongnizeWin->setObjectName(QStringLiteral("recongnizeWin"));
        recongnizeWin->resize(1024, 600);
        recongnizeWin->setStyleSheet(QStringLiteral("background-color: rgb(165, 206, 234);"));
        centralwidget = new QWidget(recongnizeWin);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        recResultLabel = new QLabel(centralwidget);
        recResultLabel->setObjectName(QStringLiteral("recResultLabel"));
        recResultLabel->setGeometry(QRect(700, 20, 301, 240));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(recResultLabel->sizePolicy().hasHeightForWidth());
        recResultLabel->setSizePolicy(sizePolicy);
        recResultLabel->setMinimumSize(QSize(300, 240));
        recResultLabel->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        recResultLabel->setAlignment(Qt::AlignCenter);
        detectLabel = new QLabel(centralwidget);
        detectLabel->setObjectName(QStringLiteral("detectLabel"));
        detectLabel->setGeometry(QRect(30, 10, 640, 480));
        sizePolicy.setHeightForWidth(detectLabel->sizePolicy().hasHeightForWidth());
        detectLabel->setSizePolicy(sizePolicy);
        detectLabel->setMinimumSize(QSize(320, 240));
        detectLabel->setStyleSheet(QStringLiteral("background-color: rgb(204, 137, 47);"));
        detectLabel->setAlignment(Qt::AlignCenter);
        registerButton = new QPushButton(centralwidget);
        registerButton->setObjectName(QStringLiteral("registerButton"));
        registerButton->setGeometry(QRect(700, 310, 301, 61));
        settingButton = new QPushButton(centralwidget);
        settingButton->setObjectName(QStringLiteral("settingButton"));
        settingButton->setGeometry(QRect(700, 380, 301, 61));
        exitButton = new QPushButton(centralwidget);
        exitButton->setObjectName(QStringLiteral("exitButton"));
        exitButton->setGeometry(QRect(700, 450, 301, 61));
        faceNumLabel = new QLabel(centralwidget);
        faceNumLabel->setObjectName(QStringLiteral("faceNumLabel"));
        faceNumLabel->setGeometry(QRect(320, 530, 101, 50));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(faceNumLabel->sizePolicy().hasHeightForWidth());
        faceNumLabel->setSizePolicy(sizePolicy1);
        faceNumLabel->setMinimumSize(QSize(101, 50));
        QFont font;
        font.setPointSize(8);
        faceNumLabel->setFont(font);
        faceNumLabel->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        faceNumLabel->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(195, 530, 130, 50));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setMinimumSize(QSize(130, 50));
        label_2->setFont(font);
        label_2->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        label_2->setAlignment(Qt::AlignCenter);
        serialNumLabel = new QLabel(centralwidget);
        serialNumLabel->setObjectName(QStringLiteral("serialNumLabel"));
        serialNumLabel->setGeometry(QRect(560, 530, 101, 50));
        sizePolicy1.setHeightForWidth(serialNumLabel->sizePolicy().hasHeightForWidth());
        serialNumLabel->setSizePolicy(sizePolicy1);
        serialNumLabel->setMinimumSize(QSize(101, 50));
        serialNumLabel->setFont(font);
        serialNumLabel->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        serialNumLabel->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(430, 530, 130, 50));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setMinimumSize(QSize(130, 50));
        label_3->setFont(font);
        label_3->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        label_3->setAlignment(Qt::AlignCenter);
        takephotoButton = new QPushButton(centralwidget);
        takephotoButton->setObjectName(QStringLiteral("takephotoButton"));
        takephotoButton->setGeometry(QRect(30, 530, 151, 51));
        sizePolicy.setHeightForWidth(takephotoButton->sizePolicy().hasHeightForWidth());
        takephotoButton->setSizePolicy(sizePolicy);
        takephotoButton->setMinimumSize(QSize(151, 51));
        takephotoButton->setFont(font);
        takephotoButton->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        camShow_lb = new QLabel(centralwidget);
        camShow_lb->setObjectName(QStringLiteral("camShow_lb"));
        camShow_lb->setGeometry(QRect(30, 10, 640, 480));
        sizePolicy.setHeightForWidth(camShow_lb->sizePolicy().hasHeightForWidth());
        camShow_lb->setSizePolicy(sizePolicy);
        camShow_lb->setMinimumSize(QSize(320, 240));
        camShow_lb->setStyleSheet(QStringLiteral("background-color: rgb(176, 116, 179);"));
        camShow_lb->setAlignment(Qt::AlignCenter);
        recongnizeWin->setCentralWidget(centralwidget);
        camShow_lb->raise();
        takephotoButton->raise();
        faceNumLabel->raise();
        label_2->raise();
        serialNumLabel->raise();
        label_3->raise();
        detectLabel->raise();
        recResultLabel->raise();
        registerButton->raise();
        settingButton->raise();
        exitButton->raise();

        retranslateUi(recongnizeWin);

        QMetaObject::connectSlotsByName(recongnizeWin);
    } // setupUi

    void retranslateUi(QMainWindow *recongnizeWin)
    {
        recongnizeWin->setWindowTitle(QApplication::translate("recongnizeWin", "MainWindow", 0));
        recResultLabel->setText(QString());
        detectLabel->setText(QString());
        registerButton->setText(QApplication::translate("recongnizeWin", "\347\224\250\346\210\267\346\263\250\345\206\214", 0));
        settingButton->setText(QApplication::translate("recongnizeWin", "\347\263\273\347\273\237\350\256\276\347\275\256", 0));
        exitButton->setText(QApplication::translate("recongnizeWin", "\351\200\200\345\207\272\347\263\273\347\273\237", 0));
        faceNumLabel->setText(QString());
        label_2->setText(QApplication::translate("recongnizeWin", "\346\243\200\346\265\213\345\210\260\347\232\204\344\272\272\350\204\270\346\225\260\357\274\232", 0));
        serialNumLabel->setText(QString());
        label_3->setText(QApplication::translate("recongnizeWin", "\351\242\204\346\265\213\347\273\223\346\236\234\346\240\207\347\255\276\345\200\274\357\274\232", 0));
        takephotoButton->setText(QApplication::translate("recongnizeWin", "\346\250\241\346\213\237\350\257\206\345\210\253", 0));
        camShow_lb->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class recongnizeWin: public Ui_recongnizeWin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FMENU_H

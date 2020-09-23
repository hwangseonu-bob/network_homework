/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLCDNumber *lcdNumber;
    QPushButton *pb_10;
    QPushButton *pb_50;
    QPushButton *pb_100;
    QPushButton *pb_500;
    QPushButton *pb_coffee;
    QPushButton *pb_tea;
    QPushButton *pb_coke;
    QPushButton *pb_reset;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(400, 300);
        lcdNumber = new QLCDNumber(Widget);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setGeometry(QRect(80, 40, 241, 81));
        pb_10 = new QPushButton(Widget);
        pb_10->setObjectName(QStringLiteral("pb_10"));
        pb_10->setGeometry(QRect(80, 160, 89, 25));
        pb_50 = new QPushButton(Widget);
        pb_50->setObjectName(QStringLiteral("pb_50"));
        pb_50->setGeometry(QRect(80, 190, 89, 25));
        pb_100 = new QPushButton(Widget);
        pb_100->setObjectName(QStringLiteral("pb_100"));
        pb_100->setGeometry(QRect(80, 220, 89, 25));
        pb_500 = new QPushButton(Widget);
        pb_500->setObjectName(QStringLiteral("pb_500"));
        pb_500->setGeometry(QRect(80, 250, 89, 25));
        pb_coffee = new QPushButton(Widget);
        pb_coffee->setObjectName(QStringLiteral("pb_coffee"));
        pb_coffee->setEnabled(false);
        pb_coffee->setGeometry(QRect(230, 170, 89, 25));
        pb_tea = new QPushButton(Widget);
        pb_tea->setObjectName(QStringLiteral("pb_tea"));
        pb_tea->setEnabled(false);
        pb_tea->setGeometry(QRect(230, 200, 89, 25));
        pb_coke = new QPushButton(Widget);
        pb_coke->setObjectName(QStringLiteral("pb_coke"));
        pb_coke->setEnabled(false);
        pb_coke->setGeometry(QRect(230, 230, 89, 25));
        pb_reset = new QPushButton(Widget);
        pb_reset->setObjectName(QStringLiteral("pb_reset"));
        pb_reset->setEnabled(false);
        pb_reset->setGeometry(QRect(300, 10, 89, 25));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Form", Q_NULLPTR));
        pb_10->setText(QApplication::translate("Widget", "10", Q_NULLPTR));
        pb_50->setText(QApplication::translate("Widget", "50", Q_NULLPTR));
        pb_100->setText(QApplication::translate("Widget", "100", Q_NULLPTR));
        pb_500->setText(QApplication::translate("Widget", "500", Q_NULLPTR));
        pb_coffee->setText(QApplication::translate("Widget", "coffee(100)", Q_NULLPTR));
        pb_tea->setText(QApplication::translate("Widget", "tea(150)", Q_NULLPTR));
        pb_coke->setText(QApplication::translate("Widget", "coke(200)", Q_NULLPTR));
        pb_reset->setText(QApplication::translate("Widget", "reset", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H

#include <QMap>
#include <QObject>
#include <QMessageBox>

#include "widget.h"
#include "ui_widget.h"

QMap<QObject*, int> pb_money;
QMap<QObject*, int> price;

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget){
    ui->setupUi(this);
    init_map();
    init_push_button();
}

void Widget::init_map() {
    pb_money[ui->pb_10] = 10;
    pb_money[ui->pb_50] = 50;
    pb_money[ui->pb_100] = 100;
    pb_money[ui->pb_500] = 500;

    price[ui->pb_coffee] = 100;
    price[ui->pb_tea] = 150;
    price[ui->pb_coke] = 200;
}

void Widget::init_push_button() {
    connect(ui->pb_10, SIGNAL(clicked()), this, SLOT(push_input_money()));
    connect(ui->pb_50, SIGNAL(clicked()), this, SLOT(push_input_money()));
    connect(ui->pb_100, SIGNAL(clicked()), this, SLOT(push_input_money()));
    connect(ui->pb_500, SIGNAL(clicked()), this, SLOT(push_input_money()));

    connect(ui->pb_coffee, SIGNAL(clicked()), this, SLOT(push_sell()));
    connect(ui->pb_tea, SIGNAL(clicked()), this, SLOT(push_sell()));
    connect(ui->pb_coke, SIGNAL(clicked()), this, SLOT(push_sell()));

    connect(ui->pb_reset, SIGNAL(clicked()), this, SLOT(push_reset()));
}

void Widget::change_money(int n) {
    money = n;
    toggle_button();
    ui->lcdNumber->display(money);
}

void Widget::toggle_button() {
    ui->pb_reset->setEnabled(money > 0);
    ui->pb_coffee->setEnabled(money >= price[ui->pb_coffee]);
    ui->pb_tea->setEnabled(money >= price[ui->pb_tea]);
    ui->pb_coke->setEnabled(money >= price[ui->pb_coke]);
}

void Widget::push_input_money() {
    change_money(money + pb_money[sender()]);
}

void Widget::push_sell() {
    change_money(money - price[sender()]);
}

void Widget::push_reset() {
    int coins[] = {500, 100, 50, 10};
    int cnt[] = {0, 0, 0, 0};

    for (int i = 0; i < 4; i++) {
        cnt[i] = money / coins[i];
        money %= coins[i];
    }

    QString str;
    str.sprintf("500: %d\n100: %d\n50: %d\n10: %d", cnt[0], cnt[1], cnt[2], cnt[3]);
    QMessageBox::information(this, "change", str);

    change_money(0);
}

Widget::~Widget() {
    delete ui;
}
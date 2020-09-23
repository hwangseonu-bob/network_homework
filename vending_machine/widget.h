#pragma once

#include <QWidget>

namespace Ui {
    class Widget;
}

class Widget : public QWidget {
Q_OBJECT
public:
    explicit Widget(QWidget *parent = nullptr);

    ~Widget();

private slots:

    void push_input_money();

    void push_sell();

    void push_reset();

private:
    int money{0};
    Ui::Widget *ui;

    void init_map();

    void init_push_button();

    void change_money(int);

    void toggle_button();
};

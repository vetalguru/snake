#include "snakewidget.h"

#include <QPalette>

SnakeWidget::SnakeWidget(QWidget *parent)
    : QWidget{parent}
{
    SetBackgroundColor();
}

void SnakeWidget::SetBackgroundColor() {
    QPalette pal;
    pal.setColor(QPalette::Window, Qt::black);
    setAutoFillBackground(true);
    setPalette(pal);
}

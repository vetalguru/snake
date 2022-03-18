#include "snakewidget.h"

#include <QPalette>

SnakeWidget::SnakeWidget(QWidget *parent)
    : QWidget{parent}
{
    setBackgroundColor();

    setMinimumSize(MIN_MAIN_WIDGET_SIZE);

    m_headImage.load("../res/head.png");
    m_bodyImage.load("../res/body.png");
    m_appleImage.load("../res/apple.png");

    generateApplePosition();
    initSnakePosition();
}

void SnakeWidget::paintEvent(QPaintEvent *e) {
    Q_UNUSED(e);

    QPainter painter(this);
    drawApple(painter);
    drawSnake(painter);
}

void SnakeWidget::setBackgroundColor() {
    QPalette pal;
    pal.setColor(QPalette::Window, Qt::black);
    setAutoFillBackground(true);
    setPalette(pal);
}

void SnakeWidget::generateApplePosition() {
    m_currentApplePoint.setX(150);
    m_currentApplePoint.setY(150);
}

void SnakeWidget::initSnakePosition() {
    m_currentSnakeSize = SNAKE_MIN_SIZE;
    for (int i =0; i < m_currentSnakeSize; ++i) {
        m_snake[i].setX(50 - i * DOT_SIZE);
        m_snake[i].setY(50);
    }
}

void SnakeWidget::drawApple(QPainter &p) {
    p.drawImage(m_currentApplePoint.x(), m_currentApplePoint.y(), m_appleImage);
}

void SnakeWidget::drawSnake(QPainter &p) {
    for (int i = 0; i < m_currentSnakeSize; ++i) {
        p.drawImage(m_snake[i].x(), m_snake[i].y(), (i ? m_bodyImage : m_headImage));
    }
}

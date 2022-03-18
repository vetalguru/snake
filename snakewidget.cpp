#include "snakewidget.h"

#include <QPalette>
#include <QTime>

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

    m_timerId = startTimer(DEFAULT_DELAY);

    setFocus();
}

void SnakeWidget::paintEvent(QPaintEvent *e) {
    Q_UNUSED(e);

    QPainter painter(this);
    drawApple(painter);
    drawSnake(painter);
}

void SnakeWidget::timerEvent(QTimerEvent *e) {
    Q_UNUSED(e);

    moveSnake();
    repaint();
}

void SnakeWidget::keyPressEvent(QKeyEvent *e) {
    int key = e->key();

    if ((key == Qt::Key_Left) && m_direction != Direction::RIGHT) {
        m_direction = Direction::LEFT;
    }

    if ((key == Qt::Key_Right) && m_direction != Direction::LEFT) {
        m_direction = Direction::RIGHT;
    }

    if ((key == Qt::Key_Up) && m_direction != Direction::DOWN) {
        m_direction = Direction::UP;
    }

    if ((key == Qt::Key_Down) && m_direction != Direction::UP) {
        m_direction = Direction::DOWN;
    }
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
    m_direction = Direction::RIGHT;

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

void SnakeWidget::moveSnake() {
    for (int i = m_currentSnakeSize; i > 0; --i) {
        m_snake[i] = m_snake[i - 1];
    }

    if (m_direction == Direction::LEFT) {
        m_snake[0].setX(m_snake[0].x() - DOT_SIZE);
    }

    if (m_direction == Direction::RIGHT) {
        m_snake[0].setX(m_snake[0].x() + DOT_SIZE);
    }

    if (m_direction == Direction::UP) {
        m_snake[0].setY(m_snake[0].y() - DOT_SIZE);
    }

    if (m_direction == Direction::DOWN) {
        m_snake[0].setY(m_snake[0].y() + DOT_SIZE);
    }
}

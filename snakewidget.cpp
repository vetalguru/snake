#include "snakewidget.h"

#include <QPalette>
#include <QRandomGenerator>
#include <QTime>

SnakeWidget::SnakeWidget(QWidget *parent)
    : QWidget{parent}
    , m_timerId{0}
    , m_isStarted{false}
    , m_isPaused{false}
{
    setBackgroundColor();

    m_headImage.load("../res/head.png");
    m_bodyImage.load("../res/body.png");
    m_appleImage.load("../res/apple.png");

    setMinimumSize(MIN_MAIN_WIDGET_SIZE);
    setFocus();
}

void SnakeWidget::startGame() {
    m_isGameOver = false;

    if (m_isPaused) {
        m_isPaused = false;
        return;
    }

    if (m_isStarted) {
        return;
    }

    m_isStarted = true;
    m_appleCounter = 0;

    initSnakePosition();
    generateApplePosition();

    m_timerId = startTimer(DEFAULT_DELAY);
}

void SnakeWidget::pauseGame() {
    m_isPaused = true;
}

void SnakeWidget::stopGame() {
    m_isStarted = false;
    if (m_timerId) {
        killTimer(m_timerId);
        m_timerId = 0;
    }
}

void SnakeWidget::paintEvent(QPaintEvent *e) {
    Q_UNUSED(e);

    if (!m_isStarted) {
        return;
    }

    QPainter painter(this);
    if (!m_isGameOver) {
        drawApple(painter);
        drawSnake(painter);
    } else {
        gameOverHandler(painter);
        m_isStarted = false;
    }
}

void SnakeWidget::timerEvent(QTimerEvent *e) {
    Q_UNUSED(e);

    if (!m_isGameOver && !m_isPaused) {
        appleEatingHandler();
        collisionHandler();
        moveSnake();
    }

    repaint();
}

void SnakeWidget::keyPressEvent(QKeyEvent *e) {
    switch (e->key()){
        case Qt::Key_Left: {
            if (m_direction != Direction::RIGHT) {
                m_direction = Direction::LEFT;
            }
            break;
        }
        case Qt::Key_Right: {
            if (m_direction != Direction::LEFT) {
                m_direction = Direction::RIGHT;
            }
            break;
        }
        case Qt::Key_Up: {
            if (m_direction != Direction::DOWN) {
                m_direction = Direction::UP;
            }
            break;
        }
        case Qt::Key_Down: {
            if (m_direction != Direction::UP) {
                m_direction = Direction::DOWN;
            }
            break;
        }
    };
}

void SnakeWidget::setBackgroundColor() {
    QPalette pal;
    pal.setColor(QPalette::Window, Qt::black);
    setAutoFillBackground(true);
    setPalette(pal);
}

void SnakeWidget::generateApplePosition() {
    bool ok;
    do {
        ok = true;
        m_currentApplePoint.setX(QRandomGenerator::global()->generate() %
                             (width() / DOT_SIZE) * DOT_SIZE);
        m_currentApplePoint.setY(QRandomGenerator::global()->generate() %
                             (height() / DOT_SIZE) * DOT_SIZE);

        for (int i = 0; i < m_currentSnakeSize; ++i) {
            if (m_snake[i] == m_currentApplePoint) {
                ok = false;
                break;
            }
        }
    } while (!ok);

    m_appleCounter++;
    emit appleCounterChanged(m_appleCounter);
}

void SnakeWidget::initSnakePosition() {
    m_direction = Direction::RIGHT;

    m_currentSnakeSize = SNAKE_MIN_SIZE;
    emit snakeSizeChanged(m_currentSnakeSize);
    for (int i = 0; i < m_currentSnakeSize; ++i) {
        m_snake[i].setX(50 - i * DOT_SIZE);
        m_snake[i].setY(50);
    }
}

void SnakeWidget::drawApple(QPainter &p) {
    p.drawImage(m_currentApplePoint.x(), m_currentApplePoint.y(), m_appleImage);
}

void SnakeWidget::appleEatingHandler() {
    if (m_snake[0] == m_currentApplePoint) {
        if (m_currentSnakeSize < SNAKE_MAX_SIZE) {
            m_currentSnakeSize++;
            emit snakeSizeChanged(m_currentSnakeSize);
            generateApplePosition();
        }
    }
}

void SnakeWidget::drawSnake(QPainter &p) {
    for (int i = 0; i < m_currentSnakeSize; ++i) {
        p.drawImage(m_snake[i].x(), m_snake[i].y(), (i ? m_bodyImage : m_headImage));
    }
}

void SnakeWidget::moveSnake() {
    for (int i = m_currentSnakeSize - 1; i > 0; --i) {
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

void SnakeWidget::collisionHandler() {
     // Check snake
    for (int i = m_currentSnakeSize; i > 0; --i) {
        if ((i > 4) && m_snake[0] == m_snake[i]) {
            m_isGameOver = true;
        }
    }

    // Check borders
    if (m_snake[0].y() >= height()) {
        m_isGameOver = true;
    }

    if (m_snake[0].y() < 0) {
        m_isGameOver = true;
    }

    if (m_snake[0].x() >= width()) {
        m_isGameOver = true;
    }

    if (m_snake[0].x() < 0) {
        m_isGameOver = true;
    }

    if (m_isGameOver) {
        if (m_timerId) {
            killTimer(m_timerId);
            m_timerId = 0;
        }
    }
}

void SnakeWidget::gameOverHandler(QPainter &p) {
    const QFont font("Courier", 15, QFont::DemiBold);

    p.setPen(QColor(Qt::white));
    p.setFont(font);

    p.translate(QPoint(width()/2, height()/2));
    p.drawText(-70, 0, "Game over!!!");
}

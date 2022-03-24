#ifndef SNAKEWIDGET_H
#define SNAKEWIDGET_H

#include <QImage>
#include <QKeyEvent>
#include <QPainter>
#include <QPoint>
#include <QSize>
#include <QWidget>

class SnakeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SnakeWidget(QWidget *parent = nullptr);

signals:
    void appleCounterChanged(int n);
    void snakeSizeChanged(int s);

public slots:
    void startGame();
    void pauseGame();
    void stopGame();

protected:
    void paintEvent(QPaintEvent *e);
    void timerEvent(QTimerEvent *e);
    void keyPressEvent(QKeyEvent *e);

private:
    enum class Direction {
        UP,
        DOWN,
        LEFT,
        RIGHT,
    };

private:
    static constexpr int DEFAULT_DELAY{150};
    static constexpr int DOT_SIZE{10};
    static constexpr QSize MIN_MAIN_WIDGET_SIZE{300, 300};
    static constexpr int SNAKE_MAX_SIZE{100};
    static constexpr int SNAKE_MIN_SIZE{3};

private:
    void setBackgroundColor();

    void generateApplePosition();
    void drawApple(QPainter &p);
    void appleEatingHandler();

    void initSnakePosition();
    void drawSnake(QPainter &p);
    void moveSnake();

    void collisionHandler();
    void gameOverHandler(QPainter &p);

private:
    QImage m_appleImage;
    QPoint m_currentApplePoint;

    QImage m_headImage;
    QImage m_bodyImage;
    QPoint m_snake[SNAKE_MAX_SIZE];
    int m_currentSnakeSize;
    Direction m_direction;

    int m_timerId;

    bool m_isStarted;
    bool m_isPaused;
    bool m_isGameOver;

    int m_appleCounter;
};

#endif // SNAKEWIDGET_H

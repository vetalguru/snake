#ifndef SNAKEWIDGET_H
#define SNAKEWIDGET_H

#include <QImage>
#include <QPainter>
#include <QPoint>
#include <QSize>
#include <QWidget>

class SnakeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SnakeWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *e);

private:
    static constexpr QSize MIN_MAIN_WIDGET_SIZE{300, 300};
    static constexpr int SNAKE_MAX_SIZE{100};
    static constexpr int SNAKE_MIN_SIZE{3};
    static constexpr int DOT_SIZE{10};
    static constexpr int RAND_POS{29};

private:
    void setBackgroundColor();

    void generateApplePosition();

    void initSnakePosition();

    void drawApple(QPainter &p);
    void drawSnake(QPainter &p);

private:
    QImage m_appleImage;
    QPoint m_currentApplePoint;

    QImage m_headImage;
    QImage m_bodyImage;
    QPoint m_snake[SNAKE_MAX_SIZE];
    int m_currentSnakeSize;

};

#endif // SNAKEWIDGET_H

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
    const QSize MIN_MAIN_WIDGET_SIZE{300, 300};
    const int DOT_SIZE{10};
    const int RAND_POS{29};

private:
    void setBackgroundColor();

    void generateApplePosition();

    void drawApple(QPainter &p);

private:
    QImage m_headImage;
    QImage m_bodyImage;
    QImage m_appleImage;

    QPoint m_currentApplePoint;

};

#endif // SNAKEWIDGET_H

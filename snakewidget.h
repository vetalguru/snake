#ifndef SNAKEWIDGET_H
#define SNAKEWIDGET_H

#include <QSize>
#include <QWidget>

class SnakeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SnakeWidget(QWidget *parent = nullptr);

private:
    const QSize MIN_MAIN_WIDGET_SIZE{300, 300};

private:
    void setBackgroundColor();

};

#endif // SNAKEWIDGET_H

#ifndef SNAKEWIDGET_H
#define SNAKEWIDGET_H

#include <QWidget>

class SnakeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SnakeWidget(QWidget *parent = nullptr);

private:
    void SetBackgroundColor();

};

#endif // SNAKEWIDGET_H

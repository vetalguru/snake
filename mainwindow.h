#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void aboutDialog();
    void changeAppleNumber(int);

private:
    QLabel *m_appleCounterLabel;
};

#endif // MAINWINDOW_H

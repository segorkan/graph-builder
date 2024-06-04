#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QPushButton *button;

    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void myClicked();
};

#endif // MAINWINDOW_H

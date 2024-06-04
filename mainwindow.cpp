#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "poland.h"
#include <QPushButton>
#include <QPainter>
#include <QPainterPath>
#include <cmath>
#include <QPen>
#include <QString>
#include <QWidget>
#include <QValidator>
#include <iostream>
#include <string>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    button = new QPushButton(this);
    resize(800, 600);
    button->setGeometry(this->width() - 45, 5, 40, 40);
    button->setText("Gen");
    connect(button, SIGNAL(clicked()), this, SLOT(myClicked()));

    QRegExp rx("^-?(0?\\.|[1-9](\\d+)?\\.)(\\d+)$");
    QValidator *validator = new QRegExpValidator(rx, this);
    ui->min_x->setValidator(validator);
    ui->min_y->setValidator(validator);
    ui->max_x->setValidator(validator);
    ui->max_y->setValidator(validator);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::myClicked(){

    QString expr = ui->lineEdit->text();
    QString tempo = expr;
    tempo.replace("x", "(1000000000)");
    double res = 0.0;
    bool pr = calculate(tempo.toStdString(), res);
    if (!pr){
        ui->lineEdit->setText("Error in function.");
        return;
    }

    ui->label->setGeometry(5, 5, this->width() - 55, this->height() - 10);
    QPixmap pixmap(ui->label->width(), ui->label->height());
    pixmap.fill(Qt::white);
    QPainter qp;
    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(2);
    qp.begin(&pixmap);
    qp.setPen(pen);
    qp.setPen(Qt::black);
    QPainterPath path;
    double xmin = ui->min_x->text().toDouble(), xmax = ui->max_x->text().toDouble();
    double ymin = ui->min_y->text().toDouble(), ymax = ui->max_y->text().toDouble();
    double xgmin = 0, xgmax = ui->label->width();
    double ygmin = 0, ygmax = ui->label->height();
    double step = (xmax - xmin) / (xgmax - xgmin);
    double kx = (xgmax - xgmin) / (xmax - xmin), ky = (ygmin - ygmax) / (ymax - ymin);
    double x0 = xgmin - kx * xmin, y0 = ygmin - ky * ymax;
    qp.setPen(Qt::red);
    qp.drawLine(0, y0, pixmap.width(), y0);
    qp.drawLine(x0, 0, x0, pixmap.height());
    qp.setPen(Qt::black);

    bool check = true;
    for (double x = xmin; x <= xmax; x += step){
        QString temp = expr;
        temp.replace("x", "(" + QString().setNum(x, 'g', 8) + ")");
        double y = 0.0;
        bool pr = calculate(temp.toStdString(), y);
        if (y <= ymax && y >= ymin && pr){
            int xg = xgmin + kx * (x - xmin), yg = ygmin + ky * (y - ymax);
            if (check){
                path.moveTo(xg, yg);
                check = false;
            }
            else {
                path.lineTo(xg, yg);
            }
        }
        else {
            check = true;
        }
    }
    qp.drawPath(path);
    ui->label->setPixmap(pixmap);
}

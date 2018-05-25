#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gravity_scene2.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralWidget->layout()->setMargin(0);
    gravity_scene *scene = new gravity_scene();
    ui->statusBar->showMessage(tr("Ready"));
    ui->graphicsView->setScene(scene);
    this->setFixedSize((12+2)*60,(9+2)*60);

    connect(scene,SIGNAL(send_message(QString)),
            this,SLOT(show_received_message(QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::show_received_message(QString s)
{
    ui->statusBar->showMessage(s);
}

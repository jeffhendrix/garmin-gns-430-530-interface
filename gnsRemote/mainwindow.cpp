#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "remoteproxy.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connectButton_clicked()
{
    char ipAddress[] = "127.0.0.1";
    m_RemoteProxy::open(ipAddress);
}

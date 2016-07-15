#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "remoteproxy.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_connectButton_clicked();

private:
    RemoteProxy m_RemoteProxy;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

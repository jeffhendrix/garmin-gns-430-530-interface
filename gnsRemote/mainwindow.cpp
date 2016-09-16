#include <windows.h>
#include "mainWindow.h"

#define DEG2RAD (0.0174532925f)

MainWindow::MainWindow(QWidget* pParent, Qt::WindowFlags flags)
    : QWidget(pParent, flags)
{
    
    ui.setupUi(this);
    
    bool hideGNSWindow = false; //Set this to true to hide the GNS window
    m_RemoteProxy.initialize(hideGNSWindow);

    //GNSIntf* pIntf = m_RemoteProxy.getInterface();

    updateGUI();

    connect(&m_updateTimer, SIGNAL(timeout()), this, SLOT(onUpdateTimer()));
    m_updateTimer.setInterval(500);
    //m_updateTimer.setSingleShot(true);
    m_updateTimer.start();   
}

MainWindow::~MainWindow()
{
    m_RemoteProxy.terminate();
}

void MainWindow::updateGUI()
{
    unsigned long ulval;

    ulval = m_RemoteProxy.getCOMActiveFrequency();
    ui.spinCOMActive->setValue((float)ulval/1000.0f);

    ulval = m_RemoteProxy.getCOMStandbyFrequency();
    ui.spinCOMStandby->setValue((float)ulval/1000.0f);

    ulval = m_RemoteProxy.getNAVActiveFrequency();
    ui.spinNAVActive->setValue((float)ulval/1000.0f);

    ulval = m_RemoteProxy.getNAVStandbyFrequency();
    ui.spinNAVStandby->setValue((float)ulval/1000.0f);

}

void MainWindow::resizeEvent ( QResizeEvent * event )
{
    QWidget::resizeEvent(event);

    QTimer::singleShot(10, this, SLOT(onRepositionViewWidget()));
}

void MainWindow::onUpdateTimer()
{
    updateGUI();
}

void MainWindow::onRepositionViewWidget()
{
    int view_width = ui.gnsViewWidget->getW();
    int view_height = ui.gnsViewWidget->getH();

    float view_ratio = (float)view_width/(float)view_height;

    int box_width = ui.view_box->width();
    int box_height = ui.view_box->height();

    float box_ratio = (float)(box_width)/(float)box_height;


    int x,y;
    int w, h;
    if(box_ratio >= view_ratio)
    {
        //this is a vertical fit, center the camera widget horizontaly
        h = box_height;
        w = view_ratio*h;

        x = (box_width-w)/2;
        y = 0;

    }else
    {
        //this a horizontal fit, center the camera widget vertically
        w = box_width;
        h = (float)w/view_ratio;

        x = 0;
        y = (box_height-h)/2;
    }
    ui.gnsViewWidget->setGeometry(x, y, w, h);
}

void MainWindow::on_btnStart_clicked ( bool checked  )
{
    Q_UNUSED(checked);

    if(0 == ui.cmbModel->currentIndex())
    {
        m_RemoteProxy.open(TYPE_GNS430);
    }else
    {
        m_RemoteProxy.open(TYPE_GNS530);
    }

    ui.gnsViewWidget->setRemoteProxy(&m_RemoteProxy);
    QTimer::singleShot(10, this, SLOT(onRepositionViewWidget()));
}

void MainWindow::on_btnStop_clicked ( bool checked  )
{
    Q_UNUSED(checked);
    m_RemoteProxy.close();

    ui.gnsViewWidget->setRemoteProxy(NULL);
    QTimer::singleShot(10, this, SLOT(onRepositionViewWidget()));
}

//COM
void MainWindow::on_btnCOMActiveSet_clicked ( bool checked )
{
    Q_UNUSED(checked);
    bool ok;
    unsigned long val = QInputDialog::getInt( this, "COM Active Frequency", "Frequency", 100000, 100000, 200000, 1, &ok);
    if(ok)
    {
        m_RemoteProxy.setCOMActiveFrequency(val);
    }
}

void MainWindow::on_btnCOMStandbySet_clicked ( bool checked )
{
    Q_UNUSED(checked);

    bool ok;
    unsigned long val = QInputDialog::getInt( this, "COM Standby Frequency", "Frequency", 100000, 100000, 200000, 1, &ok);
    if(ok)
    {
        m_RemoteProxy.setCOMStandbyFrequency(val);
    }
}

//NAV
void MainWindow::on_btnNAVActiveSet_clicked ( bool checked )
{
    Q_UNUSED(checked);
    bool ok;
    unsigned long val = QInputDialog::getInt( this, "NAV Active Frequency", "Frequency", 100000, 100000, 200000, 1, &ok);
    if(ok)
    {
        m_RemoteProxy.setNAVActiveFrequency(val);
    }
}

void MainWindow::on_btnNAVStandbySet_clicked ( bool checked )
{
    Q_UNUSED(checked);

    bool ok;
    unsigned long val = QInputDialog::getInt( this, "NAV Standby Frequency", "Frequency", 100000, 100000, 200000, 1, &ok);
    if(ok)
    {
        m_RemoteProxy.setNAVStandbyFrequency(val);
    }
}

//GPS
void MainWindow::on_btnSetGPS_clicked ( bool checked )
{
    Q_UNUSED(checked);

    float heading = ui.spinHeading->value();
    if( heading > 180) heading = heading - 360;

    m_RemoteProxy.setGPSInfo(   ui.spinLatitude->value()*DEG2RAD,
                                ui.spinLongitude->value()*DEG2RAD,
                                ui.spinSpeed->value(),
                                heading*DEG2RAD,
                                ui.spinVerticalSpeed->value(),
                                ui.spinAltitude->value()
                            );
}

void MainWindow::on_btnSimulateGPS_clicked ( bool checked )
{
    Q_UNUSED(checked);

}

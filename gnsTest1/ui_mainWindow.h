/********************************************************************************
** Form generated from reading UI file 'mainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "gnsViewWidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *view_box;
    GnsViewWidget *gnsViewWidget;
    QTabWidget *tabControl;
    QWidget *tabCOM;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QDoubleSpinBox *spinCOMActive;
    QPushButton *btnCOMActiveSet;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_3;
    QDoubleSpinBox *spinCOMStandby;
    QPushButton *btnCOMStandbySet;
    QWidget *tabNAV;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_4;
    QDoubleSpinBox *spinNAVActive;
    QPushButton *btnNAVActiveSet;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_5;
    QDoubleSpinBox *spinNAVStandby;
    QPushButton *btnNAVStandbySet;
    QWidget *tabGPS;
    QGridLayout *gridLayout;
    QDoubleSpinBox *spinLongitude;
    QDoubleSpinBox *spinLatitude;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QDoubleSpinBox *spinVerticalSpeed;
    QLabel *label_8;
    QLabel *label_9;
    QDoubleSpinBox *spinHeading;
    QDoubleSpinBox *spinAltitude;
    QLabel *label_10;
    QPushButton *btnSetGPS;
    QPushButton *btnSimulateGPS;
    QDoubleSpinBox *spinSpeed;
    QHBoxLayout *horizontalLayout;
    QComboBox *cmbModel;
    QPushButton *btnStart;
    QPushButton *btnStop;
    QPushButton *buttonOn;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(650, 549);
        verticalLayout = new QVBoxLayout(MainWindow);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(3, 3, 3, 3);
        view_box = new QFrame(MainWindow);
        view_box->setObjectName(QStringLiteral("view_box"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(view_box->sizePolicy().hasHeightForWidth());
        view_box->setSizePolicy(sizePolicy);
        gnsViewWidget = new GnsViewWidget(view_box);
        gnsViewWidget->setObjectName(QStringLiteral("gnsViewWidget"));
        gnsViewWidget->setGeometry(QRect(120, 40, 351, 121));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(gnsViewWidget->sizePolicy().hasHeightForWidth());
        gnsViewWidget->setSizePolicy(sizePolicy1);
        gnsViewWidget->setFocusPolicy(Qt::StrongFocus);

        verticalLayout->addWidget(view_box);

        tabControl = new QTabWidget(MainWindow);
        tabControl->setObjectName(QStringLiteral("tabControl"));
        tabControl->setMinimumSize(QSize(0, 100));
        tabControl->setMaximumSize(QSize(16777215, 100));
        tabCOM = new QWidget();
        tabCOM->setObjectName(QStringLiteral("tabCOM"));
        verticalLayout_2 = new QVBoxLayout(tabCOM);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(tabCOM);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        spinCOMActive = new QDoubleSpinBox(tabCOM);
        spinCOMActive->setObjectName(QStringLiteral("spinCOMActive"));
        spinCOMActive->setDecimals(3);
        spinCOMActive->setMaximum(999);
        spinCOMActive->setSingleStep(0.5);
        spinCOMActive->setValue(125.25);

        horizontalLayout_2->addWidget(spinCOMActive);

        btnCOMActiveSet = new QPushButton(tabCOM);
        btnCOMActiveSet->setObjectName(QStringLiteral("btnCOMActiveSet"));

        horizontalLayout_2->addWidget(btnCOMActiveSet);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_2 = new QLabel(tabCOM);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_3->addWidget(label_2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        spinCOMStandby = new QDoubleSpinBox(tabCOM);
        spinCOMStandby->setObjectName(QStringLiteral("spinCOMStandby"));
        spinCOMStandby->setDecimals(3);
        spinCOMStandby->setMaximum(999);
        spinCOMStandby->setSingleStep(0.5);
        spinCOMStandby->setValue(125.25);

        horizontalLayout_3->addWidget(spinCOMStandby);

        btnCOMStandbySet = new QPushButton(tabCOM);
        btnCOMStandbySet->setObjectName(QStringLiteral("btnCOMStandbySet"));

        horizontalLayout_3->addWidget(btnCOMStandbySet);


        verticalLayout_2->addLayout(horizontalLayout_3);

        tabControl->addTab(tabCOM, QString());
        tabNAV = new QWidget();
        tabNAV->setObjectName(QStringLiteral("tabNAV"));
        verticalLayout_3 = new QVBoxLayout(tabNAV);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_3 = new QLabel(tabNAV);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_4->addWidget(label_3);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        spinNAVActive = new QDoubleSpinBox(tabNAV);
        spinNAVActive->setObjectName(QStringLiteral("spinNAVActive"));
        spinNAVActive->setDecimals(3);
        spinNAVActive->setMaximum(999);
        spinNAVActive->setSingleStep(0.5);
        spinNAVActive->setValue(125.25);

        horizontalLayout_4->addWidget(spinNAVActive);

        btnNAVActiveSet = new QPushButton(tabNAV);
        btnNAVActiveSet->setObjectName(QStringLiteral("btnNAVActiveSet"));

        horizontalLayout_4->addWidget(btnNAVActiveSet);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_4 = new QLabel(tabNAV);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_5->addWidget(label_4);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        spinNAVStandby = new QDoubleSpinBox(tabNAV);
        spinNAVStandby->setObjectName(QStringLiteral("spinNAVStandby"));
        spinNAVStandby->setDecimals(3);
        spinNAVStandby->setMaximum(999);
        spinNAVStandby->setSingleStep(0.5);
        spinNAVStandby->setValue(125.25);

        horizontalLayout_5->addWidget(spinNAVStandby);

        btnNAVStandbySet = new QPushButton(tabNAV);
        btnNAVStandbySet->setObjectName(QStringLiteral("btnNAVStandbySet"));

        horizontalLayout_5->addWidget(btnNAVStandbySet);


        verticalLayout_3->addLayout(horizontalLayout_5);

        tabControl->addTab(tabNAV, QString());
        tabGPS = new QWidget();
        tabGPS->setObjectName(QStringLiteral("tabGPS"));
        gridLayout = new QGridLayout(tabGPS);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        spinLongitude = new QDoubleSpinBox(tabGPS);
        spinLongitude->setObjectName(QStringLiteral("spinLongitude"));
        spinLongitude->setMaximum(360);
        spinLongitude->setValue(254.9);

        gridLayout->addWidget(spinLongitude, 1, 1, 1, 1);

        spinLatitude = new QDoubleSpinBox(tabGPS);
        spinLatitude->setObjectName(QStringLiteral("spinLatitude"));
        spinLatitude->setMaximum(360);
        spinLatitude->setValue(39.9);

        gridLayout->addWidget(spinLatitude, 0, 1, 1, 1);

        label_5 = new QLabel(tabGPS);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 0, 0, 1, 1);

        label_6 = new QLabel(tabGPS);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 0, 2, 1, 1);

        label_7 = new QLabel(tabGPS);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 0, 4, 1, 1);

        spinVerticalSpeed = new QDoubleSpinBox(tabGPS);
        spinVerticalSpeed->setObjectName(QStringLiteral("spinVerticalSpeed"));
        spinVerticalSpeed->setMaximum(10000);

        gridLayout->addWidget(spinVerticalSpeed, 0, 5, 1, 1);

        label_8 = new QLabel(tabGPS);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 1, 0, 1, 1);

        label_9 = new QLabel(tabGPS);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout->addWidget(label_9, 1, 2, 1, 1);

        spinHeading = new QDoubleSpinBox(tabGPS);
        spinHeading->setObjectName(QStringLiteral("spinHeading"));

        gridLayout->addWidget(spinHeading, 1, 3, 1, 1);

        spinAltitude = new QDoubleSpinBox(tabGPS);
        spinAltitude->setObjectName(QStringLiteral("spinAltitude"));
        spinAltitude->setMaximum(10000);
        spinAltitude->setValue(6000);

        gridLayout->addWidget(spinAltitude, 1, 5, 1, 1);

        label_10 = new QLabel(tabGPS);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout->addWidget(label_10, 1, 4, 1, 1);

        btnSetGPS = new QPushButton(tabGPS);
        btnSetGPS->setObjectName(QStringLiteral("btnSetGPS"));

        gridLayout->addWidget(btnSetGPS, 0, 6, 1, 1);

        btnSimulateGPS = new QPushButton(tabGPS);
        btnSimulateGPS->setObjectName(QStringLiteral("btnSimulateGPS"));

        gridLayout->addWidget(btnSimulateGPS, 1, 6, 1, 1);

        spinSpeed = new QDoubleSpinBox(tabGPS);
        spinSpeed->setObjectName(QStringLiteral("spinSpeed"));
        spinSpeed->setMaximum(1000);

        gridLayout->addWidget(spinSpeed, 0, 3, 1, 1);

        tabControl->addTab(tabGPS, QString());

        verticalLayout->addWidget(tabControl);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        cmbModel = new QComboBox(MainWindow);
        cmbModel->setObjectName(QStringLiteral("cmbModel"));

        horizontalLayout->addWidget(cmbModel);

        btnStart = new QPushButton(MainWindow);
        btnStart->setObjectName(QStringLiteral("btnStart"));

        horizontalLayout->addWidget(btnStart);

        btnStop = new QPushButton(MainWindow);
        btnStop->setObjectName(QStringLiteral("btnStop"));

        horizontalLayout->addWidget(btnStop);

        buttonOn = new QPushButton(MainWindow);
        buttonOn->setObjectName(QStringLiteral("buttonOn"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(buttonOn->sizePolicy().hasHeightForWidth());
        buttonOn->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(buttonOn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(MainWindow);

        tabControl->setCurrentIndex(0);
        cmbModel->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Main window GNS", 0));
        label->setText(QApplication::translate("MainWindow", "Active", 0));
        btnCOMActiveSet->setText(QApplication::translate("MainWindow", "Set", 0));
        label_2->setText(QApplication::translate("MainWindow", "Standby", 0));
        btnCOMStandbySet->setText(QApplication::translate("MainWindow", "Set", 0));
        tabControl->setTabText(tabControl->indexOf(tabCOM), QApplication::translate("MainWindow", "COM", 0));
        label_3->setText(QApplication::translate("MainWindow", "Active", 0));
        btnNAVActiveSet->setText(QApplication::translate("MainWindow", "Set", 0));
        label_4->setText(QApplication::translate("MainWindow", "Standby", 0));
        btnNAVStandbySet->setText(QApplication::translate("MainWindow", "Set", 0));
        tabControl->setTabText(tabControl->indexOf(tabNAV), QApplication::translate("MainWindow", "NAV", 0));
        label_5->setText(QApplication::translate("MainWindow", "Latitude (deg)", 0));
        label_6->setText(QApplication::translate("MainWindow", "Speed (m/s)", 0));
        label_7->setText(QApplication::translate("MainWindow", "VerticalSpeed (m/s)", 0));
        label_8->setText(QApplication::translate("MainWindow", "Longitude (deg)", 0));
        label_9->setText(QApplication::translate("MainWindow", "Heading (deg)", 0));
        label_10->setText(QApplication::translate("MainWindow", "Altitude (m)", 0));
        btnSetGPS->setText(QApplication::translate("MainWindow", "Set", 0));
        btnSimulateGPS->setText(QApplication::translate("MainWindow", "Simulate", 0));
        tabControl->setTabText(tabControl->indexOf(tabGPS), QApplication::translate("MainWindow", "GPS", 0));
        cmbModel->clear();
        cmbModel->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "GNS 430 WAAS", 0)
         << QApplication::translate("MainWindow", "GNS 530 WAAS", 0)
        );
        btnStart->setText(QApplication::translate("MainWindow", "Start", 0));
        btnStop->setText(QApplication::translate("MainWindow", "Stop", 0));
        buttonOn->setText(QApplication::translate("MainWindow", "On", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

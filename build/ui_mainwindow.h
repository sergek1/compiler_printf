/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTextEdit *field_input;
    QPushButton *button_run;
    QTextBrowser *field_output;
    QPushButton *save;
    QPushButton *save_input;
    QPushButton *copy_input;
    QPushButton *copy_output;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(466, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        field_input = new QTextEdit(centralwidget);
        field_input->setObjectName(QString::fromUtf8("field_input"));
        field_input->setGeometry(QRect(40, 40, 300, 200));
        field_input->setAutoFillBackground(false);
        field_input->setFrameShape(QFrame::WinPanel);
        button_run = new QPushButton(centralwidget);
        button_run->setObjectName(QString::fromUtf8("button_run"));
        button_run->setGeometry(QRect(140, 250, 100, 32));
        field_output = new QTextBrowser(centralwidget);
        field_output->setObjectName(QString::fromUtf8("field_output"));
        field_output->setGeometry(QRect(40, 290, 300, 200));
        field_output->setFrameShape(QFrame::WinPanel);
        save = new QPushButton(centralwidget);
        save->setObjectName(QString::fromUtf8("save"));
        save->setGeometry(QRect(350, 280, 30, 40));
        save->setToolTipDuration(5);
        save->setStyleSheet(QString::fromUtf8(""));
        save->setInputMethodHints(Qt::ImhNone);
        save_input = new QPushButton(centralwidget);
        save_input->setObjectName(QString::fromUtf8("save_input"));
        save_input->setGeometry(QRect(350, 40, 30, 40));
        copy_input = new QPushButton(centralwidget);
        copy_input->setObjectName(QString::fromUtf8("copy_input"));
        copy_input->setGeometry(QRect(350, 90, 30, 40));
        copy_output = new QPushButton(centralwidget);
        copy_output->setObjectName(QString::fromUtf8("copy_output"));
        copy_output->setGeometry(QRect(350, 330, 30, 40));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 466, 24));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        field_input->setPlaceholderText(QString());
        button_run->setText(QCoreApplication::translate("MainWindow", "\320\227\320\220\320\237\320\243\320\241\320\242\320\230\320\242\320\254", nullptr));
#if QT_CONFIG(tooltip)
        save->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        save->setText(QString());
        save_input->setText(QString());
        copy_input->setText(QString());
        copy_output->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

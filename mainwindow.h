#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <stdio.h>
#include <string>
#include <utility>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

typedef struct ERROR {
    int string_number;
    bool wrong_func = false;
    bool no_open_bracket = false;
    bool no_close_bracket = false;
    bool extra_symblos = false;
    bool no_semicolon = false;
    bool extra_symbols_after_close_bracket = false;
} ERROR;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_button_run_clicked();

private:
    Ui::MainWindow *ui_;
    std::pair<std::string, std::string> ParserString(std::string string);
};
#endif // MAINWINDOW_H

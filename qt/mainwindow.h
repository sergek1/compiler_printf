#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <stdio.h>
#include <string>
#include <utility>
#include <vector>
#include <QToolTip>
#include <QFileDialog>
#include <QMessageBox>
#include <fstream>
#include "information.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

typedef struct ERROR {
    int string_number{};
    bool wrong_func = false;
    bool no_open_bracket = false;
    bool no_close_bracket = false;
    bool no_semicolon = false;
    bool no_quotes = false;
    bool extra_symblos = false;
    bool extra_symbols_after_close_bracket = false;
    bool extra_before_quote = false;
    bool extra_quotes = false;
    bool extra_specifier = false;
    bool extra_commas = false;
    bool extra_variables = false;
} ERROR;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_button_run_clicked();

    void on_info_clicked();

    void on_save_output_clicked();

    void on_input_from_file_clicked();

    void on_save_all_clicked();

    void on_clear_clicked();

    void on_save_input_clicked();

private:
    Ui::MainWindow *ui_;
    std::pair<std::string, std::string> ParserString(std::string string);
    void QuoteHandling(std::string string, std::vector<ERROR> *errors);
    std::string ErrorHandling(std::vector<ERROR> errors, std::string function);
};



#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow) {
    ui_->setupUi(this);
    ui_->field_input->setPlaceholderText("Введите код ...");
    ui_->field_output->setPlaceholderText("Результат запуска ...");
    QPixmap pixmap("qt/images/diskette.png");
    QIcon ButtonIcon(pixmap);
    ui_->save->setIcon(ButtonIcon);
    ui_->save->setToolTip("Сохранить поле вывода");
    ui_->save->setToolTipDuration(5000);

    QPixmap pixmap1("qt/images/floppy-disk.png");
    QIcon ButtonIcon1(pixmap1);
    ui_->save_input->setIcon(ButtonIcon1);
    ui_->save_input->setToolTip("Сохранить поле ввода");
    ui_->save_input->setToolTipDuration(5000);

    QPixmap pixmap2("qt/images/copy (1).png");
    QIcon ButtonIcon2(pixmap2);
    ui_->copy_input->setIcon(ButtonIcon2);
    ui_->copy_input->setToolTip("Скопировать поле ввода");
    ui_->copy_input->setToolTipDuration(5000);

    QPixmap pixmap3("qt/images/copy.png");
    QIcon ButtonIcon3(pixmap3);
    ui_->copy_output->setIcon(ButtonIcon3);
    ui_->copy_output->setToolTip("Скопировать поле вывода");
    ui_->copy_output->setToolTipDuration(5000);

}

MainWindow::~MainWindow() {
    delete ui_;
}

void MainWindow::on_button_run_clicked() {
    QString string = ui_->field_input->toPlainText();
    std::pair<std::string, std::string> pair = ParserString(string.toStdString());
    std::string common = pair.first; common+='\n'; common += pair.second;
    QString conclusion = QString::fromUtf8(common);
    ui_->field_output->setText("");
    ui_->field_output->setText(conclusion);
}

std::pair<std::string, std::string> MainWindow::ParserString(std::string string) {
    std::string conclusion, original_expression;
    std::string function{};
    if (string.size()){
        std::string is_wrong;
        std::vector<ERROR> errors;
        while (string.find_first_not_of(' ')
               || string.find_first_not_of('\t')
               || string.find_first_not_of('\n')) {
            string.erase(0, string.find_first_not_of(' '));
            string.erase(0, string.find_first_not_of('\t'));
            string.erase(0, string.find_first_not_of('\n'));
        }
        string[string.size()] = '\n';
        bool is_fun_end = false, is_open_bracket = false, is_close_bracket = false, is_semicolon = false, is_open_quote = false, is_close_quote = false;
        int string_number = 1, quote_count = 0;
        for (size_t index = 0; index < string.size(); index++) {
            if (index == 0) {
                while (string[index]!='(' && string[index]!=' ' && string[index]!='\t'
                       && string[index]!='\n' && string[index]!=';') {
                    function+=string[index];
                    index++;
                }
                if (function!="printf") {
                    ERROR wrong_fun;
                    wrong_fun.wrong_func = true;
                    wrong_fun.string_number = string_number;
                    errors.push_back(wrong_fun);
                }
                original_expression+=function;
                is_fun_end = true;
            }
            if (is_fun_end && !is_open_bracket && (string[index]!= ' ' && string[index]!= '\t' && string[index]!= '\n'
                                                   && string[index]!= ';' && string[index]!= '(')) {
                ERROR extra_symbols;
                extra_symbols.extra_symblos = true;
                extra_symbols.string_number = string_number;
                errors.push_back(extra_symbols);
            }
            if (string[index] == ';') {
                is_semicolon = true;
            }
            if (is_close_bracket && !is_semicolon && (string[index]!= ' ' && string[index]!= '\t' && string[index]!= '\n')) {
                ERROR extra_symbols_after_close_bracket;
                extra_symbols_after_close_bracket.extra_symbols_after_close_bracket = true;
                extra_symbols_after_close_bracket.string_number = string_number;
                errors.push_back(extra_symbols_after_close_bracket);
            }
            if (is_fun_end && !is_open_bracket && (string[index] == ')' || string[index] == '"' || index+1 >= string.size())){
                ERROR no_open_bracket;
                no_open_bracket.no_open_bracket = true;
                no_open_bracket.string_number = string_number;
                errors.push_back(no_open_bracket);
            }

            if (string[index] == ')') {
                is_close_bracket = true;
            }
            if ((is_open_bracket && !is_close_bracket  && (string[index] == ';' ||index+1 >= string.size() )) /*|| index+1 >= string.size()*/) {
                ERROR no_close_bracket;
                no_close_bracket.no_close_bracket = true;
                no_close_bracket.string_number = string_number;
                errors.push_back(no_close_bracket);
            }
            if (index+1 >= string.size()) {
                if (string[index] != ';') {
                    ERROR no_semicolon;
                    no_semicolon.no_semicolon = true;
                    no_semicolon.string_number = string_number;
                    errors.push_back(no_semicolon);
                }
                string_number++;
            }
            if (string[index]=='(') {
                is_open_bracket = true;
            }
            if (string[index]!= ' ' && string[index]!= '\t' && string[index]!= '\n'){
                original_expression+=string[index];
            }

            if (string[index] == '"' && string[index-1] != '\\') {
                quote_count++;
                if(quote_count > 2) {
                    ERROR extra_quotes;
                    extra_quotes.extra_quotes = true;
                    extra_quotes.string_number = string_number;
                    errors.push_back(extra_quotes);
                }
            }
        }

        bool no_open_bracket = false, no_close_bracket = false;
        for (size_t i = 0; i < errors.size(); ++i) {
            if (errors[i].no_open_bracket) {
                no_open_bracket = true;
            } else if (errors[i].no_close_bracket) {
                no_close_bracket = true;
            }
        }
        if(quote_count == 2 && !no_open_bracket && !no_close_bracket) {
            QuoteHandling(string, &errors);
        } else if (quote_count < 2) {
            ERROR no_quotes;
            no_quotes.no_quotes = true;
            no_quotes.string_number = string_number-1;
            errors.push_back(no_quotes);
        }
        conclusion = ErrorHandling(errors, function);
    }
    auto pair = std::make_pair(original_expression, conclusion);printf("%m");

    return pair;
}

void MainWindow::QuoteHandling(std::string string, std::vector<ERROR> *errors) {
    size_t index_of_open_quote = string.find('"');
    std::string specificators = "cdieEfgGosuxXpn%";
    size_t index_of_close_quote = string.find_last_of('"'); int count_comma = 0, count_srecificator = 0, count_quote = 0;
    for (size_t i = index_of_open_quote; i < string.size(); ++i) {
        if (string[i] == '%' && (specificators.find(string[i+1])<specificators.size())) {

            std::cout<<"\n"<<specificators.find(string[i+1])<<std::endl;
            count_srecificator++;
        }
        if(string[i] == '"') {
            count_quote++;
        }
        if(count_quote==2) {
            if(string[i] == ','){
                count_comma++;
            }
        }
    }
    if(count_srecificator > count_comma) {
        ERROR extra_specifier;
        extra_specifier.extra_specifier = true;
        errors->push_back(extra_specifier);
    } else if (count_srecificator < count_comma){
        ERROR extra_variables;
        extra_variables.extra_variables = true;
        errors->push_back(extra_variables);
    }
}

std::string MainWindow::ErrorHandling(std::vector<ERROR> errors, std::string function) {
    std::string conclusion;
    bool extra_flag = false, is_extra_close_bracket = false, is_extra_open_bracket = false, extra_flag_after_close = false, extra_quotes = false;
    for (size_t i = 0; i < errors.size(); ++i) {
        if (errors[i].wrong_func) {
            conclusion+="Строка ";
            conclusion+= std::to_string(errors[i].string_number);
            conclusion+=". Ошибка: ";
            conclusion+=function;
            conclusion+=" - нет такой функции. Возможно Вы имели ввиду printf\n";
        } else if (!extra_flag && errors[i].extra_symblos) {
            extra_flag = true;
            conclusion+="Строка ";
            conclusion+= std::to_string(errors[i].string_number);
            conclusion+=". Ошибка: лишние символы после названия функции\n";
        } else if (!extra_flag_after_close && errors[i].extra_symbols_after_close_bracket) {
            extra_flag_after_close = true;
            conclusion+="Строка ";
            conclusion+= std::to_string(errors[i].string_number);
            conclusion+=". Ошибка: лишние символы после закрывающей скобки\n";
        } else if (!is_extra_open_bracket && errors[i].no_open_bracket) {
            is_extra_open_bracket = true;
            conclusion+="Строка ";
            conclusion+= std::to_string(errors[i].string_number);
            conclusion+=". Ошибка: нет открывающей скобки\n";
        } else if (!is_extra_close_bracket && errors[i].no_close_bracket) {
            is_extra_close_bracket = true;
            conclusion+="Строка ";
            conclusion+= std::to_string(errors[i].string_number);
            conclusion+=". Ошибка: нет закрывающей скобки\n";
        } else if (errors[i].no_semicolon) {
            conclusion+="Строка ";
            conclusion+= std::to_string(errors[i].string_number);
            conclusion+=". Ошибка: нет знака ; после выражения\n";
        } else if (errors[i].extra_before_quote) {
            conclusion+="Строка ";
            conclusion+= std::to_string(errors[i].string_number);
            conclusion+=". Ошибка: лишние символы перед кавычками\n";
        } else if (!extra_quotes  && errors[i].extra_quotes) {
            extra_quotes = true;
            conclusion+="Строка ";
            conclusion+= std::to_string(errors[i].string_number);
            conclusion+=". Ошибка: лишние кавычки. Должна быть только пара кавычек\n";
        } else if (errors[i].extra_specifier) {
            conclusion+="Строка ";
            conclusion+= std::to_string(errors[i].string_number);
            conclusion+=". Ошибка: лишние спецификаторы. Число спецификаторов должно совпадать с числом аргументов\n";
        } else if (errors[i].extra_variables) {
            conclusion+="Строка ";
            conclusion+= std::to_string(errors[i].string_number);
            conclusion+=". Ошибка: лишние переменные или константы. Число спецификаторов должно совпадать с числом аргументов\n";
        } else if (errors[i].no_quotes) {
            conclusion+="Строка ";
            conclusion+= std::to_string(errors[i].string_number);
            conclusion+=". Ошибка: не хватает кавычек\n";
        }
    }

    return conclusion;
}



void MainWindow::on_save_clicked()
{
//    ui_->save->setToolTip("Сохранить отчет");
//    QToolTip::showText( ui_->save->mapToGlobal( QPoint( 0, 0 ) ), "errorString" );
//    QToolTip::showText(QPoint(10,10),"текст сообщения");
}


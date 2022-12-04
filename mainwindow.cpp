#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow) {
    ui_->setupUi(this);
    ui_->field_input->setPlaceholderText("Введите код ...");
    ui_->field_output->setPlaceholderText("Результат запуска ...");

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
        string[string.size()] = '\n'/*, string[string.size()+1] = '\0'*/;
        bool is_fun_end = false, is_open_bracket = false, is_close_bracket = false, is_semicolon = false; int string_number = 1;
        for (size_t index = 0; index < string.size(); index++) {
            if (index == 0) {

                while (string[index]!='(' && string[index]!=' ' && string[index]!='\t'
                       && string[index]!='\n' && string[index]!=';') {              // добавить условие чтобы мог находить все указанные элементы
                    function+=string[index];               // удаляем пробелы табуляции и переносы строк, смотрим какой знак после очищение. если не скобка говорим удалить лишние знаки
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


            if(is_fun_end && !is_open_bracket && (string[index]!= ' ' && string[index]!= '\t' && string[index]!= '\n'
                                                  && string[index]!= ';' && string[index]!= '(')) {
                ERROR extra_symbols;
                extra_symbols.extra_symblos = true;
                extra_symbols.string_number = string_number;
                errors.push_back(extra_symbols);
            }
            if(string[index] == ';') {
                is_semicolon = true;
            }
            if(is_close_bracket && !is_semicolon && (string[index]!= ' ' && string[index]!= '\t' && string[index]!= '\n')) {
                ERROR extra_symbols_after_close_bracket;
                extra_symbols_after_close_bracket.extra_symbols_after_close_bracket = true;
                extra_symbols_after_close_bracket.string_number = string_number;
                errors.push_back(extra_symbols_after_close_bracket);
            }
            if(is_fun_end && !is_open_bracket && (string[index] == ')' || string[index] == '"' || index+1 >= string.size())){
                ERROR no_open_bracket;
                no_open_bracket.no_open_bracket = true;
                no_open_bracket.string_number = string_number;
                errors.push_back(no_open_bracket);
            }

            if(string[index] == ')') {
                is_close_bracket = true;
            }
            if((is_open_bracket && !is_close_bracket  && (string[index] == ';' ||index+1 >= string.size() )) /*|| index+1 >= string.size()*/) {
                std::cout<<"is_open_bracket = "<<is_open_bracket<<" is_close_bracket = "<<is_close_bracket;
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

            //            size_t in =
//            if(is_open_bracket && !is_close_bracket && (string[index]!= ' ' && string[index]!= '\t' && string[index]!= '\n' && string[index]!= '"')) {
//                //                size_t in1 = string.find_first_not_of(' '),  in2 = string.find_first_not_of('\t'), in3 = string.find_first_not_of('\n');
//                //                if (string[in1]!='"' && string[in2]!='"' && string[in3]!='"') {
//                ERROR extra_before_quote;
//                extra_before_quote.extra_before_quote = true;
//                extra_before_quote.string_number = string_number;
//                errors.push_back(extra_before_quote);
//                //                }
//                //                index+=in1,index+=in2,index+=in3;
//            }



            if(string[index]!= ' ' && string[index]!= '\t' && string[index]!= '\n'){
                original_expression+=string[index];
            }
        }
        //        printf()fddfd;
        bool extra_flag = false, is_extra_close_bracket = false, is_extra_open_bracket = false, extra_flag_after_close = false;
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
            }
        }
    }

    auto pair = std::make_pair(original_expression, conclusion);
    return pair;
}

//            while ((string.find_first_not_of(' ',index) - index
//                   || string.find_first_not_of('\t',index) - index
//                   || string.find_first_not_of('\n',index) - index) && string[index] != '\0') {
//                size_t sub1 = string.find_first_not_of(' ',index) - index;
//                size_t sub2 = string.find_first_not_of('\t',index) - index;
//                size_t sub3 = string.find_first_not_of('\n',index) - index;
//                index+=sub1;
//                index+=sub2;
//                index+=sub3;
//            }


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
    //    std::cout<<string<<std::endl;
    std::string is_wrong;
    std::string conclusion, original_expression;
    while (string.find_first_not_of(' ')
           || string.find_first_not_of('\t')
           || string.find_first_not_of('\n')) {
        string.erase(0, string.find_first_not_of(' '));
        string.erase(0, string.find_first_not_of('\t'));
        string.erase(0, string.find_first_not_of('\n'));
    }
    string[string.size()] = '\n';
    bool is_printf = false, is_fun_end = false, is_left_bracket = false, is_right_bracket = false; int string_number = 1;
    for (size_t index = 0; index < string.size(); index++) {
        if (index == 0) {
            std::string function{};
            while (string[index]!='(' && string[index]!=' ' && string[index]!='\t' && string[index]!='\n') {              // добавить условие чтобы мог находить все указанные элементы
                function+=string[index];               // удаляем пробелы табуляции и переносы строк, смотрим какой знак после очищение. если не скобка говорим удалить лишние знаки
                index++;
            }
            if(function!="printf") {
                conclusion+="Строка ";
                conclusion+= std::to_string(string_number);
                conclusion+=". Ошибка: нет такой функции. Возможно Вы имели ввиду printf\n";
            }

            while (string.find_first_not_of(' ',index) - index
                   || string.find_first_not_of('\t',index) - index
                   || string.find_first_not_of('\n',index) - index) {
                size_t sub1 = string.find_first_not_of(' ',index) - index;
                size_t sub2 = string.find_first_not_of('\t',index) - index;
                size_t sub3 = string.find_first_not_of('\n',index) - index;
                index+=sub1;
                index+=sub2;
                index+=sub3;
            }
            original_expression+=function;
            is_fun_end = true;
        }
        if(is_fun_end && string[index]!='(') {
            conclusion+="Строка ";
            conclusion+= std::to_string(string_number);
            if(string[index+1]=='('){
                conclusion+=". Ошибка: удалите лишние элементы перед открывающей скобкой\n";
            }else {
                conclusion+=". Ошибка: нет открывающей скобки\n";
            }

        }
        if (string[index]=='\n') {
            if (string[index-1] != ';') {
                conclusion+="Строка ";
                conclusion+= std::to_string(string_number);
                conclusion+=". Ошибка: нет знака ; после выражения\n";
            }
            string_number++;
        }
        original_expression += string[index];
    }
    auto pair = std::make_pair(original_expression, conclusion);
    return pair;
}


#include "information.h"
#include "ui_information.h"

Information::Information(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::information)
{
    ui->setupUi(this);
    QString line;
    line="Функция <font color='red'>printf</font> выводит в стандартный поток вывода строку, отформатированную в соответствии с правилами, указанными в строке, на которую указывает аргумент format.\nКаждый спецификатор формата начинается с символа <font color='blue'>'%'</font> и имеет следующий формат: <font color='blue'>%c, %d, %i, %e, %E, %f, %g, %G, %o, %s, %u, %x, %X, %p, %n.</font>";
    ui->label->setText(line);
    ui->label_2->setText("Например: printf(\"%d\", variable);");
}

Information::~Information()
{
    delete ui;
}

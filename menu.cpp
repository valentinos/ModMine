#include "menu.h"
#include "ui_menu.h"

Menu::Menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::Click()
{
    QObject * buttonObject = sender();
    QPushButton * button = qobject_cast<QPushButton*>(buttonObject);
    if(button)
    {
        emit ChangeRow(ui->gridLayout->indexOf(button)+1);
    }
}

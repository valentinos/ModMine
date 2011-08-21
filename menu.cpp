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

void Menu::on_RestoreButton_clicked()
{
    emit ChangeRow(1);
}

void Menu::on_AboutButton_clicked()
{
    emit ChangeRow(3);
}

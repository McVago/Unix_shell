#include "file_explorer.h"
#include "ui_file_explorer.h"

File_Explorer::File_Explorer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::File_Explorer)
{
    ui->setupUi(this);
}

File_Explorer::~File_Explorer()
{
    delete ui;
}

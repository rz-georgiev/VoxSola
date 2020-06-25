#include "lockvoxsoladialog.h"
#include "ui_lockvoxsoladialog.h"

lockvoxsoladialog::lockvoxsoladialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::lockvoxsoladialog)
{
    ui->setupUi(this);


    load_main_lock_dialog_settings();

}

lockvoxsoladialog::~lockvoxsoladialog() // dialog destructor
{
    delete ui;
}

void lockvoxsoladialog::load_main_lock_dialog_settings() // load lock_vox_sola_dialog main settings [title, size, parents, etc];
{

    this->setWindowTitle("VoxSola вход");
    this->setFixedSize(this->width(), this->height());


    newMainVoxSolaDialog = new MainVoxSolaDialog(this);


    setMask((new QPixmap(":/Images/Images/LockScreenNX-01Wallpaper.png"))->mask());

    QPalette *newPalette = new QPalette();
    newPalette->setBrush(QPalette::Background, QBrush(QPixmap(":/Images/Images/LockScreenNX-01Wallpaper.png")));
    setPalette(*newPalette);

}


void lockvoxsoladialog::on_EnterVoxSolaMainMenuButton_clicked() // check username and password to enter in the main dialog, otherwise return error message
{
    if(ui->UsernameLine->text() == "Vox" && ui->PasswordLine->text() == "Sola")
    {
        newMainVoxSolaDialog->show();
        ui->EnterVoxSolaMainMenuButton->setEnabled(false);
        ui->CloseDialogButton->setEnabled(false);
        ui->UsernameLine->setEnabled(false);
        ui->PasswordLine->setEnabled(false);
    }
    else
    {
        QMessageBox::critical(this, "Грешно въведени данни", "Моля опитайте отново");
    }
}

void lockvoxsoladialog::on_CloseDialogButton_clicked() // when click close button, close the program on low level [exit(0)]
{
    exit(0);
}


void lockvoxsoladialog::mouseMoveEvent(QMouseEvent *event) // allows dialog to be moved, when moving mouse after erasing background with NX-01
{
    if(event->buttons() == Qt::LeftButton)
    {
        move(event->globalPos() - dragPosition);
        event->accept();
    }
}

void lockvoxsoladialog::mousePressEvent(QMouseEvent *event) // allows dialog to be moved, when pressing left mouse button
{
    if(event->button() == Qt::LeftButton)
    {
        dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

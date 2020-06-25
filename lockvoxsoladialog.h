#ifndef LOCKVOXSOLADIALOG_H
#define LOCKVOXSOLADIALOG_H

#include <QDialog>

#include <QtGui>
#include <QtCore>
#include <QDebug>
#include <QPixmap>
#include <QPalette>
#include <QMessageBox>
#include <QCoreApplication>
#include "mainvoxsoladialog.h"



namespace Ui {
class lockvoxsoladialog;
}

class lockvoxsoladialog : public QDialog
{
    Q_OBJECT

public:
    explicit lockvoxsoladialog(QWidget *parent = 0);
    ~lockvoxsoladialog();


private slots:

    void on_EnterVoxSolaMainMenuButton_clicked();

    void on_CloseDialogButton_clicked();


private:

    Ui::lockvoxsoladialog *ui;

    MainVoxSolaDialog *newMainVoxSolaDialog;

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

    void load_main_lock_dialog_settings();

    QPoint dragPosition;

};

#endif // LOCKVOXSOLADIALOG_H

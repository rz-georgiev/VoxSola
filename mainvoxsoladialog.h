#ifndef MAINVOXSOLADIALOG_H
#define MAINVOXSOLADIALOG_H

#include <QDialog>

#include <QDir>
#include <QChar>
#include <QtGui>
#include <QtCore>
#include <QDebug>
#include <QEvent>
#include <QString>
#include <QPixmap>
#include <QPalette>
#include <QMessageBox>
#include <QFileDialog>
#include <QApplication>
#include <QInputDialog>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QGraphicsEffect>

namespace Ui {
class MainVoxSolaDialog;
}

class MainVoxSolaDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MainVoxSolaDialog(QWidget *parent = 0);
    ~MainVoxSolaDialog();

private slots:

    void on_CryptButton_clicked();

    void on_SaveMessageButton_clicked();

    void on_PlayMessageButton_clicked();

    void on_StopMessageButton_clicked();

    void on_DecryptMessageButton_clicked();

    void on_PlayMessageOnDecrypt_clicked();

    void on_StopMessageOnDecrypt_clicked();

    void on_ExitVoxSolaButton_clicked();


private:
    Ui::MainVoxSolaDialog *ui;


    int MessageWithUnicode[32768], MessageWithPreBinary[32768], MessageBinaryLengths[32768];

    int BinaryCounter, MainCounter, SecondaryCounter, MaximumCounter, BinaryToUnicodeCounter, BinaryToUnicodeMinusCounter;

    QChar MessageWithChars[32768];

    QString MessageWithBinary[32768];

    QString MessageForCrypting, MessagePath, CopyMessagePath, BinarySpacePath, BinaryStringTempList;

    QMediaPlayer *newBinaryMediaPlayer;

    QMediaPlaylist *newBinaryMediaPlayerList;

    QPoint dragPosition;


    void checkMaxCounter();
    void checkMaxCounterOnBinarySpace();

    void readDirectoryFilesAndPlayMessage();
    void prepareToReadDirFilesAndDecryptMessage();

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

    void Load_Main_Settings();

    void reject();
};

#endif // MAINVOXSOLADIALOG_H

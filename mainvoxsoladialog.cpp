#include "mainvoxsoladialog.h"
#include "ui_mainvoxsoladialog.h"

MainVoxSolaDialog::MainVoxSolaDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainVoxSolaDialog)
{
    ui->setupUi(this);

    Load_Main_Settings();

}

MainVoxSolaDialog::~MainVoxSolaDialog()  // dialog destructor
{
    delete ui;
}

void MainVoxSolaDialog::Load_Main_Settings()  // load lock_vox_sola_dialog main settings [title, size, parents, etc];
{
    this->setFixedSize(this->width(), this->height());


    setMask((new QPixmap(":/Images/Images/VoxSolaMainDialogWallpaper.png"))->mask().createHeuristicMask());
    QPalette *newPalette = new QPalette();

    newPalette->setBrush(QPalette::Background, QBrush(QPixmap(":/Images/Images/VoxSolaMainDialogWallpaper.png")));
    setPalette(*newPalette);

    ui->DecryptPlainBox->setReadOnly(true);

    newBinaryMediaPlayer = new QMediaPlayer;
    newBinaryMediaPlayerList = new QMediaPlaylist;

    newBinaryMediaPlayerList->setPlaybackMode(QMediaPlaylist::Sequential);
    newBinaryMediaPlayer->setPlaylist(newBinaryMediaPlayerList);


    MainCounter = 0;
    BinaryCounter = 0;
    MaximumCounter = 0;
    SecondaryCounter = 0;
    BinaryToUnicodeCounter = 0;
    BinaryToUnicodeMinusCounter = 0;
}


void MainVoxSolaDialog::on_CryptButton_clicked()  // crypting the string that you've entered
{

    if(ui->CryptPlainBox->toPlainText().isEmpty())
    {
        QMessageBox::information(this, "Информация", "Моля въведете израз");
    }
    else
    {
        for(int i = 0; i <= 32767; i++)
        {
            MessageWithUnicode[i] = 0;
            MessageWithPreBinary[i] = 0;
            MessageWithChars[i] = 0;
            MessageWithBinary[i].clear();
        }
        MessageForCrypting.clear();

        MessageForCrypting = ui->CryptPlainBox->toPlainText();
        for(int i = 0; i <= MessageForCrypting.length() - 1; i++)
        {
            MessageWithChars[i] = MessageForCrypting.at(i);
            MessageWithUnicode[i] = MessageWithChars[i].unicode();


            if( MessageWithUnicode[i] >= 0 && MessageWithUnicode[i] <= 10)
            {
                MessageWithPreBinary[i] = MessageWithUnicode[i] + 2;
            }
            else if( MessageWithUnicode[i] >= 11 && MessageWithUnicode[i] <= 99)
            {
                MessageWithPreBinary[i] = MessageWithUnicode[i] + 2;
            }
            else if( MessageWithUnicode[i] >= 100 && MessageWithUnicode[i] <= 999)
            {
                MessageWithPreBinary[i] = MessageWithUnicode[i] + 22;
            }
            else if( MessageWithUnicode[i] >= 1000)
            {
                MessageWithPreBinary[i] = MessageWithUnicode[i] + 222;
            }
            else
            {
                MessageWithPreBinary[i] = MessageWithUnicode[i];
            }


            while(MessageWithPreBinary[i] != 0)
            {
                if(MessageWithPreBinary[i] % 2 == 0)
                {
                    MessageWithBinary[i] = MessageWithBinary[i] + "0";
                }
                else
                {
                    MessageWithBinary[i] = MessageWithBinary[i] + "1";
                }
                MessageWithPreBinary[i] = MessageWithPreBinary[i] / 2;

            }
            std::reverse(MessageWithBinary[i].begin(), MessageWithBinary[i].end());

        }

        ui->CryptPlainBox->selectAll();
        ui->CryptPlainBox->copy();
        QMessageBox::information(this, "Информация", "Съобщението е криптирано и е запазено на клипборда");
    }



}

void MainVoxSolaDialog::on_SaveMessageButton_clicked() // saving crypted message to the directory that the user choose
{
    if(ui->CryptPlainBox->toPlainText().isEmpty())
    {
        QMessageBox::information(this, "Информация", "Моля въведете израз");
    }
    else
    {
        MessagePath.clear();
        CopyMessagePath.clear();

        MaximumCounter = 0;

        for(int i = 0; i <= 32767; i++)
        {
            MessageBinaryLengths[i] = 0;
        }

        MessagePath = QFileDialog::getExistingDirectory(this, "Избор на директория", "Моля изберете директория");

        qDebug() << MessagePath;

        if(MessagePath.isEmpty())
        {
            QMessageBox::information(this, "Информация", "Неправилно зададена директория или грешно име");
        }
        else
        {
            for(MainCounter = 0; MainCounter <= ui->CryptPlainBox->toPlainText().length() - 1; MainCounter++)
            {

                   MessageBinaryLengths[MainCounter] = MessageWithBinary[MainCounter].length();

                   for(SecondaryCounter = 0; SecondaryCounter <= MessageBinaryLengths[MainCounter] - 1; SecondaryCounter++)
                   {
                           if(MessageWithBinary[MainCounter].at(SecondaryCounter) == '0')
                           {
                               CopyMessagePath.clear();

                                   MaximumCounter += 1;

                                   checkMaxCounter();

                                 QFile::copy(QApplication::applicationDirPath() + "/Zero_Wave_Signal.wav", CopyMessagePath);
                           }

                           else
                           {
                               CopyMessagePath.clear();

                               MaximumCounter += 1;

                               checkMaxCounter();

                               QFile::copy(QApplication::applicationDirPath() + "/First_Wave_Signal.wav", CopyMessagePath);
                           }


                    }

                   BinarySpacePath.clear();

                   MaximumCounter += 1;

                   checkMaxCounterOnBinarySpace();


                   QFile::copy(QApplication::applicationDirPath() + "/BinarySpace.txt", BinarySpacePath);

            }
            QMessageBox::information(this, "Информация", "Ващето съобщение беше разбито на фрагменти");
        }

    }



}

void MainVoxSolaDialog::on_DecryptMessageButton_clicked()  // choosing crypted message directory and decrypt message by using the function below
{
    prepareToReadDirFilesAndDecryptMessage();
}



void MainVoxSolaDialog::checkMaxCounter() // check how much zeros to put before copy message path
{
    if(MaximumCounter <= 9)
    {
        CopyMessagePath = MessagePath + "/" + "00000" + QString::number(MaximumCounter) + ".wav";
    }
    else if(MaximumCounter <= 99)
    {
        CopyMessagePath = MessagePath + "/" + "0000" + QString::number(MaximumCounter) + ".wav";
    }
    else if(MaximumCounter <= 999)
    {
        CopyMessagePath = MessagePath + "/" + "000" + QString::number(MaximumCounter) + ".wav";
    }
    else if(MaximumCounter <= 9999)
    {
        CopyMessagePath = MessagePath + "/" + "00" + QString::number(MaximumCounter) + ".wav";
    }
    else if(MaximumCounter <= 99999)
    {
        CopyMessagePath = MessagePath + "/" + "0" + QString::number(MaximumCounter) + ".wav";
    }
    else
    {
        CopyMessagePath = MessagePath + "/" + QString::number(MaximumCounter) + ".wav";
    }
}

void MainVoxSolaDialog::checkMaxCounterOnBinarySpace() // check how much zeros to put before binary space path
{
    if(MaximumCounter <= 9)
    {
        BinarySpacePath = MessagePath + "/" + "00000" + QString::number(MaximumCounter) + ".txt";
    }
    else if(MaximumCounter <= 99)
    {
        BinarySpacePath = MessagePath + "/" + "0000" + QString::number(MaximumCounter) + ".txt";
    }
    else if(MaximumCounter <= 999)
    {
        BinarySpacePath = MessagePath + "/" + "000" + QString::number(MaximumCounter) + ".txt";
    }
    else if(MaximumCounter <= 9999)
    {
        BinarySpacePath = MessagePath + "/" + "00" + QString::number(MaximumCounter) + ".txt";
    }
    else if(MaximumCounter <= 99999)
    {
        BinarySpacePath = MessagePath + "/" + "0" + QString::number(MaximumCounter) + ".txt";
    }
    else
    {
        BinarySpacePath = MessagePath + "/" + QString::number(MaximumCounter) + ".txt";
    }
}



void MainVoxSolaDialog::readDirectoryFilesAndPlayMessage() // check files sound signals sizes in bytes, fill media player buffer, and play message
{
    newBinaryMediaPlayerList->clear();


    QString MessageDirPath = QFileDialog::getExistingDirectory(this, "Моля изберете директория", "Моля изберете директория");
    if(MessageDirPath.isEmpty())
    {
        QMessageBox::critical(this,"Грешка", "Не е зададена директория");
    }
    else
    {

        QDir MessageDir(MessageDirPath);



               MessageDir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
               MessageDir.setSorting(QDir::Name);

               QFileInfoList list = MessageDir.entryInfoList();

               for (int i = 0; i < list.size(); i++) {
                   QFileInfo fileInfo = list.at(i);


                   if(fileInfo.size() == 11968)
                   {
                       newBinaryMediaPlayerList->addMedia(QUrl(QApplication::applicationDirPath() + "/First_Wave_Signal.wav"));
                   }
                   else if(fileInfo.size() == 9702)
                   {
                       newBinaryMediaPlayerList->addMedia(QUrl(QApplication::applicationDirPath() + "/Zero_Wave_Signal.wav"));
                   }
              }

               newBinaryMediaPlayer->play();

    }
}

void MainVoxSolaDialog::prepareToReadDirFilesAndDecryptMessage() // read binary signals in the directory with crypted message
{
    newBinaryMediaPlayerList->clear();
    ui->DecryptPlainBox->clear();

    QString MessageDirPath = QFileDialog::getExistingDirectory(this, "Моля изберете директория", "Моля изберете директория");
    if(MessageDirPath.isEmpty())
    {
        QMessageBox::critical(this,"Грешка", "Не е зададена директория");
    }
    else
    {

        QDir MessageDir(MessageDirPath);


               MessageDir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
               MessageDir.setSorting(QDir::Name);

               QFileInfoList list = MessageDir.entryInfoList();

               for (int i = 0; i < list.size(); i++)
               {

                   QFileInfo fileInfo = list.at(i);

                   if(fileInfo.size() == 11968)
                   {
                       BinaryStringTempList = BinaryStringTempList + "1";
                   }
                   else if(fileInfo.size() == 9702)
                   {
                       BinaryStringTempList = BinaryStringTempList + "0";
                   }
                   else if(fileInfo.size() == 11)
                   {
                       BinaryToUnicodeMinusCounter = BinaryStringTempList.length() - 1;

                        for(int j = 0; j <= BinaryStringTempList.length() - 1; j++)
                        {


                            if(BinaryStringTempList.at(j) == '1')
                            {
                                BinaryToUnicodeCounter = BinaryToUnicodeCounter + 1*pow(2,BinaryToUnicodeMinusCounter);

                                BinaryToUnicodeMinusCounter = BinaryToUnicodeMinusCounter - 1;

                            }

                            else if(BinaryStringTempList.at(j) == '0')
                            {
                                BinaryToUnicodeCounter = BinaryToUnicodeCounter + 0*pow(2,BinaryToUnicodeMinusCounter);

                                BinaryToUnicodeMinusCounter = BinaryToUnicodeMinusCounter - 1;

                            }

                        }


                        int DecryptPlainBoxCharToInt = 0;

                        if(BinaryToUnicodeCounter >= 2 && BinaryToUnicodeCounter <= 12)
                        {
                           DecryptPlainBoxCharToInt = BinaryToUnicodeCounter - 2;
                        }
                        else if(BinaryToUnicodeCounter >= 13 && BinaryToUnicodeCounter <= 101)
                        {
                           DecryptPlainBoxCharToInt = BinaryToUnicodeCounter - 2;
                        }
                        else if(BinaryToUnicodeCounter >= 122 && BinaryToUnicodeCounter <= 1021)
                        {
                           DecryptPlainBoxCharToInt = BinaryToUnicodeCounter - 22;
                        }
                        else if(BinaryToUnicodeCounter >= 1222)
                        {
                           DecryptPlainBoxCharToInt = BinaryToUnicodeCounter - 222;
                        }
                        else
                        {
                            DecryptPlainBoxCharToInt = BinaryToUnicodeCounter;
                        }




                        QChar nMyChar = (QChar)DecryptPlainBoxCharToInt;
                        qDebug() << "ORIGINAL VALUE AGAIN: " << DecryptPlainBoxCharToInt;
                        ui->DecryptPlainBox->setPlainText(ui->DecryptPlainBox->toPlainText() + QString(nMyChar));


                        BinaryToUnicodeMinusCounter = 0;
                        BinaryToUnicodeCounter = 0;

                        BinaryStringTempList.clear();
                   }
              }
               ui->DecryptPlainBox->selectAll();
               ui->DecryptPlainBox->copy();
               QMessageBox::information(this, "Информация", "Съобщението е декриптирано и е запазено на клипборда");
    }

}



void MainVoxSolaDialog::on_PlayMessageButton_clicked() // play all sound files that are in the media player buffer on crypt mode
{
    readDirectoryFilesAndPlayMessage();
}

void MainVoxSolaDialog::on_StopMessageButton_clicked() // stop all sound files that are in the media player buffer on crypt mode
{
    newBinaryMediaPlayer->stop();
}



void MainVoxSolaDialog::on_PlayMessageOnDecrypt_clicked() // play all sound files that are in the media player buffer on decrypt mode
{
    readDirectoryFilesAndPlayMessage();
}

void MainVoxSolaDialog::on_StopMessageOnDecrypt_clicked() // stop all sound files that are in the media player buffer on decrypt mode
{
    newBinaryMediaPlayer->stop();
}



void MainVoxSolaDialog::mouseMoveEvent(QMouseEvent *event) // allows dialog to be moved, when moving mouse after erasing background with the Vox Sola Planet
{
    if(event->buttons() == Qt::LeftButton)
    {
        move(event->globalPos() - dragPosition);
        event->accept();
    }
}

void MainVoxSolaDialog::mousePressEvent(QMouseEvent *event) // allows dialog to be moved, when pressing left mouse button
{
    if(event->button() == Qt::LeftButton)
    {
        dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}



void MainVoxSolaDialog::on_ExitVoxSolaButton_clicked() // exit from Vox Sola in the standard Qt way [ this->close() ];
{
    this->close();
}

void MainVoxSolaDialog::reject()  // override exit function with low level exit, instead of Qt way exit
{
    exit(0);
}

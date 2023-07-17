#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SetWindowPos(reinterpret_cast<HWND>(this->winId()), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent * event)
{
    ui->edtText->resize(ui->centralwidget->size());

    QMainWindow::resizeEvent(event);
}

void MainWindow::closeEvent(QCloseEvent * event)
{
    if(!ui->edtText->toPlainText().isEmpty())
    {
        QMessageBox * pMsgBox = new QMessageBox(nullptr);
        pMsgBox->setText("文本框中存在文本，是否确认关闭？");
        pMsgBox->setIcon(QMessageBox::Question);
        pMsgBox->setStandardButtons(QMessageBox::Close | QMessageBox::Cancel);
        pMsgBox->buttons().at(0)->setText("关闭");
        pMsgBox->buttons().at(1)->setText("不关闭");
        int buttunPressed = pMsgBox->exec();
        delete pMsgBox;
        if(buttunPressed == QMessageBox::Close)
        {
            event->accept();
        }
        else if(buttunPressed == QMessageBox::Cancel)
        {
            event->ignore();
        }
    }
    else
    {
        event->accept();
    }
}


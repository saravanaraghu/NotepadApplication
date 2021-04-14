#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFile>
#include<QFileDialog>
#include<QMessageBox>
#include<QFontDialog>
#include<QFont>
#include<QIODevice>
#include<QtPrintSupport/qprinter.h>
#include<QtPrintSupport/qprintdialog.h>
#include<QPrinter>
#include<QPrintDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionnee_file_triggered()
{
    ui->textEdit->setText(QString());



}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionOpen_file_triggered()
{
    QString filename=QFileDialog::getOpenFileName(this,"Open the file");
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"Warning","The file can't be opened "+file.errorString());
    }
    setWindowTitle(filename);
    QTextStream in(&file);
    QString text=in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void MainWindow::on_actionSave_as_triggered()
{
    QString filename=QFileDialog::getSaveFileName(this,"Save as..");
    QFile file(filename);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"Warning","The file can't be saved "+file.errorString());
        return;
    }
    setWindowTitle(filename);
    QTextStream out(&file);
    QString text=ui->textEdit->toPlainText();
    out<<text;
    file.close();
}

void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;
    printer.setPrinterName("Printer Name");
    QPrintDialog pDialog(&printer,this);
    if(pDialog.exec()==QDialog::Rejected){
        QMessageBox::warning(this,"Warning","Cannot access private");
        return;
    }
    ui->textEdit->print(&printer);
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionUnderlinne_triggered()
{
    ui->textEdit->setStyleSheet("font:Vladimir Script");
}

void MainWindow::on_actionSelect_font_triggered()
{
    bool fontselected;
    QFont font=QFontDialog::getFont(&fontselected,this);
    if(fontselected){
        ui->textEdit->setFont(font);
    }
}

void MainWindow::on_actionItalic_triggered()
{
    ui->textEdit->setStyleSheet("font:italic");
}


void MainWindow::on_actionBold_triggered()
{
    ui->textEdit->setStyleSheet("font:bold");
}

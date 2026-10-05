#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QFile"
#include "QTextStream"
#include "QStringList"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setStyleSheet(
        "QMainWindow { background-color: #2b2b2b; }"
        "QLabel { color: #ffffff; font-size: 16px; font-weight: bold; }"
        "QPushButton { background-color: #007acc; color: white; border-radius: 5px; padding: 8px; font-weight: bold; }"
        "QPushButton:hover { background-color: #0098ff; }"
        "QTableWidget { background-color: #3c3f41; color: white; gridline-color: #555555; font-size: 14px; border: none; }"
        "QHeaderView::section { background-color: #2d2d2d; color: white; padding: 5px; font-weight: bold; border: 1px solid #444; }"
        "QLineEdit { background-color: #3c3f41; color: white; border: 1px solid #555; border-radius: 4px; padding: 5px; font-size: 14px; }"
        );

    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels({" Descriere", "Suma"});

    QFile file("cheltuieli.txt");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in (&file);
        double total = 0;

        while(!in.atEnd()){
            QString linie = in.readLine();
            QStringList bucati = linie.split(",");

            if(bucati.size() == 2){
                int randNou = ui -> tableWidget -> rowCount();

                ui -> tableWidget -> insertRow(randNou);
                ui->tableWidget->setItem(randNou, 0, new QTableWidgetItem(bucati[0]));
                ui->tableWidget->setItem(randNou, 1, new QTableWidgetItem(bucati[1]));

                total += bucati[1].toDouble();
            }
            file.close();
            ui->label->setText("Total : " + QString::number(total));
        }
    }
}

MainWindow::~MainWindow()
{
    QFile file("cheltuieli.txt");
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream out(&file);

        for(int i = 0; i < ui->tableWidget->rowCount(); ++i){
            QString descriere = ui -> tableWidget ->item(i,0) -> text();
            QString suma = ui->tableWidget->item(i, 1)->text();

            out << descriere << "," << suma << "\n";
        }
    }
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString descriere = ui -> lineEdit -> text();
    QString suma = ui -> lineEdit_2 -> text();

    if(!descriere.isEmpty() && !suma.isEmpty()){
        int randNou = ui -> tableWidget -> rowCount();

        ui -> tableWidget -> insertRow(randNou);

        ui -> tableWidget -> setItem(randNou, 0, new QTableWidgetItem(descriere));
        ui -> tableWidget -> setItem(randNou , 1 , new QTableWidgetItem(suma));

        ui -> lineEdit -> clear();
        ui -> lineEdit_2 -> clear();
    }

    double total = 0;


    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {

        QTableWidgetItem *itemSuma = ui->tableWidget->item(i, 1);

        if (itemSuma != nullptr) {

            total += itemSuma->text().toDouble();
        }
    }

    ui->label->setText("Total: " + QString::number(total));
}


void MainWindow::on_pushButton_2_clicked()
{
    int rand_selectat = ui -> tableWidget -> currentRow();

    if(rand_selectat >= 0){
        ui -> tableWidget -> removeRow(rand_selectat);
    }

    double total = 0;


    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {

        QTableWidgetItem *itemSuma = ui->tableWidget->item(i, 1);

        if (itemSuma != nullptr) {

            total += itemSuma->text().toDouble();
        }
    }

    ui->label->setText("Total: " + QString::number(total));
}


void MainWindow::on_pushButton_3_clicked()
{
    int randSelectat = ui -> tableWidget -> currentRow();

    if(randSelectat >= 0){
        QString descriere = ui ->  lineEdit -> text();
        QString suma = ui ->  lineEdit_2 -> text();


        if(!descriere.isEmpty() && !suma.isEmpty()){
            ui -> tableWidget -> setItem(randSelectat, 0, new QTableWidgetItem(descriere));
            ui -> tableWidget -> setItem(randSelectat, 1 , new QTableWidgetItem(suma));

            double total = 0;

            for(int i = 0; i < ui -> tableWidget->rowCount(); ++i){
                QTableWidgetItem* ItemSuma = ui ->tableWidget->item(i,1);
                if(ItemSuma != nullptr){
                    total += ItemSuma -> text().toDouble();
                }
            }

            ui -> label->setText("Total : " + QString :: number(total));

            ui -> lineEdit -> clear();
            ui -> lineEdit_2 -> clear();
        }
    }
}


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <signal.h>
#include <QDebug>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->qDebugButton, &QPushButton::clicked, this, &MainWindow::onDebug);
    QObject::connect(ui->qInfoButton, &QPushButton::clicked, this, &MainWindow::onInfo);
    QObject::connect(ui->qWarningButton, &QPushButton::clicked, this, &MainWindow::onWarning);
    QObject::connect(ui->qCriticalButton, &QPushButton::clicked, this, &MainWindow::onCritical);
    QObject::connect(ui->qFatalButton, &QPushButton::clicked, this, &MainWindow::onFatal);
    QObject::connect(ui->outOfRangeQListIndex, &QPushButton::clicked, this, &MainWindow::outOfRangeQListIndex);
    QObject::connect(ui->invalidAccessMemory, &QPushButton::clicked, this, &MainWindow::invalidAccessMemory);
    QObject::connect(ui->abortError, &QPushButton::clicked, this, &MainWindow::abortError);
    QObject::connect(ui->assertFalse, &QPushButton::clicked, this, &MainWindow::assertFalse);
    QObject::connect(ui->divideBy0, &QPushButton::clicked, this, &MainWindow::divideBy0);
    QObject::connect(ui->longLongInt, &QPushButton::clicked, this, &MainWindow::longLongInt);
    QObject::connect(ui->throwError, &QPushButton::clicked, this, &MainWindow::throwError);
    QObject::connect(ui->unsignedInt, &QPushButton::clicked, this, &MainWindow::unsignedInt);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onDebug() {
    qDebug()<< "DEFLEXION : ";
}

void MainWindow::onInfo() {
    qInfo() << "Info Log!";
}

void MainWindow::onWarning() {
    qWarning() << "Warning Log!";
}

void MainWindow::onCritical() {
    qCritical() << "Critical Log!";
}

void MainWindow::onFatal() {
    qFatal("Fatal Log!");
}

void MainWindow::outOfRangeQListIndex(){
    QList<double> myQList;
    myQList.append(12.5);
    myQList.append(12.1);
    std::cout << myQList[99];
}

void MainWindow::invalidAccessMemory(){
    int *a;
    *a = 0;
}

void MainWindow::abortError(){
    abort();
}

void MainWindow::assertFalse(){
    assert(false);
}

void MainWindow::divideBy0(){
    std::cout << 1/0;
}

void MainWindow::longLongInt(){
    for (long long int i = 0; ++i; (&i)[i] = i);
}

void MainWindow::throwError(){
    throw 10;
}

void MainWindow::unsignedInt(){
    *((unsigned int*)0) = 0xDEAD;
}

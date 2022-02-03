#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public:
    void onDebug();
    void onInfo();
    void onWarning();
    void onCritical();
    void onFatal();
    void outOfRangeQListIndex();
    void invalidAccessMemory();
    void abortError();
    void assertFalse();
    void divideBy0();
    void longLongInt();
    void throwError();
    void unsignedInt();
    void activateDebug();

};
#endif // MAINWINDOW_H

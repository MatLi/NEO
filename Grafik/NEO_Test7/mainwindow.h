//Mari
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent (QPaintEvent *event);

private:
    Ui::MainWindow *ui;


private slots:
    void on_pushButton_clicked();
    void on_actionOpen_activated();
};

#endif // MAINWINDOW_H

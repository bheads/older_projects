#ifndef ULMMAINWINDOW_HPP
#define ULMMAINWINDOW_HPP

#include <QMainWindow>

namespace Ui {
    class ulmMainWindow;
}

class ulmMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ulmMainWindow(QWidget *parent = 0);
    ~ulmMainWindow();

private slots:
    void on_ClientAddButton_clicked();

private:
    Ui::ulmMainWindow *ui;
};

#endif // ULMMAINWINDOW_HPP

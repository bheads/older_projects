#ifndef ADDCLIENTDIALOG_HPP
#define ADDCLIENTDIALOG_HPP

#include <QDialog>

namespace Ui {
    class AddClientDialog;
}

class AddClientDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddClientDialog(QWidget *parent = 0);
    ~AddClientDialog();

private:
    Ui::AddClientDialog *ui;
};

#endif // ADDCLIENTDIALOG_HPP

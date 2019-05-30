#ifndef CONTROLL_H
#define CONTROLL_H

#include <memory>
#include <QMainWindow>
#include <QLabel>
#include <QStandardItemModel>
#include "DataBase.h"

namespace Ui {
class Controll;
}

class Controll : public QMainWindow
{
    Q_OBJECT

public:
    explicit Controll(QWidget *parent = nullptr);
    ~Controll();

    void computeSalaryClicked();
    void computeSalaryAllClicked();
    void addClicked();
    void removeClicked();
    void updateClicked();

private:
    Ui::Controll *ui;
    QLabel *m_status;
    QStandardItemModel *m_model;
    std::shared_ptr<DataBase> m_db;

    QString clerkToString(Clerk *clerk);
    QString computeSalaryFor(int id);
};

#endif // CONTROLL_H

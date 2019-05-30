#include "ClerkCreate.h"
#include "ui_ClerkCreate.h"
#include "Employe.h"
#include "Manager.h"
#include "Sales.h"

ClerkCreate::ClerkCreate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClerkCreate)
{
    ui->setupUi(this);
    ui->cbType->addItem("Employee");
    ui->cbType->addItem("Manager");
    ui->cbType->addItem("Sales");
}

ClerkCreate::~ClerkCreate()
{
    delete ui;
}

void ClerkCreate::setDb(std::shared_ptr<DataBase> &db)
{
    m_db = db;
    auto l = m_db->getClerkList("WHERE type<>'Employee'");
    ui->cbHead->addItem("");
    for (auto &clerk : *l)
        ui->cbHead->addItem(QString("%1. %2")
                    .arg(clerk->id)
                    .arg(clerk->name));

}

Clerk *ClerkCreate::getClerk() const
{
    Clerk *clerk = nullptr;
    int type = ui->cbType->currentIndex();
    if (type == 0)
        clerk = new Employee;
    else if (type == 1)
        clerk = new Manager;
    else if (type == 2)
        clerk = new Sales;

    clerk->name = ui->leName->text();
    clerk->salary = ui->leSalary->text().toFloat();
    clerk->date = ui->deDate->date();
    QString head = ui->cbHead->currentText();
    clerk->head = head.mid(0, head.indexOf('.')).toInt();

    return clerk;
}

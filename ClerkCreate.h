#ifndef CLERKCREATE_H
#define CLERKCREATE_H

#include <memory>
#include <QDialog>
#include "DataBase.h"

namespace Ui {
class ClerkCreate;
}

class ClerkCreate : public QDialog
{
    Q_OBJECT

public:
    explicit ClerkCreate(QWidget *parent = nullptr);
    ~ClerkCreate();

    void setDb(std::shared_ptr<DataBase> &db);
    Clerk *getClerk() const;

private:
    Ui::ClerkCreate *ui;
    std::shared_ptr<DataBase> m_db;
};

#endif // CLERKCREATE_H

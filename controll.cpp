
#include <QDebug>
#include "controll.h"
#include "ui_controll.h"
#include "functions.h"
#include "ClerkCreate.h"

const QString DB_PATH = "clerks.sqlite";

Controll::Controll(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Controll),
    m_db(new DataBase(DB_PATH))
{
    ui->setupUi(this);
    m_status = new QLabel;
    m_model = new QStandardItemModel;
    ui->lvClerks->setModel(m_model);
    ui->statusBar->addWidget(m_status);

    connect(ui->pbCompute, &QPushButton::clicked,
            this, &Controll::computeSalaryClicked);
    connect(ui->pbComputeAll, &QPushButton::clicked,
            this, &Controll::computeSalaryAllClicked);
    connect(ui->pbAdd, &QPushButton::clicked,
            this, &Controll::addClicked);
    connect(ui->pbRemove, &QPushButton::clicked,
            this, &Controll::removeClicked);
    connect(ui->pbUpdate, &QPushButton::clicked,
            this, &Controll::updateClicked);

    updateClicked();

    m_status->setText("Программа загружена.");
}

Controll::~Controll()
{
    delete ui;
}

void Controll::computeSalaryClicked()
{
    QModelIndex index = ui->lvClerks->currentIndex();

    if (index.isValid())
    {
        // Извлечение id.
        QString title = index.data(Qt::DisplayRole).toString();
        QString id = title.mid(0, title.indexOf('.'));

        // Загрузка из БД и подсчет ЗП.
        title = computeSalaryFor(id.toInt());

        // Обновление в моделе.
        m_model->setItem(index.row(), 0, new QStandardItem(title));
    }

    m_status->setText(QString("ЗП на %1 посчитана")
                      .arg(ui->calendar->selectedDate().toString("dd.MM.yyyy")));
}

void Controll::computeSalaryAllClicked()
{
    for (int i = 0; i < m_model->rowCount(); ++i)
    {
        // Извлечение id.
        QModelIndex index = m_model->index(i, 0);
        QString title = index.data(Qt::DisplayRole).toString();
        QString id = title.mid(0, title.indexOf('.'));

        // Загрузка из БД и подсчет ЗП.
        title = computeSalaryFor(id.toInt());

        // Обновление в моделе.
        m_model->setItem(index.row(), 0, new QStandardItem(title));
    }
    m_status->setText(QString("ЗП на %1 посчитана")
                      .arg(ui->calendar->selectedDate().toString("dd.MM.yyyy")));
}

void Controll::addClicked()
{
    ClerkCreate create(this);
    create.setDb(m_db);
    if (create.exec() != QDialog::Accepted)
    {
        m_status->setText("Добавление пользователя отменено.");
        return;
    }

    Clerk *newClerk = create.getClerk();
    m_db->addClerk(newClerk);
    delete newClerk;

    updateClicked();
    m_status->setText("Пользователь добавлен.");
}

void Controll::removeClicked()
{
    QModelIndex index = ui->lvClerks->currentIndex();

    if (index.isValid())
    {
        QString title = index.data(Qt::DisplayRole).toString();
        QString removedId = title.mid(0, title.indexOf('.'));
        m_db->delClerk(removedId.toInt());
        updateClicked();
        m_status->setText(QString("Пользователь \"%1\" удален из БД.")
                          .arg(title));
    }
    else
    {
        m_status->setText("При удалении пользователя что-то пошло не так.");
    }
}

void Controll::updateClicked()
{
    m_model->clear();
    auto list = m_db->getClerkList();
    if (list == nullptr)
    {
        m_status->setText("При попытке получить список сотрудников произошла ошибка.");
        return;
    }

    for (auto &clerk : *list)
    {
        QStandardItem *item = new QStandardItem(clerkToString(clerk));
        m_model->appendRow(item);
    }

    m_status->setText("Список сотрудников успешно обновлен.");
}

QString Controll::clerkToString(Clerk *clerk)
{
    QString title = QString("%1.\t%2 (%3)\tгод: %4, | базовая ставка: $%5")
            .arg(clerk->id)
            .arg(clerk->name)
            .arg(clerk->getType()[0])
            .arg(clerk->date.year())
            .arg(clerk->salary);

    return title;
}

QString Controll::computeSalaryFor(int id)
{
    // Загрузка сотрудника из БД.
    Clerk *clerk = m_db->getClerk(id);

    // Подсчет ЗП.
    float salary = computeSalary(clerk, ui->calendar->selectedDate(), m_db);
    QString title = clerkToString(clerk) + QString(" | ЗП: $%1")
            .arg(salary);

    return title;
}

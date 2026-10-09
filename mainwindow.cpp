#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFormLayout>
#include <QComboBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createMenus();
    mainForm();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mainForm() {

    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    QComboBox *languageSelection = new QComboBox(central);
    QComboBox *standardSelection = new QComboBox(central);
    QComboBox *buildSelection = new QComboBox(central);
    languageSelection->setMinimumWidth(120);
    standardSelection->setMinimumWidth(120);
    buildSelection->setMinimumWidth(120);

    QPushButton *generateButton = new QPushButton(tr("Generate"), central);
    connect(generateButton, &QPushButton::clicked, this, &MainWindow::generateProject);

    connect(languageSelection, &QComboBox::currentIndexChanged, this,
            [standardSelection](int index) {
                standardSelection->clear();

                if (index == 0)        // C
                    standardSelection->addItems({"C23", "C17", "C11", "C99"});
                else if (index == 1)   // C++
                    standardSelection->addItems({"C++23", "C++20", "C++17", "C++14", "C++11", "C++03"});
            });

    languageSelection->addItems({"C", "C++"});
    buildSelection->addItems({"CMake", "Makefile", "Meson", "None"});


    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow(tr("Select the language"), languageSelection);
    formLayout->addRow(tr("Select standard"), standardSelection);
    formLayout->addRow("Build System", buildSelection);


    QVBoxLayout *outer = new QVBoxLayout(central);
    outer->addStretch();
    outer->addLayout(formLayout);
    outer->addWidget(generateButton, 0, Qt::AlignHCenter);
    outer->addStretch();
    outer->setAlignment(formLayout, Qt::AlignHCenter);

}

void MainWindow::generateProject() {

    statusBar()->showMessage(tr("Generating project..."), 3000);
}

void MainWindow::createMenus()
{
    QAction *aboutAct = new QAction(tr("&About"), this);
    QAction *docsAct = new QAction(tr("&Documentation"), this);
    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(docsAct);
    helpMenu->addAction(aboutAct);

    connect(aboutAct, &QAction::triggered, this, [this]() {
        QMessageBox::about(this, tr("About"), tr("This is an application that generates C/C++ project for you."));
    });
}
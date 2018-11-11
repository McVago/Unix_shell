/********************************************************************************
** Form generated from reading UI file 'file_explorer.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILE_EXPLORER_H
#define UI_FILE_EXPLORER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_File_Explorer
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *File_Explorer)
    {
        if (File_Explorer->objectName().isEmpty())
            File_Explorer->setObjectName(QStringLiteral("File_Explorer"));
        File_Explorer->resize(400, 300);
        menuBar = new QMenuBar(File_Explorer);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        File_Explorer->setMenuBar(menuBar);
        mainToolBar = new QToolBar(File_Explorer);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        File_Explorer->addToolBar(mainToolBar);
        centralWidget = new QWidget(File_Explorer);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        File_Explorer->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(File_Explorer);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        File_Explorer->setStatusBar(statusBar);

        retranslateUi(File_Explorer);

        QMetaObject::connectSlotsByName(File_Explorer);
    } // setupUi

    void retranslateUi(QMainWindow *File_Explorer)
    {
        File_Explorer->setWindowTitle(QApplication::translate("File_Explorer", "File_Explorer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class File_Explorer: public Ui_File_Explorer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILE_EXPLORER_H

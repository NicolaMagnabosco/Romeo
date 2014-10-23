#include "dialog.h"
#include "view/window/mainwindow.h"

using Romeo::View::Dialog::Dialog;
using Romeo::View::Window::MainWindow;

Dialog::Dialog(const QString& title, const QString& text, const QString& info, const QString& detail, QWidget *parent) : QMessageBox(parent)
{
    setWindowTitle(title);
    setWindowIcon(QIcon(":/Romeo/romeoLogo.png"));
    setText(text);
    setInformativeText(info);
    setDetailedText(detail);
}

int Dialog::dialogInfo(const QString& title, const QString& text, const QString& info, const QString& detail, QWidget *parent)
{
    Dialog *dialog = new Dialog(title, text, info, detail, (!parent ? MainWindow::getMainWindow(): parent));
    dialog->setIcon(QMessageBox::Information);
    dialog->setStandardButtons(QMessageBox::Ok);
    dialog->setDefaultButton(QMessageBox::Ok);
    return dialog->exec();
}

int Dialog::dialogQuestion(const QString& title, const QString& text, const QString& info, const QString& detail, QWidget *parent)
{
    Dialog *dialog = new Dialog(title, text, info, detail, (!parent ? MainWindow::getMainWindow(): parent));
    dialog->setIcon(QMessageBox::Question);
    dialog->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    dialog->setDefaultButton(QMessageBox::Yes);
    return dialog->exec();
}

int Dialog::dialogWarning(const QString& title, const QString& text, const QString& info, const QString& detail, QWidget *parent)
{
    Dialog *dialog = new Dialog(title, text, info, detail, (!parent ? MainWindow::getMainWindow(): parent));
    dialog->setIcon(QMessageBox::Warning);
    dialog->setStandardButtons(QMessageBox::Ok);
    dialog->setDefaultButton(QMessageBox::Ok);
    return dialog->exec();
}

int Dialog::dialogCritical(const QString& title, const QString& text, const QString& info, const QString& detail, QWidget *parent)
{
    Dialog *dialog = new Dialog(title, text, info, detail, (!parent ? MainWindow::getMainWindow(): parent));
    dialog->setIcon(QMessageBox::Critical);
    dialog->setStandardButtons(QMessageBox::Ok);
    dialog->setDefaultButton(QMessageBox::Ok);
    return dialog->exec();
}

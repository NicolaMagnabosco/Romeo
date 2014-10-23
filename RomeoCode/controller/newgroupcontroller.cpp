#include "newgroupcontroller.h"

using Romeo::Controller::NewGroupController;
using Romeo::Model::QtModel::NewGroupTableModel;
using Romeo::View::Dialog::Dialog;
using Romeo::Model::Util::DAO::SubjectDAO;
using Romeo::Model::Util::DAO::GroupDAO;
using Romeo::Controller::MainWindowController;

NewGroupController::NewGroupController(NewGroupView *view, QObject *parent): AController(view,parent), edit(false), idEdit("")
{
    createConnections();
}

NewGroupController::NewGroupController(NewGroupView *view, const QString& group, QObject *parent) : AController(view,parent), edit(true), idEdit(group)
{
    createConnections();
}

void NewGroupController::createConnections() const
{
    NewGroupView *newGroupView = qobject_cast<NewGroupView*>(view);

    connect(view, SIGNAL(selectAll()), this, SLOT(slotSelectAll()));
    connect(view, SIGNAL(deselectAll()), this, SLOT(slotDeselectAll()));
    connect(newGroupView, SIGNAL(typeSelection(QString)), this, SLOT(slotTypeSelection(QString)));
    connect(newGroupView, SIGNAL(saveObject()), this, SLOT(slotSaveGroup()));
}

void NewGroupController::slotSelectAll()
{
    NewGroupView *newGroupView = qobject_cast<NewGroupView*>(view);
    newGroupView->getTableView()->selectAll();
    newGroupView->getTableView()->setFocus();
}

void NewGroupController::slotDeselectAll()
{
    NewGroupView *newGroupView = qobject_cast<NewGroupView*>(view);
    newGroupView->getTableView()->clearSelection();
    newGroupView->getTableView()->setFocus();
}

void NewGroupController::slotTypeSelection(const QString& selection)
{
    NewGroupView *newGroupView = qobject_cast<NewGroupView*>(view);
    NewGroupTableModel *model = qobject_cast<NewGroupTableModel*>(newGroupView->getTableView()->model());
    QSortFilterProxyModel *proxyModel = qobject_cast<QSortFilterProxyModel*>(newGroupView->getTableView()->model());

    if(model && !proxyModel) {
        if(selection==Utils::ROMEO_SELECT_TYPE)
            model->resetListModel();
        else
            model->filterSubjectsForType(selection);

        newGroupView->getTableView()->setModel(newGroupView->updateProxyModel(model));
        newGroupView->setNSubjects(model->rowCount());
    }
    else if(proxyModel && !model) {
        NewGroupTableModel *newModel = newGroupView->getNewGroupTableModel()->getRefreshModelForType(selection);
        if(selection==Utils::ROMEO_SELECT_TYPE)
            newModel->resetListModel();
        else
            newModel->filterSubjectsForType(selection);

        newGroupView->getTableView()->setModel(newGroupView->updateProxyModel(newModel));
        newGroupView->setNSubjects(newModel->rowCount());
    }
}

void NewGroupController::slotSaveGroup()
{
    int maxChar = 200;
    NewGroupView *newGroupView = qobject_cast<NewGroupView*>(view);
    newGroupView->removeResultMessageWidget();
    QString name = newGroupView->getName();
    QString type = newGroupView->getType();
    QModelIndexList selectedIndex = newGroupView->getSelectedSubjects();    

    if(name.isEmpty() || selectedIndex.size() == 0)
        newGroupView->addResultMessageWidget("Name and Subjects are Required", false);
    else {
        if(name.size()>maxChar) {
         newGroupView->addResultMessageWidget("The name of the Group must not exceed "+QString::number(maxChar)+" characters.", false);
         return;
        }
        QVector<ASubject*> subjects;
        SubjectDAO subjectDao;
        QAbstractItemModel *model = newGroupView->getTableView()->model();
        for(int i=0; i<selectedIndex.size(); i++){
            subjects.append(subjectDao.getSubjectByName(model->index(selectedIndex.at(i).row(), 0 ,selectedIndex.at(i)).data().toString()));
        }
        GroupOfSubject *group = new GroupOfSubject(name, type, subjects);
        create_Update (group, name);
    }
}

void NewGroupController::create_Update(GroupOfSubject *group, QString &name)
{
    NewGroupView *newGroupView = qobject_cast<NewGroupView*>(view);
    GroupDAO dao;
    if(edit){
        if(dao.updateGroupOfSubject(*group)) {
            newGroupView->resetFields();
            MainWindow::getMainWindow()->writeStatusBar("Group "+name+" Updated", 10000);

            newGroupView->addResultMessageWidget("Group "+name+" Updated", true);

            edit=false;
            idEdit.clear();
        }
        else {
            newGroupView->addResultMessageWidget("Group name already exists", false);
        }
    }
    else {
        if(dao.createGroup(*group)) {
            newGroupView->resetFields();
            MainWindow::getMainWindow()->writeStatusBar("Group "+name+" inserted", 10000);

            newGroupView->addResultMessageWidget("Group "+name+" inserted", true);
        }
        else{
            newGroupView->addResultMessageWidget("Group name already exists", false);
        }
    }
}

void NewGroupController::setEditFields(const QString& groupS)
{
    NewGroupView *newGroupView = qobject_cast<NewGroupView*>(view);
    GroupDAO dao;
    GroupOfSubject *group = dao.getGroupByName(groupS);

    newGroupView->setEditFields(group);
}

void NewGroupController::slotBack()
{
    if(edit) MainWindowController::getMainWindowController()->slotShowGroups(idEdit);
    else AController::slotBack();
}

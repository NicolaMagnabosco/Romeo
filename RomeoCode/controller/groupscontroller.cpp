#include "groupscontroller.h"

using Romeo::Controller::GroupsController;
using Romeo::Model::Util::DAO::GroupDAO;
using Romeo::Model::QtModel::GroupSubjectsTableModel;
using Romeo::Model::QtModel::GroupTableModel;
using Romeo::View::Dialog::Dialog;
using Romeo::Controller::MainWindowController;

GroupsController::GroupsController(GroupView *view, QObject *parent): AController(view,parent)
{
    createConnections();
}

void GroupsController::createConnections() const
{
    GroupView *groupView = qobject_cast<GroupView*>(view);

    connect(groupView, SIGNAL(itemSelected(QModelIndex)), this, SLOT(slotItemSelected(QModelIndex)));
    connect(groupView, SIGNAL(deleteObject()), this, SLOT(slotDeleteGroup()));
    connect(groupView, SIGNAL(editObject()), this, SLOT(slotEditGroup()));
}

void GroupsController::slotItemSelected(const QModelIndex &index)
{
    GroupView *groupView=qobject_cast<GroupView*>(view);

    item = groupView->getGroupTable()->model()->index(index.row(), 0 ,index).data().toString();

    GroupDAO *db = new GroupDAO();
    QVector<ASubject*> subjects = db->getSubjectsOfGroup(item);

    QSortFilterProxyModel *proxyModel = qobject_cast<QSortFilterProxyModel*>(groupView->getSubjectsTable()->model());

    GroupSubjectsTableModel *model = qobject_cast<GroupSubjectsTableModel*>(proxyModel->sourceModel());
    model->resetListModel(subjects);
}

void GroupsController::slotDeleteGroup()
{
    GroupView *groupView=qobject_cast<GroupView*>(view);

    groupView->removeResultMessageWidget();

    if(!item.isEmpty()) {
        GroupDAO *db = new GroupDAO();
        int response = Dialog::dialogQuestion("Delete Group?", "Are you sure you want to delete the group \""+item+"\"?", "If you delete the Group will be deleted all the Datasets associated");
        if(response == QMessageBox::Yes) {
            if(db->deleteGroup(item)) {
                MainWindow::getMainWindow()->writeStatusBar("Group "+item+" deleted", 10000);
                groupView->addResultMessageWidget("Group "+item+" deleted", true);

                QSortFilterProxyModel *proxyModel = qobject_cast<QSortFilterProxyModel*>(groupView->getGroupTable()->model());
                GroupTableModel *groupModel = qobject_cast<GroupTableModel*>(proxyModel->sourceModel());
                proxyModel = qobject_cast<QSortFilterProxyModel*>(groupView->getSubjectsTable()->model());
                GroupSubjectsTableModel *subjectsModel = qobject_cast<GroupSubjectsTableModel*>(proxyModel->sourceModel());
                subjectsModel->resetListModel();
                groupModel->refreshModelData();
            }
            else Dialog::dialogCritical("Delete Error", "Group does not exist in the database");
            item.clear();
        }
    }
    else groupView->addResultMessageWidget("You must select a Group to delete it", false);
}

void GroupsController::slotEditGroup()
{
    GroupView *groupView=qobject_cast<GroupView*>(view);

    groupView->removeResultMessageWidget();

    if(!item.isEmpty()) {
        MainWindowController::getMainWindowController()->slotEditGroup(item);
    }
    else groupView->addResultMessageWidget("You must select a Group to edit it", false);
}

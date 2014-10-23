#include "resultscontroller.h"

using Romeo::Controller::ResultsController;
using Romeo::Controller::MainWindowController;

ResultsController::ResultsController(ResultsView *view, QObject *parent): AController(view, parent), idSelected(-1)
{
    createConnections();
}

void ResultsController::createConnections() const 
{
    ResultsView *viewR = qobject_cast<ResultsView*>(view);

    connect(viewR, SIGNAL(rowSelected(QModelIndex)), this, SLOT(slotRowSelected(QModelIndex)));
    connect(viewR, SIGNAL(rowSelectedDouble(QModelIndex)), this, SLOT(slotRowSelectedDouble(QModelIndex)));
    connect(viewR, SIGNAL(restartAnalysis()), this, SLOT(slotRestartClicked()));
    connect(viewR, SIGNAL(showAnalysisResults()), this, SLOT(slotShowClicked()));
}

void ResultsController::slotRestartClicked() 
{
    ResultsView *viewR = qobject_cast<ResultsView*>(view);

    if(idSelected == -1)
        viewR->addResultMessageWidget("You must select an Analysis to restart", false);
    else
        MainWindowController::getMainWindowController()->slotRestartAnalysis(idSelected);
}

void ResultsController::slotShowClicked() 
{
    ResultsView *viewR = qobject_cast<ResultsView*>(view);

    if(idSelected == -1)
        viewR->addResultMessageWidget("You must select an Analysis to show the results", false);
    else {
        MainWindowController::getMainWindowController()->slotDetailedResults(idSelected, titleRestult);
    }
}

void ResultsController::slotRowSelected(const QModelIndex &index)
{
    ResultsView *viewR = qobject_cast<ResultsView*>(view);

    idSelected = viewR->getModel()->index(index.row(), 0 ,index).data().toInt();

    titleRestult.clear();
    titleRestult = "Results of Analysis on Dataset";
    titleRestult += "("+viewR->getModel()->index(index.row(), 0 ,index).data().toString()+")";
    titleRestult += " "+viewR->getModel()->index(index.row(), 2 ,index).data().toString();
    if(viewR->getModel()->index(index.row(), 1 ,index).data().toString() == Utils::ROMEO_YES)
        titleRestult +=" - COMPLETED";
    else
        titleRestult +=" - NOT COMPLETED";

    viewR->enableButtons();
}

void ResultsController::slotRowSelectedDouble(const QModelIndex &index)
{
    slotShowClicked();
}

#ifndef ANALYSISCONTROLLER_H
#define ANALYSISCONTROLLER_H

#include "controller/acontroller.h"
#include "view/window/analysisview.h"
#include <QObject>
#include "model/qtModel/analysissubjectstablemodel.h"
#include "model/qtModel/analysisprotocolstablemodel.h"
#include "utils.h"
#include "model/core/protocol.h"
#include "model/core/analysis.h"
#include "view/dialog/analysisdialog.h"
#include "model/core/feature/afeature.h"
#include "model/util/dao/analysisdao.h"
#include "controller/mainwindowcontroller.h"

using Romeo::Controller::AController;
using Romeo::View::Window::AnalysisView;
using Romeo::Model::Core::Protocol;
using Romeo::View::Dialog::AnalysisDialog;
using Romeo::Model::Core::Analysis;

/*!
*\file analysiscontroller.h
*\author Adami Alberto (alberto.adami.7@gmail.com)
*\date 2013-03-03
*/

/*
*Changes:
*+----------+------------+---------------- +--------------------------------------------+---------------------------+
*| Version + Date + Programmer + Changes + Description |
*+----------+------------+-----------------+--------------------------------------------+---------------------------+
*| |
*| 0.0.1 | 2013-03-03 | Adami Alberto | Romeo::Controleller::AnalysisController | First version of class |
*| | |
*+----------+------------+-----------------+--------------------------------------------+---------------------------+
*/

namespace Romeo {

    namespace Controller {
        /*!
* \brief The AnalysisController class, extends AController, represents the controller for the user inputs of the analyisis view.
*/
        class AnalysisController : public AController
        {
            Q_OBJECT
        private:
            /*!
* \brief dataset represents the dataset of the analyisis.
*/
            QString dataset;
            /*!
* \brief protocolOfDataset represents the protocols of the dataset.
*/
            QVector<Protocol*> protocolOfDataset;
            /*!
* \brief dialog represent a pointer to the analysis start dialog->
*/
            AnalysisDialog *dialog;
            /*!
* \brief analysis represents the analysis object.
*/
            Analysis *analysis;
            /*!
* \brief lastCreateID represents the id of the current created analyisis in database.
*/
            int lastCreateID;
            /*!
* \brief restart represents a flag true if it is a restart analysis, false if it is a new analysis->
*/
            bool restart;

            /*!
* \brief clearData method remove the data of the controller object.
*/
            void clearData();
            /*!
* \brief createDialogConnections method create the connections for the dialog start analysis
*/
            void createDialogConnections();

        protected:
            /*!
* \brief createConnections method create the connections between view and controller.
*/
            void createConnections() const;

        public:
            /*!
* \brief AnalysisController constructor create the controller object for a new analysis
* \param view is the connected view for the controller.
* \param parent is the parent of controller object.
*/
            AnalysisController(AnalysisView *view, QObject *parent=0);
            /*!
* \brief AnalysisController constructor create the controller object for a restart analysis
* \param view is the connected view for the controller.
* \param id is the unique id of the analysis object in the database.
* \param parent is the parent of controller object.
*/
            AnalysisController(AnalysisView *view, int id, QObject *parent=0);

        public slots:
            /*!
* \brief slotDatasetSelected slot recieve the signal when user select the dataset
* \param datasetS is the dataset name selected
*/
            void slotDatasetSelected(const QString& datasetS);
            /*!
* \brief slotSelectResultsFolder slot recieve the signal when user click on export folder button.
*/
            void slotSelectResultsFolder();
            /*!
* \brief slotStartAnalysis slot recieve the signal when user click on start analysis button.
*/
            void slotStartAnalysis();
            /*!
* \brief slotUpdateDialog slot recieve the signal when the analysis dialog need to update the view
* \param description is the description text set to the view
*/
            void slotUpdateDialog(const QString &description);
            /*!
* \brief slotRealClose slot recieve the signal when the dialog finish the analysis and set the analysis pointer and dialog pointer to null.
*/
            void slotRealClose();
            /*!
* \brief slotFeatureSelected slot recieve the signal when the user select the feature to show or save.
* \param index is the index of the table.
*/
            void slotFeatureSelected(const QModelIndex & index);
            /*!
* \brief slotSelAllSubjects slot recieve the signal when the user click on select all subjects button.
*/
            void slotSelAllSubjects();
            /*!
* \brief slotDeselAllSubjects slot recieve the signal when the user click on deselect all subjects button.
*/
            void slotDeselAllSubjects();
            /*!
* \brief slotSaveAll slot recieve the signal when the user click on select save all features button.
*/
            void slotSaveAll();
            /*!
* \brief slotShowAll slot recieve the signal when the user click on select show all features button.
*/
            void slotShowAll();
            /*!
* \brief slotFinishAnalysis slot recieve the signal when the analysis ends.
*/
            void slotFinishAnalysis();
            /*!
* \brief slotResetView slot recieve the signal of resetting view
*/
            void slotResetView();
            /*!
* \brief slotShowNewImage slot recieve the signal when the new image of analysis is ready to be shown
* \param image is the image to show
* \param description is the description of the image
*/
            void slotShowNewImage(QImage *image, const QString &description);
            /*!
* \brief slotShowNextImage slot recieve the signal when the user click on next button on the analysis dialog
*/
            void slotShowNextImage();
            /*!
* \brief slotShowPreviousImage slot recieve the signal when the user click on previous button on the analysis dialog
*/
            void slotShowPreviousImage();
            /*!
* \brief slotIncrementSubject slot recieve the signal for increment the number of subject of the analysis
*/
            void slotIncrementSubject();
            /*!
* \brief slotBack slot recieve the signal when the user click on back button.
* Go to welcome view if it is a new analysis
* Go to analysis results if it is a restart analysis
*/
            virtual void slotBack();
        };

    }//namespace Controller

} //namespace Romeo

#endif // ANALYSISCONTROLLER_H
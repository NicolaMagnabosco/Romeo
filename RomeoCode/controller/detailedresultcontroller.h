#ifndef DETAILEDRESULTCONTROLLER_H
#define DETAILEDRESULTCONTROLLER_H

#include "controller/acontroller.h"
#include "view/window/detailedresult.h"
#include "controller/mainwindowcontroller.h"
#include "model/util/dao/analysisdao.h"
#include <QDesktopServices>
#include "view/dialog/dialog.h"
#include "utils.h"
#include <QFileDialog>

using Romeo::Controller::AController;
using Romeo::View::Window::DetailedResult;

namespace Romeo {
    namespace Controller {
    /*!
     * \brief The DetailedResultController class, extends AController, represents the controller for the user inputs of the detailed results view.
     */
        class DetailedResultController : public AController
        {
            Q_OBJECT

        private:
            /*!
             * \brief idResult is the id of the analysis
             */
            int idResult;

            /*!
             * \brief setPathTree method set the path of the tree view
             */
            void setPathTree();
            /*!
             * \brief setPageTitle method set the title on the top of the page
             * \param txt is the string put on the title
             */
            void setPageTitle(const QString& txt) const;

        protected:
            /*!
             * \brief method create the connections between view and controller.
             */
            virtual void createConnections() const;

        public:
            /*!
             * \brief DetailedResultController constructor create the controller object with the informations in the parameters
             * \param id is the id of the analysis
             * \param title is the title of the page
             * \param view is the view connected
             * \param parent is the parent of the controller object
             */
            DetailedResultController(int id, const QString& title, DetailedResult *view, QObject *parent=0);

        public slots:
            /*!
             * \brief slotBack slot recieve the signal when the user click on back button
             */
            virtual void slotBack();
            /*!
             * \brief slotTreeClicked slot recieve the signal when the user click on the tree
             * \param item is the item clicked
             */
            void slotTreeClicked(const QModelIndex& item);
            /*!
             * \brief SlotImageDoubleClicked slot recieve the signal when the user double click on the image or video
             * \param path is the path of the file clicked
             */
            void SlotImageDoubleClicked(const QString& path);

            /*!
             * \brief slotExport slot recieve the signal when the user click on export button
             */
            void slotExport();
        };
    }
}

#endif // DETAILEDRESULTCONTROLLER_H

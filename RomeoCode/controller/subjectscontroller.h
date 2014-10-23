#ifndef SUBJECTSCONTROLLER_H
#define SUBJECTSCONTROLLER_H

#include <QObject>
#include "controller/acontroller.h"
#include "view/window/subjectsview.h"
#include "model/qtModel/subjecttablemodel.h"
#include "model/core/asubject.h"
#include "model/util/dao/subjectdao.h"
#include <QImage>
#include "utils.h"
#include "controller/mainwindowcontroller.h"
#include <QDesktopServices>
#include "view/dialog/dialog.h"

using Romeo::Controller::AController;
using Romeo::View::Window::SubjectsView;

/*!
 *\file subjectscontroller.h
 *\author Nicolò Bissacco (nickbissa@gmail.com)
 *\date 2013-02-20
*/
/*
*Changes:
*+----------+------------+-------------------+-------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer      +                 Changes                   +         Description       |
*+----------+------------+-------------------+-------------------------------------------+---------------------------+
*|                                                                                                                   |
*|   0.0.1  | 2013-02-20 |   Nicolò Bissacco |  Romeo::Controller::WelcomeController     |   First version of class  |
*|                                                                                                                   |
*|   0.0.2  | 2013-03-28 |   Nicolò Bissacco |  Romeo::Controller::WelcomeController     | Complete the documentation|
*|                                                                                                                   |                            |                                                                               |
*+----------+------------+-------------------+-------------------------------------------+---------------------------+
*/


namespace Romeo {

    namespace Controller 
    {
        /*!
         * \brief The SubjectsController class, extends AController, represents the controller for the user inputs of the subjects view.
         */
        class SubjectsController : public AController
        {
            Q_OBJECT

        private:
            /*!
             * \brief loadImage2D method load the 2D image of the subject
             * \param image is the image to load
             * \param mask is the mask to load
             * \param pathI is the path of the image
             * \param pathM is the path of the mask
             * \param subject is a subject pointer
             */
            void loadImage2D(QImage &image, QImage &mask, QString &pathI, QString &pathM, ASubject *subject);
            /*!
             * \brief loadImage3D_Video method load the 3D image and 2D/3D video of the subject
             * \param image is the image to load
             * \param mask is the mask to load
             * \param pathI is the path of the image
             * \param pathM is the path of the mask
             * \param subject is a subject pointer
             */
            void loadImage3D_Video(QImage &image, QImage &mask, QString &pathI, QString &pathM, ASubject *subject);

        public:
            /*!
             * \brief SubjectsController constructs a SubjectsController's object with the given view and parent.
             * \param view represent the view that the SubjectsController have to manage.
             * \param parent represent the parent of the SubjectsController.
             */
            SubjectsController(SubjectsView *view, QObject *parent =0);

        protected:
            /*!
             * \brief createConnections creates all the connection for the Controller.
             */
            virtual void createConnections() const;

        public slots:
            //riceve la selezione del subject e imposta nella view le info del subject selezionato
            /*!
             * \brief slotItemSelcetet show to the user the details about the subjected selected by the user in the view.
             * \param index represent the index of the item associate to the Subject selected by the user in the view,
             */
            void slotItemSelected(const QModelIndex &index);
            /*!
             * \brief SlotImageDoubleClicked slot recieve the signal when the user double click on image or video preview.
             * \param path is the path of the file clicked.
             */
            void SlotImageDoubleClicked(const QString& path);
        };

    }

}

#endif // SUBJECTSCONTROLLER_H

#ifndef ROMEO_CONTROLLER_NEWSUBJECTCONTROLLER_H
#define ROMEO_CONTROLLER_NEWSUBJECTCONTROLLER_H

#include "model/core/asubject.h"
#include "controller/acontroller.h"
#include "view/window/newsubjectview.h"
#include "view/window/mainwindow.h"
#include <QObject>
#include <QFileDialog>
#include <QDir>
#include <QString>
#include "view/dialog/dialog.h"
#include "utils.h"

using Romeo::Controller::AController;
using Romeo::View::Window::NewSubjectView;
using Romeo::View::Window::MainWindow;
using Romeo::Model::Core::ASubject;

/*!
 *\file newsubjectcontroller.h
 *\author Adami Alberto (alberto.adami.7@gmail.com)
 *\date 2013-02-17
*/
/*
*Changes:
*+----------+------------+-----------------+-----------------------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                                    Changes                      +       Description         |
*+----------+------------+-----------------+-----------------------------------------------------------------+---------------------------+
*|                                                                                                                                       |
*|   0.0.1  | 2013-02-17 |   Adami Alberto |  Romeo::Controleller::NewSubjectController                      |   First version of class  |
*|                                                                                                                                       |
*|   0.0.2  | 2013-02-18 |   Adami Alberto |  Romeo::Controller::NewSubjectController::createConnections()   |  Add all the connections. |                                                                                                                 |
*+----------+------------+-----------------+--------------------------------------------+------------------------------------------------+
*/

namespace Romeo {

    namespace Controller {

        /*!
         * \brief The NewSubjectController class represent the controller for a NewSubjectView's object.
         */
        class NewSubjectController : public AController
        {
            Q_OBJECT

        private:
            /*!
             * \brief creationDone method copy the file load with the subject creation and display the results message
             * \param name name of the subject
             * \param imagePath path of the image
             * \param image name of the image
             * \param mask name of the mask
             * \param maskPath path of the mask
             */
            void creationDone(QString &name, QFileInfo &imagePath, QString &image, QString &mask, QFileInfo &maskPath);

        protected:
            /*!
             * \brief Creates all the connection for the Controller.
             */
            virtual void createConnections() const;

        public:
            /*!
             * \brief Constructs a NewSubjectController's object with the given view and parent.
             * \param view represent the NewSubjectView's object that the controller manage.
             * \param parent represent the parent of the controller.
             */
            NewSubjectController(NewSubjectView * view, QObject * parent = 0);

        public slots:
            /*!
             * \brief Change the current name of the subjet that the user is going to create.
             * \param newName represent the new subject's name.
             */
            void slotChangeSubjectName(const QString & newName);

            /*!
             * \brief Change the image of the subject.
             * \param newImage repsent the new subject's image path.
             */
            void slotChangeSubjectImage(const QString & newImage);

            /*!
             * \brief Change the mask of the subject.
             * \param newMask represent the new subject's mask.
             */
            void slotChangeSubjectMask(const QString & newMask);

            /*!
             * \brief Allow to the user to save the subject in the system.
             */
            void slotSaveSubject();

            /*!
             * \brief Allow to the user to add the image for the subject.
             */
            void slotAddImage();

            /*!
             * \brief Allow to the user to add the mask for the subject.
             */
            void slotAddMask();

            /*!
             * \brief Change the type of the Subject that the user is going to create in the associate view.
             * \param selection represent the type of the Subject (2D, 2D-t, 3D, 3D-t).
             */
            void slotChangeType(const QString & selection);
        };

    } // namespace Controller

} // namespace Romeo

#endif // ROMEO_CONTROLLER_NEWSUBJECTCONTROLLER_H

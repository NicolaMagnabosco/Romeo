#ifndef ROMEO_VIEW_DIALOG_ANALYSISDIALOG_H
#define ROMEO_VIEW_DIALOG_ANALYSISDIALOG_H

#include <QDialog>
#include <QVector>
#include <QImage>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "view/component/navwidget.h"

using Romeo::View::Component::NavWidget;
/*!
 *\file analysisdialog.h
 *\author Bissacco Nicolò (nickbissa@gmail.com)
 *\date 2013-02-12
*/
/*
*Changes:
*+----------+------------+-----------------+---------------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                           Changes                       +       Description         |
*+----------+------------+-----------------+---------------------------------------------------------+---------------------------+
*|          |            |                 |                                                         |                           |
*|   0.0.1  | 2013-02-12 | Bissacco Nicolò |             Romeo::View::Dialog::AnalysisDialog         |   First version of class  |
*|          |            |                 |                                                         |                           |
*+----------+------------+-----------------+---------------------------------------------------------+---------------------------+
*/
namespace Romeo {

    namespace View {

        namespace Dialog {

        /*!
         * \brief The class AnalysisDialog, extends QDialog, represents the dialog displayed to the user when starting the analysis.
         */
        class AnalysisDialog : public QDialog
        {
            Q_OBJECT
        private:
            /*!
             * \brief finished represents if the analysis is finished or not.
             */
            bool finished;
            /*!
             * \brief number represents the current subjects.
             */
            int number;
            /*!
             * \brief currentSubject represents the current subject show to the dialog.
             */
            int currentSubject;
            /*!
             * \brief totalSubjects represents the number of subjects on which the analysis is executed.
             */
            int totalSubjects;
            /*!
             * \brief images represents the images of the analysis ready.
             */
            QVector<QImage*> images;
            /*!
             * \brief imageDescription represents the description of the images ready.
             */
            QVector<QString> imagesDescription;
            /*!
             * \brief imageShow represents the current image show to the dialog.
             */
            int imageShow;

            QGroupBox *previewBox;
                QLabel *imageDescription;
                QLabel *previewImage;
                QWidget *buttonWidget;
                    QPushButton *nextButton;
                    QLabel *numberSubjects;
                    QPushButton *previousButton;
            QWidget *progressWidget;
                QProgressBar *progressBar;
                QLabel *progressLabel;
            QWidget *bottomWidget;
                QPushButton *cancelButton;

            /*!
             * \brief The method create the top components of the view.
             */
            void createTop();
            /*!
             * \brief The method create the progress bar.
             */
            void createProgress();
            /*!
             * \brief The method create the bottom components of the view.
             */
            void createBottom();
            /*!
             * \brief The method create the layout of the dialog.
             */
            void createLayout();
            /*!
             * \brief The method create the name of the Qt objects.
             */
            void setupObjectName();
            /*!
             * \brief The method create the connection of the view.
             */
            void addConnect();
            /*!
             * \brief Method that update the state of the buttons based on the image show.
             */
            void updateButtonsState();
            /*!
             * \brief Method that show the i image on the view.
             */
            void showImage(int i);

        protected:
            /*!
             * \brief Reimplemented from QDialog::closeEvent().
             * This event handler is called with the given event when Qt receives a window close request for a top-level widget from the window system.
             */
            virtual void closeEvent(QCloseEvent *event);

        public:
            /*!
             * \brief Construct an AnalysisDialog with the given parameters.
             * \param numberOfStep represent the number of the steps of the progressbar.
             * \param subjects represent the number of subject's analysis.
             * \param parent represent the parent of the AnalysisDialog object.
             */
            AnalysisDialog(int numberOfStep, int subjects, QWidget *parent = 0);

            /*!
             * \brief Method that update the view when the analysis is complete.
             */
            void analysisFinish();
            /*!
             * \brief The method increment the progress bar and set the informative text.
             * \param description represent the informative text show to the users.
             */
            void setBarValue(const QString& description);
            /*!
             * \brief The method add the passed image and show it in the dialog.
             * \param image represent the image to show to the dialog.
             * \param description represent the description of the image.
             */
            void addImage(QImage *image, const QString &description);
            /*!
             * \brief Method that show to the dialog the previous image (if exists).
             */
            void showPreviousImage();
            /*!
             * \brief Method that show to the dialog the next image (if exists).
             */
            void showNextImage();
            /*!
             * \brief The method set the description of the current shown image.
             * \param txt represent the informative text.
             */
            void setImageDescription(const QString& txt);
            /*!
             * \brief Method that increment the actual number of subject on the dialog.
             */
            void incrementCurrentSubject();
            /*!
             * \brief Destroy the list of the images of the analysis.
            */
            ~AnalysisDialog();

        signals:
            /*!
             * \brief The nextImage signal is emitted when the user click the next button.
             */
            void nextImage();
            /*!
             * \brief The previousImage signal is emitted when the user click the previous button.
             */
            void previousImage();
            /*!
             * \brief The cancelAnalysis signal is emitted when the user click the cancel button.
             */
            void cancelAnalysis();
            /*!
             * \brief The realClose signal is emitted when the user click Yes on the question dialog for cancel the analysis.
             */
            void realClose();
            /*!
             * \brief The closeOnFinish signal is emitted when the analysis terminated.
             */
            void closeOnFinish();

        };

        } // namespace Dialog

    } // namespace View

} // namespace Romeo

#endif // ROMEO_VIEW_DIALOG_ANALYSISDIALOG_H

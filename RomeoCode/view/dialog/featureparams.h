#ifndef FEATUREPARAMS_H
#define FEATUREPARAMS_H

#include <QDialog>
#include <QComboBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QWidget>
#include <QPushButton>
#include "model/core/feature/afeature.h"
#include <QStringList>
#include "view/dialog/dialog.h"

using Romeo::Model::Core::Feature::AFeature;
/*!
 *\file featureparams.h
 *\author Bissacco Nicolò (nickbissa@gmail.com)
 *\date 2013-02-12
*/
/*
*Changes:
*+----------+------------+-----------------+---------------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                           Changes                       +       Description         |
*+----------+------------+-----------------+---------------------------------------------------------+---------------------------+
*|          |            |                 |                                                         |                           |
*|   0.0.1  | 2013-02-12 | Bissacco Nicolò |         Romeo::Dialog::FeatureParams                    |   First version of class  |
*|          |            |                 |                                                         |                           |
*+----------+------------+-----------------+---------------------------------------------------------+---------------------------+
*/
namespace Romeo {

    namespace View {

        namespace Dialog {
            /*!
             * \brief The class FeatureParams, extends QDialog, represents the dialog for the feature selection and feature parameters input.
             */
            class FeatureParams : public QDialog
            {
                Q_OBJECT
            private:
                /*!
                 * \brief features represent the list of features to show in the list.
                 */
                QVector<AFeature*> features;
                /*!
                 * \brief params represent the list of the input parameters for the feature.
                 */
                QStringList params;
                /*!
                 * \brief type represent the type of the features to show.
                 */
                QString type;
                /*!
                 * \brief feature represent the feature selected by the user.
                 */
                AFeature* feature;

                QGroupBox *featuresBox;
                    QComboBox *featuresComboBox;
                QGroupBox *firstOrderBox;
                    QWidget *firstFirstParam;
                        QLabel *firstWSizeLabel;
                        QLineEdit *firstWSize;
                QGroupBox *secondOrderBox;
                    QWidget *secondFirstParam;
                        QLabel *secondWSizeLabel;
                        QLineEdit *secondWSize;
                    QWidget *secondSecondParam;
                        QLabel *secondGlcmLabel;
                        QLineEdit *secondGlcm;
                QGroupBox *dynamicBox;
                    QWidget *dynamicSecondParam;
                        QLabel *dynamicInitialFrameLabel;
                        QLineEdit *dynamicInitialFrame;
                    QWidget *dynamicThirdParam;
                        QLabel *dynamicFinalFrameLabel;
                        QLineEdit *dynamicFinalFrame;
                QWidget *bottomWidget;
                    QPushButton *cancelButton;
                    QPushButton *okButton;

                /*!
                 * \brief The method create the top components of the view.
                 */
                void createTop();
                /*!
                 * \brief The method create the selection feature box.
                 */
                void createFeatureBox();
                /*!
                 * \brief The method create the box for the firts order features.
                 */
                void createFirstBox();
                /*!
                 * \brief The method create the box for the second order features.
                 */
                void createSecondBox();
                /*!
                 * \brief The method create the box for the dynamic features.
                 */
                void createDynamicBox();
                /*!
                 * \brief The method create bottom components of the view.
                 */
                void createBottom();
                /*!
                 * \brief The method create the layout of the view.
                 */
                void createLayout();
                /*!
                 * \brief The method create the name for the Qt objects.
                 */
                void setupObjectName();
                /*!
                 * \brief The method create the connections for the users input.
                 */
                void addConnect();
                /*!
                 * \brief The method reset the input fields.
                 */
                void resetDefaultValues();

            public:
                /*!
                 * \brief Construct a ToolBar with the given parent.
                 * \param featureP represent the list of features to show.
                 * \param parent represent the parent of the FeatureParams object.
                 */
                FeatureParams(const QVector<AFeature*>& featureP, QWidget *parent = 0);

                /*!
                 * \brief The method reset the dialog input fields.
                 */
                void resetBox();
                /*!
                 * \brief The method show the box based on type.
                 * \param type represent the type of the features to show.
                 */
                void visibleBox(const QString& type);
                /*!
                 * \brief The method set the feature selected by the user.
                 * \param featureF represent the feature selected by the user.
                 */
                void setFeature(AFeature* featureF);
                /*!
                 * \brief The method return the feature selected by the user.
                 * \return Return AFeature* that represent the feature selected by the user.
                 */
                AFeature *getFeature() const;

            signals:
                /*!
                 * \brief The featureSelected signal is emitted when the user select a feature from the list.
                 * \param feature represent the feature name selected by the user.
                 */
                void featureSelected(const QString& feature);
                /*!
                 * \brief The ok signal is emitted when the user press Ok button and all the parameters are validated.
                 * \param params represent the list of input parameters for selected feature.
                 */
                void ok(const QStringList& params);

            public slots:
                /*!
                 * \brief The slotOk slot receives the signal emitted from the Ok button.
                 */
                void slotOk();

            };
        }
    }
}

#endif // FEATUREPARAMS_H

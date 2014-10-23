#ifndef ROMEO_MODEL_CORE_ANALYSIS_H
#define ROMEO_MODEL_CORE_ANALYSIS_H

#include <QThread>
#include <QVector>
#include <QString>
#include <QDir>
#include <QDateTime>
#include <QMap>
#include "model/core/dataset.h"
#include "model/core/asubject.h"
#include "model/core/algorithm/aalgorithm.h"
#include "model/core/feature/afeature.h"
#include "model/core/romeoobject.h"

using Romeo::Model::Core::Dataset;
using Romeo::Model::Core::ASubject;
using Romeo::Model::Core::Algorithm::AAlgorithm;
using Romeo::Model::Core::RomeoObject;
using Romeo::Model::Core::Feature::AFeature;


/*!
 *\file analysis.h
 *\author Adami Alberto (alberto.adami.7@gmail.com)
 *\date 2013-03-09
*/
/*
*Changes:
*+----------+------------+-----------------+-------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +              Changes                +       Description         |
*+----------+------------+-----------------+-------------------------------------+---------------------------+
*|                                                                                                           |
*|   0.0.1  | 2013-03-09 |   Adami Alberto |    Romeo::Model::Core::Analysis           |   First version of class  |
*|                                                                                                           |
*|   0.1.0  | 2013-03-20 |   Adami Alberto |    Romeo::Model::Core::Analysis::run()    |   Fixed some bugs.        |
*|                                                                                                           |
*|   1.0.0  | 2013-04-10 |   Adami Alberto |    Romeo::Model::Core::Analysis           |Definitive verison of class|                                                                                                 |                            |                                                                               |
*+----------+------------+-----------------+-------------------------------------+---------------------------+
*/

namespace Romeo {

    namespace Model {

        namespace Core {

            /*!
             * \brief The Analysis class represent an Analysis in the Romeo's system.
             * At the beginning
             */

            class Analysis: public QThread
            {
                Q_OBJECT
            private:
                /*!
                 * \brief id represents the id of the analysis.
                 */
                int id;
                /*!
                 * \brief dataset represents the dataset on which the analysis is performed.
                 */
                Dataset *dataset;
                /*!
                 * \brief selectedSubject represents the names of the subjects on wich the analysis is performed.
                 */
                QVector<QString> selectedSubject;
                /*!
                 * \brief featuresShow represents the features to show on the dialog.
                 */
                QMap<int, bool> featuresShow;
                /*!
                 * \brief featuresSave represents the features to export.
                 */
                QMap<int, bool> featuresSave;
                /*!
                 * \brief saveDirectory represents the directory on which save the results.
                 */
                QDir saveDirectory;
                /*!
                 * \brief completed represents the state of the analysis.
                 * True indicated that the analysis is finished.
                 * False indicated that the analysis isn't finished.
                 */
                bool completed;
                /*!
                 * \brief creationDate represent the date on which the analysis has been created.
                 */
                QDateTime creationDate;
                /*!
                 * \brief Execute the subject on the given subject.
                 * \param subject represent the subject to be analyzed.
                 * \param save represent a boolean containing if the results of the analysis
                 * on the subject msut be saved.
                 */
                void executeAnalysisOnSubject(ASubject& subject, bool save);

                /*!
                 * \brief Execute the given feature on the given subject.
                 * \param feature represents the feature to execute.
                 * \param image represents the actual image representation.
                 * \param subject represent the subject on which has to been execute the feature.
                 * \return the output image representation.
                 */
                RomeoObject* runFeature(AFeature* feature, RomeoObject *image, ASubject &subject);

                /*!
                 * \brief Execute the given algorithm on the given subject.
                 * \param alg represents the algorithm to execute.
                 * \param image represents the actual image representation.
                 * \param subject represent hte subject on which has to been execute the algorithm.
                 */
                RomeoObject* runAlgorithm(AAlgorithm *alg, RomeoObject *image, ASubject &subject);
                /*!
                 * \brief Export the result of the feature in the filesystem.
                 * \param pathInternal represents the path on wich exports the image.
                 * \param feature represent the feature result that the image is representing.
                 * \param image represent the image format to be exported.
                 * \param subject represents the subject of the image to be exported.
                 * \param protocol represents the protocol of the given feature.
                 */

                void writeFeature(const QString& pathInternal, AFeature* feature, RomeoObject *image, ASubject &subject, Protocol *protocol);
                /*!
                 * \brief Export the result of the algorithm in the filesystem.
                 * \param pathInternal represents the path on wich exports the image.
                 * \param alg represent the algorithm result that the image is representing.
                 * \param image represent the image format to be exported.
                 * \param subject represents the subject of the image to be exported.
                 * \param protocol represents the protocol of the given algorithm.
                 */
                void writeAlgorithm(const QString& pathInternal, AAlgorithm *alg, RomeoObject *image, ASubject &subject, Protocol *protocol);
                /*!
                 * \brief Method that create the image after execute the feature on the subject.
                 * \param feature represent the feature that has been finished.
                 * \param subject reprsent the subject on which the feature has been executed.
                 * \param image represent the path of the image's result.
                 */
                void showFeature(AFeature *feature, ASubject *subject, const QString &image);
                /*!
                 * \brief Method that emit the imageReady signal when the algorithm or feature has been finished.
                 * \param image represents the path of the image's result.
                 * \param description represents the description of the image result.
                 */
                void showImage(const QString &image, const QString &description);

            protected:
                /*!
                 * \brief Start the analysis's thread.
                 */
                virtual void run();

            public:
                /*!
                 * \brief Crate an analysis object.
                 * \param datasetSelected represents the dataset on which execute the analysis.
                 * \param subjects represents the subjects on which execute the analysis.
                 * \param featShow represent the feature to show.
                 * \param featSave represents the features to save.
                 * \param directory represents the directory on which save the analysis's results.
                 * \param tId represents the analysis id.
                 * \param date represents the date on which the analysis has been created for the first time.
                 * \param parent represents the parent ot the Analysis's object.
                 */
                Analysis(Dataset *datasetSelected, QVector<QString> subjects, const QMap<int, bool> featShow, const QMap<int, bool> featSave, const QDir& directory, int tId = -1, const QDateTime& date =QDateTime(), QObject *parent = 0);
                /*!
                 * \brief Return the id of the Analysis.
                 * \return an int representing the id of the analysis.
                 */
                int getID() const;
                /*!
                 * \brief Set the id of the anlysis.
                 * \param i represents the new id of the analysis.
                 */
                void setID(int i);
                /*!
                 * \brief Return if the analysis has been completed.
                 * \return a boolean that represents the state of the analysis.
                 * True indicates that the analysis has been completed.
                 * False indicated that the analysis has not been completed.
                 */
                bool getComplete() const;
                /*!
                 * \brief Method that set the state of the analysis.
                 * \param c represent the new state of the analysis.
                 */
                void setComplete(bool c);
                /*!
                 * \brief Method that returns the dataset object on which execute the analysis.
                 * \return  a Dataset's object.
                 */
                Dataset *getDataset() const;
                /*!
                 * \brief Method that returns tha names of the subjects on which execute the analysis.
                 * \return a vector of strings.
                 */
                QVector<QString> getSelectedSubject() const;
                /*!
                 * \brief Method that returns the features that must been show in the dialog.
                 * \return Return a map of (int, bool).
                 * The int represents the feature's id.
                 * The bool represents if the feature must to be show in the dialog or not.
                 */
                QMap<int, bool> getFeaturesShow() const;
                /*!
                 * \brief Method that return the features that must been saved.
                 * \return Return a map of (int, bool).
                 * The int represent the features's id.
                 * The bool represents if the feature's result must to be saved.
                 */
                QMap<int, bool> getFeaturesSave() const;
                /*!
                 * \brief Method that change the creation date of the analysis.
                 * \param date represents the new date.
                 */
                void setCreationDate(const QString &date);
                /*!
                 * \brief Method that return the creation date of the analysis.
                 * \return Return a QDateTime's object that reprsents the date on which the analysis has been created.
                 */
                QDateTime getCreationDate() const;
                /*!
                 * \brief Method that return the number of subjects in the dataset.
                 * \return Return an int that represent the number of subjects in the dataset.
                 */
                int getTotalSubjects() const;
                /*!
                 * \brief Method that return the number of subject on which execute the anlysis.
                 * \return Return an int that represent the number of subject on which execute the analysis.
                 */
                int getSelectedSubjectCount() const;
                /*!
                 * \brief Static method that crete the internal path of the folder in Romeo.
                 * \param path path is the absolute path.
                 * \param id is the analysis id.
                 * \param datasetName is the name of the dataset
                 * \param subjectName is the name of the subjet.
                 * \param protocolName is the name of the protocol
                 * \return Return a QString containing the absolute path of the internal path.
                 */
                static QString makeInternalPath(const QString& path, const QString& id, const QString& datasetName, const QString& subjectName, const QString& protocolName);
                /*!
                 * \brief Static method that create the external path of the folder in Romeo.
                 * \param dir represent the absolute directory of home path.
                 * \param folder is the name of the directory used for save the results.
                 * \param id is the id of the analysis.
                 * \param datasetName is the name of the dataset.
                 * \param subjectName is the name of the subject.
                 * \param protocolName is the name of the protocol.
                 * \return Return a QString containing the absolute path of the external path.
                 */
                static QString makeExternalPath(const QString &dir, const QString& folder, const QString& id, const QString& datasetName, const QString& subjectName, const QString& protocolName);
                /*!
                 * \brief Static method that create the complete path with the file name.
                 * \param path reprsent the location on which will be saved the file.
                 * \param feature inicated if the file represents a feature or not.
                 * \param objName is the name of the subject.
                 * \param id is the id of the analysis.
                 * \param ext is the extension of the file.
                 * \return Return a QString containing the absolute path of the file.
                 */
                static QString makePathFileName(const QString &path, bool feature, const QString &objName, const QString &id, const QString &ext);
                /*!
                  Destruct an Analysis object.
                  */
                ~Analysis();

            signals:
                /*!
                 * \brief resultUpdate signal is emitted for update the analysisdialog's state description.
                 * \param s represent the description of what the thread is executing.
                 */
                void resultUpdate(const QString &s);
                /*!
                 * \brief imageReady signal is emitted when a new image is created.
                 * \param image represent the new image.
                 * \param description represent the description of the image.
                 */
                void imageReady(QImage *image, const QString &description);
                /*!
                 * \brief resultReady signal is emitted when the thread has been finished.
                 */
                void resultReady();
                /*!
                 * \brief beginSubject signal is emitted when a the analysis has been begin on a new subject.
                 */
                void beginSubject();


            };

        } // namespace Core

    } // namespace Model

} // namespace Romeo

#endif // ROMEO_MODEL_CORE_ANALYSIS_H

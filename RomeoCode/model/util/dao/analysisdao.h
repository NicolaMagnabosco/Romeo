#ifndef ROMEO_MODEL_UTIL_DAO_ANALYSISDAO_H
#define ROMEO_MODEL_UTIL_DAO_ANALYSISDAO_H

#include "model/util/dao/adatabase.h"
#include "model/util/dao/datasetdao.h"
#include "model/util/dao/subjectdao.h"
#include "model/core/analysis.h"
#include "model/core/dataset.h"
#include <QMap>

using Romeo::Model::Util::DAO::ADatabase;
using Romeo::Model::Core::Analysis;

/*!
 *\file analysisdao.h
 *\author Luisetto Luca (lucaluisetto91@gmail.com)
 *\date 2013-02-21
*/
/*
*Changes:
*+----------+------------+---------------- +------------------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                             Changes                        +       Description         |
*+----------+------------+-----------------+------------------------------------------------------------+---------------------------+
*|                                                                                                                                  |
*|   0.0.1  | 2013-02-21 |   Luisetto Luca |   Romeo::Model::Util::Dao::AnalysisDAO                     |   First version of class  |
*|                                                                                                                                  |
*+----------+------------+-----------------+------------------------------------------------------------+---------------------------+
*/
namespace Romeo {

    namespace Model {

        namespace Util {

            namespace DAO {

                /*!
                 * \brief The class ToolBar, extends ADatabase, represents the class that interfaces with the analysis table of the database.
                 */
                class AnalysisDAO : public ADatabase
                {
                public:
                    /*!
                     * \brief when AnalysisDAO is built it call the superclass method connect that create a connection with the database romeodata.sql
                     */
                    AnalysisDAO();
                    /*!
                     * \brief The method test if the analysis id already exists.
                     * \param id is the id to test.
                     * \return Return true if the algorith already exist, false if not.
                     */
                    bool existAnalysis(int id) const;
                    /*!
                     * \brief The method create the analysis in the database.
                     * \param analysis is the analysis to save.
                     * \return Return a vector with the insert id and the timestamp.
                     */
                    QVector<QString> createAnalysis(const Analysis& analysis);
                    /*!
                     * \brief The method set to 1 the complete flag for the analysis.
                     * \param id is the id of the analysis.
                     * \return Return true if update successful, false if fails.
                     */
                    bool setComplete(int id);
                    /*!
                     * \brief The method get the analysis with the given id.
                     * \param id is the id of the analysis.
                     * \return Return an analysis pointer.
                     */
                    Analysis *getAnalysis(int id) const;
                    /*!
                     * \brief The method get all analysis saved in the database.
                     * \return Return a vector with analysis pointer.
                     */
                    QVector<Analysis*> getAllAnalysis() const;
                    /*!
                     * \brief The method get the selected subjects for the analysis.
                     * \param id is the id of the analysis.
                     * \return Return a vector with subjects pointer.
                     */
                    QVector<ASubject*> getSelectedSubject(int id) const;
                    /*!
                     * \brief The method get the name of the selected subjects for the analysis.
                     * \param id is the id of the analysis.
                     * \return Return a vector with subjects name.
                     */
                    QVector<QString> getSelectedSubjectString(int id) const;
                    /*!
                     * \brief The method get the features to show during the analysis.
                     * \param id is the id of the analysis.
                     * \return Return a map with id of feature and a boolean true if to show, false if not to show.
                     */
                    QMap<int, bool> getFeatShow(int id) const;
                    /*!
                     * \brief The method get the features to save during the analysis.
                     * \param id is the id of the analysis.
                     * \return Return a map with id of features and a boolean true if to save, false if not to save.
                     */
                    QMap<int, bool> getFeatSave(int id) const;
                    /*!
                     * \brief The method get the dataset name of the analysis.
                     * \param id is the id of the analysis.
                     * \return Return the name of dataset.
                     */
                    QString getDatasetname(int id);
                };

            } // namespace DAO

        } // namespace Util

    } // namespace Model

} // namespace Romeo

#endif // ROMEO_MODEL_UTIL_DAO_ANALYSISDAO_H

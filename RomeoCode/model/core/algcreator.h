#ifndef ROMEO_MODEL_CORE_ALGCREATOR_H
#define ROMEO_MODEL_CORE_ALGCREATOR_H

#include "model/core/algorithm/aalgorithm.h"
#include <QVector>

using Romeo::Model::Core::Algorithm::AAlgorithm;

/*!
 *\file aalgorithm.h
 *\author Adami Alberto (alberto.adami.7@gmail.com)
 *\date 2013-02-21
*/
/*
*Changes:
*+----------+------------+---------------- +-------------------------------------+------------------------------+
*|  Version +    Date    +   Programmer    +              Changes                +       Description            |
*+----------+------------+-----------------+-------------------------------------+------------------------------+
*|                                                                                                              |
*|   0.0.1  | 2013-02-21 |   Adami Alberto |  Romeo::Model::Core::AController     |   First version of class    |
*|                                                                                                              |                                                                                                 |
*|   0.1.0  | 2013-03-10 |   Adami Alberto |  Romeo::Model::Core::AController     |  Definitive version of class|
*+----------+------------+-----------------+-------------------------------------+------------------------------+
*/

namespace Romeo {

    namespace Model {

        namespace Core {
            /*!
             * \brief The AlgCreator class represent a class used to obtain instance of Algorithms.
             * It's implemented with the Singleton pattern.
             */
            class AlgCreator
            {
            private:
                /*!
                 * \brief algCreator represent the pointer to the unique instance of the AlgCreator class.
                 */
                static AlgCreator *algCreator;
                /*!
                 * \brief Constructs the AlgCreator object.
                 */
                AlgCreator();
            public:
                /*!
                 * \brief Return the unique instance of the AlgCrator object.
                 * \return the unique instance.
                 */
                static AlgCreator *getAlgCreator();
                /*!
                 * \brief Create the Algorithm with the given paramethers.
                 * \param name represents the name of the algorithm.
                 * \param parameters represents the paramethers of the algorithm.
                 * \param algId represent the id of the algorith.
                 * \return the AAlogirhm's object created.
                 */
                AAlgorithm* buildAlgorithm(const QString& name, const QStringList& parameters = QStringList(), int algId = -1) const;
                /*!
                 * \brief Create all the possible algorithms.
                 * \return a vector of all the algorithms created.
                 */
                QVector<AAlgorithm*> getAllAlgorithms() const;

            };

        } // namespace Core

    } // namespace Model

} // namespace Romeo

#endif // ROMEO_MODEL_CORE_ALGCREATOR_H

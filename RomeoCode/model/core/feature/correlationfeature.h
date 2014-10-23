#ifndef ROMEO_MODEL_CORE_FEATURE_CORRELATIONFEATURE_H
#define ROMEO_MODEL_CORE_FEATURE_CORRELATIONFEATURE_H
#include "model/core/feature/secondorderfeature.h"


using Romeo::Model::Core::Feature::SecondOrderFeature;

/*!
 *\file correlationfeature.h
 *\author Scapin Davide (davideskap@gmail.com)
 *\date 2013-03-16
*/
/*
*Changes:
*+----------+------------+-----------------+-----------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                       Changes                       +       Description         |
*+----------+------------+-----------------+-----------------------------------------------------+---------------------------+
*|          |            |                 |                                                     |                           |
*|   0.0.1  | 2013-03-16 | Scapin Davide   |  Romeo::Model::Core::Feature::CorrelationFeature    |   First version of class  |
*|          |            |                 |                                                     |                           |
*+----------+------------+-----------------+-----------------------------------------------------+---------------------------+
*/


namespace Romeo {
    namespace Model {
        namespace Core {
            namespace Feature {


            /*!
             * \brief CorrelationFeature class represent Correlation features extraction alghorithm.
             * It can be applied to 2D or 3D images.
             */
            class CorrelationFeature : public SecondOrderFeature
            {
            public:
                /*!
                 * \brief CorrelationFeature is a default or 1 parameters constructor of the class
                 * \param idFeat is the id code of the feature;the default value is -1.
                 */
                CorrelationFeature(int idFeat = -1);
                /*!
                 * \brief CorrelationFeature is the 1 or 2 parameters constructor of the class.
                 * \param parameters is a QString list that conteins feature's parameters.
                 * \param idFeat is the id code of the feature;the default value is -1.
                 */
                CorrelationFeature(const QStringList& parameters, int idFeat = -1);
                /*!
                 * \brief singleChannelEXecution2D performs Correlation feature extractor on 2D images.
                 * \param channel input image in InternalData2D format.
                 * \return Output image in InternalData2D format.
                 */
                virtual InternalData2D* singleChannelEXecution2D(InternalData2D *channel);
                /*!
                 * \brief singleChannelEXecution3D performs Correlation feature extractor on 3D images.
                 * \param channel input image in InternalData3D format.
                 * \return Output image in InternalData3D format.
                 */
                virtual InternalData3D* singleChannelEXecution3D(InternalData3D *channel);
                /*!
                 * \brief Calculate mean index that need to calculate feature correlation.
                 * \param GLCM is the histogram of grey level co-occurence matrix
                 * \param size is the dimension of GLCM
                 * \return array of float
                 */
                float* meanIndexI (const InternalData2D::HistogramType* GLCM,int size);
                /*!
                 * \brief Calculate std index that need to calculate feature correlation.
                 * \param GLCM is the histogram of grey level co-occurence matrix.
                 * \param size is the dimension of GLCM.
                 * \param float*m is the array returned from meanIndexI function.
                 * \return array of float.
                 */
                float * stdIndexI(const InternalData2D::HistogramType* GLCM,int size,float*m);
                /*!
                 * \brief Calculate mean index that need to calculate feature correlation.
                 * \param GLCM is the histogram of grey level co-occurence matrix
                 * \param size is the dimension of GLCM
                 * \return array of float
                 */
                float* meanIndexJ (const InternalData2D::HistogramType* GLCM,int size);
                /*!
                 * \brief Calculate std index that need to calculate feature correlation.
                 * \param GLCM is the histogram of grey level co-occurence matrix
                 * \param size is the dimension of GLCM
                 * \param m is the array returnedi form meanIndexI function
                 * \return array of float
                 */
                float * stdIndexJ(const InternalData2D::HistogramType* GLCM,int size,float*m);
                /*!
                 * \brief ~CorrelationFeature virtual destructor of the class
                 */
                virtual ~CorrelationFeature();
            };

            } // namespace Feature
        } // namespace Core
    } // namespace Model
} // namespace Romeo


#endif // ROMEO_MODEL_CORE_FEATURE_CORRELATIONFEATURE_H

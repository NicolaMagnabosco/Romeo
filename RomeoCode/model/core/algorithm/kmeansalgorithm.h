#ifndef ROMEO_MODEL_CORE_ALGORITHM_KMEANSALGORITHM_H
#define ROMEO_MODEL_CORE_ALGORITHM_KMEANSALGORITHM_H

#include "model/core/algorithm/aalgorithm.h"
#include "itkOpenCVImageBridge.h"
#include "itkScalarImageKmeansImageFilter.h"
#include "cv.h"

using Romeo::Model::Core::Algorithm::AAlgorithm;
/*!
 *\file fuzzycmeans.h
 *\author Magnabosco Nicola (nick.magnabosco@gmail.com)
 *\date 2013-04-07
*/
/*
*Changes:
*+----------+------------+---------------- +------------------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                             Changes                        +       Description         |
*+----------+------------+-----------------+------------------------------------------------------------+---------------------------+
*|                                                                                                                                  |
*|   0.0.1  | 2013-04-07 |Magnabosco Nicola|    Romeo::Model::Core::Algorithm::KMeansAlgorithm          |   First version of class  |
*|                                                                                                                                  |
*+----------+------------+-----------------+------------------------------------------------------------+---------------------------+
*/
namespace Romeo {

    namespace Model {

        namespace Core {

            namespace Algorithm {
            /*!
                 * \brief The KmeansAlgorithm class represents the Kmeans cluster algorithm in Romeo.
                 */
                class KMeansAlgorithm : public AAlgorithm
                {
                private:
                    char distance;
                    int maxIteration;
                    int numberOfCluster;
                    int numberOfReplicates;
                    int * arIt;
                    int * arClust;
                    int *arReplic;
                    QVector<int*>minMaxArray;

                    void generateArrays();

                protected:
                    /*!
                     * \brief execute2DAnalysis execute the algorithm on 2D images.
                     * \param image is the input image.
                     * \return the output image.
                     */
                    virtual RomeoObject* execute2DAnalysis(RGBImage2D* image);
                    /*!
                     * \brief execute3DAnalysis execute the algorithm on 3D images.
                     * \param image is the input image.
                     * \return the output image.
                     */
                    virtual RomeoObject* execute3DAnalysis(RGBImage3D* image);
                    /*!
                     * \brief execute2DVideoAnalysis execute the algorithm on 2D videos.
                     * \param video is the input video.
                     * \return the output image.
                     */
                    virtual RomeoObject* execute2DVideoAnalysis(Video2D* video);
                    /*!
                     * \brief execute3DVideoAnalysis execute the algorithm on 3D videos.
                     * \param video is the input video.
                     * \return the output image.
                     */
                    virtual RomeoObject* execute3DVideoAnalysis(Video3D* video);
                public:
                    /*!
                     * \brief KMeansAlgorithm is the constructor.
                     * \param idAlg is the id of the Algorithm.
                     */
                    KMeansAlgorithm(int idAlg = -1);
                    /*!
                     * \brief KMeansAlgorithm is the class constructor of the class.
                     * \param parameters is the parameters of the class.
                     * \param idAlg is the id of the algorithm.
                     */
                    KMeansAlgorithm(const QStringList& parameters, int idAlg = -1);
                    /*!
                     * \brief getNumberOfCluster gets the number of clusters.
                     * \return the number of clusters.
                     */
                    int getNumberOfCluster() const;
                    /*!
                     * \brief getNumberOfReplicates gets the number of replicates.
                     * \return the number of replicates.
                     */
                    int getNumberOfReplicates() const;
                    /*!
                     * \brief getMaxIteration gets the maximum number of iteration.
                     * \return the maximum number of iteration.
                     */
                    int getMaxIteration() const;
                    /*!
                     * \brief getDistance gets the distance type.
                     * \return the distance type.
                     */
                    char getDistance() const;
                    /*!
                     * \brief getParameters gets the parameters of the algorithm.
                     * \return the parameters of the algorithm.
                     */
                    virtual QStringList getParameters() const;
                    /*!
                     * \brief setParameters sets the parameters of the algorithm.
                     * \param is the parameters of the algorithm.
                     */
                    virtual void setParameters(const QStringList& pars);

                    virtual QMap<QString, QList<int> > getParametersTypeList() const;
                    virtual QVector< QMap<char, QString> > getParametersOfTypeChoice() const;
                    virtual QStringList testParameters(const QStringList& pars) const;
                    /*!
                     * \brief ~KMeansAlgorithm delete the object.
                     */
                    virtual ~KMeansAlgorithm();
                };

            } // namespace Algorithm
        } // namespace Core
    } // namespace Model
} // namespace Romeo

#endif // ROMEO_MODEL_CORE_ALGORITHM_KMEANSALGORITHM_H

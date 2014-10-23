#ifndef ROMEO_MODEL_CORE_FEATURE_FUZZYCMEANSALGORITHM_H
#define ROMEO_MODEL_CORE_FEATURE_FUZZYCMEANSALGORITHM_H

#include "model/core/algorithm/aalgorithm.h"
#include "utils.h"
#include <stdlib.h>
#include <math.h>
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkImageRegionIterator.h"
#include "itkImageLinearConstIteratorWithIndex.h"
#include "itkImageLinearIteratorWithIndex.h"
#include "itkImageFileWriter.h"
#include "itkImageConstIterator.h"
#include "itkImageRandomConstIteratorWithIndex.h"
#include <QVector>
#include "fuzzycmeans.h"
#include "fuzzycmeans3d.h"

using Romeo::Model::Core::Algorithm::AAlgorithm;
/*!
 *\file fuzzycmeansagorithm.h
 *\author Magnabosco Nicola (nick.magnabosco@gmail.com)
 *\date 2013-04-05
*/
/*
*Changes:
*+----------+------------+---------------- +------------------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                             Changes                        +       Description         |
*+----------+------------+-----------------+------------------------------------------------------------+---------------------------+
*|                                                                                                                                  |
*|   0.0.1  | 2013-04-05 |Magnabosco Nicola|    Romeo::Model::Core::Algorithm::FuzzyCMeansAlgorithm     |   First version of class  |
*|                                                                                                                                  |
*+----------+------------+-----------------+------------------------------------------------------------+---------------------------+
*/
namespace Romeo {

    namespace Model {

        namespace Core {

            namespace Algorithm {
            /*!
                 * \brief The AAlgorithm class represents CMeans cluster algorithm in Romeo.
                 */
                class FuzzyCMeansAlgorithm : public AAlgorithm
                {


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
                    typedef itk::RGBPixel<unsigned char> RGBPixel;
                    typedef itk::RGBPixel<unsigned char> RGBPixelType;
                    typedef itk::Image<RGBPixelType,2> imageType;
                    /*!
                     * \brief FuzzyCMeansAlgorithm is the constructor of the class.
                     * \param idAlg is the id of the algorithm.
                     */
                    FuzzyCMeansAlgorithm(int idAlg = -1);
                    /*!
                     * \brief FuzzyCMeansAlgorithm is the constructor of the class.
                     * \param algorithmName is the name of the algorithm.
                     * \param algorithmId is the id code of the algorithm.
                     */
                    FuzzyCMeansAlgorithm(const QStringList& parameters, int idAlg = -1);
                    /*!
                     * \brief getNumberOfCluster gets the number of clusters.
                     * \return the number of clusters.
                     */
                    int getNumberOfCluster() const;
                    /*!
                     * \brief getMaxIteration gets the number of maximum iteration.
                     * \return the number of maximum iteration.
                     */
                    int getMaxIteration()const;
                    /*!
                     * \brief getFuzzyIndex gets the fuzzy index number.
                     * \return the fuzzy index number.
                     */
                    int getFuzzyIndex()const;

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

                    virtual ~FuzzyCMeansAlgorithm();

                private:
                    int maxIteration;
                    int fuzzyIndex;
                    int numberOfCluster;
                    int * arIt;
                    int * arIndex;
                    int * arClust;
                    QVector<int*>minMaxArray;
                    RGBPixel * arrayPixel;

                    void generateArrays();

                    /*!
                     * \brief generateColors generate 20 fixed color for the cluster
                     */
                    void generateColors();
                };

            } // namespace Feature

        } // namespace Core

    } // namespace Model

} // namespace Romeo

#endif // ROMEO_MODEL_CORE_FEATURE_FUZZYCMEANSALGORITHM_H

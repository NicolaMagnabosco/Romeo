#ifndef ROMEO_MODEL_CORE_ALGORITHM_FUZZYCMEANS_H
#define ROMEO_MODEL_CORE_ALGORITHM_FUZZYCMEANS_H

#include <math.h>
#include <cmath>
#include <QVector>
#include "clustercentroid2d.h"
#include "clusterpoint2d.h"
#include "itkImage.h"
#include "itkImageLinearIteratorWithIndex.h"
#include "itkRGBPixel.h"
#include <boost/numeric/ublas/matrix.hpp>
#include "itkImageFileWriter.h"
#include "QString"
/*!
 *\file fuzzycmeans.h
 *\author Magnabosco Nicola (nick.magnabosco@gmail.com)
 *\date 2013-04-03
*/
/*
*Changes:
*+----------+------------+---------------- +------------------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                             Changes                        +       Description         |
*+----------+------------+-----------------+------------------------------------------------------------+---------------------------+
*|                                                                                                                                  |
*|   0.0.1  | 2013-04-03 |Magnabosco Nicola|    Romeo::Model::Core::Algorithm::FuzzyCMeans              |   First version of class  |
*|                                                                                                                                  |
*+----------+------------+-----------------+------------------------------------------------------------+---------------------------+
*/
namespace Romeo {

    namespace Model {

        namespace Core {

            namespace Algorithm {

                class FuzzyCMeans
                {
                public:
                    typedef itk::RGBPixel<unsigned char> RGBPixelType;
                    typedef itk::Image<RGBPixelType,2> imageType;
                    QVector<ClusterPoint2D> Points;
                    QVector<ClusterCentroid2D> Clusters;
                    boost::numeric::ublas::matrix<double> U;
                    imageType::Pointer myImage;
                    imageType::Pointer processedImage;
                    int myImageWidth;
                    int myImageHeight;
                    double J;

                    imageType::Pointer getProcessedImage() { return processedImage; }
                    bool Converged() { return isConverged; }

                    FuzzyCMeans();
                    FuzzyCMeans(QVector<ClusterPoint2D>& points, QVector<ClusterCentroid2D>& clusters, float fuzzy, imageType::Pointer myImage, int numCluster);
                    void Step();
                    double CalculateObjectiveFunction();
                    void CalculateClusterCentroids();
                private:
                    bool isConverged;
                    double Fuzzyness;
                    double Eps;
                    double CalculateEuclideanDistance(ClusterPoint2D p, ClusterCentroid2D c);
                    void RecalculateClusterMembershipValues();

                };

            } // namespace Algorithm

        } // namespace Core

    } // namespace Model

} // namespace Romeo

#endif // ROMEO_MODEL_CORE_ALGORITHM_FUZZYCMEANS_H

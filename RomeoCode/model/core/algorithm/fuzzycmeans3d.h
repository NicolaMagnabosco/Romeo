#ifndef ROMEO_MODEL_CORE_ALGORITHM_FUZZYCMEANS3D_H
#define ROMEO_MODEL_CORE_ALGORITHM_FUZZYCMEANS3D_H

#include <math.h>
#include <cmath>
#include <QVector>
#include "clustercentroid3d.h"
#include "clusterpoint3d.h"
#include "itkImage.h"
#include "itkImageLinearIteratorWithIndex.h"
#include "itkRGBPixel.h"
#include <boost/numeric/ublas/matrix.hpp>
#include "itkImageFileWriter.h"
#include "QString"
/*!
 *\file fuzzycmeans3d.h
 *\author Magnabosco Nicola (nick.magnabosco@gmail.com)
 *\date 2013-04-04
*/
/*
*Changes:
*+----------+------------+---------------- +------------------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                             Changes                        +       Description         |
*+----------+------------+-----------------+------------------------------------------------------------+---------------------------+
*|                                                                                                                                  |
*|   0.0.1  | 2013-04-04 |Magnabosco Nicola|    Romeo::Model::Core::Algorithm::FuzzyCMeans3D            |   First version of class  |
*|                                                                                                                                  |
*+----------+------------+-----------------+------------------------------------------------------------+---------------------------+
*/
namespace Romeo {
namespace Model {
namespace Core {
namespace Algorithm {

class FuzzyCMeans3D
{
public:
    typedef itk::RGBPixel<unsigned char> RGBPixelType;
    typedef itk::Image< float,3> imageType;
    QVector<ClusterPoint3D*> Points;
    QVector<ClusterCentroid3D*> Clusters;
    boost::numeric::ublas::matrix<double> U;
    imageType::Pointer myImage;
    int myImageWidth;
    int myImageHeight;
    int myImageDepth;
    double J;

    bool Converged() { return isConverged; }

    FuzzyCMeans3D();
    FuzzyCMeans3D(QVector<ClusterPoint3D*>& points, QVector<ClusterCentroid3D*>& clusters, float fuzzy, imageType::Pointer myImage, int numCluster);
    void Step();
    double CalculateObjectiveFunction();
    void CalculateClusterCentroids();
private:
    bool isConverged;
    double Fuzzyness;
    double Eps;
    double CalculateEuclideanDistance(ClusterPoint3D* p, ClusterCentroid3D* c);
    void RecalculateClusterMembershipValues();

};

} // namespace Algorithm
} // namespace Core
} // namespace Model
} // namespace Romeo

#endif // ROMEO_MODEL_CORE_ALGORITHM_FUZZYCMEANS3D_H

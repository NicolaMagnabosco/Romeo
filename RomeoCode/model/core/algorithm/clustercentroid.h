#ifndef ROMEO_MODEL_CORE_ALGORITHM_CLUSTERCENTROID_H
#define ROMEO_MODEL_CORE_ALGORITHM_CLUSTERCENTROID_H

#include "itkRGBPixel.h"
/*!
 *\file clustercentroid.h
 *\author Luisetto Luca (lucaluisetto91@gmail.com)
 *\date 2013-04-01
*/
/*
*Changes:
*+----------+------------+---------------- +------------------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                             Changes                        +       Description         |
*+----------+------------+-----------------+------------------------------------------------------------+---------------------------+
*|                                                                                                                                  |
*|   0.0.1  | 2013-04-01 |   Luisetto Luca |    Romeo::Model::Core::Algorithm::ClusterCentroid          |   First version of class  |
*|                                                                                                                                  |
*+----------+------------+-----------------+------------------------------------------------------------+---------------------------+
*/
namespace Romeo {

    namespace Model {

        namespace Core {

            namespace Algorithm {

                class ClusterCentroid
                {

                public:
                    typedef itk::RGBPixel<unsigned char> RGBPixel;
                    double MembershipSum;
                    double Sum;
                    double PixelCount;
                    ClusterCentroid();
                    ClusterCentroid(int r, int c);
                    int getRow();
                    int getColumn();
                private:
                    int row;
                    int column;
                };

            } // namespace Algorithm

        } // namespace Core

    } // namespace Model

} // namespace Romeo

#endif // ROMEO_MODEL_CORE_ALGORITHM_CLUSTERCENTROID_H

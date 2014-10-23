#ifndef ROMEO_MODEL_CORE_ALGORITHM_CLUSTERCENTROID2D_H
#define ROMEO_MODEL_CORE_ALGORITHM_CLUSTERCENTROID2D_H

#include "model/core/algorithm/clustercentroid.h"
/*!
 *\file clustercentroid2d.h
 *\author Luisetto Luca (lucaluisetto91@gmail.com)
 *\date 2013-04-01
*/
/*
*Changes:
*+----------+------------+---------------- +------------------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                             Changes                        +       Description         |
*+----------+------------+-----------------+------------------------------------------------------------+---------------------------+
*|                                                                                                                                  |
*|   0.0.1  | 2013-04-01 |   Luisetto Luca |    Romeo::Model::Core::Algorithm::ClusterCentroid2D        |   First version of class  |
*|                                                                                                                                  |
*+----------+------------+-----------------+------------------------------------------------------------+---------------------------+
*/
namespace Romeo {

    namespace Model {

        namespace Core {

            namespace Algorithm {

                class ClusterCentroid2D : public ClusterCentroid
                {
                public:
                    double RSum;
                    double GSum;
                    double BSum;

                    RGBPixel PixelColor;
                    RGBPixel OriginalPixelColor;


                    ClusterCentroid2D();
                    ClusterCentroid2D(int r, int c, RGBPixel cl);
                    RGBPixel getColor();
                private:
                    RGBPixel color;
                };

            } // namespace Algorithm

        } // namespace Core

    } // namespace Model

} // namespace Romeo

#endif // ROMEO_MODEL_CORE_ALGORITHM_CLUSTERCENTROID2D_H

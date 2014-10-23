#ifndef ROMEO_MODEL_CORE_ALGORITHM_CLUSTERPOINT2D_H
#define ROMEO_MODEL_CORE_ALGORITHM_CLUSTERPOINT2D_H

#include "model/core/algorithm/clusterpoint.h"
/*!
 *\file clusterpoint2D.h
 *\author Luisetto Luca (lucaluisetto91@gmail.com)
 *\date 2013-04-02
*/
/*
*Changes:
*+----------+------------+---------------- +------------------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                             Changes                        +       Description         |
*+----------+------------+-----------------+------------------------------------------------------------+---------------------------+
*|                                                                                                                                  |
*|   0.0.1  | 2013-04-02 |   Luisetto Luca |    Romeo::Model::Core::Algorithm::ClusterPoint2D           |   First version of class  |
*|                                                                                                                                  |
*+----------+------------+-----------------+------------------------------------------------------------+---------------------------+
*/
namespace Romeo {

    namespace Model {

        namespace Core {

            namespace Algorithm {

                class ClusterPoint2D : public ClusterPoint
                {
                public:
                    ClusterPoint2D();

                    ClusterPoint2D(int r, int c, RGBPixel cl);

                    ClusterPoint2D(int r, int c, RGBPixel cl, int cluster);

                    RGBPixel getColor();

                    RGBPixel getOriginalPixelColor();
                private:
                    RGBPixel color;
                    RGBPixel originalPixelColor;
                };

            } // namespace Algorithm

        } // namespace Core

    } // namespace Model

} // namespace Romeo

#endif // ROMEO_MODEL_CORE_ALGORITHM_CLUSTERPOINT2D_H

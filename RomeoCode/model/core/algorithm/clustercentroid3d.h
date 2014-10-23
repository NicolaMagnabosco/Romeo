#ifndef ROMEO_MODEL_CORE_ALGORITHM_CLUSTERCENTROID3D_H
#define ROMEO_MODEL_CORE_ALGORITHM_CLUSTERCENTROID3D_H

#include "model/core/algorithm/clustercentroid.h"
/*!
 *\file clustercentroid3d.h
 *\author Luisetto Luca (lucaluisetto91@gmail.com)
 *\date 2013-04-01
*/
/*
*Changes:
*+----------+------------+---------------- +------------------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                             Changes                        +       Description         |
*+----------+------------+-----------------+------------------------------------------------------------+---------------------------+
*|                                                                                                                                  |
*|   0.0.1  | 2013-04-01 |   Luisetto Luca |    Romeo::Model::Core::Algorithm::ClusterCentroid3D        |   First version of class  |
*|                                                                                                                                  |
*+----------+------------+-----------------+------------------------------------------------------------+---------------------------+
*/
namespace Romeo {

    namespace Model {

        namespace Core {

            namespace Algorithm {

                class ClusterCentroid3D : public ClusterCentroid
                {
                public:
                    double PixelColor;
                    double OriginalPixelColor;

                    ClusterCentroid3D();
                    ClusterCentroid3D(int r, int c, int d, double cl);
                    double getColor();
                    int getDepth();
                private:
                    int depth;
                    double color;
                };

            } // namespace Algorithm

        } // namespace Core

    } // namespace Model

} // namespace Romeo

#endif // ROMEO_MODEL_CORE_ALGORITHM_CLUSTERCENTROID3D_H

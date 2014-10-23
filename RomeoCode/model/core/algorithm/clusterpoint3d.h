#ifndef ROMEO_MODEL_CORE_ALGORITHM_CLUSTERPOINT3D_H
#define ROMEO_MODEL_CORE_ALGORITHM_CLUSTERPOINT3D_H

#include "model/core/algorithm/clusterpoint.h"
/*!
 *\file clusterpoint3d.h
 *\author Luisetto Luca (lucaluisetto91@gmail.com)
 *\date 2013-04-02
*/
/*
*Changes:
*+----------+------------+---------------- +------------------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                             Changes                        +       Description         |
*+----------+------------+-----------------+------------------------------------------------------------+---------------------------+
*|                                                                                                                                  |
*|   0.0.1  | 2013-04-02 |   Luisetto Luca |    Romeo::Model::Core::Algorithm::ClusterPoint3D           |   First version of class  |
*|                                                                                                                                  |
*+----------+------------+-----------------+------------------------------------------------------------+---------------------------+
*/
namespace Romeo {

    namespace Model {

        namespace Core {

            namespace Algorithm {

                class ClusterPoint3D : public ClusterPoint
                {
                public:
                    int depth;

                    ClusterPoint3D();

                    ClusterPoint3D(int r, int c, int d, double cl);

                    ClusterPoint3D(int r, int c, int d, double cl, int cluster);

                    double getColor();

                    double getOriginalPixelColor();

                    int getDepth();

                private:
                    double color;
                    double originalPixelColor;
                };

            } // namespace Algorithm

        } // namespace Core

    } // namespace Model

} // namespace Romeo

#endif // ROMEO_MODEL_CORE_ALGORITHM_CLUSTERPOINT3D_H

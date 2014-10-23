#ifndef ROMEO_MODEL_CORE_ALGORITHM_CLUSTERPOINT_H
#define ROMEO_MODEL_CORE_ALGORITHM_CLUSTERPOINT_H

#include "itkRGBPixel.h"
/*!
 *\file clusterpoint.h
 *\author Luisetto Luca (lucaluisetto91@gmail.com)
 *\date 2013-04-02
*/
/*
*Changes:
*+----------+------------+---------------- +------------------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                             Changes                        +       Description         |
*+----------+------------+-----------------+------------------------------------------------------------+---------------------------+
*|                                                                                                                                  |
*|   0.0.1  | 2013-04-02 |   Luisetto Luca |    Romeo::Model::Core::Algorithm::ClusterPoint             |   First version of class  |
*|                                                                                                                                  |
*+----------+------------+-----------------+------------------------------------------------------------+---------------------------+
*/
namespace Romeo {

    namespace Model {

        namespace Core {

            namespace Algorithm {

                class ClusterPoint
                {

                public:
                    typedef itk::RGBPixel<unsigned char> RGBPixel;

                    double ClusterIndex;

                    ClusterPoint();

                    ClusterPoint(int r, int c);

                    ClusterPoint(int r, int c, int cluster);

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

#endif // ROMEO_MODEL_CORE_ALGORITHM_CLUSTERPOINT_H

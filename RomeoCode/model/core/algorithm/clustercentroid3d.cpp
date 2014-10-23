#include "clustercentroid3d.h"

using Romeo::Model::Core::Algorithm::ClusterCentroid3D;
using Romeo::Model::Core::Algorithm::ClusterCentroid;

ClusterCentroid3D::ClusterCentroid3D()
    : ClusterCentroid()
{
}

ClusterCentroid3D::ClusterCentroid3D(int r, int c, int d, double cl)
    : ClusterCentroid(r,c), PixelColor(cl), OriginalPixelColor(cl), depth(d), color(cl)
{

}

int ClusterCentroid3D::getDepth()
{
    return depth;
}

double ClusterCentroid3D::getColor()
{
    return PixelColor;
}

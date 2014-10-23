#include "clusterpoint3d.h"

using Romeo::Model::Core::Algorithm::ClusterPoint;
using Romeo::Model::Core::Algorithm::ClusterPoint3D;

ClusterPoint3D::ClusterPoint3D() : ClusterPoint()
{
}

ClusterPoint3D::ClusterPoint3D(int r, int c, int d, double cl)
    : ClusterPoint(r,c), depth(d), color(cl), originalPixelColor(cl)
{

}

ClusterPoint3D::ClusterPoint3D(int r, int c, int d, double cl, int cluster)
    : ClusterPoint(r,c,cluster), depth(d), color(cl), originalPixelColor(cl)
{

}

double ClusterPoint3D::getColor(){
    return color;
}

double ClusterPoint3D::getOriginalPixelColor()
{
    return originalPixelColor;
}

int ClusterPoint3D::getDepth(){
    return depth;
}

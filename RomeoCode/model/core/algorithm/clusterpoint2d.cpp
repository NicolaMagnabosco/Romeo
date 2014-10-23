#include "clusterpoint2d.h"

using Romeo::Model::Core::Algorithm::ClusterPoint2D;
using Romeo::Model::Core::Algorithm::ClusterPoint;

ClusterPoint2D::ClusterPoint2D() : ClusterPoint()
{
}

ClusterPoint2D::ClusterPoint2D(int r, int c, RGBPixel cl)
    : ClusterPoint(r,c), color(cl), originalPixelColor(cl)
{
}

ClusterPoint2D::ClusterPoint2D(int r, int c, RGBPixel cl, int cluster)
    : ClusterPoint(r,c,cluster), color(cl), originalPixelColor(cl)
{

}

ClusterPoint2D::RGBPixel ClusterPoint2D::getColor()
{
    return color;
}

ClusterPoint2D::RGBPixel ClusterPoint2D::getOriginalPixelColor()
{
    return originalPixelColor;
}

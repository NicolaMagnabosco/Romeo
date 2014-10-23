#include "clustercentroid2d.h"

using Romeo::Model::Core::Algorithm::ClusterCentroid2D;

ClusterCentroid2D::ClusterCentroid2D() :
    ClusterCentroid()
{

}

ClusterCentroid2D::ClusterCentroid2D(int r, int c, RGBPixel cl)
    : ClusterCentroid(r,c), PixelColor(cl), OriginalPixelColor(cl), color(cl)
{
    RSum = 0;
    GSum = 0;
    BSum = 0;
}

ClusterCentroid2D::RGBPixel ClusterCentroid2D::getColor()
{
    return PixelColor;
}

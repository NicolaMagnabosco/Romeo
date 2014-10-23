#include "clustercentroid.h"

using Romeo::Model::Core::Algorithm::ClusterCentroid;

ClusterCentroid::ClusterCentroid()
{
}

ClusterCentroid::ClusterCentroid(int r, int c)
{
    row=r;
    column=c;
    Sum=0;
    MembershipSum = 0;
    PixelCount = 0;

}

int ClusterCentroid::getRow()
{
    return row;
}

int ClusterCentroid::getColumn()
{
    return column;
}

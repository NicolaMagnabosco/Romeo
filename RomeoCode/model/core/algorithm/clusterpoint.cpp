#include "clusterpoint.h"

using Romeo::Model::Core::Algorithm::ClusterPoint;

ClusterPoint::ClusterPoint()
{
}

ClusterPoint::ClusterPoint(int r, int c)
{
    row=r;
    column=c;
    ClusterIndex=-1;
}

ClusterPoint::ClusterPoint(int r, int c, int cluster)
{
    row=r;
    column=c;
    ClusterIndex=cluster;
}

int ClusterPoint::getRow()
{
    return row;
}

int ClusterPoint::getColumn()
{
    return column;
}

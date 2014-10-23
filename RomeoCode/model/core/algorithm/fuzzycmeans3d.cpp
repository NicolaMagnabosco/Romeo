#include "fuzzycmeans3d.h"

using Romeo::Model::Core::Algorithm::FuzzyCMeans3D;
using Romeo::Model::Core::Algorithm::ClusterPoint3D;
using Romeo::Model::Core::Algorithm::ClusterCentroid3D;

FuzzyCMeans3D::FuzzyCMeans3D()
{
}


double FuzzyCMeans3D::CalculateEuclideanDistance(ClusterPoint3D* p, ClusterCentroid3D* c)
{
    return std::sqrt(std::pow(p->getColor() - c->getColor(),2.0));
}

void FuzzyCMeans3D::RecalculateClusterMembershipValues()
{
    QVector<ClusterPoint3D*>::iterator it;
    it=Points.begin();
    for (int i = 0; i < Points.size(); i++)
   {
       double max = 0.0;
       double min = 0.0;
       double sum = 0.0;
       double newmax = 0;
       ClusterPoint3D* p = Points.at(i);
       //Normalize the entries
       for (int j = 0; j < Clusters.size(); j++)
       {
           if (U(i,j)> max){
               max=U(i,j);
           }
           if (U(i,j)<min){
               min=U(i,j);
           }
       }
       for (int j = 0; j < Clusters.size(); j++)
       {
           U(i, j) = (U(i, j) - min) / (max - min);
           sum += U(i, j);
       }
       //Makes it so that the sum of all values is 1
       for (int j = 0; j < Clusters.size(); j++)
       {
           U(i, j) = U(i, j) / sum;
           if (std::isnan(U(i, j)))
           {
               ///Console.WriteLine("NAN value: point({0}) cluster({1}) sum {2} newmax {3}", i, j, sum, newmax);
               U(i, j) = 0.0;
           }

           if (U(i,j)> newmax){
               newmax=U(i,j);
           }
       }
       // ClusterIndex is used to store the strongest membership value to a cluster, used for defuzzification
        p->ClusterIndex=newmax;
        ++it;
     };

}


FuzzyCMeans3D::FuzzyCMeans3D(QVector<ClusterPoint3D*> &points, QVector<ClusterCentroid3D*> &clusters, float fuzzy, imageType::Pointer myImage, int numCluster)
{


    this->Eps = std::pow(10, -5);
    this->isConverged=false;
    this->Points = points;
    this->Clusters = clusters;
    this->myImageHeight = myImage->GetBufferedRegion().GetSize()[0];
    this->myImageWidth = myImage->GetBufferedRegion().GetSize()[1];
    this->myImageDepth = myImage->GetBufferedRegion().GetSize()[2];
    this->myImage = myImage;
    U= boost::numeric::ublas::matrix<double>(Points.size(),Clusters.size());
    this->Fuzzyness = fuzzy;

    double diff;

    // Iterate through all points to create initial U matrix
    for (int i = 0; i < Points.size()-1; i++)
    {
        ClusterPoint3D* p = Points.at(i);
        double sum = 0.0;

        for (int j = 0; j < Clusters.size(); j++)
        {
            ClusterCentroid3D* c = Clusters.at(j);
            diff = std::sqrt(std::pow(CalculateEuclideanDistance(p, c), 2.0));
            if (diff==0){
                U(i,j)=Eps;
            }
            else{
                U(i,j)=diff;
            }
            sum += U(i, j);
        }
     }

    this->RecalculateClusterMembershipValues();
}

void FuzzyCMeans3D::Step()
{
    for (int c = 0; c < Clusters.size(); c++)
    {
        for (int h = 0; h < Points.size(); h++)
        {

            double top;
            top = CalculateEuclideanDistance(Points.at(h), Clusters.at(c));
            if (top < 1.0) top = Eps;

            // sumTerms is the sum of distances from this data point to all clusters.
            double sumTerms = 0.0;

            for (int ck = 0; ck < Clusters.size(); ck++)
            {
                sumTerms += top / CalculateEuclideanDistance(Points.at(h), Clusters.at(ck));

            }
            // Then the membership value can be calculated as...
            U(h, c) = (double)(1.0 / std::pow(sumTerms, (2 / (this->Fuzzyness - 1))));
        }
    };


    this->RecalculateClusterMembershipValues();
}

double FuzzyCMeans3D::CalculateObjectiveFunction()
{
    double Jk = 0.0;

    for (int i = 0; i < Points.size();i++)
    {
        for (int j = 0; j < Clusters.size(); j++)
        {
            Jk += std::pow(U(i, j), Fuzzyness) * std::pow(this->CalculateEuclideanDistance(Points.at(i), Clusters.at(j)), 2);
        }
    }
    return Jk;
}

void FuzzyCMeans3D::CalculateClusterCentroids()
{
    for (int j = 0; j < this->Clusters.size(); j++)
    {
        ClusterCentroid3D* c = this->Clusters.at(j);
        double l = 0.0;
        c->PixelCount = 1;
        c->MembershipSum = 0;
        c->Sum=0;

        for (int i = 0; i < this->Points.size(); i++)
        {

            ClusterPoint3D* p = this->Points.at(i);
            l = std::pow(U(i, j), this->Fuzzyness);
            c->Sum +=l*p->getColor();
            c->MembershipSum += l;

            if (U(i, j) == p->ClusterIndex)
            {
                c->PixelCount += 1;
            }
        }
        c->PixelColor=c->Sum/c->MembershipSum;
    }

}

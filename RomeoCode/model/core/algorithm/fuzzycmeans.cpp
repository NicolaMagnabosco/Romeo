#include "fuzzycmeans.h"

using Romeo::Model::Core::Algorithm::FuzzyCMeans;

FuzzyCMeans::FuzzyCMeans()
{
}

FuzzyCMeans::FuzzyCMeans(QVector<ClusterPoint2D> &points, QVector<ClusterCentroid2D> &clusters, float fuzzy, imageType::Pointer myImage, int numCluster)
{
    this->Eps = std::pow(10, -5);
        this->isConverged=false;
        this->Points = points;
        this->Clusters = clusters;
        this->myImageHeight = myImage->GetBufferedRegion().GetSize()[0];
        this->myImageWidth = myImage->GetBufferedRegion().GetSize()[1];
        this->myImage = myImage;
        U= boost::numeric::ublas::matrix<double>(Points.size(),Clusters.size());
        this->Fuzzyness = fuzzy;

        double diff;


        imageType::SizeType size;
        size[0]=myImageWidth; // x axis
        size[1]=myImageHeight; // y
        imageType::RegionType region;
        region.SetSize(size);
        imageType::Pointer image = imageType::New();
        image->SetRegions(region);
        image->Allocate(); // immagine create

        // Iterate through all points to create initial U matrix
        for (int i = 0; i < Points.size()-1; i++)
        {
            ClusterPoint2D p = Points.at(i);
            double sum = 0.0;

            for (int j = 0; j < Clusters.size()-1; j++)
            {
                ClusterCentroid2D c = Clusters.at(j);
                diff = std::sqrt(std::pow(CalculateEuclideanDistance(p, c), 2.0));
                //U(i, j) = (diff == 0) ? Eps : diff;
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

double FuzzyCMeans::CalculateEuclideanDistance(ClusterPoint2D p, ClusterCentroid2D c)
{
    return std::sqrt(std::pow((p.getColor() - c.getColor()).GetScalarValue(),2.0));
}

void FuzzyCMeans::RecalculateClusterMembershipValues()
{
        QVector<ClusterPoint2D>::iterator it;
        it=Points.begin();
        for (int i = 0; i < Points.size(); i++)
       {
           double max = 0.0;
           double min = 0.0;
           double sum = 0.0;
           double newmax = 0;
           ClusterPoint2D p = Points.at(i);
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
           //Sets the values to the normalized values between 0 and 1
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
            it->ClusterIndex=newmax;
            ++it;
         };
}

void FuzzyCMeans::Step()
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

double FuzzyCMeans::CalculateObjectiveFunction()
{
    double Jk = 0.0;

        for (int i = 0; i < this->Points.size();i++)
        {
            for (int j = 0; j < this->Clusters.size(); j++)
            {
                Jk += std::pow(U(i, j), this->Fuzzyness) * std::pow(this->CalculateEuclideanDistance(Points.at(i), Clusters.at(j)), 2);
            }
        }
        return Jk;
}

void FuzzyCMeans::CalculateClusterCentroids()
{
    for (int j = 0; j < this->Clusters.size(); j++)
       {
           ClusterCentroid2D c = this->Clusters.at(j);
           double l = 0.0;
           c.PixelCount = 1;
           c.RSum = 0;
           c.GSum = 0;
           c.BSum = 0;
           c.MembershipSum = 0;

           for (int i = 0; i < this->Points.size(); i++)
           {

               ClusterPoint2D p = this->Points.at(i);
               l = std::pow(U(i, j), this->Fuzzyness);
               c.RSum += l * p.getColor().GetRed();
               c.GSum += l * p.getColor().GetGreen();
               c.BSum += l * p.getColor().GetBlue();
               c.MembershipSum += l;

               if (U(i, j) == p.ClusterIndex)
               {
                   c.PixelCount += 1;
               }
           }
           FuzzyCMeans::RGBPixelType color;
           color.SetRed(c.RSum / c.MembershipSum);
           color.SetGreen(c.GSum / c.MembershipSum);
           color.SetBlue(c.BSum / c.MembershipSum);
           c.PixelColor=color;
       }

       //update the original image
       imageType::SizeType size;
       size[0]=myImageWidth;
       size[1]=myImageHeight;
       imageType::RegionType region;
       region.SetSize(size);
       imageType::Pointer tempImage = imageType::New();
       tempImage->SetRegions(region);
       tempImage->Allocate();
       typedef itk::ImageLinearIteratorWithIndex<imageType > IteratorType2;
       for (int j = 0; j < this->Points.size(); j++)
       {
           for (int i = 0; i < this->Clusters.size(); i++)
           {
               ClusterPoint2D p = this->Points.at(j);
               if (U(j, i) == p.ClusterIndex)
               {
                   imageType::IndexType index;
                   index[0]=p.getRow();
                   index[1]=p.getColumn();
               }
           }
       }

       processedImage = tempImage;
}

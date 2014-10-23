#include "fuzzycmeansalgorithm.h"

using Romeo::Model::Core::Algorithm::FuzzyCMeansAlgorithm;
using Romeo::Model::Core::RGBImage2D;
using Romeo::Model::Core::RGBImage3D;
using Romeo::Model::Core::RomeoObject;
using Romeo::Model::Core::InternalData2D;
using Romeo::Model::Core::InternalData3D;
using Romeo::Model::Core::Algorithm::FuzzyCMeans;
using Romeo::Model::Core::Algorithm::ClusterCentroid2D;
using Romeo::Model::Core::Algorithm::ClusterPoint2D;
using Romeo::Model::Core::Algorithm::FuzzyCMeans3D;
using Romeo::Model::Core::Algorithm::ClusterCentroid3D;
using Romeo::Model::Core::Algorithm::ClusterPoint3D;
using Romeo::Model::Core::Video2D;
using Romeo::Model::Core::Video3D;
using Romeo::Model::Core::Feature::MeanDynamicFeature;

FuzzyCMeansAlgorithm::FuzzyCMeansAlgorithm(int idAlg)
    : AAlgorithm(Utils::ALGORITHM_FUZZY, idAlg), maxIteration(200), fuzzyIndex(2),
      numberOfCluster(10), arIt(new int[2]), arIndex(new int[2]),
      arClust(new int[2]), arrayPixel(new RGBPixel[20])
{
    generateArrays();
    generateColors();
}

FuzzyCMeansAlgorithm::FuzzyCMeansAlgorithm(const QStringList& parameters, int idAlg)
    : AAlgorithm(Utils::ALGORITHM_FUZZY, idAlg), maxIteration(200), fuzzyIndex(2),
      numberOfCluster(10), arIt(new int[2]), arIndex(new int[2]),
      arClust(new int[2]), arrayPixel(new RGBPixel[20])
{
    generateArrays();
    generateColors();

    if(parameters.size()>0)
        setParameters(parameters);
}

void FuzzyCMeansAlgorithm::generateArrays()
{
    arIndex[0] = 2;
    arIndex[1] = 5;
    arIt[0] = 2;
    arIt[1] = 500;
    arClust[0] = 2;
    arClust[1] = 20;

    minMaxArray.append(arIndex);
    minMaxArray.append(arIt);
    minMaxArray.append(arClust);
}

RomeoObject* FuzzyCMeansAlgorithm::execute2DAnalysis(RGBImage2D *image)
{
    RGBImage2D::RGBImageType::Pointer imageRead = image->getImage();

    int nrows = image->getYSize();
    int ncol = image->getXSize();

    typedef itk::ImageLinearConstIteratorWithIndex<imageType > IteratorType2;
      QVector<ClusterPoint2D> points;
      IteratorType2 iter(imageRead, imageRead->GetBufferedRegion());
      iter.SetDirection(0);
      iter.GoToBegin();
      RGBPixel c2;
      for (int row = 0; row < nrows; ++row)
      {
          for (int col = 0; col < ncol; ++col)
          {
              c2 = iter.Value();
              ClusterPoint2D ctoadd(row,col,c2);
              points.append(ctoadd);
              ++iter;
          }
          iter.NextLine();
      }

      QVector<ClusterCentroid2D> centroids;
        typedef itk::ImageRandomConstIteratorWithIndex<imageType> rconstIteratoritk;
        rconstIteratoritk iter2(imageRead, imageRead->GetBufferedRegion());
        iter2.GoToBegin();

        //Create random points to use as the cluster centroids
        int numClusters=getNumberOfCluster();
        for (int i = 0; i < numClusters; i++)
        {
            imageType::IndexType index;
            index=iter2.GetIndex();
            ClusterCentroid2D cctoadd(index[1], index[0], iter2.Value());
            centroids.append(cctoadd);
            ++iter2;
        }

          FuzzyCMeans alg(points, centroids, getFuzzyIndex(), imageRead, numClusters);
          int maxIterations=getMaxIteration();
          for(int k=0; k<maxIterations; ++k)
          {
              alg.J = alg.CalculateObjectiveFunction();
              alg.CalculateClusterCentroids();
              alg.Step();
              double Jnew = alg.CalculateObjectiveFunction();
          }


          boost::numeric::ublas::matrix<double> matrice = alg.U;

       imageType::SizeType size;
       size[0]=ncol;
       size[1]=nrows;
       imageType::RegionType region;
       region.SetSize(size);
       imageType::Pointer imageToWrite = imageType::New();
       imageToWrite->SetRegions(region);
       imageToWrite->Allocate();


       for (int j = 0; j < points.size(); j++)
         {
             for (int i = 0; i < centroids.size(); i++)
             {
                 ClusterPoint2D p = alg.Points.at(j);

                 if (matrice(j,i) == p.ClusterIndex)
                 {
                       imageType::IndexType index;
                       index[1]=p.getRow();
                       index[0]=p.getColumn();
                       imageToWrite->SetPixel(index,arrayPixel[i]);
                 }
             }
          }

    RGBImage2D* output = new RGBImage2D();
    output->setImage(imageToWrite);
    return output;
}

RomeoObject* FuzzyCMeansAlgorithm::execute3DAnalysis(RGBImage3D *image)
{

    typedef itk::Image<itk::RGBPixel<unsigned char>,3> outputImageType;

    InternalData3D* data = image->getGreyScaleImage();
    RGBImage3D::ImageType::Pointer imageRead = data->getImage();

    int nrows = image->getYSize();
    int ncol = image->getXSize();
    int depth = image->getZSize();

    typedef itk::ImageLinearConstIteratorWithIndex<RGBImage3D::ImageType > IteratorType3d;

    QVector<ClusterPoint3D*> points;
    IteratorType3d iter(imageRead, imageRead->GetBufferedRegion());
    int c2;

      for (int row = 0; row < nrows; ++row)
      {
          for (int col = 0; col < ncol; ++col)
          {
              for (int z=0; z<depth; ++z)
              {
                  RGBImage3D::ImageType::IndexType index;
                  index[0]=col;
                  index[1]=row;
                  index[2]=z;
                  iter.SetIndex(index);
                  c2 = iter.Value();
                  ClusterPoint3D* ctoadd= new ClusterPoint3D(index[1],index[0],index[2],c2);
                  points.append(ctoadd);

              }
          }
      }

      QVector<ClusterCentroid3D*> centroids;

      int numClusters=getNumberOfCluster();

      typedef itk::ImageRandomConstIteratorWithIndex<RGBImage3D::ImageType> rconstIteratoritk3d;
      rconstIteratoritk3d iter2(imageRead, imageRead->GetBufferedRegion());
      iter2.GoToBegin();

        for (int i = 0; i < numClusters;)
        {
            RGBImage3D::ImageType::IndexType index;
            index=iter2.GetIndex();

            QVector<ClusterCentroid3D*>::iterator Qit;

            bool check=false;

            for (Qit=centroids.begin(); Qit!=centroids.end() && check==false; Qit++){

                if ((*Qit)->getColor()==iter2.Value()){
                    check=true;
                }
            }

            if (check==false){
                ClusterCentroid3D* cctoadd= new ClusterCentroid3D(index[1], index[0], index[2], iter2.Value());
                centroids.append(cctoadd);
                i++;
            }
            ++iter2;
        }

        FuzzyCMeans3D alg(points, centroids, getFuzzyIndex(), imageRead, numClusters);

          int maxIterations=getMaxIteration();

          for(int k=0; k<maxIterations; ++k)
          {
              alg.J = alg.CalculateObjectiveFunction();
              alg.CalculateClusterCentroids();
              alg.Step();

              double Jnew = alg.CalculateObjectiveFunction();
          }


          boost::numeric::ublas::matrix<double> matrice = alg.U;

            RGBImage3D::ImageType::SizeType size;
            size[0]=imageRead->GetLargestPossibleRegion().GetSize()[0]; // x
            size[1]=imageRead->GetLargestPossibleRegion().GetSize()[1]; // y
            size[2]=imageRead->GetLargestPossibleRegion().GetSize()[2]; // z
            RGBImage3D::ImageType::RegionType region;
            region.SetSize(size);
            outputImageType::Pointer outputImage = outputImageType::New();
            outputImage->SetRegions(region);
            outputImage->Allocate();




            for (int j = 0; j < points.size(); j++)
            {
                for (int i = 0; i < centroids.size(); i++)
                {
                    ClusterPoint3D* p = alg.Points.at(j);
                    if (matrice(j,i) == p->ClusterIndex)
                    {
                          outputImageType::IndexType index;
                          index[0]=p->getColumn();
                          index[1]=p->getRow();
                          index[2]=p->getDepth();
                          outputImage->SetPixel(index,arrayPixel[i]);
                    }
                }
             }

    RGBImage3D* output = new RGBImage3D();
    output->setImage(outputImage);
    return output;
}

RomeoObject* FuzzyCMeansAlgorithm::execute2DVideoAnalysis(Video2D *video)
{
    int nFrames = video->getNumberOfFrames();
    InternalData2D* frame = video->getFrame(nFrames/2);
    RGBImage2D* rgbFrame = new RGBImage2D(frame);


    RomeoObject* output = execute2DAnalysis(rgbFrame);
    return output;
}

RomeoObject* FuzzyCMeansAlgorithm::execute3DVideoAnalysis(Video3D *video)
{
    int nFrames = video->getNumberOfFrames();
    InternalData3D* frame = video->getFrame(nFrames/2);
    RGBImage3D* rgbFrame = new RGBImage3D(frame);


    RomeoObject* output = execute3DAnalysis(rgbFrame);
    return output;
}

void FuzzyCMeansAlgorithm::generateColors()
{
    arrayPixel[0].Set(255,0,0);
    arrayPixel[1].Set(255,128,0);
    arrayPixel[2].Set(255,255,0);
    arrayPixel[3].Set(128,255,0);
    arrayPixel[4].Set(0,255,0);
    arrayPixel[5].Set(0,255,128);
    arrayPixel[6].Set(0,255,255);
    arrayPixel[7].Set(0,128,255);
    arrayPixel[8].Set(0,0,255);
    arrayPixel[9].Set(128,0,255);
    arrayPixel[10].Set(255,0,255);
    arrayPixel[11].Set(255,0,128);
    arrayPixel[12].Set(255,153,153);
    arrayPixel[13].Set(255,255,153);
    arrayPixel[14].Set(153,255,153);
    arrayPixel[15].Set(153,255,255);
    arrayPixel[16].Set(153,153,255);
    arrayPixel[17].Set(204,153,255);
    arrayPixel[18].Set(255,153,203);
    arrayPixel[19].Set(255,204,204);

}

int FuzzyCMeansAlgorithm::getNumberOfCluster() const
{
    return numberOfCluster;
}
int FuzzyCMeansAlgorithm::getMaxIteration()const
{
    return maxIteration;
}
int FuzzyCMeansAlgorithm::getFuzzyIndex()const
{
    return fuzzyIndex;
}

void FuzzyCMeansAlgorithm::setParameters(const QStringList& pars) {
    fuzzyIndex = pars.at(0).toInt();
    maxIteration = pars.at(1).toInt();
    numberOfCluster = pars.at(2).toInt();
}

QStringList FuzzyCMeansAlgorithm::getParameters() const
{
    QStringList ret;
    ret.append(QString::number(fuzzyIndex));
    ret.append(QString::number(maxIteration));
    ret.append(QString::number(numberOfCluster));
    return ret;
}

QMap<QString, QList<int> > FuzzyCMeansAlgorithm::getParametersTypeList() const {
    QMap<QString, QList<int> > ret;
    ret.insert(QString("Max iterations"), QList<int>()<<Utils::_INT<<200);
    ret.insert(QString("Number of Cluster"), QList<int>()<<Utils::_INT<<10);
    ret.insert(QString("Fuzzy Index"), QList<int>()<<Utils::_INT<<2);


    return ret;
}

QVector< QMap<char, QString> > FuzzyCMeansAlgorithm::getParametersOfTypeChoice() const {
    QVector< QMap<char, QString> > ret;

    return ret;
}

QStringList FuzzyCMeansAlgorithm::testParameters(const QStringList& pars) const
{
    QStringList ret;

    QMap<QString, QList<int> > parsList = getParametersTypeList();
    if(pars.size() < parsList.size()) {
        ret.append("Parameters Error!");
    }
    else {
        QMapIterator<QString, QList<int> > it(parsList);
        int iInt = 0;
        for(int i=0; i<pars.size(); ++i) {
            it.next();
            if(it.value().at(0) == Utils::_INT) {
                if(pars.at(i).isEmpty()) ret.append(it.key()+" is required.");
                if(pars.at(i).toInt() < minMaxArray.at(iInt)[0] || pars.at(i).toInt() > minMaxArray.at(iInt)[1]) ret.append(it.key()+" must be between "+QString::number(minMaxArray.at(iInt)[0])+" and "+QString::number(minMaxArray.at(iInt)[1])+".");
                iInt++;
            }
        }
    }

    return ret;
}

FuzzyCMeansAlgorithm::~FuzzyCMeansAlgorithm()
{
    delete arIt;
    delete arIndex;
    delete arClust;
    delete arrayPixel;
}

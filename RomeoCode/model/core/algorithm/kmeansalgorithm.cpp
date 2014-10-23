#include "kmeansalgorithm.h"
#include "utils.h"

using Romeo::Model::Core::Algorithm::KMeansAlgorithm;
using Romeo::Model::Core::RGBImage2D;
using Romeo::Model::Core::RGBImage3D;
using Romeo::Model::Core::RomeoObject;
using Romeo::Model::Core::InternalData;
using Romeo::Model::Core::InternalData3D;
using Romeo::Model::Core::InternalData2D;
using Romeo::Model::Core::Video2D;
using Romeo::Model::Core::Video3D;
using namespace cv;

KMeansAlgorithm::KMeansAlgorithm(int idAlg)
    : AAlgorithm(Utils::ALGORITHM_KMEANS, idAlg), distance('e'), maxIteration(100),
      numberOfCluster(10), numberOfReplicates(5), arIt(new int[2]),
      arClust(new int[2]), arReplic(new int[2])
{
    generateArrays();
}

KMeansAlgorithm::KMeansAlgorithm(const QStringList& parameters, int idAlg)
    : AAlgorithm(Utils::ALGORITHM_KMEANS, idAlg), distance('e'), maxIteration(100),
      numberOfCluster(10), numberOfReplicates(5), arIt(new int[2]),
      arClust(new int[2]), arReplic(new int[2])
{
    generateArrays();

    if(parameters.size()>0)
        setParameters(parameters);
}

void KMeansAlgorithm::generateArrays()
{
    arIt[0] = 2;
    arIt[1] = 500;
    arClust[0] = 2;
    arClust[1] = 20;
    arReplic[0] = 1;
    arReplic[1] = 20;
    minMaxArray.append(arIt);
    minMaxArray.append(arClust);
    minMaxArray.append(arReplic);
}

RomeoObject* KMeansAlgorithm::execute2DAnalysis(RGBImage2D *image)
{
    Mat src = itk::OpenCVImageBridge::ITKImageToCVMat<RGBImage2D::RGBImageType>(image->getImage());

    Mat samples(src.rows * src.cols, 5, CV_32F);
    for( int y = 0; y < src.rows; y++ )
      for( int x = 0; x < src.cols; x++ )
        for( int z = 0; z < 3; z++)
          samples.at<float>(y + x*src.rows, z) = src.at<Vec3b>(y,x)[z];

    int clusterCount = this->getNumberOfCluster();
    Mat labels;
    int attempts = this->getMaxIteration();
    Mat centers;

    cv::kmeans(samples, clusterCount, labels,
                       TermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 10, 1.0),
                       attempts, KMEANS_PP_CENTERS, centers);

    Mat new_image( src.size(), src.type() );
    for( int y = 0; y < src.rows; y++ )
      for( int x = 0; x < src.cols; x++ )
      {
        int cluster_idx = labels.at<int>(y + x*src.rows,0);
        new_image.at<Vec3b>(y,x)[0] = centers.at<float>(cluster_idx, 0);
        new_image.at<Vec3b>(y,x)[1] = centers.at<float>(cluster_idx, 1);
        new_image.at<Vec3b>(y,x)[2] = centers.at<float>(cluster_idx, 2);
      }
    image->setImage(itk::OpenCVImageBridge::CVMatToITKImage<RGBImage2D::RGBImageType>(new_image));
    return image;
}

RomeoObject* KMeansAlgorithm::execute3DAnalysis(RGBImage3D *image)
{

    InternalData3D* data = image->getGreyScaleImage();

    typedef itk::ScalarImageKmeansImageFilter<RGBImage3D::ImageType,RGBImage3D::ImageType> KMeanFilterType;

    KMeanFilterType::Pointer kmean = KMeanFilterType::New();
    kmean->SetCoordinateTolerance(2);
    int numberOfClasses = getNumberOfCluster();
    for(int i = 0; i<numberOfClasses; ++i)
        kmean->AddClassWithInitialMean((i+20)%255);

    kmean->SetInput(data->getImage());
    kmean->Update();

    data->setImage(kmean->GetOutput());

    RGBImage3D* output = new RGBImage3D(data);
    return output;
}

RomeoObject* KMeansAlgorithm::execute2DVideoAnalysis(Video2D *video)
{
    int nFrames = video->getNumberOfFrames();
    InternalData2D* frame = video->getFrame(nFrames/2);
    RGBImage2D* rgbFrame = new RGBImage2D(frame);


    RomeoObject* output = execute2DAnalysis(rgbFrame);
    return output;
}

RomeoObject* KMeansAlgorithm::execute3DVideoAnalysis(Video3D *video)
{
    int nFrames = video->getNumberOfFrames();
    InternalData3D* frame = video->getFrame(nFrames/2);
    RGBImage3D* rgbFrame = new RGBImage3D(frame);


    RomeoObject* output = execute3DAnalysis(rgbFrame);
    return output;
}

int KMeansAlgorithm::getNumberOfCluster() const
{
    return numberOfCluster;
}

int KMeansAlgorithm::getNumberOfReplicates() const
{
    return numberOfReplicates;
}

int KMeansAlgorithm::getMaxIteration() const
{
    return maxIteration;
}

char KMeansAlgorithm::getDistance() const
{
    return distance;
}

void KMeansAlgorithm::setParameters(const QStringList& pars) {
    distance = pars.at(0).toStdString().c_str()[0];
    maxIteration = pars.at(1).toInt();
    numberOfCluster = pars.at(2).toInt();
    numberOfReplicates = pars.at(3).toInt();
}

QStringList KMeansAlgorithm::getParameters() const
{
    QStringList ret;
    ret.append(QString(distance));
    ret.append(QString::number(maxIteration));
    ret.append(QString::number(numberOfCluster));
    ret.append(QString::number(numberOfReplicates));
    return ret;
}

QMap<QString, QList<int> > KMeansAlgorithm::getParametersTypeList() const {
    QMap<QString, QList<int> > ret;

    ret.insert(QString("Distance"), QList<int>()<<Utils::_CHOICE<<'e');
    ret.insert(QString("Max iterations"), QList<int>()<<Utils::_INT<<100);
    ret.insert(QString("Number of Cluster"), QList<int>()<<Utils::_INT<<10);
    ret.insert(QString("Number of Replicates"), QList<int>()<<Utils::_INT<<5);
    return ret;
}

QVector< QMap<char, QString> > KMeansAlgorithm::getParametersOfTypeChoice() const {
    QVector< QMap<char, QString> > ret;
    QMap<char, QString> dist;

    dist.insert('e', QString("Euclidean distance"));
    dist.insert('c', QString("Correlation"));
    dist.insert('a', QString("Absolute value of the correlation"));
    dist.insert('u', QString("Uncentered correlation"));
    dist.insert('x', QString("Absolute uncentered correlation"));
    dist.insert('s', QString("Spearman's rank correlation"));
    dist.insert('k', QString("Kendall's τ"));
    dist.insert('b', QString("City-block distance"));

    ret.append(dist);

    return ret;
}

QStringList KMeansAlgorithm::testParameters(const QStringList &pars) const
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

KMeansAlgorithm::~KMeansAlgorithm()
{
    //deallocate the array from the heap
    delete arIt;
    delete arClust;
    delete arReplic;
}

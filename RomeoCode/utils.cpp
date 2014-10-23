#include "utils.h"

QImage *getImage3DVideo(const QString &path)
{
    QImage* image = 0;

    if(path.endsWith(".nii") || path.endsWith(".hdr")) {
        if(check3DVideo(path))
            image = get3DtFrom(path);
        else
            image = get3DFrom(path);
    }
    else if(path.endsWith(".avi") || path.endsWith(".mpg")) {
        image = get2DtFrom(path);
    }

    return image;
}

QImage *get2DtFrom(const QString &path)
{
    QImage* image = 0;

    typedef itk::RGBPixel<float> RGBPixel;
    typedef itk::Image<RGBPixel,2> imageType;

    cv::VideoCapture vidCap(path.toStdString());

    cv::Mat frame;
    for (int i=0; i<5;i++){
        vidCap.read(frame);
    }

    imageType::Pointer imageItk=itk::OpenCVImageBridge::CVMatToITKImage< imageType >( frame );

    imageType::SizeType size = imageItk->GetBufferedRegion().GetSize();
    int width    = size[0];
    int height    = size[1];

    image=new QImage(width, height,QImage::Format_RGB32);
    typedef itk::ImageLinearIteratorWithIndex<imageType> IteratorType;
    IteratorType it(imageItk,imageItk->GetBufferedRegion());
    it.SetDirection(1);
    it.GoToBegin();
    for (int i=0; i<width; i++){
        for (int j=0; j<height; j++){
            image->setPixel(i,j, qRgb(it.Get().GetRed(), it.Get().GetGreen(), it.Get().GetBlue()));
            ++it;
        }
        it.NextLine();
    }

    return image;
}

QImage *get3DFrom(const QString &path)
{
    QImage* image = 0;

    typedef itk::Image<itk::RGBPixel<unsigned char>,3> imageType;
    itk::ImageFileReader<imageType>::Pointer fileReader  = itk::ImageFileReader<imageType>::New();

    fileReader->SetFileName(path.toStdString().c_str());
    fileReader->Update();

    imageType::Pointer imageItk = fileReader->GetOutput();

    imageType::SizeType size = imageItk->GetBufferedRegion().GetSize();
    int width = size[0];
    int height = size[1];

    image = new QImage(width, height,QImage::Format_RGB32);
    typedef itk::ImageLinearIteratorWithIndex<imageType> IteratorType;
    IteratorType it(imageItk,imageItk->GetBufferedRegion());
    imageType::IndexType index;
    index[0]=0;
    index[1]=0;
    index[2]=size[2]/2;
    it.SetDirection(1);
    it.SetIndex(index);
    for (int i=0; i<width; i++){
        for (int j=0; j<height; j++){
            image->setPixel(i,height-j-1, qRgb(it.Get().GetRed(), it.Get().GetGreen(), it.Get().GetBlue()));
            ++it;
        }
        it.NextLine();
    }

    return image;
}

QImage *get3DtFrom(const QString &path)
{
    QImage* image = 0;

    typedef itk::Image<itk::RGBPixel<unsigned char>,4> imageType;
    itk::ImageFileReader<imageType>::Pointer fileReader = itk::ImageFileReader<imageType>::New();

    fileReader->SetFileName(path.toStdString().c_str());
    fileReader->Update();


    imageType::Pointer imageItk = fileReader->GetOutput();

    imageType::SizeType size = imageItk->GetBufferedRegion().GetSize();
    int width = size[0];
    int height = size[1];

    image = new QImage(width, height,QImage::Format_RGB32);
    typedef itk::ImageLinearIteratorWithIndex<imageType> IteratorType;
    IteratorType it(imageItk,imageItk->GetBufferedRegion());
    it.GoToBegin();
    for (int i=0; i<width; i++){
        for (int j=0; j<height; j++){
            imageType::IndexType index;
            index[0]=i;
            index[1]=j;
            index[2]=size[2]/2;
            index[3]=size[3]/2;
            it.SetIndex(index);
            image->setPixel(i,height-j-1, qRgb(it.Get().GetRed(), it.Get().GetGreen(), it.Get().GetBlue()));
        }
    }

    return image;
}

bool check3DVideo(const QString &path)
{
    bool ret = false;

    typedef itk::Image<float,4> ImageType;
    typedef itk::ImageFileReader<ImageType> readerType;

    readerType::Pointer reader = readerType::New();
    reader->SetFileName(path.toStdString());
    reader->Update();
    ImageType::Pointer imageRead = reader->GetOutput();
    ImageType::SizeType size=imageRead->GetBufferedRegion().GetSize();

    if(size[3]>1)
      ret = true;

    return ret;
}

bool checkPathExistsFromHome(const QString& path)
{
    QDir dir(QDir::homePath());
    return dir.mkpath(path);
}

bool copyDir(const QString source, const QString destination, const bool override) {
    QDir directory(source);
    bool error = false;

    if (!directory.exists()) {
        return false;
    }

    QStringList dirs = directory.entryList(QDir::AllDirs | QDir::Hidden | QDir::NoDotAndDotDot);
    QStringList files = directory.entryList(QDir::Files | QDir::Hidden);

    QList<QString>::iterator d,f;

    for (d = dirs.begin(); d != dirs.end(); ++d) {

        if (!QFileInfo(directory.path() + "/" + (*d)).isDir()) {
            continue;
        }

        QDir temp(destination + "/" + (*d));
        temp.mkpath(temp.path());

        if (!copyDir(directory.path() + "/" + (*d), destination + "/" + (*d), override)) {
            error = true;
        }
    }

    for (f = files.begin(); f != files.end(); ++f) {
        QFile tempFile(directory.path() + "/" + (*f));


        if (QFileInfo(directory.path() + "/" + (*f)).isDir()) {
            continue;
        }

        QFile destFile(destination + "/" + directory.relativeFilePath(tempFile.fileName()));

        if (destFile.exists() && override) {
            destFile.remove();
        }

        if (!tempFile.copy(destination + "/" + directory.relativeFilePath(tempFile.fileName()))) {
            error = true;

        }
    }


    return !error;
}

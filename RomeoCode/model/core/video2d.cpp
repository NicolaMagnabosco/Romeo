#include "video2d.h"

using Romeo::Model::Core::Video2D;
using Romeo::Model::Util::ReaderModel::Reader;
using Romeo::Model::Core::InternalData2D;




Video2D::Video2D(const QString &fileN, const QString &mask, bool hasMask) : Video(fileN)

{
    // fill the vector with frames
    QVector<Reader::Image2DType::Pointer> video = reader->read2D(fileName);
    for(int i=0; i<video.size(); ++i){
        Reader::Image2DType::Pointer frame = video.at(i);
        InternalData2D* img = new InternalData2D();
        img->setImage(frame);
        originalVideo.append(img);
    }

    if(hasMask){
        maskImage(mask);
    }
}

void Video2D::maskImage(const QString &mask)
{

    MaskImageFilterType::Pointer maskFilter = MaskImageFilterType::New();
    maskFilter->SetCoordinateTolerance(10);
    maskFilter->SetDirectionTolerance(10);


    ImageType::Pointer maskImage = reader->read2D(mask).first();

    maskFilter->SetMaskImage(maskImage);

    for(int i=0; i<originalVideo.size(); ++i){
        maskFilter->SetInput(originalVideo.at(i)->getImage());
        maskFilter->Update();
        originalVideo.at(i)->getImage() = maskFilter->GetOutput();
    }


}

int Video2D::getXSize() const{
    return originalVideo.first()->getXSize();
}

int Video2D::getYSize() const{
    return originalVideo.first()->getYSize();
}

int Video2D::getNumberOfFrames() const
{
    return originalVideo.size();
}

InternalData2D *Video2D::getFrame(int i) const
{
    return originalVideo.at(i);
}

Video2D::~Video2D()
{
    for(int i=0; i<originalVideo.size(); ++i){
        delete originalVideo.at(i);
    }
}

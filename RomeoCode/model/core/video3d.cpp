#include "video3d.h"

using Romeo::Model::Core::Video3D;
using Romeo::Model::Util::ReaderModel::Reader;
using Romeo::Model::Core::InternalData3D;



Video3D::Video3D(const QString &fileN, const QString &mask, bool hasMask) : Video(fileN)

{
    // fill the vector with frames
    QVector<Reader::Image3DType::Pointer> video = reader->read3D(fileName);
    for(int i=0; i<video.size(); ++i){
        Reader::Image3DType::Pointer frame = video.at(i);
        InternalData3D* img = new InternalData3D();
        img->setImage(frame);
        originalVideo.append(img);

    }

    if(hasMask){
        maskImage(mask);
    }
}

void Video3D::maskImage(const QString &mask)
{
    MaskImageFilterType::Pointer maskFilter = MaskImageFilterType::New();
    maskFilter->SetCoordinateTolerance(10);
    maskFilter->SetDirectionTolerance(10);


    ImageType::Pointer maskImage = reader->read3D(mask).first();

    maskFilter->SetMaskImage(maskImage);

    for(int i=0; i<originalVideo.size(); ++i){
        maskFilter->SetInput(originalVideo.at(i)->getImage());
        maskFilter->Update();
        originalVideo.at(i)->getImage() = maskFilter->GetOutput();
    }


}

int Video3D::getXSize() const{
    return originalVideo.first()->getXSize();
}

int Video3D::getYSize() const{
    return originalVideo.first()->getYSize();
}

int Video3D::getZSize() const{
    return originalVideo.first()->getZSize();
}


int Video3D::getNumberOfFrames() const
{
    return originalVideo.size();
}

InternalData3D *Video3D::getFrame(int i) const
{
    return originalVideo.at(i);
}

Video3D::~Video3D()
{
    for(int i=0; i<originalVideo.size(); ++i){
        delete originalVideo.at(i);
    }
}

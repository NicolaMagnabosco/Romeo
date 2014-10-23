#include "firstorderfeature.h"

using Romeo::Model::Core::Feature::FirstOrderFeature;
using Romeo::Model::Core::Feature::AFeature;
using Romeo::Model::Core::InternalData2D;
using Romeo::Model::Core::InternalData3D;
using Romeo::Model::Core::RGBImage2D;
using Romeo::Model::Core::RGBImage3D;
using Romeo::Model::Core::RomeoObject;

FirstOrderFeature::FirstOrderFeature(const QString &name, int idFeat): AFeature(name, idFeat), windowSize(3), type(Utils::FEATURE_FIRST_ORDER){

}

FirstOrderFeature::FirstOrderFeature(const QString& name, const QStringList& parameters, int idFeat)
    : AFeature(name, idFeat), type(Utils::FEATURE_FIRST_ORDER)
{
    windowSize = parameters.at(0).toInt();
}

RomeoObject *FirstOrderFeature::executeAnalysis(RomeoObject *image)
{
    if (dynamic_cast<RGBImage2D*>(image))
        return execute2DAnalysis(dynamic_cast<RGBImage2D*>(image));
    if (dynamic_cast<RGBImage3D*>(image))
       return execute3DAnalysis(dynamic_cast<RGBImage3D*>(image));

    return 0;
}

RGBImage2D *FirstOrderFeature::execute2DAnalysis(RGBImage2D* image)
{
    RGBImage2D* output=new RGBImage2D(*image);

    InternalData2D* red = dynamic_cast<InternalData2D*>(output->getRedImage());
    InternalData2D* green = dynamic_cast<InternalData2D*>(output->getGreenImage());
    InternalData2D* blue = dynamic_cast<InternalData2D*>(output->getBlueImage());

    if(red && green && blue){
       red->setImage(singleChannelEXecution2D(red)->getImage());
       green->setImage(singleChannelEXecution2D(green)->getImage());
       blue->setImage(singleChannelEXecution2D(blue)->getImage());
   }
    output->RGBMerger();

    return output;
}

RGBImage3D * FirstOrderFeature:: execute3DAnalysis(RGBImage3D *image)
{
    InternalData3D* greyImage = image->getGreyScaleImage();
    RGBImage3D* output = new RGBImage3D(singleChannelEXecution3D(greyImage));

    return output;
}

QStringList FirstOrderFeature::getParameters() const
{
    return QStringList(QString::number(windowSize));
}

int FirstOrderFeature::getWindowSize() const
{
    return windowSize;
}

FirstOrderFeature::~FirstOrderFeature()
{

}

QString FirstOrderFeature::getType() const
{
    return type;
}

void FirstOrderFeature::setParemeters(const QStringList& params) {
    windowSize = params.at(0).toInt();
}

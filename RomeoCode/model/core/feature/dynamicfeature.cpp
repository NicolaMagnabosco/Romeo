#include "dynamicfeature.h"

using Romeo::Model::Core::Feature::DynamicFeature;
using Romeo::Model::Core::Feature::AFeature;
using Romeo::Model::Core::RomeoObject;
using Romeo::Model::Core::Video2D;
using Romeo::Model::Core::Video3D;

DynamicFeature::DynamicFeature(const QString& name,int idFeat): AFeature(name,idFeat),type(Utils::FEATURE_DYNAMIC){

}

DynamicFeature::DynamicFeature(const QString& name, const QStringList& parameters, int idFeat): AFeature(name, idFeat), initialFrame(1), endFrame(0),type(Utils::FEATURE_DYNAMIC)
{
    initialFrame = parameters.at(0).toInt();
    endFrame = parameters.at(1).toInt();
}

RomeoObject* DynamicFeature:: executeAnalysis(RomeoObject *image){
    if (dynamic_cast<Video2D*>(image))
        return execute2DAnalysis(dynamic_cast<Video2D*>(image));
    if (dynamic_cast<Video3D*>(image)){
        return execute3DAnalysis(dynamic_cast<Video3D*>(image));
    }
    return 0;
}

int DynamicFeature::getInitialFrame() const {

    return initialFrame;
}

int DynamicFeature::getEndFrame() const {

    return endFrame;
}

QStringList DynamicFeature::getParameters() const {
    QStringList ret;
    ret.append(QString::number(initialFrame));
    ret.append(QString::number(endFrame));
    return ret;
}

void DynamicFeature::setEndFrame(int last){
    endFrame=last;
}

void DynamicFeature::setParemeters(const QStringList& params) {
    initialFrame = params.at(0).toInt();
    endFrame=params.at(1).toInt();
}


QString DynamicFeature::getType() const{
    return type;
}

DynamicFeature::~DynamicFeature()
{

}



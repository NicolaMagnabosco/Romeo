#include "aalgorithm.h"

using Romeo::Model::Core::Algorithm::AAlgorithm;
using Romeo::Model::Core::InternalData;
using Romeo::Model::Core::InternalData2D;
using Romeo::Model::Core::RGBImage;
using Romeo::Model::Core::RGBImage2D;
using Romeo::Model::Core::RGBImage3D;
using Romeo::Model::Core::RomeoObject;
using Romeo::Model::Core::Video2D;
using Romeo::Model::Core::Video3D;

AAlgorithm::AAlgorithm(const QString& algorithmName, int algorithmId): name(algorithmName), id(algorithmId)
{

}

QString AAlgorithm::getName() const
{
    return name;
}

int AAlgorithm::getId() const
{
    return id;
}

void AAlgorithm::setId(int i)
{
    id = i;
}

RomeoObject* AAlgorithm::executeAnalysis(RomeoObject *image)
{
    if (dynamic_cast<RGBImage2D*>(image))
        return execute2DAnalysis(dynamic_cast<RGBImage2D*>(image));
    if (dynamic_cast<RGBImage3D*>(image))
        return execute3DAnalysis(dynamic_cast<RGBImage3D*>(image));
    if (dynamic_cast<Video2D*>(image))
        return execute2DVideoAnalysis(dynamic_cast<Video2D*>(image));
    if (dynamic_cast<Video3D*>(image))
        return execute3DVideoAnalysis(dynamic_cast<Video3D*>(image));
    return 0;
}


AAlgorithm::~AAlgorithm()
{

}

QVector< QMap<char, QString> > AAlgorithm::getParametersOfTypeChoice() const
{
    return QVector< QMap<char, QString> >();
}

QString AAlgorithm::getKeyComboBox(int i, const QString& txt) const
{
    QString ret;
    QVector< QMap<char, QString> > vector = getParametersOfTypeChoice();

    if(i<vector.size())
        ret = vector.at(i).key(txt);

    return ret;
}

QString AAlgorithm::getValueComboBox(int i, const QString& txt) const
{
    QString ret;
    QVector< QMap<char, QString> > vector = getParametersOfTypeChoice();

    if(i<vector.size())
        ret = vector.at(i).value(txt.toStdString().c_str()[0]);

    return ret;
}

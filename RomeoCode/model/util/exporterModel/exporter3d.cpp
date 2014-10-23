#include "exporter3d.h"

using Romeo::Model::Util::ExporterModel::Exporter3D;
using Romeo::Model::Core::RGBImage;
using Romeo::Model::Core::RGBImage3D;



Exporter3D::Exporter3D(): Exporter(), writer(WriterType::New())
{

}


void Exporter3D::exportFile(const QString &file, RGBImage* image) const {

    RGBImage3D* image3D=dynamic_cast<RGBImage3D*>(image);
    if (image3D){
        writer->SetFileName(file.toStdString().c_str());
        writer->SetInput(image3D->getImage());
        writer->UpdateLargestPossibleRegion();
        writer->Update();
    }
}

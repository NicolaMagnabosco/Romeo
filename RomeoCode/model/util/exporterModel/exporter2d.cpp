#include "exporter2d.h"

using Romeo::Model::Util::ExporterModel::Exporter2D;
using Romeo::Model::Core::RGBImage;


Exporter2D::Exporter2D() : Exporter(), writer(WriterType::New()) {

}

void Exporter2D::exportFile(const QString &file, RGBImage* image) const {


    RGBImage2D* image2D = dynamic_cast<RGBImage2D*>(image);
    if (image2D){
        writer->SetFileName(file.toStdString().c_str());
        writer->SetInput(image2D->getImage());
        writer->Update();
    }
}

#ifndef ROMEO_MODEL_UTIL_EXPORTERMODEL_EXPORTER3D_H
#define ROMEO_MODEL_UTIL_EXPORTERMODEL_EXPORTER3D_H

#include "model/util/exporterModel/exporter.h"
#include "model/core/rgbimage3d.h"

using Romeo::Model::Util::ExporterModel::Exporter;
using Romeo::Model::Core::RGBImage;
using Romeo::Model::Core::RGBImage3D;
/*!
 *\file exporter3d.h
 *\author Scapin Davide (davideskap@gmail.com)
 *\date 2013-03-09
*/
/*
*Changes:
*+----------+------------+-----------------+-----------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                       Changes                       +       Description         |
*+----------+------------+-----------------+-----------------------------------------------------+---------------------------+
*|          |            |                 |                                                     |                           |
*|   0.0.1  | 2013-03-09 |  Scapin Davide  |       Romeo::Model::Core::Feature::Exporter3D       |   First version of class  |
*|          |            |                 |                                                     |                           |
*+----------+------------+-----------------+-----------------------------------------------------+---------------------------+
*/
namespace Romeo {
    namespace Model {
        namespace Util {
            namespace ExporterModel {

                typedef itk::ImageFileWriter< RGBImage3D::RGBImageType > WriterType;
            /*!
             * \brief The Exporter class represents the data exporter object.
             */
                class Exporter3D : public Exporter
                {
                private:
                    /*!
                      * \brief writer is the object that write the image on the filesystem.
                      */
                    WriterType::Pointer writer;
                public:
                    /*!
                    * \brief Exporter2D default constructor.
                    */
                    Exporter3D();
                    /*!
                     * \brief exportFile exports the data in the filesystem.
                     * \param file is the filesystem path.
                     * \param image is the exported data.
                     */
                    virtual void exportFile(const QString &file, RGBImage* image) const;
                };

            } // namespace ExporterModel
        } // namespace Util
    } // namespace Model
} // namespace Romeo

#endif // ROMEO_MODEL_UTIL_EXPORTERMODEL_EXPORTER3D_H

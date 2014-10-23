#ifndef ROMEO_MODEL_UTIL_EXPORTERMODEL_EXPORTER2D_H
#define ROMEO_MODEL_UTIL_EXPORTERMODEL_EXPORTER2D_H

#include <QString>
#include "itkObject.h"
#include "model/util/exporterModel/exporter.h"
#include "model/core/rgbimage2d.h"

using Romeo::Model::Util::ExporterModel::Exporter;
using Romeo::Model::Core::RGBImage;
using Romeo::Model::Core::RGBImage2D;
/*!
 *\file exporter2d.h
 *\author Scapin Davide (davideskap@gmail.com)
 *\date 2013-03-09
*/
/*
*Changes:
*+----------+------------+-----------------+-----------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                       Changes                       +       Description         |
*+----------+------------+-----------------+-----------------------------------------------------+---------------------------+
*|          |            |                 |                                                     |                           |
*|   0.0.1  | 2013-03-09 |  Scapin Davide  |       Romeo::Model::Core::Feature::Exporter2D       |   First version of class  |
*|          |            |                 |                                                     |                           |
*+----------+------------+-----------------+-----------------------------------------------------+---------------------------+
*/
typedef itk::ImageFileWriter< RGBImage2D::RGBImageType> WriterType;

namespace Romeo {
    namespace Model {
        namespace Util {
            namespace ExporterModel {
                /*!
                 * \brief The Exporter class represents the data exporter object.
                 */
                class Exporter2D : public Exporter
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
                    Exporter2D();
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

#endif // ROMEO_MODEL_UTIL_EXPORTERMODEL_EXPORTER2D_H

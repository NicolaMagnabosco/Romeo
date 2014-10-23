#ifndef ROMEO_MODEL_UTIL_EXPORTERMODEL_EXPORTER_H
#define ROMEO_MODEL_UTIL_EXPORTERMODEL_EXPORTER_H

#include <QString>
#include "itkImageFileWriter.h"
#include "itkDataObject.h"
#include "itkObject.h"
#include "model/core/rgbimage.h"

using Romeo::Model::Core::RGBImage;
/*!
 *\file exporter.h
 *\author Scapin Davide (davideskap@gmail.com)
 *\date 2013-03-09
*/
/*
*Changes:
*+----------+------------+-----------------+-----------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                       Changes                       +       Description         |
*+----------+------------+-----------------+-----------------------------------------------------+---------------------------+
*|          |            |                 |                                                     |                           |
*|   0.0.1  | 2013-03-09 |  Scapin Davide  | Romeo::Model::Core::Util::ReaderModel::Exporter     |   First version of class  |
*|          |            |                 |                                                     |                           |
*+----------+------------+-----------------+-----------------------------------------------------+---------------------------+
*/
namespace Romeo {

    namespace Model {

        namespace Util {

            namespace ExporterModel {
                /*!
                 * \brief The Exporter class represents the data exporter object
                 */
                class Exporter
                {
                 protected:
                    /*!
                     * \brief Exporter object constructor.
                     */
                    Exporter();
                 public:
                    typedef itk::RGBPixel<unsigned char> RGBPixel;
                    typedef itk::Image<RGBPixel,2> RGBImageType2D;
                    /*!
                     * \brief exportFile exports the data in the filesystem.
                     * \param file is the filesystem path.
                     * \param image is the exported data.
                     */
                    virtual void exportFile(const QString& file, RGBImage* image) const=0;
                    /*!
                     * \brief ~Exporter deletes Exporter class.
                     */
                    virtual ~Exporter();
                };

            } // namespace ExporterModel
        } // namespace Util
    } // namespace Model
} // namespace Romeo

#endif // ROMEO_MODEL_UTIL_EXPORTERMODEL_EXPORTER_H

#ifndef ROMEO_MODEL_CORE_ALGORITHM_IALGORITHM_H
#define ROMEO_MODEL_CORE_ALGORITHM_IALGORITHM_H

#include "itkObject.h"
#include "model/core/internaldata.h"
#include "model/core/internaldata2d.h"
#include "model/core/internaldata3d.h"
#include "model/core/feature/meandynamicfeature.h"
#include "model/core/rgbimage.h"
#include "model/core/rgbimage2d.h"
#include "model/core/rgbimage3d.h"
#include "model/core/video.h"
#include "model/core/video2d.h"
#include "model/core/video3d.h"
#include "model/core/romeoobject.h"
#include <QString>
#include <QStringList>
#include "utils.h"
#include <QMap>

using Romeo::Model::Core::InternalData;
using Romeo::Model::Core::InternalData2D;
using Romeo::Model::Core::InternalData3D;
using Romeo::Model::Core::RGBImage;
/*!
 *\file aalgorithm.h
 *\author Magnabosco Nicola (nick.magnabosco@gmail.com)
 *\date 2013-04-01
*/
/*
*Changes:
*+----------+------------+---------------- +------------------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                             Changes                        +       Description         |
*+----------+------------+-----------------+------------------------------------------------------------+---------------------------+
*|                                                                                                                                  |
*|   0.0.1  | 2013-04-01 |Magnabosco Nicola|    Romeo::Model::Core::Algorithm::AAlgorithm               |   First version of class  |
*|                                                                                                                                  |
*+----------+------------+-----------------+------------------------------------------------------------+---------------------------+
*/

namespace Romeo {
    namespace Model {
        namespace Core {
            namespace Algorithm {
            /*!
                 * \brief The AAlgorithm class represents a cluster algorithm in Romeo.
                 */
                class AAlgorithm
                {
                private:
                    /*!
                     * \brief name is the algorithm name.
                     */
                    QString name;
                    /*!
                     * \brief id is the identification code of algorithm
                     */
                    int id;
                protected:
                    /*!
                     * \brief execute2DAnalysis execute the algorithm on 2D images.
                     * \param image is the input image.
                     * \return the output image.
                     */
                    virtual RomeoObject* execute2DAnalysis(RGBImage2D* image) =0;
                    /*!
                     * \brief execute3DAnalysis execute the algorithm on 3D images.
                     * \param image is the input image.
                     * \return the output image.
                     */
                    virtual RomeoObject* execute3DAnalysis(RGBImage3D *image) =0;
                    /*!
                     * \brief execute2DVideoAnalysis execute the algorithm on 2D videos.
                     * \param video is the input video.
                     * \return the output image.
                     */
                    virtual RomeoObject* execute2DVideoAnalysis(Video2D* video) =0;
                    /*!
                     * \brief execute3DVideoAnalysis execute the algorithm on 3D videos.
                     * \param video is the input video.
                     * \return the output image.
                     */
                    virtual RomeoObject* execute3DVideoAnalysis(Video3D* video) =0;
                public:
                    /*!
                     * \brief AAlgorithm Constructor of the class.
                     * \param algorithmName is the name of the algorithm.
                     * \param algorithmId is the id code of the algorithm.
                     */
                    AAlgorithm(const QString& algorithmName, int algorithmId = -1);
                    /*!
                     * \brief getParameters gets the parameters of the algorithm.
                     * \return the parameters of the algorithm.
                     */
                    virtual QStringList getParameters() const =0;
                    /*!
                     * \brief setParameters sets the parameters of the algorithm.
                     * \param is the parameters of the algorithm.
                     */
                    virtual void setParameters(const QStringList& pars) =0;
                    /*!
                     * \brief getName gets algorithm's name.
                     * \return algorithm's name.
                     */
                    virtual QString getName() const;
                    /*!
                     * \brief getId gets algorithm's id code.
                     * \return algorithm's id code.
                     */
                    int getId() const;
                    /*!
                     * \brief setId sets algorithm's id code.
                     * \param i is algorithm's id code.
                     */
                    void setId(int i);
                    /*!
                     * \brief executeAnalysis execute Algorithm analysis.
                     * \param image is the input data.
                     * \return the output data.
                     */
                    RomeoObject* executeAnalysis(RomeoObject *image);
                    /*!
                     * \brief ~AAlgorithm delete object.
                     */
                    virtual ~AAlgorithm();

                    virtual QMap<QString, QList<int> > getParametersTypeList() const =0;
                    virtual QVector< QMap<char, QString> > getParametersOfTypeChoice() const;
                    virtual QString getKeyComboBox(int i, const QString& txt) const;
                    virtual QString getValueComboBox(int i, const QString& txt) const;
                    virtual QStringList testParameters(const QStringList& pars) const =0;
                };

            } // namespace Algorithm
        } // namespace Core
    } // namespace Model
} // namespace Romeo

#endif // ROMEO_MODEL_CORE_ALGORITHM_IALGORITHM_H

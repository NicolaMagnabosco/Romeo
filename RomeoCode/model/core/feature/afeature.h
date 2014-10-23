#ifndef ROMEO_MODEL_CORE_FEATURE_IFEATURE_H
#define ROMEO_MODEL_CORE_FEATURE_IFEATURE_H

#include "itkObject.h"
#include "model/core/internaldata.h"
#include "model/core/internaldata2d.h"
#include "model/core/internaldata3d.h"
#include "model/core/rgbimage.h"
#include "model/core/rgbimage2d.h"
#include "model/core/rgbimage3d.h"
#include "model/core/video2d.h"
#include "model/core/video3d.h"
#include <QString>
#include <QStringList>
#include <QStringListIterator>
#include <math.h>
#include "utils.h"
#include<qthread.h>
#include "model/core/romeoobject.h"


using Romeo::Model::Core::InternalData;

/*!
 *\file afeature.h
 *\author Scapin Davide (davideskap@gmail.com)
 *\date 2013-03-07
*/
/*
*Changes:
*+----------+------------+-----------------+-----------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                       Changes                       +       Description         |
*+----------+------------+-----------------+-----------------------------------------------------+---------------------------+
*|          |            |                 |                                                     |                           |
*|   0.0.1  | 2013-03-07 |  Scapin Davide  |        Romeo::Model::Core::Feature::AFeature        |   First version of class  |
*|          |            |                 |                                                     |                           |
*+----------+------------+-----------------+-----------------------------------------------------+---------------------------+
*/

namespace Romeo {
    namespace Model {
        namespace Core {
            namespace Feature {
                /*!
                 * \brief DynamicFeature class represents the base class of all features.
                 *
                 */
                class AFeature //: public QThread
                {
                private:
                    /*!
                     * \brief name represents the name of the feature.
                     */
                    QString name;
                    /*!
                     * \brief id represent the id code of the feature.
                     */
                    int id;
                protected:
                    /*!
                     * \brief AFeature is the 1 or 2 parameters constructor of the class.
                     * \param featureName is the name of the feature.
                     * \param idFeat is the id code of the feature;the default value is -1.
                     */
                    AFeature(const QString &featureName, int idFeat = -1);
                public:
                    /*!
                     * \brief executeAnalysis is a pure method instantiate in concreate subclasses.
                     * \param image is the input data for the feature extractor
                     * \return the output data of the feature extractor
                     */
                    virtual RomeoObject* executeAnalysis(RomeoObject *image)=0;
                    /*!
                     * \brief getType is a pure method that return the type of the feature(2D,3D,2D-t,3D-t).
                     * \return a QString that indicates the type of the feature.
                     */
                    virtual QString getType() const =0;
                    /*!
                     * \brief getParameters is a pure method that return the parameters of the feature.
                     * \return a QString that conteins the parameters of the feature.
                     */
                    virtual QStringList getParameters() const =0;
                    /*!
                     * \brief setParemeters is a pure method that sets the parameters of the feature.
                     * \param params is a QString that conteins the parameters of the feature.
                     */
                    virtual void setParemeters(const QStringList& params) =0;
                    /*!
                     * \brief getName returns the name of the feature.
                     * \return a QString that conteins the name of the feature.
                     */
                    QString getName() const;
                    /*!
                     * \brief getId returns the id of the feature.
                     * \return the int id code of the feature.
                     */
                    int getId() const;
                    /*!
                     * \brief setId sets the id code of the feature.
                     * \param i int that represent the id code of the feature.
                     */
                    void setId(int i);
                    /*!
                     * \brief ~AFeature virtual desctructor of the AFeature object.
                     */
                    virtual ~AFeature();
                };

            } // namespace Feature
        } // namespace Core
    } // namespace Model
} // namespace Romeo

#endif // ROMEO_MODEL_CORE_FEATURE_IFEATURE_H

#ifndef ROMEO_MODEL_CORE_FEATURE_DYNAMICFEATURE_H
#define ROMEO_MODEL_CORE_FEATURE_DYNAMICFEATURE_H

#include "model/core/feature/afeature.h"
#include "utils.h"
#include <QString>
#include "model/core/video2d.h"
#include "model/core/video3d.h"

using Romeo::Model::Core::Feature::AFeature;

/*!
 *\file dynamicfeature.h
 *\author Scapin Davide (davideskap@gmail.com)
 *\date 2013-03-07
*/
/*
*Changes:
*+----------+------------+-----------------+-----------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                       Changes                       +       Description         |
*+----------+------------+-----------------+-----------------------------------------------------+---------------------------+
*|          |            |                 |                                                     |                           |
*|   0.0.1  | 2013-03-07 |  Scapin Davide  |    Romeo::Model::Core::Feature::DynamicFeature      |   First version of class  |
*|          |            |                 |                                                     |                           |
*+----------+------------+-----------------+-----------------------------------------------------+---------------------------+
*/

namespace Romeo {
    namespace Model {
        namespace Core {
            namespace Feature {
                /*!
                * \brief The DynamicFeature class represents the superclass of all dynamic features .
                */
                class DynamicFeature : public AFeature
                {
                protected:
                    /*!
                     * \brief initialFrame is the initial frame of the video.
                     */
                    int initialFrame;
                    /*!
                     * \brief endFrame is the last frame of the video.
                     */
                    int endFrame;
                    /*!
                     * \brief type is the type of the feature (2D-t,3D-t)
                     */
                    QString type;
                protected:
                    /*!
                     * \brief DynamicFeature is the 1 or 2 parameters constructor of the class.
                     * \param name is the name of the feature.
                     * \param idFeat is the id code of the feature;the default value is -1.
                     */
                    DynamicFeature(const QString& name,int idFeat = -1);
                    /*!
                     * \brief DynamicFeature is the 2 or 3 parameters constructor of the class.
                     * \param name is the name of the feature.
                     * \param parameters is a QString list that conteins feature's parameters.
                     * \param idFeat is the id code of the feature.
                     */
                    DynamicFeature(const QString& name,const QStringList& parameters, int idFeat = -1);
                public:
                    /*!
                     * \brief executeAnalysis executes the feature in 2D and 3D video.
                     * \param image is the input video of the feature.
                     * \return the output image of the feature.
                     */
                    virtual RomeoObject* executeAnalysis(RomeoObject *image);
                    /*!
                     * \brief execute2DAnalysis is the pure method that execute the feature on 2D video.
                     * \param video is the input video 2D of the feature.
                     * \return the output 2D RGB image of the feature.
                     */
                    virtual RGBImage2D* execute2DAnalysis(Video2D* video)=0;
                    /*!
                     * \brief execute3DAnalysis is the pure method that execute the feature on 2D video.
                     * \param video is the input video 3D of the feature.
                     * \return the output 3D RGB image of the feature.
                     */
                    virtual RGBImage3D* execute3DAnalysis(Video3D* video)=0;
                    /*!
                     * \brief getInitialFrame gets the initial frame of the video.
                     * \return the initial frame of the video.
                     */
                    int getInitialFrame() const;
                    /*!
                     * \brief getEndFrame gets the last frame of the video.
                     * \return the last frame of the video.
                     */
                    int getEndFrame() const;
                    /*!
                     * \brief setEndFrame sets the last frame of the video.
                     */
                    void setEndFrame(int last);
                    /*!
                     * \brief getParameters gets the parameters list values of the feature.
                     * \return the list of parameters values.
                     */
                    virtual QStringList getParameters() const;
                    /*!
                     * \brief setParemeters set the parameters of the feature.
                     * \param params list of the parameters.
                     */
                    virtual void setParemeters(const QStringList& params);
                    /*!
                     * \brief getType gets the type of the feature (2D-t,3D-t).
                     * \return the type of the feature.
                     */
                    virtual QString getType() const;
                    /*!
                     * \brief ~DynamicFeature is the virtual destructor of the class.
                     */
                    virtual ~DynamicFeature();
                };

            } // namespace Feature
        } // namespace Core
    } // namespace Model
} // namespace Romeo

#endif // ROMEO_MODEL_CORE_FEATURE_DYNAMICFEATURE_H

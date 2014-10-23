#ifndef ROMEO_MODEL_CORE_FEATURE_FIRSTORDERFEATURE_H
#define ROMEO_MODEL_CORE_FEATURE_FIRSTORDERFEATURE_H

#include "model/core/feature/afeature.h"
#include "utils.h"
#include <QString>

using Romeo::Model::Core::Feature::AFeature;

/*!
 *\file firstorderfeature.h
 *\author Magnabosco Nicola (nick.magnabosco@gmail.com)
 *\date 2013-03-07
*/
/*
*Changes:
*+----------+------------+-------------------+-----------------------------------------------------+---------------------------+
*|  Version +    Date    +    Programmer     +                       Changes                       +       Description         |
*+----------+------------+-------------------+-----------------------------------------------------+---------------------------+
*|          |            |                   |                                                     |                           |
*|   0.0.1  | 2013-03-07 | Magnabosco Nicola |   Romeo::Model::Core::Feature::FirstOrderFeature    |   First version of class  |
*|          |            |                   |                                                     |                           |
*+----------+------------+-------------------+-----------------------------------------------------+---------------------------+
*/

namespace Romeo {
    namespace Model {
        namespace Core {
            namespace Feature {

                /*!
                * \brief The FirsOrderFeature class represents the superclass of all first order features .
                */
                class FirstOrderFeature : public AFeature
                {
                private:
                    /*!
                     * \brief windowSize is the size of the window that iterate throught the data.
                     */
                    int windowSize;
                    /*!
                     * \brief type is the type of the feature (2D,3D)
                     */
                    QString type;
                protected:
                    /*!
                    * \brief FirstOrderFeature is the 1 or 2 parameters constructor of the class.
                    * \param name is the name of the feature.
                    * \param idFeat is the id code of the feature;the default value is -1.
                    */
                    FirstOrderFeature(const QString& name, int idFeat = -1);
                    /*!
                     * \brief FirstOrderFeature is the 2 or 3 parameters constructor of the class.
                     * \param name is the name of the feature.
                     * \param parameters is a QString list that conteins feature's parameters.
                     * \param idFeat is the id code of the feature.
                     */
                    FirstOrderFeature(const QString& name, const QStringList& parameters, int idFeat = -1);
                public:
                    /*!
                     * \brief executeAnalysis executes the feature in 2D and 3D images.
                     * \param image is the input image of the feature.
                     * \return the output image of the feature.
                     */
                    virtual RomeoObject* executeAnalysis(RomeoObject *image);
                    /*!
                     * \brief execute2DAnalysis is method that execute the feature on 2D images.
                     * \param image is the input image 2D of the feature.
                     * \return the output 2D RGB image of the feature.
                     */
                    RGBImage2D* execute2DAnalysis(RGBImage2D *image);
                    /*!
                     * \brief execute2DAnalysis is method that execute the feature on 3D images.
                     * \param image is the input image 3D of the feature.
                     * \return the output 3D RGB image of the feature.
                     */
                    RGBImage3D* execute3DAnalysis(RGBImage3D *image);
                    /*!
                     * \brief singleChannelEXecution2D execute feature extractor in a single channel of RGB 2D image.
                     * \param channel is one of the 3 channels of RGB 2D image.
                     * \return the result of the application of the feature in a RGB 2D channel.
                     */
                    virtual InternalData2D* singleChannelEXecution2D(InternalData2D* channel) =0;
                    /*!
                     * \brief singleChannelEXecution3D execute feature extractor in a single channel of RGB 3D image.
                     * \param channel is one of the 3 channels of RGB 3D image.
                     * \return the result of the application of the feature in a RGB 3D channel.
                     */
                    virtual InternalData3D* singleChannelEXecution3D(InternalData3D* channel) =0;
                    /*!
                     * \brief getWindowSize gets the window size value.
                     * \return the windows size value of the feature
                     */
                    int getWindowSize() const;
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
                     * \brief getType gets the type of the feature (2D,3D).
                     * \return the type of the feature.
                     */
                     virtual QString getType() const;
                    /*!
                     * \brief ~FirstOrderFeature virtual destructor of the class.
                     */
                    virtual ~FirstOrderFeature();

                };

            } // namespace Feature
        } // namespace Core
    } // namespace Model
} // namespace Romeo

#endif // ROMEO_MODEL_CORE_FEATURE_FIRSTORDERFEATURE_H

#include "featcreator.h"

using Romeo::Model::Core::FeatCreator;
using Romeo::Model::Core::Feature::AFeature;
using Romeo::Model::Core::Feature::MeanFeature;
using Romeo::Model::Core::Feature::StandardDeviationFeature;
using Romeo::Model::Core::Feature::SkewnessFeature;
using Romeo::Model::Core::Feature::KurtosisFeature;
using Romeo::Model::Core::Feature::EntropyFeature;
using Romeo::Model::Core::Feature::EnergyFeature;
using Romeo::Model::Core::Feature::ContrastFeature;
using Romeo::Model::Core::Feature::HomogeneityFeature;
using Romeo::Model::Core::Feature::CorrelationFeature;
using Romeo::Model::Core::Feature::MaximumFeature;
using Romeo::Model::Core::Feature::MinimumFeature;
using Romeo::Model::Core::Feature::MeanDynamicFeature;
using Romeo::Model::Core::Feature::AreaUnderCurveFeature;

FeatCreator::FeatCreator(){

}

FeatCreator *FeatCreator::getFeatCreator() {

    if(!featCreator)
        featCreator = new FeatCreator();
    return featCreator;
}

AFeature* FeatCreator::buildFeature(const QString &name, QStringList &parameters, int idFeat) const
{
    AFeature* feature = 0;

    if (name==Utils::FEATURE_MEAN) {
        feature=new MeanFeature(parameters);
    }
    else if(name==Utils::FEATURE_STANDARD_DEVIATION) {
        feature=new StandardDeviationFeature(parameters);
    }
    else if(name==Utils::FEATURE_SKEWNESS) {
        feature=new SkewnessFeature(parameters);
    }
    else if(name==Utils::FEATURE_KURTOSIS) {
        feature=new KurtosisFeature(parameters);
    }
    else if(name==Utils::FEATURE_CONTRAST) {
        feature=new ContrastFeature(parameters);
    }
    else if(name==Utils::FEATURE_HOMOGENEITY) {
        feature=new HomogeneityFeature(parameters);
    }
    else if(name==Utils::FEATURE_ENTROPY) {
        feature=new EntropyFeature(parameters);
    }
    else if(name==Utils::FEATURE_ENERGY) {
        feature=new EnergyFeature(parameters);
    }
    else if(name==Utils::FEATURE_CORRELATION) {
        feature=new CorrelationFeature(parameters);
    }
    else if(name==Utils::FEATURE_MAXIMUM) {
        feature=new MaximumFeature(parameters);
    }
    else if(name==Utils::FEATURE_MINIMUM) {
        feature=new MinimumFeature(parameters);
    }
    else if(name==Utils::FEATURE_MEAN_DYNAMIC) {
        feature=new MeanDynamicFeature(parameters);
    }
    else if(name==Utils::FEATURE_AREA_UNDER_CURVE) {
        feature=new AreaUnderCurveFeature(parameters);
    }


    if(feature) feature->setId(idFeat);

    return feature;
}

FeatCreator *FeatCreator::featCreator = 0;

AFeature* FeatCreator::buildFeature(const QString &name, int idFeat) const
{
    AFeature* feature=0;

    if (name==Utils::FEATURE_MEAN) {
        feature=new MeanFeature();
    }
    else if(name==Utils::FEATURE_STANDARD_DEVIATION) {
        feature=new StandardDeviationFeature();
    }
    else if(name==Utils::FEATURE_SKEWNESS) {
        feature=new SkewnessFeature();
    }
    else if(name==Utils::FEATURE_KURTOSIS) {
        feature=new KurtosisFeature();
    }
    else if(name==Utils::FEATURE_CONTRAST) {
        feature=new ContrastFeature();
    }
    else if(name==Utils::FEATURE_HOMOGENEITY) {
        feature=new HomogeneityFeature();
    }
    else if(name==Utils::FEATURE_ENTROPY) {
        feature=new EntropyFeature();
    }
    else if(name==Utils::FEATURE_ENERGY) {
        feature=new EnergyFeature();
    }
    else if(name==Utils::FEATURE_CORRELATION) {
        feature=new CorrelationFeature();
    }
    else if(name==Utils::FEATURE_MAXIMUM) {
        feature=new MaximumFeature();
    }
    else if(name==Utils::FEATURE_MINIMUM) {
        feature=new MinimumFeature();
    }
    else if(name==Utils::FEATURE_MEAN_DYNAMIC) {
        feature=new MeanDynamicFeature();
    }
    else if(name==Utils::FEATURE_AREA_UNDER_CURVE) {
        feature=new AreaUnderCurveFeature();
    }

    if(feature) feature->setId(idFeat);

    return feature;
}

QVector<AFeature*> FeatCreator::getAllFeaturesFirstOrder() const {
    QVector<AFeature*> features;

    features.append(buildFeature(Utils::FEATURE_MEAN));
    features.append(buildFeature(Utils::FEATURE_STANDARD_DEVIATION));
    features.append(buildFeature(Utils::FEATURE_SKEWNESS));
    features.append(buildFeature(Utils::FEATURE_KURTOSIS));

    return features;
}

QVector<AFeature*> FeatCreator::getAllFeaturesSecondOrder() const {
    QVector<AFeature*> features;

    features.append(buildFeature(Utils::FEATURE_CONTRAST));
    features.append(buildFeature(Utils::FEATURE_HOMOGENEITY));
    features.append(buildFeature(Utils::FEATURE_ENTROPY));
    features.append(buildFeature(Utils::FEATURE_ENERGY));
    features.append(buildFeature(Utils::FEATURE_CORRELATION));

    return features;
}

QVector<AFeature*> FeatCreator::getAllFeaturesDynamic() const {
    QVector<AFeature*> features;

    features.append(buildFeature(Utils::FEATURE_MAXIMUM));
    features.append(buildFeature(Utils::FEATURE_MINIMUM));
    features.append(buildFeature(Utils::FEATURE_MEAN_DYNAMIC));
    features.append(buildFeature(Utils::FEATURE_AREA_UNDER_CURVE));

    return features;
}

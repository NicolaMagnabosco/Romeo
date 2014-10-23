#include "algcreator.h"
#include "model/core/algorithm/fuzzycmeansalgorithm.h"
#include "model/core/algorithm/kmeansalgorithm.h"
#include "utils.h"

using Romeo::Model::Core::AlgCreator;
using Romeo::Model::Core::Algorithm::AAlgorithm;
using Romeo::Model::Core::Algorithm::FuzzyCMeansAlgorithm;
using Romeo::Model::Core::Algorithm::KMeansAlgorithm;

AlgCreator::AlgCreator() {

}

AlgCreator *AlgCreator::getAlgCreator() {

    if(!algCreator)
        algCreator = new AlgCreator();
    return algCreator;
}

AlgCreator *AlgCreator::algCreator = 0;

AAlgorithm* AlgCreator::buildAlgorithm(const QString &name, const QStringList &parameters, int algId) const
{
    AAlgorithm* algorithm = 0;

    if (name == Utils::ALGORITHM_KMEANS) {
        algorithm = new KMeansAlgorithm(parameters, algId);
    }
    else if (name == Utils::ALGORITHM_FUZZY) {
        algorithm = new FuzzyCMeansAlgorithm(parameters, algId);
    }

    return algorithm;
}

QVector<AAlgorithm*> AlgCreator::getAllAlgorithms() const
{
    //result contain all the algoritms to return
    QVector<AAlgorithm*> result;
    result.append(buildAlgorithm(Utils::ALGORITHM_FUZZY));
    result.append(buildAlgorithm(Utils::ALGORITHM_KMEANS));
    return result;
}

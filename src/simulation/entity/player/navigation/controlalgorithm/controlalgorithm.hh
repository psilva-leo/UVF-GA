#ifndef CONTROLALGORITHM_HH
#define CONTROLALGORITHM_HH

#include <simulation/simulationUtils/simulationutils.h>
#include <simulation/entity/player/navigation/controlalgorithm/controlalgorithmparameters.hh>
#include <QString>

class ControlAlgorithmParameters;

class ControlAlgorithm {
public:
    ControlAlgorithm();
    virtual ~ControlAlgorithm();
    virtual QString name() = 0;

    virtual float iterate(float distance);
    virtual void reset();

    virtual void accept(ControlAlgorithmParameters *setter) = 0;
private:
    virtual float _iterate(float error, float dt) = 0;

    // Timer to calc looptime
    Timer _dt;
};

#endif // CONTROLALGORITHM_HH

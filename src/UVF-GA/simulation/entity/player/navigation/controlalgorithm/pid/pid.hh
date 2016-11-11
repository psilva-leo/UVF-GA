#ifndef PID_HH
#define PID_HH

#include <UVF-GA/simulation/entity/player/navigation/controlalgorithm/controlalgorithm.hh>

class PID :public ControlAlgorithm {
public:
    PID();
    PID(float kp, float ki, float kd, float iLimit);
    ~PID();

    QString name();

    void reset();

    void accept(ControlAlgorithmParameters *setter);
    void setParameters(double kp, double ki, double kd, double iLimit);
private:
    float _iterate(float error, float dt);

    // PID parameters
    double _kp;
    double _ki;
    double _kd;
    double _iLimit;

    // Internal variables
    bool _hasLastError;
    float _lastError;
    float _iError;
};

#endif // PID_HH

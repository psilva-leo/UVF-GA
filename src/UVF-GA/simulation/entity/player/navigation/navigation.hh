#ifndef NAVIGATION_HH
#define NAVIGATION_HH

#include <UVF-GA/simulation/entity/player/player.h>
#include <UVF-GA/utils/utils.h>
#include <UVF-GA/simulation/entity/player/navigation/navigationalgorithm/navigationalgorithm.hh>
#include <UVF-GA/simulation/entity/player/navigation/controlalgorithm/controlalgorithm.hh>
#include <QMutexLocker>

class Player;
class ControlAlgorithm;
class NavigationAlgorithm;

class Navigation {
public:
    Navigation(Player *player, SSLWorld *world);

    virtual ~Navigation();

    // Setters
    void setGoal(const Position &destination, const float &orientation, bool avoidRobots, bool avoidBall);
    void setMaxLSpeed(float maxLSpeed) { _maxLSpeed = fabs(maxLSpeed); }
    void setMaxASpeed(float maxASpeed) { _maxASpeed = fabs(maxASpeed); }
    void setMaxLAcceleration(float maxLAcceleration) { _maxLAcceleration = maxLAcceleration; }

    // Getters
    float getDirection() const;
    float getDistance() const;
    float getMaxLSpeed() const { return _maxLSpeed; }
    float getMaxASpeed() const { return _maxASpeed; }
    float getmaxLAcceleration() const { return _maxLAcceleration; }

    // Interface functions
    void reset();
    double getLinearSpeed(float distError);
    double getAngularSpeed(float angularError);

    // Avoid
    void avoidRobots();
    void avoidBall();

    // PID
    void setLinearPIDParameters(double kp, double ki, double kd, double ilimit);
    void setAngularPIDParameters(double kp, double ki, double kd, double ilimit);
    void setUVFParameters(double de, double kr, double dmin, double delta, double k0);

private:
    // General access
    Player *_player;
    NavigationAlgorithm *_navAlg;
    mutable QMutex _navAlgMutex;
    SSLWorld *_world;

    // Internal
    ControlAlgorithm *_linCtrAlg;
    ControlAlgorithm *_angCtrAlg;

    // Direction and distance
    float _direction;
    float _distance;

    // Maximum speed
    float _maxLSpeed;
    float _maxASpeed;

    // Maximum acceleration
    float _maxLAcceleration;

    float _calculateLinearSpeed(float distError);
    float _calculateAngularSpeed(float angGoal );
};

#endif // NAVIGATION_HH

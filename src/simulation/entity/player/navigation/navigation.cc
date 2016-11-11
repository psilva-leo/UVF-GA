#include "navigation.hh"

#include <simulation/entity/player/navigation/controlalgorithm/pid/pid.hh>
#include <simulation/entity/player/navigation/navigationalgorithm/uvf/uvf.hh>
#include <iostream>

Navigation::Navigation(Player *player, SSLWorld *world) {
    _player    = player;
    _navAlg    = new UVF();
    _linCtrAlg = new PID(2.5, 0.0 , 0.25, 0.0);
    _angCtrAlg = new PID(2.5, 0.05, 0.1, 20.0);
    _world = world;
}

Navigation::~Navigation() {
    delete _navAlg;
    delete _linCtrAlg;
    delete _angCtrAlg;
}

void Navigation::setGoal(const Position &destination, const float &orientation, bool avoidRobots, bool avoidBall) {
    QMutexLocker locker(&_navAlgMutex);

    // Reset algorithm
    _navAlg->reset();

    // Set origin position and orientation
    _navAlg->setOrigin(_player->position(), _player->orientation());

    // Sets goal position and orientation
    _navAlg->setGoal(destination, orientation);

    // Calculate ball pos
    dReal ballX, ballY, ballZ;
    _world->ball->getBodyPosition(ballX, ballY, ballZ);

    // Add ball as repulsive
    if(avoidBall)
        _navAlg->addBall(Position(ballX, ballY), Velocity(0.0, 0.0));

    /// TODO: ADD ROBOTS
    // Adds robots as repulsive
    if(avoidRobots) {
//        QList<Player*> avOpPlayers = _opTeam->avPlayers().values();
//        for(int i=0; i<avOpPlayers.size(); i++) {
//            Player *opponent = avOpPlayers.at(i);

//            // Add robot as repulsive
//            _navAlg->addEnemyRobot(opponent->position(), opponent->velocity());
//        }
    }

}

float Navigation::getDirection() const {
    QMutexLocker locker(&_navAlgMutex);

    // Execute algorithm
    _navAlg->runNavigationAlgorithm();

    return _navAlg->getDirection();
}

float Navigation::getDistance() const {
    QMutexLocker locker(&_navAlgMutex);
    return _navAlg->getDistance();
}

void Navigation::reset() {
    _linCtrAlg->reset();
    _angCtrAlg->reset();
}

void Navigation::setLinearPIDParameters(double kp, double ki, double kd, double iLimit) {
    ControlAlgorithmParameters params;
    params.setPIDParameters(kp, ki, kd, iLimit);
    params.setTo(_linCtrAlg);
}

void Navigation::setAngularPIDParameters(double kp, double ki, double kd, double ilimit) {
    ControlAlgorithmParameters params;
    params.setPIDParameters(kp, ki, kd, ilimit);
    params.setTo(_angCtrAlg);
}

void Navigation::setUVFParameters(double de, double kr, double dmin, double delta, double k0) {
    _navAlg->setParameters(de, kr, dmin, delta, k0);
}

double Navigation::getLinearSpeed(float distError) {    
    // Iterate control algorithm
    float linearSpeed = _linCtrAlg->iterate(distError);

    // Limit to max linear speed
    if(linearSpeed < -_maxLSpeed) linearSpeed = -_maxLSpeed;
    if(linearSpeed >  _maxLSpeed) linearSpeed =  _maxLSpeed;

    return linearSpeed;
}

double Navigation::getAngularSpeed(float angularError) {
    float angularSpeed = 0.0;

    // Fix high angle
    if(angularError >  PI) angularError -= 2*PI;
    if(angularError < -PI) angularError += 2*PI;

    // Iterate control algorithm
    angularSpeed = _angCtrAlg->iterate(angularError);

    // Limit to max angular speed
    if(angularSpeed < -_maxASpeed) angularSpeed = -_maxASpeed;
    if(angularSpeed >  _maxASpeed) angularSpeed =  _maxASpeed;

    return angularSpeed;
}

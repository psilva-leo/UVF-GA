#ifndef TESTCASE_H
#define TESTCASE_H

#include <UVF-GA/utils/entity/entity.hh>
#include <UVF-GA/simulation/player/player.hh>
#include <UVF-GA/utils/utils.hh>
#include <3rdparty/sslworld/sslworld.hh>

class TestCase : public Entity {
public:
    TestCase();
    ~TestCase();

    QString name();

    /// TODO: Condição de parada no loop (tempo e distancia)
    /// TODO: Varias disposições de jogadores

    // Setters
    void setLinearCtrlParameters(float kp, float ki, float kd, float limit);
    void setAngularCtrlParameters(float kp, float ki, float kd, float limit);
    void setUVFParameters(double de, double kr, double dmin, double delta, double k0);
    void setMaxSpeed(float maxASpeed, float maxLSpeed);

    // Getters
    double timemsec() { return _timer->timemsec(); }
    double timensec() { return _timer->timensec(); }
    double timeusec() { return _timer->timeusec(); }
    bool idle() { return _player->hasReachedGoal(); }

    // Config
    void configGoToLookTo(Position desiredPos, float angleToLook, bool avoidRobots, bool avoidBall);

private:
    SSLWorld *_world;
    Player *_player;
    Timer *_timer;

    Position _desiredPos;
    float _desiredAngle;
    bool _avoidRobots;
    bool _avoidBall;
    bool _reachedGoal;
    double _msecTestTime;

    void initialization();
    void loop();
    void finalization();
};

#endif // TESTCASE_H

#ifndef UVF_HH
#define UVF_HH

#include <UVF-GA/simulation/entity/player/navigation/navigationalgorithm/uvf/uvfobstacle.hh>
#include <UVF-GA/simulation/entity/player/navigation/navigationalgorithm/navigationalgorithm.hh>
#include <cmath>
#include <QList>

class UVF : public NavigationAlgorithm {
public:
    UVF();
    ~UVF();

    void reset();

    // Config
    void setParameters(double de, double kr, double dmin, double delta, double k0);

    // Add obstacles
    void addBall(const Position &pos, const Velocity &vel);
    void addGoalArea(const Position &pos);
    void addRobot(const Position &pos, const Velocity &vel);
    //void addEnemyRobot(const Position &pos, const Velocity &vel);

    // Return results
    float getDirection() const;
private:
    // Run
    void run();

    // Obstacle avoidance
    void addObstacle(const Position &pos, const Velocity &vel);
    QList <UVFObstacle> _obstacles;

    // Auxiliar functions
    Position rotate(const Position &pos, float rot);
    Velocity rotate(const Velocity &vel, float rot);
    float getPhi(const Position &p, bool ccw, float de) const;
    float getPhiTUF(float x, float y, float de);
    float mergeVF(const Position &auf, float phiAUF, float phiTUF, Position tmpObst, Position tmpGoalPos);
    float gauss(float r) const;

    float wrapToPi(float angle);

    // Results
    float _resultantDirection;

    // UVF CONSTANTS
    double _de;
    double _kr;
    double _dmin;
    double _delta;
    double _k0;
};


#endif // UVF_HH

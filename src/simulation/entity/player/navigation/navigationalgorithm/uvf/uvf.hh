#ifndef UVF_HH
#define UVF_HH

#include <simulation/entity/player/navigation/navigationalgorithm/uvf/uvfobstacle.hh>
#include <simulation/entity/player/navigation/navigationalgorithm/navigationalgorithm.hh>
#include <cmath>
#include <QList>

class UVF : public NavigationAlgorithm {
public:
    UVF();
    ~UVF();

    void reset();

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
    // Hyperbolic spiral univector field
    double _de; // Raio do círculo da espiral
    double _kr; // Suavidade da espiral, quanto maior mais suave

    // Composition of move-to-goal univector field and avoid-obstacle univector field
    double _dmin; // AUF total se d <= dmin (praticamente o raio do obstáculo)
    double _delta; // Maior o delta, maior da gaussiana então desvia-se antes

    // Virtual obstacles calc
    double _k0; // Fator multiplicativo da velocidade relativa

};


#endif // UVF_HH

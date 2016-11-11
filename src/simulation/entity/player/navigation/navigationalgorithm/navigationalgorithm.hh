#ifndef NAVIGATIONALGORITHM_HH
#define NAVIGATIONALGORITHM_HH

#include <simulation/simulationUtils/simulationutils.h>
#include <QMutexLocker>

class NavigationAlgorithm {
public:
    NavigationAlgorithm();
    virtual ~NavigationAlgorithm();

    // Access to Navigation
    void runNavigationAlgorithm();

    // Config
    virtual void setParameters(double de, double kr, double dmin, double delta, double k0) = 0;

    // Reset algorithm
    virtual void reset() = 0;

    // Set origin and goal
    void setOrigin(const Position &pos, const float &ori);
    void setGoal(const Position &pos, const float &ori);

    // Add obstacles
    virtual void addBall(const Position &pos, const Velocity &vel) = 0;
    virtual void addRobot(const Position &pos, const Velocity &vel) = 0;

    // Return results
    virtual float getDirection() const = 0;
    virtual float getDistance() const;
//    virtual QLinkedList<Position> getPath() const;

protected:
    // Origin access
    Position originPos() const { return _originPos; }
    float originOri() const { return _originOri; }

    // Goal access
    Position goalPos() const { return _goalPos; }
    float goalOri() const { return _goalOri; }

private:
    // Execute algorithm
    virtual void run() = 0;

    // NavigationAlgorithm Origin
    Position _originPos;
    float _originOri;

    // NavigationAlgorithm Goal
    Position _goalPos;
    float _goalOri;

    // Distance
    float _distance;
};

#endif // NAVIGATIONALGORITHM_HH

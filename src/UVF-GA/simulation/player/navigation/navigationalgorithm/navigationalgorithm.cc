#include "navigationalgorithm.hh"

#define NAVALG_MAXTIME 5 // ms

NavigationAlgorithm::NavigationAlgorithm() {

}

NavigationAlgorithm::~NavigationAlgorithm() {

}

void NavigationAlgorithm::runNavigationAlgorithm() {
    // Run NavigationAlgorithm specific implementation
    run();
}

void NavigationAlgorithm::setOrigin(const Position &pos, const float &ori) {
    _originPos = pos;
    _originOri = ori;
}

void NavigationAlgorithm::setGoal(const Position &pos, const float &ori) {
    _goalPos = pos;
    _goalOri = ori;
}

float NavigationAlgorithm::getDistance() const {
//    QMutexLocker locker(&_pathMutex);
//    return _distance;
    return sqrt(pow(_goalPos.x()-_originPos.x(),2)+pow(_goalPos.y()-_originPos.y(), 2));
}

//QLinkedList<Position> NavigationAlgorithm::getPath() const {
//    QMutexLocker locker(&_pathMutex);

//    // Return path
//    return _path;
//}


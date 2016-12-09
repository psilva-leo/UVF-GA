#ifndef PARAMS_H
#define PARAMS_H

struct UVFParams {
    double de;
    double kr;
    double dmin;
    double delta;
};

struct SpeedParams {
    float maxASpeed;
    float maxLSpeed;
};

struct Results {
    float linearTime;
    float angularTime;
    float linearError;
    float angularError;
    int reachedGoal;
    float entryAngError;
    unsigned collisions;
};

#endif // PARAMS_H

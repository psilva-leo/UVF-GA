#ifndef PARAMS_H
#define PARAMS_H

struct UVFParams {
    double de;
    double kr;
    double dmin;
    double delta;
    double k0;
};

struct SpeedParams {
    float maxASpeed;
    float maxLSpeed;
};

struct Results {
    float time;
    float distance;
    int reachedGoal;
};

#endif // PARAMS_H

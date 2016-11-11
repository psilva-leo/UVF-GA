/*
grSim - RoboCup Small Size Soccer Robots Simulator
Copyright (C) 2011, Parsian Robotic Center (eew.aut.ac.ir/~parsian/grsim)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SSLWORLD_H
#define SSLWORLD_H

#define ROBOT_COUNT 6
#define WALL_COUNT 10

#include <QTime>
#include "robot.h"
#include "fieldconfig.h"
#include "physics/pworld.h"
#include "physics/pball.h"
#include "physics/pground.h"
#include "physics/pfixedbox.h"
#include "physics/pray.h"

class RobotsFomation {
    public:
        dReal x[ROBOT_COUNT];
        dReal y[ROBOT_COUNT];
        RobotsFomation(int type);
        void setAll(dReal *xx,dReal *yy);
        void resetRobots(Robot** r,int team);
};

class SSLWorld {
private:
    dReal last_dt;
public:    
    SSLWorld(FieldConfig* _cfg,RobotsFomation *form1,RobotsFomation *form2);
    virtual ~SSLWorld();

    void step(dReal dt=-1);

    Robot* robots[ROBOT_COUNT*2];
    FieldConfig* cfg;

    PWorld* p;
    PBall* ball;
    PGround* ground;
    PRay* ray;
    PFixedBox* walls[WALL_COUNT];

    QTime *timer;
};

dReal fric(dReal f);
int robotIndex(int robot,int team);

#endif // SSLWORLD_H

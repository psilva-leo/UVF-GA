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

#include "sslworld.hh"
#include <QTime>

#pragma GCC diagnostic ignored "-Wunused-parameter"

#define ROBOT_GRAY 0.4
#define WHEEL_COUNT 4

SSLWorld* _w;

dReal fric(dReal f) {
    if (f==-1) return dInfinity;
    return f;
}

int robotIndex(int robot,int team) {
    return robot + team*ROBOT_COUNT;
}

bool wheelCallBack(dGeomID o1,dGeomID o2,PSurface* s) {
    const dReal* r; //wheels rotation matrix
    if ((o1==s->id1) && (o2==s->id2)) {
        r=dBodyGetRotation(dGeomGetBody(o1));
    } else if ((o1==s->id2) && (o2==s->id1)) {
        r=dBodyGetRotation(dGeomGetBody(o2));
    } else {
        return false;
    }

    s->surface.mode = dContactFDir1 | dContactMu2  | dContactApprox1 | dContactSoftCFM;
    s->surface.mu = fric(_w->cfg->robotSettings.WheelPerpendicularFriction);
    s->surface.mu2 = fric(_w->cfg->robotSettings.WheelTangentFriction);
    s->surface.soft_cfm = 0.002;

    dVector3 v={0,0,1,1};
    dVector3 axis;
    dMultiply0(axis,r,v,4,3,1);
    dReal l = sqrt(axis[0]*axis[0] + axis[1]*axis[1]);
    s->fdir1[0] = axis[0]/l;
    s->fdir1[1] = axis[1]/l;
    s->fdir1[2] = 0;
    s->fdir1[3] = 0;
    s->usefdir1 = true;
    return true;
}

bool rayCallback(dGeomID o1,dGeomID o2,PSurface* s) {
    dGeomID obj;
    if (o1==_w->ray->geom) obj = o2;
    else obj = o1;
    for (int i=0;i<ROBOT_COUNT * 2;i++)
    {
        if (_w->robots[i]->chassis->geom==obj || _w->robots[i]->dummy->geom==obj)
        {
            _w->robots[i]->selected = true;
            _w->robots[i]->select_x = s->contactPos[0];
            _w->robots[i]->select_y = s->contactPos[1];
            _w->robots[i]->select_z = s->contactPos[2];
        }
    }
    return false;
}

bool ballCallBack(dGeomID o1,dGeomID o2,PSurface* s) {
    if (_w->ball->tag!=-1) //spinner adjusting
    {
        dReal x,y,z;
        _w->robots[_w->ball->tag]->chassis->getBodyDirection(x,y,z);
        s->fdir1[0] = x;
        s->fdir1[1] = y;
        s->fdir1[2] = 0;
        s->fdir1[3] = 0;
        s->usefdir1 = true;
        s->surface.mode = dContactMu2 | dContactFDir1 | dContactSoftCFM;
        s->surface.mu = _w->cfg->BallFriction();
        s->surface.mu2 = 0.5;
        s->surface.soft_cfm = 0.002;
    }
    return true;
}

SSLWorld::SSLWorld() {
    cfg = new FieldConfig();
    RobotsFomation form(1);

    _w = this;

    last_dt = -1;    
    p = new PWorld(0.05,9.81f);
    ball = new PBall (0,0,0.5,cfg->BallRadius(),cfg->BallMass(), 1,0.7,0);

    ground = new PGround(cfg->Field_Rad(),cfg->Field_Length(),cfg->Field_Width(),cfg->Field_Penalty_Rad(),cfg->Field_Penalty_Line(),cfg->Field_Penalty_Point(),cfg->Field_Line_Width(),cfg->Field_Defense_Stretch(),cfg->Field_Defense_Rad(),0);
    ray = new PRay(50);
    
    // Bounding walls
    const double thick = cfg->Wall_Thickness();
    const double increment = cfg->Field_Margin() + cfg->Field_Referee_Margin() + thick / 2;
    const double pos_x = cfg->Field_Length() / 2.0 + increment;
    const double pos_y = cfg->Field_Width() / 2.0 + increment;
    const double pos_z = 0.0;
    const double siz_x = 2.0 * pos_x;
    const double siz_y = 2.0 * pos_y;
    const double siz_z = 0.4;
    const double tone = 1.0;
    
    walls[0] = new PFixedBox(thick/2, pos_y, pos_z,
                             siz_x, thick, siz_z,
                             tone, tone, tone);

    walls[1] = new PFixedBox(-thick/2, -pos_y, pos_z,
                             siz_x, thick, siz_z,
                             tone, tone, tone);
    
    walls[2] = new PFixedBox(pos_x, -thick/2, pos_z,
                             thick, siz_y, siz_z,
                             tone, tone, tone);

    walls[3] = new PFixedBox(-pos_x, thick/2, pos_z,
                             thick, siz_y, siz_z,
                             tone, tone, tone);
    
    // Goal walls
    
    const double gthick = cfg->Goal_Thickness();
    const double gpos_x = (cfg->Field_Length() + gthick) / 2.0 + cfg->Goal_Depth();
    const double gpos_y = (cfg->Goal_Width() + gthick) / 2.0;
    const double gpos_z = cfg->Goal_Height() / 2.0;
    const double gsiz_x = cfg->Goal_Depth() + gthick;
    const double gsiz_y = cfg->Goal_Width();
    const double gsiz_z = cfg->Goal_Height();
    const double gpos2_x = (cfg->Field_Length() + gsiz_x) / 2.0;

    walls[4] = new PFixedBox(gpos_x, 0.0, gpos_z,
                             gthick, gsiz_y, gsiz_z,
                             tone, tone, tone);
    
    walls[5] = new PFixedBox(gpos2_x, -gpos_y, gpos_z,
                             gsiz_x, gthick, gsiz_z,
                             tone, tone, tone);
    
    walls[6] = new PFixedBox(gpos2_x, gpos_y, gpos_z,
                             gsiz_x, gthick, gsiz_z,
                             tone, tone, tone);

    walls[7] = new PFixedBox(-gpos_x, 0.0, gpos_z,
                             gthick, gsiz_y, gsiz_z,
                             tone, tone, tone);
    
    walls[8] = new PFixedBox(-gpos2_x, -gpos_y, gpos_z,
                             gsiz_x, gthick, gsiz_z,
                             tone, tone, tone);
    
    walls[9] = new PFixedBox(-gpos2_x, gpos_y, gpos_z,
                             gsiz_x, gthick, gsiz_z,
                             tone, tone, tone);
    
    p->addObject(ground);
    p->addObject(ball);
    p->addObject(ray);
    for (int i=0;i<10;i++)
        p->addObject(walls[i]);
    const int wheeltexid = 37;


    cfg->robotSettings = cfg->blueSettings;
    for (int k=0;k<ROBOT_COUNT;k++)
        robots[k] = new Robot(p,ball,cfg,-form.x[k],form.y[k],ROBOT_START_Z(cfg),ROBOT_GRAY,ROBOT_GRAY,ROBOT_GRAY,k+1,wheeltexid,1);
    cfg->robotSettings = cfg->yellowSettings;
    for (int k=0;k<ROBOT_COUNT;k++)
        robots[k+ROBOT_COUNT] = new Robot(p,ball,cfg,form.x[k],form.y[k],ROBOT_START_Z(cfg),ROBOT_GRAY,ROBOT_GRAY,ROBOT_GRAY,k+ROBOT_COUNT+1,wheeltexid,-1);//XXX

    p->initAllObjects();

    // Surfaces
    p->createSurface(ray,ground)->callback = rayCallback;
    p->createSurface(ray,ball)->callback = rayCallback;
    for (int k=0;k<ROBOT_COUNT * 2;k++)
    {
        p->createSurface(ray,robots[k]->chassis)->callback = rayCallback;
        p->createSurface(ray,robots[k]->dummy)->callback = rayCallback;
    }
    PSurface ballwithwall;
    ballwithwall.surface.mode = dContactBounce | dContactApprox1;
    ballwithwall.surface.mu = 1;
    ballwithwall.surface.bounce = cfg->BallBounce();
    ballwithwall.surface.bounce_vel = cfg->BallBounceVel();
    ballwithwall.surface.slip1 = 0;

    PSurface wheelswithground;
    PSurface* ball_ground = p->createSurface(ball,ground);
    ball_ground->surface = ballwithwall.surface;
    ball_ground->callback = ballCallBack;

    PSurface ballwithkicker;
    ballwithkicker.surface.mode = dContactApprox1;
    ballwithkicker.surface.mu = fric(cfg->robotSettings.Kicker_Friction);
    ballwithkicker.surface.slip1 = 5;
    
    for (int i = 0; i < WALL_COUNT; i++)
        p->createSurface(ball, walls[i])->surface = ballwithwall.surface;
    
    for (int k = 0; k < 2 * ROBOT_COUNT; k++)
    {
        p->createSurface(robots[k]->chassis,ground);
        for (int j = 0; j < WALL_COUNT; j++)
            p->createSurface(robots[k]->chassis,walls[j]);
        p->createSurface(robots[k]->dummy,ball);
        p->createSurface(robots[k]->kicker->box,ball)->surface = ballwithkicker.surface;
        for (int j = 0; j < WHEEL_COUNT; j++)
        {
            p->createSurface(robots[k]->wheels[j]->cyl,ball);
            PSurface* w_g = p->createSurface(robots[k]->wheels[j]->cyl,ground);
            w_g->surface=wheelswithground.surface;
            w_g->usefdir1=true;
            w_g->callback=wheelCallBack;
        }
        for (int j = k + 1; j < 2 * ROBOT_COUNT; j++)
        {            
            if (k != j)
            {
                p->createSurface(robots[k]->dummy,robots[j]->dummy); //seams ode doesn't understand cylinder-cylinder contacts, so I used spheres
                p->createSurface(robots[k]->chassis,robots[j]->kicker->box);
            }
        }
    }

    timer = new QTime();
    timer->start();
}

SSLWorld::~SSLWorld() {
    delete p;
    delete cfg;
}

void SSLWorld::step(dReal dt) {
    for (int kk=0;kk<5;kk++)
    {
        const dReal* ballvel = dBodyGetLinearVel(ball->body);
        dReal ballspeed = ballvel[0]*ballvel[0] + ballvel[1]*ballvel[1] + ballvel[2]*ballvel[2];
        ballspeed = sqrt(ballspeed);
        dReal ballfx=0,ballfy=0,ballfz=0;
        dReal balltx=0,ballty=0,balltz=0;
        if (ballspeed>=0.01) {
            dReal fk = cfg->BallFriction()*cfg->BallMass()*cfg->Gravity();
            ballfx = -fk*ballvel[0] / ballspeed;
            ballfy = -fk*ballvel[1] / ballspeed;
            ballfz = -fk*ballvel[2] / ballspeed;
            balltx = -ballfy*cfg->BallRadius();
            ballty = ballfx*cfg->BallRadius();
            balltz = 0;
            dBodyAddTorque(ball->body,balltx,ballty,balltz);
        }
        dBodyAddForce(ball->body,ballfx,ballfy,ballfz);
        if (dt==0) dt=last_dt;
        else last_dt = dt;

        p->step(dt*0.2);
    }


    ball->tag = -1;
    for (int k=0;k<ROBOT_COUNT * 2;k++) {
        robots[k]->step();
    }
}

void RobotsFomation::setAll(dReal* xx,dReal *yy) {
    for (int i=0;i<ROBOT_COUNT;i++) {
        x[i] = xx[i];
        y[i] = yy[i];
    }
}

RobotsFomation::RobotsFomation(int type) {
    if (type==0)
    {
        dReal teamPosX[ROBOT_COUNT] = {2.2, 1.0,   1.0, 1.0,  0.33, 1.22};
        dReal teamPosY[ROBOT_COUNT] = {0.0, -0.75, 0.0, 0.75, 0.25, 0.0};
        setAll(teamPosX,teamPosY);
    }
    if (type==1) // formation 1
    {
        dReal teamPosX[ROBOT_COUNT] = {1.5,  1.5, 1.5,   0.5,   2.5, 3.6};
        dReal teamPosY[ROBOT_COUNT] = {1.12, 0.0, -1.12, -0.37, 0.0, 0.0};
        setAll(teamPosX,teamPosY);
    }
    if (type==2) // formation 2
    {
        dReal teamPosX[ROBOT_COUNT] = {4.2, 3.40,  3.40, 0.7, 0.7,  0.7};
        dReal teamPosY[ROBOT_COUNT] = {0.0, -0.20, 0.20, 0.0, 2.25, -2.25};
        setAll(teamPosX,teamPosY);
    }
    if (type==3) // outside field
    {
        dReal teamPosX[ROBOT_COUNT] = {0.4,  0.8,  1.2,  1.6,  2.0,  2.4};
        dReal teamPosY[ROBOT_COUNT] = {-4.0, -4.0, -4.0, -4.0, -4.0, -4.0};
        setAll(teamPosX,teamPosY);
    }
    if (type==4)
    {
        dReal teamPosX[ROBOT_COUNT] = {2.8, 2.5, 2.5, 0.8, 0.8, 1.1};
        dReal teamPosY[ROBOT_COUNT] = {5+0.0, 5-0.3, 5+0.3, 5+0.0, 5+1.5, 5.5};
        setAll(teamPosX,teamPosY);
    }
    if (type==-1) // blue outside
    {
        dReal teamPosX[ROBOT_COUNT] = {0.4,  0.8,  1.2,  1.6,  2.0,  2.4};
        dReal teamPosY[ROBOT_COUNT] = {-3.4, -3.4, -3.4, -3.4, -3.4, -3.4};
        setAll(teamPosX,teamPosY);
    }
    if (type==-2) // yellow outside
    {
        dReal teamPosX[ROBOT_COUNT] = {0.4,  0.8,  1.2,  1.6,  2.0,  2.4};
        dReal teamPosY[ROBOT_COUNT] = {-3.4, -3.4, -3.4, -3.4, -3.4, -3.4};
        setAll(teamPosX,teamPosY);
    }
}

void RobotsFomation::resetRobots(Robot** r,int team)
{
    dReal dir=-1;
    if (team==1) dir = 1;
    for (int k=0;k<ROBOT_COUNT;k++)
    {
        r[robotIndex(k,team)]->setXY(x[k]*dir,y[k]);
        r[robotIndex(k,team)]->resetRobot();
    }
}


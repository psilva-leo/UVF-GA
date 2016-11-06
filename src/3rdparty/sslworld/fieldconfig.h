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

#ifndef FIELDCONFIG_H
#define FIELDCONFIG_H

#define DEF_VALUE(type,name,value)  \
    inline type name() {return value;}

class RobotSettings {
public:
    //geometeric settings
    double RobotCenterFromKicker;
    double RobotRadius;
    double RobotHeight;
    double BottomHeight;
    double KickerZ;
    double KickerThickness;
    double KickerWidth;
    double KickerHeight;
    double WheelRadius;
    double WheelThickness;
    double Wheel1Angle;
    double Wheel2Angle;
    double Wheel3Angle;
    double Wheel4Angle;

    //physical settings
    double BodyMass;
    double WheelMass;
    double KickerMass;
    double KickerDampFactor;
    double RollerTorqueFactor;
    double RollerPerpendicularTorqueFactor;
    double Kicker_Friction;
    double WheelTangentFriction;
    double WheelPerpendicularFriction;
    double Wheel_Motor_FMax;
};


class FieldConfig {
public:
  FieldConfig();

  RobotSettings robotSettings;
  RobotSettings blueSettings;
  RobotSettings yellowSettings;

  DEF_VALUE(double,Field_Line_Width, 0.010)
  DEF_VALUE(double,Field_Length,9.000)
  DEF_VALUE(double,Field_Width,6.000)
  DEF_VALUE(double,Field_Rad,0.500)
  DEF_VALUE(double,Field_Defense_Rad,1.000)
  DEF_VALUE(double,Field_Defense_Stretch,0.500)
  DEF_VALUE(double,Field_Penalty_Rad,0.50)
  DEF_VALUE(double,Field_Penalty_Line,0.350)
  DEF_VALUE(double,Field_Penalty_Point,0.950)
  DEF_VALUE(double,Field_Margin,0.250)
  DEF_VALUE(double,Field_Referee_Margin,0.455)
  DEF_VALUE(double,Wall_Thickness,0.050)
  DEF_VALUE(double,Goal_Thickness,0.020)
  DEF_VALUE(double,Goal_Depth,0.200)
  DEF_VALUE(double,Goal_Width,1.000)
  DEF_VALUE(double,Goal_Height,0.160)

  DEF_VALUE(double,BallRadius,0.0215)
  DEF_VALUE(double,Gravity,9.8)

  DEF_VALUE(double,BallMass,0.043)
  DEF_VALUE(double,BallFriction,0.05)
  DEF_VALUE(double,BallBounce,0.5)
  DEF_VALUE(double,BallBounceVel,0.1)

  void loadRobotsSettings();
  void loadRobotSettings();
};

#endif // FIELDCONFIG_H

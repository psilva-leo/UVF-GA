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

#include "fieldconfig.h"

FieldConfig::FieldConfig() {
    loadRobotsSettings();
}

void FieldConfig::loadRobotsSettings() {
    loadRobotSettings();
    yellowSettings = robotSettings;
    blueSettings = robotSettings;
}

void FieldConfig::loadRobotSettings() {
    robotSettings.RobotCenterFromKicker = 0.073;
    robotSettings.RobotRadius = 0.09;
    robotSettings.RobotHeight = 0.13;
    robotSettings.BottomHeight = 0.02;
    robotSettings.KickerZ = 0.005;
    robotSettings.KickerThickness = 0.005;
    robotSettings.KickerWidth = 0.08;
    robotSettings.KickerHeight = 0.04;
    robotSettings.WheelRadius = 0.0325;
    robotSettings.WheelThickness = 0.005;
    robotSettings.Wheel1Angle = 60;
    robotSettings.Wheel2Angle = 135;
    robotSettings.Wheel3Angle = 225;
    robotSettings.Wheel4Angle = 300;

    robotSettings.BodyMass  = 2;
    robotSettings.WheelMass = 0.2;
    robotSettings.KickerMass= 0.02;
    robotSettings.KickerDampFactor = 0.2f;
    robotSettings.RollerTorqueFactor = 0.06f;
    robotSettings.RollerPerpendicularTorqueFactor = 0.005f;
    robotSettings.Kicker_Friction = 0.8f;
    robotSettings.WheelTangentFriction = 0.8f;
    robotSettings.WheelPerpendicularFriction = 0.05f;
    robotSettings.Wheel_Motor_FMax = 0.2f;
}

/*
 * Global.h
 *
 *  Created on: Jul 14, 2015
 *      Author: colman
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <math.h>
using namespace std;

#define PLAYER 1
#define DEBUG 0
//#define ROBOT_IP "localhost"
#define ROBOT_IP "10.10.245.63"

// Particle
#define DEGREE_TO_RADIAN(degree)		((degree * M_PI) / 180)
#define MAX_PARTICLE 200
#define MIU_FOR_BELIEF 1.1
#define MAX_DISTANCE_FOR_PROB 0.2
#define MAX_YAW_FOR_PROB 0.1
#define BELIEF_TRASHHOLD 0.4
#define PARTICLE_RADIUS 0.3
//Laser

#define LASER_MAX_DEGREE 240.0;
#define LASER_READS_AMOUNT 666
#define MAX_LEASER_DISTANCE  4.0
#define PARTICLE_LASER_NOISE_IN_METER 0.25
#define PARTICLE_LASER_NOISE_IN_CM 25
#define CM_TO_CHECK_LASER 15

/* LASER */
const unsigned LASER_SLEASER_ARRAY_SIZE = 666;
const double MIN_LEASER_DISTANCE = 0; // meters
const double LASER_FRONT_SAMPLES_HALF = 75;
const double OBJECTS_DISTANCE_FROM_LASER_METER = 0.65;
const double START_RIGHT_RAYS_RANGE_ANGLE = -120;
const double END_RIGHT_RAYS_RANGE_ANGLE = -60;
const double START_LEFT_RAYS_RANGE_ANGLE = 60;
const double END_LEFT_RAYS_RANGE_ANGLE = 120;


// movement
#define ROTATION_SPEED 0.12
#define FORWARD_SPEED_SLOW 0.2
#define FORWARD_SPEED 0.2
#define ROTATION_FORWARD_SPEED 0.06
//#define MINIMUM_DISTANCE 1.7
#define MINIMUM_DISTANCE 25

// Smooth
#define MINIMUM_ANGLE 0.5
#define ANGLE_RANGE 0.085

// robot movement directions
#define MOVE_FORWARD 0
#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4
#define UP_LEFT 5
#define UP_RIGHT 6
#define DOWN_LEFT 7
#define DOWN_RIGHT 8
#define STOP 9

// Grid
#define FREE 0
#define BLOCK 1
#define PATH_CELL 2
#define START_CELL 3
#define GOAL_CELL 4

//Grid Power
#define NEAR_WALL 5
#define ALMOST_NEAR_WALL 10

// robot angle directions
#define ANGLE_UP 1.57
#define ANGLE_DOWN -1.57
#define ANGLE_RIGHT 0
#define ANGLE_LEFT -3.14
#define ANGLE_UP_LEFT 2.425
//#define ANGLE_UP_LEFT 2.356
#define ANGLE_UP_RIGHT 0.785
#define ANGLE_DOWN_LEFT -2.356
#define ANGLE_DOWN_RIGHT -0.785


#endif /* GLOBAL_H_ */

#pragma once
#ifndef collisionBallsHeader
#define collisionBallsHeader
#include "olcConsoleGameEngine.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


struct sBall {
	float px, py; // coordinate point
	float vx, vy; // velocity vector
	float ax, ay; // acceleration vector
	float radius; // radius 

	int id;  // id of ball
};

class CirclePhysics :public olcConsoleGameEngine
{
private:
	std::vector<std::pair<float, float>> modelCircle; // vector which contains pair of coordinates of balls
	std::vector<sBall> vecBalls;                      // vector which contains balls common witch their "vectors" (velocity, acceleration, radius)
	void addBall(float x, float y, float r = 5.0f);
public:
	CirclePhysics();
	virtual bool OnUserCreate() override;
	virtual bool OnUserUpdate(float fElapsedTime) override;	

};







#endif // !collisionBallsHeader
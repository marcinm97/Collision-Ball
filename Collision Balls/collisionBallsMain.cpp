

#include "olcConsoleGameEngine.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

struct sBall {
	float px, py; // coordinate point
	float vx, vy; // velocity vector
	float ax, ay; // acceleration vector
	float radius; // radius 

	//COLOUR color; // color of ball   /// ============== to do later ==============

	int id;  // id of ball
};

class CirclePhysics :public olcConsoleGameEngine
{
private:
	std::vector<std::pair<float, float>> modelCircle; // vector which contains pair of coordinates of balls
	std::vector<sBall> vecBalls;                      // vector which contains balls common witch their "vectors" (velocity, acceleration, radius)

	void addBall(float x, float y, float r) {
		srand(time(NULL));				
		sBall b;
		b.px = x;
		b.py = y;
		
		b.vx = 0.0f;
		b.vy = 0.0f;
		//b.color = COLOUR(std::rand() + 33);
		b.ax = 0.0f;
		b.ay = 0.0f;

		b.radius = r;

		b.id = vecBalls.size();

		vecBalls.emplace_back(b);  // we're using move constructor
	}
public:

	CirclePhysics() {
		m_sAppName = L"Circle Physics";
	}

	bool OnUserCreate() {
		// define Circle Model
		modelCircle.push_back({ 0.0f,0.0f });

		int nPoints = 20;
		for (int i = 0; i < nPoints; ++i)
			modelCircle.push_back({ cosf(i / (float)(nPoints - 1) * 2.0f * 3.14159f),sinf(i / (float)(nPoints - 1)* 2.0f * 3.14159f) });
		// generating points to draw objects

		float fDefaultRad = 20.0f;

		addBall(ScreenWidth() * 0.25f, ScreenHeight() * 0.5f, fDefaultRad);
		addBall(ScreenWidth() * 0.75f, ScreenHeight() * 0.5f, fDefaultRad);
		

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) {
		
		Fill(0, 0, ScreenWidth(), ScreenHeight(), ' '); // clear screen
		/*
		srand(time(NULL));

		// random color
		COLOUR color;
		
		color = COLOUR(5);
		*/
	// drawing balls
		for (auto bl : vecBalls)
			DrawWireFrameModel(modelCircle, bl.px, bl.py, atan2f(bl.vy, bl.vx), bl.radius, FG_WHITE);

		return true;
	}


};



int main() {
	CirclePhysics game;
	if (game.ConstructConsole(160, 100, 8, 8)) // we can't change second value where now is 100 (throw exception)
		game.Start();
	else
		std::cout << L"Could not construct console" << std::endl;

	return 0;
}
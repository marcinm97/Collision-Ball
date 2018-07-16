

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
	sBall* pSelectBall;

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
		pSelectBall = nullptr;
	}

	bool OnUserCreate() {
		// define Circle Model
		modelCircle.push_back({ 0.0f,0.0f });

		int nPoints = 20;
		for (int i = 0; i < nPoints; ++i)
			modelCircle.push_back({ cosf(i / (float)(nPoints - 1) * 2.0f * 3.14159f),sinf(i / (float)(nPoints - 1)* 2.0f * 3.14159f) });
		// generating points to draw objects

		float fDefaultRad = 10.0f;

		addBall(ScreenWidth() * 0.25f, ScreenHeight() * 0.5f, fDefaultRad);
		addBall(ScreenWidth() * 0.75f, ScreenHeight() * 0.5f, fDefaultRad);
		addBall(ScreenWidth() * 0.75f, ScreenHeight() * 0.9f, fDefaultRad);
		

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) {
		auto DoCirclesOverlap = [](float x1, float y1, float r1, float x2, float y2, float r2) {  // lambda function which returns bool
			// we calculate length betweean both points according coordinates
			return fabs((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)) <= (r1 + r2)*(r1 + r2);  // count of radius to "pow"
		};
		auto IsPointInCircle = [](float x1, float y1, float r1, float px, float py) {
			return fabs((x1 - px)*(x1 - px) + (y1 - py)* (y1 - py)) < (r1*r1);         // checking if mouse is in a circle range
		};

		if (m_mouse[0].bPressed){  // what happens when we press left mouse button
			pSelectBall = nullptr;
			for (auto& ball : vecBalls) {
				if (IsPointInCircle(ball.px, ball.py,ball.radius, m_mousePosX, m_mousePosY)) {
					pSelectBall = &ball;
					break;
				}
			}
		}

		if (m_mouse[0].bHeld) {
			if (pSelectBall != nullptr) {
				pSelectBall->px = m_mousePosX;
				pSelectBall->py = m_mousePosY;
			}
		}

		if (m_mouse[0].bReleased) {
			pSelectBall = nullptr;
		}
		for (auto& ball : vecBalls)
		{
			for (auto& target : vecBalls) {
				if (ball.id != target.id)
				{
					if (DoCirclesOverlap(ball.px, ball.py, ball.radius, target.px, target.py, target.radius))
					{
						float fDistance = (sqrtf((ball.px - target.px)*(ball.px - target.px)) + sqrtf((ball.py - target.py) * (ball.py - target.py)));
						float fOverlap = 0.5f * (fDistance - ball.radius - target.radius);

						// current ball
						ball.px -= fOverlap * (ball.px - target.px) / fDistance;
						ball.py -= fOverlap * (ball.py - target.py) / fDistance;

						// target ball
						target.px += fOverlap * (ball.px - target.px) / fDistance;
						target.py += fOverlap * (ball.py - target.py) / fDistance;
					}
				}

			}
		}
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
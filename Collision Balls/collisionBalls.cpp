#include "collisionBallsHeader.h"


CirclePhysics::CirclePhysics() {
	m_sAppName = L"Circle Physics";
}

bool CirclePhysics::OnUserCreate() {
	// define Circle Model
	modelCircle.push_back({ 0.0f,0.0f });

	int nPoints = 20;
	for (int i = 0; i < nPoints; ++i)
		modelCircle.push_back({ cosf(i / (float)(nPoints - 1) * 2.0f * 3.14159f),sinf(i / (float)(nPoints - 1)* 2.0f * 3.14159f) });
		// generating coordinates for objects

	float fDefaultRad = 4.0f;

	addBall(ScreenWidth() * 0.25f, ScreenHeight() * 0.5f, fDefaultRad);
	addBall(ScreenWidth() * 0.75f, ScreenHeight() * 0.5f, fDefaultRad);

	return true;
}

bool CirclePhysics::OnUserUpdate(float fElapsedTime) {

	Fill(0, 0, ScreenWidth(), ScreenHeight(), ' '); // clear screen

	// drawing balls
	for (auto bl : vecBalls)
		DrawWireFrameModel(modelCircle, bl.px, bl.py, atan2f(bl.vy, bl.vx), bl.radius, FG_WHITE);

	return true;
}
void CirclePhysics::addBall(float x, float y, float r) {
	sBall b;
	b.px = x;
	b.py = y;

	b.vx = 0.0f;
	b.vy = 0.0f;

	b.ax = 0.0f;
	b.ay = 0.0f;

	b.radius = r;

	b.id = vecBalls.size();

	vecBalls.emplace_back(b);  // we're using move constructor
}
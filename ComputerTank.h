#pragma once
#include <windows.h>		// Header File For Windows
#include "glew.h"
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <math.h>
#include "OBB.h"
#include "Image_Loading/nvImage.h"
#include "FreeType.h"
#include <iostream>
#include <vector>

using namespace std;

class ComputerTank
{

private:

	const float PI = 3.1415926535897932384626433832795f;

public:

	OBB    obb;
	GLuint TankBody;
	GLuint TankBarrel;
	bool keys[256];
	float speed = 4;
	float x = 150;
	float y = 0;
	float v = 0;
	float lastx = 150;
	float lasty = 0;
	float compMatrix[16];
	float direction = 0;
	float ticks;
	float pIndex = 0;
	vector<Point> movementPoints;

	ComputerTank() { }

	void loadTexture();

	void drawTank();

	void incrementMovement();

	void tank1SetPoints();
	
	void tank2SetPoints();
	
	void tank3SetPoints();
	
	void tank4SetPoints();

	void moveTank();

	void setOBBPoints();

	void handleCollision();


	static std::vector<Point> drawCircleClockwise(float x, float y, float radius, float startingAngle, float endAngle)
	{
		std::vector<Point> points;



		for (float i = startingAngle; i > endAngle; i -= 1)
		{
			Point point;
			point.x = x + radius * cosf(i * (3.1415926535897932384626433832795f / 180.0f));
			point.y = y + radius * sinf(i * (3.1415926535897932384626433832795f / 180.0f));
			points.push_back(point);
		}



		return points;
	}

	static std::vector<Point> drawCircleAnticlockwise(float x, float y, float radius, float startingAngle, float endAngle)
	{
		std::vector<Point> points;

		for (float i = startingAngle; i < endAngle; i += 1)
		{
			Point point;
			point.x = x + radius * cosf(i * (3.1415926535897932384626433832795f / 180.0f));
			point.y = y + radius * sinf(i * (3.1415926535897932384626433832795f / 180.0f));
			points.push_back(point);
		}



		return points;
	}
};


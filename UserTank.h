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

class UserTank
{

private:
	
	const float PI = 3.1415926535897932384626433832795f;

public:

	//POINT point;
	OBB   tankOBB;
	GLuint userTankBody;
	GLuint userTankBarrel;
	bool keys[256];
	float speed = 0.06f;
	float x = -20;
	float y = 0;
	float v = 0;
	float lastx = 0;
	float lasty = 0;
	float matrix[16];
	float direction = 0;
	
	UserTank() { }

	void loadTexture();

	void drawTank();

	void setOBBPoints();

	void moveTank();

	void handleKeys(double deltaTime);

	void handleOffTrack();

	void handleBarrierCollision();
};
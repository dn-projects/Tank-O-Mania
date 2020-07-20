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

public:

	OBB   tankOBB;
	GLuint tracks;
	GLuint body;
	GLuint barrel;
	float x = 0;
	float y = 0;
	float v = 0;
	float matrix[16];
	float direction = 0;
	
	UserTank() { }

	void fillTexture();

	void drawTank();

	void setOBBPoints();
};
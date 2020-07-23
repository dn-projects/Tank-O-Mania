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

class Track
{

private:

public:

	GLuint road1;
	GLuint road2;
	GLuint realisticGrass1;
	OBB trackOBB;
	float matrix[16];

	Track() { }

	void loadTexture();

	void drawTrackBackground();

	void drawEasyTrack();

	void drawTrackOBB(float x,     float y, 
		             float width, float height);

	void drawIntermediateTrack();

	void drawHardTrack();
};


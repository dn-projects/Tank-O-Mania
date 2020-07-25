#pragma once
#include <windows.h>		// Header File For Windows
#include "glew.h"
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <math.h>
#include "OBB.h"
#include "Image_Loading/nvImage.h"
#include "FreeType.h"
#include "Asset.h"
#include <iostream>
#include <vector>

using namespace std;

class Track
{

private:

public:

	GLuint background;
	OBB trackOBB;
	float matrix[16];
	std::vector<Asset> mapAssets;

	Track() { }

	void loadTexture();

	void drawTrackBackground();

	void drawEasyTrack();

	void drawTrackOBB(float x,     float y, 
		             float width, float height);

	void drawIntermediateTrack();

	void drawHardTrack();

	
	void drawMapAssets();
};


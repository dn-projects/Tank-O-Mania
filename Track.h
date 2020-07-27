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

	OBB trackOBB;
	GLuint background;
	float matrix[16];
	vector<Asset> mapAssets;
	vector<OBB> mapOffTrackOBBs;
	vector<Asset> mapBarrierOBBs;

	Track() { }

	void loadTexture();

	void drawOffTrackOBB();

	void drawTrackBarrierOBB();

	void drawIntermediateTrack();

	void drawHardTrack();

	
	void drawMapAssets();
};


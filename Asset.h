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

using namespace std;

class Asset
{

private:

public:

	OBB OBB1;
	OBB OBB2;
	OBB OBB3;
	float OBB1matrix[16];
	float x = 0;
	float y = 0;
	float height = 128;
	float width = 128;
	GLuint texture;

	void applyTexture(int tileNumber);

	void drawAsset();

	void setOBB1Points(Point bottomLeft, Point topLeft, Point topRight, Point bottomRight);
	
	void setOBB2Points(Point bottomLeft, Point topLeft, Point topRight, Point bottomRight);
	
	void setOBB3Points(Point bottomLeft, Point topLeft, Point topRight, Point bottomRight);
};


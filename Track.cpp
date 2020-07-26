#include "Track.h"
#include "Asset.h"
#include <iostream>
#include <fstream>
#include <sstream>

GLuint loadTrackPNG(char* name)
{
	// Texture loading object
	nv::Image img;

	GLuint myTextureID;

	// Return true on success
	if (img.loadImageFromFile(name))
	{
		glGenTextures(1, &myTextureID);
		glBindTexture(GL_TEXTURE_2D, myTextureID);
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
		glTexImage2D(GL_TEXTURE_2D, 0, img.getInternalFormat(), img.getWidth(), img.getHeight(), 0, img.getFormat(), img.getType(), img.getLevel(0));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
	}

	else
		MessageBox(NULL, "Failed to load texture", "End of the world", MB_OK | MB_ICONINFORMATION);

	return myTextureID;
}

void Track::loadTexture()
{
	ifstream inFile;
	inFile.open("PNG/Assets/Map.txt");
	int x = -1920;
	int y = 1920;
	string row;
	if (inFile.is_open()) 
	{
		while (getline(inFile, row))
		{
			istringstream ss(row);
			string token;

			while (getline(ss, token, ' '))
			{
				Asset asset = Asset();
				asset.x = x;
				asset.y = y;
				asset.applyTexture(stoi(token));
				mapAssets.push_back(asset);
				x += 128;

			}
			x = -1920;
			y -= 128;
		}
	}
}

void Track::drawMapAssets()
{
	for (Asset asset : mapAssets) 
	{
		asset.drawAsset();
		glPushMatrix();
		glColor3f(1, 1, 1);
		glPointSize(2.0);
		glBegin(GL_POINTS);
		glVertex2f(asset.x, asset.y);
		glEnd();
		glPopMatrix();
	}
}

void Track::drawTrackOBB(float x,
	float y,
	float width,
	float height)
{
	glPushMatrix();
	glColor3f(1, 1, 1);
	glBegin(GL_LINE_STRIP);
	glVertex2f(x, y);
	glVertex2f(x, y + height);
	glVertex2f(x + width, y + height);
	glVertex2f(x + width, y);
	glEnd();
	glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
	glPopMatrix();

	trackOBB.vertOriginal[0].x = x; 
	trackOBB.vertOriginal[0].y = y;

	trackOBB.vertOriginal[1].x = x;
	trackOBB.vertOriginal[1].y = y + height;

	trackOBB.vertOriginal[2].x = x + width;
	trackOBB.vertOriginal[2].y = y + height;

	trackOBB.vertOriginal[3].x = x + width;
	trackOBB.vertOriginal[3].y = y;
}

void Track::drawIntermediateTrack()
{
	// medium map
	glPushMatrix();
	glColor3f(1, 1, 1);
	glBegin(GL_LINE_STRIP);
	glVertex2f(0, 0);
	glVertex2f(0, 2500);
	glVertex2f(-2500, 2500);
	glVertex2f(-2500, 1900);
	glVertex2f(-1500, 1900);
	glVertex2f(-1500, -1900);
	glVertex2f(-2200, -1900);
	glVertex2f(-2200, -2500);
	glVertex2f(2500, -2500);
	glVertex2f(2500, 2100);
	glVertex2f(1800, 2100);
	glVertex2f(1800, -1000);
	glVertex2f(1000, -1000);
	glVertex2f(1000, -500);
	glVertex2f(0, -500);
	glVertex2f(0, 0);
	glEnd();
	glPopMatrix();
}

void Track::drawHardTrack()
{
	// hard map
	glPushMatrix();
	glColor3f(1, 1, 1);
	glBegin(GL_LINE_STRIP);
	glVertex2f(0, 0);
	glVertex2f(0, 1200);
	glVertex2f(1000, 1200);
	glVertex2f(1000, 0);
	glVertex2f(1900, 0);
	glVertex2f(1900, 2500);
	glVertex2f(2500, 2500);
	glVertex2f(2500, -2500);
	glVertex2f(-2500, -2500);
	glVertex2f(-2500, -1800);
	glVertex2f(-1400, -1800);
	glVertex2f(-1400, -1100);
	glVertex2f(-2500, -1100);
	glVertex2f(-2500, 2500);
	glVertex2f(200, 2500);
	glVertex2f(200, 2000);
	glVertex2f(-1800, 2000);
	glVertex2f(-1800, 500);
	glVertex2f(-1200, 500);
	glVertex2f(-1200, -400);
	glVertex2f(-600, -400);
	glVertex2f(-600, -1500);
	glVertex2f(900, -1500);
	glVertex2f(900, -800);
	glVertex2f(0, -800);
	glVertex2f(0, 0);
	glEnd();
	glPopMatrix();
}
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

void Track::drawOffTrackOBB()
{
	OBB obb1 = OBB();
	obb1.vert[0].x = -1040;
	obb1.vert[0].y = -1168;
	obb1.vert[1].x = -1040;
	obb1.vert[1].y = 1168;
	obb1.vert[2].x = -112;
	obb1.vert[2].y = 1168;
	obb1.vert[3].x = -112;
	obb1.vert[3].y = -1168;
	mapOffTrackOBBs.push_back(obb1);

	OBB obb2 = OBB();
	obb2.vert[0].x = -112;
	obb2.vert[0].y = -1168;
	obb2.vert[1].x = -112;
	obb2.vert[1].y = -482;
	obb2.vert[2].x = 1265;
	obb2.vert[2].y = -482;
	obb2.vert[3].x = 1265;
	obb2.vert[3].y = -1168;
	mapOffTrackOBBs.push_back(obb2);

	OBB obb3 = OBB();
	obb3.vert[0].x = 1265;
	obb3.vert[0].y = -1168;
	obb3.vert[1].x = 1265;
	obb3.vert[1].y = 910;
	obb3.vert[2].x = 1420;
	obb3.vert[2].y = 910;
	obb3.vert[3].x = 1420;
	obb3.vert[3].y = -1168;
	mapOffTrackOBBs.push_back(obb3);

	OBB obb4 = OBB();
	obb4.vert[0].x = -1920;
	obb4.vert[0].y = -1920;
	obb4.vert[1].x = -1920;
	obb4.vert[1].y = 2048;
	obb4.vert[2].x = -1392;
	obb4.vert[2].y = 2048;
	obb4.vert[3].x = -1392;
	obb4.vert[3].y = -1920;
	mapOffTrackOBBs.push_back(obb4);

	OBB obb5 = OBB();
	obb5.vert[0].x = -1920;
	obb5.vert[0].y = -1920;
	obb5.vert[1].x = -1920;
	obb5.vert[1].y = -1520;
	obb5.vert[2].x = 1920;
	obb5.vert[2].y = -1520;
	obb5.vert[3].x = 1920;
	obb5.vert[3].y = -1920;
	mapOffTrackOBBs.push_back(obb5);

	OBB obb6 = OBB();
	obb6.vert[0].x = -1920;
	obb6.vert[0].y = 1520;
	obb6.vert[1].x = -1920;
	obb6.vert[1].y = 2048;
	obb6.vert[2].x = 1920;
	obb6.vert[2].y = 2048;
	obb6.vert[3].x = 1920;
	obb6.vert[3].y = 1520;
	mapOffTrackOBBs.push_back(obb6);

	OBB obb7 = OBB();
	obb7.vert[0].x = 1772;
	obb7.vert[0].y = -1920;
	obb7.vert[1].x = 1772;
	obb7.vert[1].y = 2048;
	obb7.vert[2].x = 1920;
	obb7.vert[2].y = 2048;
	obb7.vert[3].x = 1920;
	obb7.vert[3].y = -1920;
	mapOffTrackOBBs.push_back(obb7);

	OBB obb8 = OBB();
	obb8.vert[0].x = 240;
	obb8.vert[0].y = -130;
	obb8.vert[1].x = 240;
	obb8.vert[1].y = 1520;
	obb8.vert[2].x = 913;
	obb8.vert[2].y = 1520;
	obb8.vert[3].x = 913;
	obb8.vert[3].y = -130;
	mapOffTrackOBBs.push_back(obb8);

	OBB obb9 = OBB();
	obb9.vert[0].x = 913;
	obb9.vert[0].y = 1264;
	obb9.vert[1].x = 913;
	obb9.vert[1].y = 1520;
	obb9.vert[2].x = 1920;
	obb9.vert[2].y = 1520;
	obb9.vert[3].x = 1920;
	obb9.vert[3].y = 1264;
	mapOffTrackOBBs.push_back(obb9);
}

void Track::drawTrackBarrierOBB()
{
	char png[] = "PNG/Assets/fenceRed.png";

	//Asset asset1 = Asset();
	//asset1.x = -200;
	//asset1.y = 0;
	//asset1.width = 16;
	//asset1.height = 48;
	//asset1.texture = loadTrackPNG(png);
	//asset1.setOBB1Points({-200,0}, { -200,48 }, { -184,48 }, { -184, 0 });
	//mapBarrierOBBs.push_back(asset1);

	for (float i = 0; i < 1100; i += 48)
	{
		Asset asset = Asset();
		asset.x = -200;
		asset.y = i;
		asset.width = 16;
		asset.height = 48;
		asset.texture = loadTrackPNG(png);
		asset.setOBB1Points({ -200,i }, { -200,i + 48 }, { -184,i + 48 }, { -184, i });
		mapBarrierOBBs.push_back(asset);
	}
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
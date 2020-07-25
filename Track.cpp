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
	//vector<Asset> mapAssets;
	if (inFile.is_open()) {
		//cout << "test" << endl;
		//Read until no more lines in text file to read
		while (getline(inFile, row))
			//while (inFile >> row)
		{
			istringstream ss(row);
			string token;

			//Separate string based on commas and white spaces
			while (getline(ss, token, ' '))
			{
				Asset asset = Asset();
				asset.x = x;
				asset.y = y;
				asset.applyTexture(stoi(token));
				//Push each token to the vector
				mapAssets.push_back(asset);
				x += 128;

			}

			x = -1920;
			y -= 128;

		}
	}
}





/*char backgroundPNG[] = "PNG/Assets/towerDefense_tile098.png";

background = loadTrackPNG(backgroundPNG);
for (int i = -64; i < 640; i += 128)
{
	char png[] = "PNG/Assets/towerDefense_tile257.png";
	Asset asset = Asset();
	asset.x = -64;
	asset.y = i;
	asset.applyTexture(png);
	mapAssets.push_back(asset);

	char png1[] = "PNG/Assets/grassLeft1.png";
	Asset asset2 = Asset();
	asset2.x = -192;
	asset2.y = i;
	asset2.applyTexture(png1);
	mapAssets.push_back(asset2);

	char png2[] = "PNG/Assets/grassRight1.png";
	Asset asset3 = Asset();
	asset3.x = 64;
	asset3.y = i;
	asset3.applyTexture(png2);
	mapAssets.push_back(asset3);
}*/


void Track::drawTrackBackground()
{
	// glPushMatrix - draws the whole map size 6000x6000 
	//and texture maps the realistic grass to it
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D, background);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex2f(-3000, -3000);
	glTexCoord2f(0, 80); glVertex2f(-3000, 3000);
	glTexCoord2f(80, 80); glVertex2f(3000, 3000);
	glTexCoord2f(80, 0); glVertex2f(3000, -3000);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void Track::drawEasyTrack()
{
	// left line
	glPushMatrix();
	glColor3f(1, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(0, 0);
	glVertex2f(0, 500);
	glVertex2f(-2000, 500);
	glVertex2f(-2000, -2000);
	glVertex2f(2000, -2000);
	glVertex2f(2000, 2000);
	glVertex2f(1000, 2000);
	glVertex2f(1000, -1000);
	glVertex2f(0, -1000);
	glVertex2f(0, 0);
	glEnd();
	glPopMatrix();

	// right line
	glPushMatrix();
	glColor3f(1, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(100, 0);
	glVertex2f(100, 750);
	glVertex2f(-2100, 750);
	glVertex2f(-2100, -2100);
	glVertex2f(2100, -2100);
	glVertex2f(2100, 2100);
	glVertex2f(900, 2100);
	glVertex2f(900, -900);
	glVertex2f(100, -900);
	glVertex2f(100, 0);
	glEnd();
	glPopMatrix();
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


void Track::drawMapAssets()
{
	for (Asset asset : mapAssets) {
		asset.drawAsset();
	}

}
#include "Track.h"

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
	char road1PNG[] = "PNG/Environment/realisticRoad1.png";
	char road2PNG[] = "PNG/Environment/realisticRoad3.png";
	char realisticGrass1PNG[] = "PNG/Environment/realisticGrass1.png";

	road1 = loadTrackPNG(road1PNG);
	road2 = loadTrackPNG(road2PNG);
	realisticGrass1 = loadTrackPNG(realisticGrass1PNG);
}

void Track::drawTrackBackground()
{
	// glPushMatrix - draws the whole map size 6000x6000 
	//and texture maps the realistic grass to it
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D, realisticGrass1);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex2f(-3000, -3000);
	glTexCoord2f(0, 60); glVertex2f(-3000, 3000);
	glTexCoord2f(60, 60); glVertex2f(3000, 3000);
	glTexCoord2f(60, 0); glVertex2f(3000, -3000);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// draws road 01
	// road width is 300 and height is 1400
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPEAT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, road1);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex2f(-150, -900);
	glTexCoord2f(0, 3); glVertex2f(-150, 500);
	glTexCoord2f(1, 3); glVertex2f(150, 500);
	glTexCoord2f(1, 0); glVertex2f(150, -900);
	glEnd();
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// draws road 01
	// road width is 300 and height is 1400
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPEAT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, road2);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex2f(-150, 500);
	glTexCoord2f(0, 1); glVertex2f(-148, 750);
	glTexCoord2f(1, 1); glVertex2f(150, 750);
	glTexCoord2f(1, 0); glVertex2f(148, 500);
	glEnd();
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// draws road 02
	//glPushMatrix();
	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, road);
	////glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPEAT);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glTranslatef(75,550, 0);
	//glRotatef(45, 0, 0, 1);
	//glBegin(GL_POLYGON);
	//glTexCoord2f(0, 0); glVertex2f(-100,-50);
	//glTexCoord2f(0, 1); glVertex2f(-100, 50);
	//glTexCoord2f(1, 1); glVertex2f(50, 50);
	//glTexCoord2f(1, 0); glVertex2f(50, -50);
	//glEnd();
	//glDisable(GL_BLEND);
	//glDisable(GL_TEXTURE_2D);
	//glPopMatrix();
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
	glVertex2f(100, 600);
	glVertex2f(-2100, 600);
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
	glColor3f(1,1,1);
	glBegin(GL_LINE_STRIP);
		glVertex2f(x         ,y);
		glVertex2f(x         ,y + height);
		glVertex2f(x + width ,y + height);
		glVertex2f(x + width ,y);
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
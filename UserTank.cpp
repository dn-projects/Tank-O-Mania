#include "UserTank.h"

GLuint loadTankPNG(char* name)
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

void UserTank::loadTexture()
{
	char userTankBodyPNG[] = "PNG/Retina/towerDefense_tile268.png";
	char userTankBarrelPNG[] = "PNG/Retina/towerDefense_tile291.png";

	userTankBody = loadTankPNG(userTankBodyPNG);
	userTankBarrel = loadTankPNG(userTankBarrelPNG);
}

void UserTank::drawTank()
{
	// glPushMatrix - draws the tank tracks and applies 
	//movement to tank
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, userTankBody);
	glTranslatef(x, y, 0.0);
	glRotatef(direction, 0, 0, 1);
	glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);	glVertex2f(-30, -30);
	glTexCoord2f(0, 1);	glVertex2f(-30, 30);
	glTexCoord2f(1, 1);	glVertex2f(30, 30);
	glTexCoord2f(1, 0);	glVertex2f(30, -30);
	glEnd();
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// glPushMatrix - draws the tank barrel and applies 
	//movement to barrel
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, userTankBarrel);
	glTranslatef(x, y, 0.0);
	//glRotatef((atan2(point.y, point.x) * 180 / PI),0,0,1);
	glRotatef(direction, 0, 0, 1);
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);	glVertex2f(-30, -30);
	glTexCoord2f(0, 1);	glVertex2f(-30, 30);
	glTexCoord2f(1, 1);	glVertex2f(30, 30);
	glTexCoord2f(1, 0);	glVertex2f(30, -30);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void UserTank::setOBBPoints()
{
	tankOBB.vertOriginal[0].x = -18;
	tankOBB.vertOriginal[0].y = -26;
	
	tankOBB.vertOriginal[1].x = -18;
	tankOBB.vertOriginal[1].y = 26;

	tankOBB.vertOriginal[2].x = 18;
	tankOBB.vertOriginal[2].y = 26;

	tankOBB.vertOriginal[3].x = 18;
	tankOBB.vertOriginal[3].y = -26;
}
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

void UserTank::fillTexture()
{
	char tracksPNG[] = "PNG/Tanks/tracksSmall.png";
	char bodyPNG[] = "PNG/Tanks/tankBlue_outline.png";
	char barrelPNG[] = "PNG/Tanks/barrelBlue.png";

	tracks = loadTankPNG(tracksPNG);
	body = loadTankPNG(bodyPNG);
	barrel = loadTankPNG(barrelPNG);
}

void UserTank::drawTank()
{
	// glPushMatrix - draws the tank tracks and applies movement to tracks
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, tracks);
	glTranslatef(x, y, 0.0);
	glRotatef(direction, 0, 0, 1);
	glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);	glVertex2f(-18, -26);
	glTexCoord2f(0, 1);	glVertex2f(-18, 26);
	glTexCoord2f(1, 1);	glVertex2f(18, 26);
	glTexCoord2f(1, 0);	glVertex2f(18, -26);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// glPushMatrix - draws the tank body and applies movement to body
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, body);
	glTranslatef(x, y, 0.0);
	glRotatef(direction, 0, 0, 1);
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);	glVertex2f(-15, -20);
	glTexCoord2f(0, 1);	glVertex2f(-15, 20);
	glTexCoord2f(1, 1);	glVertex2f(15, 20);
	glTexCoord2f(1, 0);	glVertex2f(15, -20);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// glPushMatrix - draws the tank barrel and applies movement to barrel
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, barrel);
	glTranslatef(x, y, 0.0);
	glRotatef(direction, 0, 0, 1);
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);	glVertex2f(-4, 0);
	glTexCoord2f(0, 1);	glVertex2f(-4, 40);
	glTexCoord2f(1, 1);	glVertex2f(4, 40);
	glTexCoord2f(1, 0);	glVertex2f(4, 0);
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
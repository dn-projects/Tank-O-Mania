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
	char userTankBodyPNG[] = "PNG/Assets/towerDefense_tile268.png";
	char userTankBarrelPNG[] = "PNG/Assets/towerDefense_tile291.png";

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
	glTexCoord2f(0, 0);	glVertex2f(-25, -25);
	glTexCoord2f(0, 1);	glVertex2f(-25, 25);
	glTexCoord2f(1, 1);	glVertex2f(25, 25);
	glTexCoord2f(1, 0);	glVertex2f(25, -25);
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
	glTexCoord2f(0, 0);	glVertex2f(-25, -25);
	glTexCoord2f(0, 1);	glVertex2f(-25, 25);
	glTexCoord2f(1, 1);	glVertex2f(25, 25);
	glTexCoord2f(1, 0);	glVertex2f(25, -25);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	tankOBB.transformPoints(matrix);
	setOBBPoints();
}

void UserTank::setOBBPoints()
{
	tankOBB.vertOriginal[0].x = -16;
	tankOBB.vertOriginal[0].y = -22;

	tankOBB.vertOriginal[1].x = -16;
	tankOBB.vertOriginal[1].y = 24;

	tankOBB.vertOriginal[2].x = 16;
	tankOBB.vertOriginal[2].y = 24;

	tankOBB.vertOriginal[3].x = 16;
	tankOBB.vertOriginal[3].y = -22;
}

void UserTank::moveTank()
{
	lastx = x;
	lasty = y;

	x += v * cosf((90 + direction) * (PI / 180.0f));
	y += v * sinf((90 + direction) * (PI / 180.0f));
}

void UserTank::handleKeys(double deltaTime)
{
	if (keys[VK_LEFT])
	{
		direction += 4 * deltaTime;
	}
	if (keys[VK_RIGHT])
	{
		direction -= 4 * deltaTime;
	}
	if (keys[VK_UP])
	{
		if (v > 10)
		{
			v = v;
		}
		else if (v > 5)
		{
			speed = 0.004f;
			v += speed * deltaTime;
		}
		else
		{
			speed = 0.3f;
			v += speed * deltaTime;
		}
	}
	if (keys[VK_DOWN])
	{
		float downSpeed = v > 0 ? speed * 10 : speed / 4;
		v -= downSpeed * deltaTime;
	}
}

void UserTank::handleOffTrack()
{
	if (1.5 > v)
	{
		speed = 0.1f;
	}
	else
	{
		v -= 0.6f;
	}
}

void UserTank::handleBarrierCollision()
{
	v *= -0.5f;
	int i = 2;

	if (x < lastx && y < lasty)
	{
		x = lastx + i;
		y = lasty + i;
		return;
	}
	if (y == lasty && x < lastx)
	{
		x = lastx + i;
		return;
	}

	if (x < lastx && y > lasty)
	{
		y = lasty - i;
		x = lastx + i;
		return;
	}
	if (x > lastx && y > lasty)
	{
		y = lasty - i;
		x = lastx - i;
		return;
	}
	if (y == lasty && x > lastx)
	{
		x = lastx - i;
		return;
	}
	if (x > lastx && y < lasty)
	{
		x = lastx - i;
		y = lasty + i;
		return;
	}
	if (x == lastx && y < lasty)
	{
		y = lasty + i;
		return;
	}
	if (x == lastx && y > lasty)
	{
		y = lasty - i;
		return;
	}
}
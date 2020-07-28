#include "ComputerTank.h"
#include <cmath>

GLuint loadComputerTankPNG(char* name)
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

void ComputerTank::loadTexture()
{
	char TankBodyPNG[] = "PNG/Assets/towerDefense_tile269.png";
	char TankBarrelPNG[] = "PNG/Assets/towerDefense_tile292.png";

	TankBody = loadComputerTankPNG(TankBodyPNG);
	TankBarrel = loadComputerTankPNG(TankBarrelPNG);
}

void ComputerTank::drawTank()
{
	// glPushMatrix - draws the tank tracks and applies 
	//movement to tank
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, TankBody);
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
	glBindTexture(GL_TEXTURE_2D, TankBarrel);
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
	obb.transformPoints(matrix);
	setOBBPoints();
}

void ComputerTank::incrementMovement()
{
	ticks += 0.005;
	if (ticks > 1)
	{
		ticks = 0;
		if (movementPoints.size() > pIndex)
		{
			pIndex += 1;
		}
		else
		{
			pIndex = 0;
		}
	}
}

void ComputerTank::setMovementPoints()
{
	Point p0 = { 150, 0};
	movementPoints.push_back(p0);

	Point p1 = { 150, 300 };
	movementPoints.push_back(p1);
	
	Point p2 = { 500, 500 };
	movementPoints.push_back(p2);
	
	/*Point p3 = { 80, 50 };
	movementPoints.push_back(p3);

	Point p4 = { 150,0 };
	movementPoints.push_back(p4);*/
}

void ComputerTank::moveTank()
{
		// dealing with collision A - stop this function on collision and run Sleep() 
	    // then check if still colliding and then continue function if not collision

		// dealing with collision B - if colliding, stop running function and do collision response, 
		// once not colliding continue function

		pIndex + 1 >= movementPoints.size() ? pIndex = 0 : pIndex = pIndex;

		//direction = 0;



		//// deals with movement
		x = (movementPoints[pIndex].x + (ticks * (movementPoints[pIndex + 1].x - movementPoints[pIndex].x)));
		y = (movementPoints[pIndex].y + (ticks * (movementPoints[pIndex + 1].y - movementPoints[pIndex].y)));

		//float numerator = (movementPoints[pIndex].x * movementPoints[pIndex + 1].x) + (movementPoints[pIndex].y * movementPoints[pIndex + 1].y);

		//// denominator
		//float denominator1 = (sqrt(pow(2, movementPoints[pIndex].x) + pow(2, movementPoints[pIndex].y)));
		//float denominator2 = (sqrt(pow(2, movementPoints[pIndex + 1].x) + pow(2, movementPoints[pIndex + 1].y)));

		////float dot = (movementPoints[pIndex].x * movementPoints[pIndex + 1].x) + (movementPoints[pIndex].y * movementPoints[pIndex + 1].y);
		//float det = (movementPoints[pIndex].x * movementPoints[pIndex + 1].y) - (movementPoints[pIndex].y * movementPoints[pIndex + 1].x);

		////direction = (atan2(dot, det) * 180) / PI;
		//
		//float angle = (acos(numerator / (denominator1 * denominator2)) * (180 / PI));

		//if (det > 0)
		//{
		//	direction += angle;
		//}
		//else
		//{
		//	direction -= angle;
		//}


		direction = 0;

		Point currentPoint;
		currentPoint.x = x;
		currentPoint.y = y + 30;

		Point cb;
		cb.x = currentPoint.x - x;
		cb.y = currentPoint.y - y;

		Point ca;
		ca.x = movementPoints[pIndex + 1].x - x;
		ca.y = movementPoints[pIndex + 1].y - y;



		float num = (cb.x * ca.x) + (cb.y * ca.y);
		float sqrt1 = sqrt((cb.x * cb.x) + (cb.y * cb.y));
		float sqrt2 = sqrt((ca.x * ca.x) + (ca.y * ca.y));
		float angle = (acos(num / (sqrt1 * sqrt2)) * (180.0 / PI));

		// a = endPoint
		// b = currentPoint
		// c = pos

		float det = ((currentPoint.x - x) * (movementPoints[pIndex + 1].y - y)) - ((movementPoints[pIndex + 1].x - x) * (currentPoint.y - y));

		if (det > 0) {
			direction += angle;
		}
		else {
			direction -= angle;
		}
}

void ComputerTank::setOBBPoints()
{
	obb.vertOriginal[0].x = -18;
	obb.vertOriginal[0].y = -26;

	obb.vertOriginal[1].x = -18;
	obb.vertOriginal[1].y = 26;

	obb.vertOriginal[2].x = 18;
	obb.vertOriginal[2].y = 26;

	obb.vertOriginal[3].x = 18;
	obb.vertOriginal[3].y = -26;
	obb.transformPoints(matrix);
}

void ComputerTank::handleCollision()
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
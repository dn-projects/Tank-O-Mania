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

	setOBBPoints();
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
    glGetFloatv(GL_MODELVIEW_MATRIX, compMatrix);
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
	glBindTexture(GL_TEXTURE_2D, TankBarrel);
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

   
    obb.transformPoints(compMatrix);
	
}

void ComputerTank::incrementMovement()
{
	Point point1 = { movementPoints[pIndex].x, movementPoints[pIndex].y };
	Point point2 = { movementPoints[pIndex + 1].x, movementPoints[pIndex + 1].y };

	float vectorX = (point1.x - point2.x);
	float vectorY = (point1.y - point2.y);

	vectorX = (vectorX * vectorX);
	vectorY = (vectorY * vectorY);

	float twoVectorDistance = sqrt(vectorX + vectorY);

	ticks += (6 / twoVectorDistance);  // change 1.5 to adjust travel speed of computerTank 
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

	Point p1 = { 150, 1240 };
	movementPoints.push_back(p1);

	vector<Point> leftcorner1 = ComputerTank::drawCircleAnticlockwise(30, 1250, 120, 0, 90);
	std::copy(leftcorner1.begin(), leftcorner1.end(), std::back_inserter(movementPoints));

	Point p2 = { -1040, 1300 };
	movementPoints.push_back(p2);

	vector<Point> leftcorner2 = ComputerTank::drawCircleAnticlockwise(-1050, 1180, 120, 90, 180);
	std::copy(leftcorner2.begin(), leftcorner2.end(), std::back_inserter(movementPoints));

	Point p3 = { -1250, -1270 };
	movementPoints.push_back(p3);

	vector<Point> leftcorner3 = ComputerTank::drawCircleAnticlockwise(-1130, -1280, 120, 180, 270);
	std::copy(leftcorner3.begin(), leftcorner3.end(), std::back_inserter(movementPoints));
	
	Point p4 = { 1440,-1400 };
	movementPoints.push_back(p4);

	vector<Point> leftcorner4 = ComputerTank::drawCircleAnticlockwise(1450, -1280, 120, 270, 360);
	std::copy(leftcorner4.begin(), leftcorner4.end(), std::back_inserter(movementPoints));

	Point p5 = { 1500,890 };
	movementPoints.push_back(p5);

	vector<Point> leftcorner5 = ComputerTank::drawCircleAnticlockwise(1350, 900, 150, 0, 180);
	std::copy(leftcorner5.begin(), leftcorner5.end(), std::back_inserter(movementPoints));

	Point p7 = { 1100,-240 };
	movementPoints.push_back(p7);

	vector<Point> rightcorner1 = ComputerTank::drawCircleClockwise(950, -250, 150, 355, 270);
	std::copy(rightcorner1.begin(), rightcorner1.end(), std::back_inserter(movementPoints));

	Point p8 = { 300,-300 };
	movementPoints.push_back(p8);

	vector<Point> rightcorner2 = ComputerTank::drawCircleClockwise(280, -150, 150, 275, 180);
	std::copy(rightcorner2.begin(), rightcorner2.end(), std::back_inserter(movementPoints));

	Point p9 = { 150, 0};
	movementPoints.push_back(p9);
}

void ComputerTank::moveTank()
{
	

		// dealing with collision A - stop this function on collision and run Sleep() 
	    // then check if still colliding and then continue function if not collision

		// dealing with collision B - if colliding, stop running function and do collision response, 
		// once not colliding continue function

		pIndex + 1 >= movementPoints.size() ? pIndex = 0 : pIndex = pIndex;


		// deals with movement
		x = (movementPoints[pIndex].x + (ticks * (movementPoints[pIndex + 1].x - movementPoints[pIndex].x)));
		y = (movementPoints[pIndex].y + (ticks * (movementPoints[pIndex + 1].y - movementPoints[pIndex].y)));

		direction = 0;

		Point constructionPoint;
		constructionPoint.x = x;
		constructionPoint.y = y + 50;

		Point cb;
		cb.x = constructionPoint.x - x;
		cb.y = constructionPoint.y - y;

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

		float det = ((constructionPoint.x - x) * (movementPoints[pIndex + 1].y - y)) - ((movementPoints[pIndex + 1].x - x) * (constructionPoint.y - y));

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

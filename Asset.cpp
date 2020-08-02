#include "Asset.h"

GLuint loadAssetPNG(char* name)
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

void Asset::applyTexture(int tileNumber)
{
	switch (tileNumber)
	{
	case 0: {
		char png[] = "PNG/Assets/tile0.png";
		texture = loadAssetPNG(png);}
		break;
	case 1: {
		char png1[] = "PNG/Assets/tile1.png";
		texture = loadAssetPNG(png1);}
		break;
	case 2: {
		char png2[] = "PNG/Assets/tile2.png";
		texture = loadAssetPNG(png2);}
		break;
	case 3: {
		char png3[] = "PNG/Assets/tile3.png";
		texture = loadAssetPNG(png3);}
		break;
	case 4: {
		char png4[] = "PNG/Assets/tile4.png";
		texture = loadAssetPNG(png4);}
		break;
	case 5: {
		char png5[] = "PNG/Assets/tile5.png";
		texture = loadAssetPNG(png5);}
		break;
	case 6: {
		char png6[] = "PNG/Assets/tile6.png";
		texture = loadAssetPNG(png6);}
		break;
	case 7: {
		char png7[] = "PNG/Assets/tile7.png";
		texture = loadAssetPNG(png7);}
		break;
	case 8: {
		char png8[] = "PNG/Assets/tile8.png";
		texture = loadAssetPNG(png8);}
		break;
	case 9: {
		char png9[] = "PNG/Assets/tile9.png";
		texture = loadAssetPNG(png9);}
		break;
	case 10: {
		char png10[] = "PNG/Assets/tile10.png";
		texture = loadAssetPNG(png10);}
		break;
	case 11: {
		char png11[] = "PNG/Assets/tile11.png";
		texture = loadAssetPNG(png11);}
		break;
	case 12: {
		char png12[] = "PNG/Assets/tile12.png";
		texture = loadAssetPNG(png12);}
		break;
	case 13: {
		char png13[] = "PNG/Assets/tile13.png";
		texture = loadAssetPNG(png13);}
		break;
	}
}

void Asset::drawAsset()
{
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, texture);
	glGetFloatv(GL_MODELVIEW_MATRIX, OBB1matrix);
	glTranslatef(xTrans,yTrans,0);
	glRotatef(rotation,0,0,1);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex2f(x, y);
	glTexCoord2f(0, yTexture); glVertex2f(x, y + height);
	glTexCoord2f(xTexture, yTexture); glVertex2f(x + width, y + height);
	glTexCoord2f(xTexture, 0); glVertex2f(x + width, y);
	glEnd();
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	
	OBB1.transformPoints(OBB1matrix);
}

void Asset::setOBB1Points(Point bottomLeft, Point topLeft, Point topRight, Point bottomRight)
{
	OBB1.vert[0].x = bottomLeft.x;
	OBB1.vert[0].y = bottomLeft.y;

	OBB1.vert[1].x = topLeft.x;
	OBB1.vert[1].y = topLeft.y;

	OBB1.vert[2].x = topRight.x;
	OBB1.vert[2].y = topRight.y;

	OBB1.vert[3].x = bottomRight.x;
	OBB1.vert[3].y = bottomRight.y;
}

void Asset::setOBB2Points(Point bottomLeft, Point topLeft, Point topRight, Point bottomRight)
{
	//glPushMatrix();
	//glColor3f(1, 1, 1);
	//glBegin(GL_QUADS);
	//glVertex2f(bottomLeft.x, bottomLeft.y);
	//glVertex2f(topLeft.x, topLeft.y);
	//glVertex2f(topRight.x,  topRight.y);
	//glVertex2f(bottomRight.x, bottomRight.y);
	//glEnd();
	//glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
	//glPopMatrix();

	OBB2.vert[0].x = bottomLeft.x;
	OBB2.vert[0].y = bottomLeft.y;

	OBB2.vert[1].x = topLeft.x;
	OBB1.vert[1].y = topLeft.y;

	OBB2.vert[2].x = topRight.x;
	OBB2.vert[2].y = topRight.y;

	OBB2.vert[3].x = bottomRight.x;
	OBB2.vert[3].y = bottomRight.y;
}

void Asset::setOBB3Points(Point bottomLeft, Point topLeft, Point topRight, Point bottomRight)
{
	//glPushMatrix();
	//glColor3f(1, 1, 1);
	//glBegin(GL_QUADS);
	//glVertex2f(bottomLeft.x, bottomLeft.y);
	//glVertex2f(topLeft.x, topLeft.y);
	//glVertex2f(topRight.x,  topRight.y);
	//glVertex2f(bottomRight.x, bottomRight.y);
	//glEnd();
	//glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
	//glPopMatrix();

	OBB3.vert[0].x = bottomLeft.x;
	OBB3.vert[0].y = bottomLeft.y;

	OBB3.vert[1].x = topLeft.x;
	OBB3.vert[1].y = topLeft.y;

	OBB3.vert[2].x = topRight.x;
	OBB3.vert[2].y = topRight.y;

	OBB3.vert[3].x = bottomRight.x;
	OBB3.vert[3].y = bottomRight.y;
}
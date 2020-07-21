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
	char backgroundPNG[] = "PNG/Environment/grass.png";

	background = loadTrackPNG(backgroundPNG);
}

void Track::drawTrack()
{
	// glPushMatrix - draws the whole map size 6000x6000 and texture maps green to it
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, background);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex2f(-3000, -3000);
	glTexCoord2f(0, 1); glVertex2f(-3000, 3000);
	glTexCoord2f(1, 1); glVertex2f(3000, 3000);
	glTexCoord2f(1, 0); glVertex2f(3000, -3000);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
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
		asset.OBB1.drawOBB();
		asset.drawAsset();
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
	char png2[] = "PNG/Assets/fenceredH.png";
	char png3[] = "PNG/Assets/crateWood.png";

	// going up
	for (float i = -580; i < 1100; i += 48)
	{
		Asset asset = Asset();
		asset.x = -222;
		asset.y = i;
		asset.width = 16;
		asset.height = 48;
		asset.texture = loadTrackPNG(png);
		asset.setOBB1Points({ -222,i }, { -222,i + 48 }, { -222 + 16,i + 48 }, { -222 + 16, i });
		mapBarrierOBBs.push_back(asset);
	}	
	
	// going left
	for (float i = -255; i > -950; i -= 48)
	{
		Asset asset = Asset();
		asset.x = i;
		asset.y = 1085;
		asset.width = 48;
		asset.height = 16;
		asset.texture = loadTrackPNG(png2);
		asset.setOBB1Points({ i , 1085 }, { i , 1085 + 16 }, { i+48, 1085 +16}, { i + 48, 1085 });
		mapBarrierOBBs.push_back(asset);
	}

	// going down
	for (float i = 1052; i > -1100; i -= 48)
	{
		Asset asset = Asset();
		asset.x = -928;             
		asset.y = i;                     
		asset.width = 16;
		asset.height = 48;
		asset.texture = loadTrackPNG(png);
		asset.setOBB1Points({ -928,i }, { -928,i + 48 }, { -928 + 16,i + 48 }, { -928 + 16, i });
		mapBarrierOBBs.push_back(asset);
	}

	// going right
	for (float i = -928; i < 1350; i += 48)
	{
		Asset asset = Asset();
		asset.x = i;
		asset.y = -1060;
		asset.width = 48;
		asset.height = 16;
		asset.texture = loadTrackPNG(png2);
		asset.setOBB1Points({ i , -1060 }, { i , -1060 + 16 }, { i + 48, -1060 + 16 }, { i + 48, -1060 });
		mapBarrierOBBs.push_back(asset);
	}

	// going up
	for (float i = -1060; i < 850; i += 48)
	{
		Asset asset = Asset();
		asset.x = 1361;
		asset.y = i;
		asset.width = 16;
		asset.height = 48;
		asset.texture = loadTrackPNG(png);
		asset.setOBB1Points({ 1361, i }, { 1361, i + 48 }, { 1361 + 16, i + 48 }, { 1361 + 16, i });
		mapBarrierOBBs.push_back(asset);
	}

	// going left (drawing right)
	for (float i = 1321; i < 1360; i += 48)
	{
		Asset asset = Asset();
		asset.x = i;
		asset.y = 844;
		asset.width = 48;
		asset.height = 16;
		asset.texture = loadTrackPNG(png2);
		asset.setOBB1Points({ i , 844 }, { i , 844 + 16 }, { i + 48, 844 + 16 }, { i + 48, 844 });
		mapBarrierOBBs.push_back(asset);
	}

	// going down (drawing up)
	for (float i = -580; i < 850; i += 48)
	{
		Asset asset = Asset();
		asset.x = 1313;
		asset.y = i;
		asset.width = 16;
		asset.height = 48;
		asset.texture = loadTrackPNG(png);
		asset.setOBB1Points({ 1313, i }, { 1313, i + 48 }, { 1313 + 16, i + 48 }, { 1313 + 16, i });
		mapBarrierOBBs.push_back(asset);
	}

	// going left
	for (float i = 1280; i > -250; i -= 48)
	{
		Asset asset = Asset();
		asset.x = i;
		asset.y = -580;
		asset.width = 48;
		asset.height = 16;
		asset.texture = loadTrackPNG(png2);
		asset.setOBB1Points({ i , -580 }, { i , -580 + 16 }, { i + 48, -580 + 16 }, { i + 48, -580 });
		mapBarrierOBBs.push_back(asset);
	}








































	// going up
	for (float i = -50; i < 1600; i += 48)
	{
		Asset asset = Asset();
		asset.x = 330;
		asset.y = i;
		asset.width = 16;
		asset.height = 48;
		asset.texture = loadTrackPNG(png);
		asset.setOBB1Points({ 330,i }, { 330,i + 48 }, { 330 + 16,i + 48 }, { 330 + 16, i });
		mapBarrierOBBs.push_back(asset);
	}

	// going left
	for (float i = 298; i > -1550; i -= 48)
	{
		Asset asset = Asset();
		asset.x = i;
		asset.y = 1613;
		asset.width = 48;
		asset.height = 16;
		asset.texture = loadTrackPNG(png2);
		asset.setOBB1Points({ i , 1613 }, { i , 1613 + 16 }, { i + 48, 1613 + 16 }, { i + 48, 1613 });
		mapBarrierOBBs.push_back(asset);
	}

	// going down
	for (float i = 1580; i > -1610; i -= 48) 
	{
		Asset asset = Asset();
		asset.x = -1526;         
		asset.y = i;                 
		asset.width = 16;
		asset.height = 48;
		asset.texture = loadTrackPNG(png);
		asset.setOBB1Points({ -1526,i }, { -1526,i + 48 }, { -1526 + 16,i + 48 }, { -1526 + 16, i }); 
		mapBarrierOBBs.push_back(asset);
	}

	// going right
	for (float i = -1526; i < 1850; i += 48)
	{
		Asset asset = Asset();
		asset.x = i;
		asset.y = -1588;
		asset.width = 48;
		asset.height = 16;
		asset.texture = loadTrackPNG(png2);
		asset.setOBB1Points({ i , -1588 }, { i , -1588 + 16 }, { i + 48, -1588 + 16 }, { i + 48, -1588 });
		mapBarrierOBBs.push_back(asset);
	}

	// going up
	for (float i = -1586; i < 1300; i += 48)
	{
		Asset asset = Asset();
		asset.x = 1866;
		asset.y = i;
		asset.width = 16;
		asset.height = 48;
		asset.texture = loadTrackPNG(png);
		asset.setOBB1Points({ 1866, i }, { 1866, i + 48 }, { 1866 + 16, i + 48 }, { 1866 + 16, i });
		mapBarrierOBBs.push_back(asset);
	}

	// going left
	for (float i = 1834; i > 800; i -= 48)
	{
		Asset asset = Asset();
		asset.x = i;
		asset.y = 1327;
		asset.width = 48;
		asset.height = 16;
		asset.texture = loadTrackPNG(png2);
		asset.setOBB1Points({ i , 1327 }, { i , 1327 + 16 }, { i + 48, 1327 + 16 }, { i + 48, 1327 });
		mapBarrierOBBs.push_back(asset);
	}

	// going down
	for (float i = 1294; i > -80; i -= 48)
	{
		Asset asset = Asset();
		asset.x = 825;               
		asset.y = i;                     
		asset.width = 16;
		asset.height = 48;
		asset.texture = loadTrackPNG(png);
		asset.setOBB1Points({ 825,i }, { 825,i + 48 }, { 825 + 16,i + 48 }, { 825 + 16, i });
		mapBarrierOBBs.push_back(asset);
	}

	// going left
	for (float i = 792; i > 350; i -= 48)
	{
		Asset asset = Asset();
		asset.x = i;
		asset.y = -50;
		asset.width = 48;
		asset.height = 16;
		asset.texture = loadTrackPNG(png2);
		asset.setOBB1Points({ i , -50 }, { i , -50 + 16 }, { i + 48, -50 + 16 }, { i + 48, -50 });
		mapBarrierOBBs.push_back(asset);
	}

	Asset crateRight = Asset();
	crateRight.x = 325;
	crateRight.y = -60;
	crateRight.width = 40;
	crateRight.height = 40;
	crateRight.texture = loadTrackPNG(png3);
	crateRight.setOBB1Points({ 325 , -60 }, { 325 , -60 + 40 }, { 325 + 40, -60 + 40 }, { 325 + 40, -60 });
	mapBarrierOBBs.push_back(crateRight);

	Asset crateLeft = Asset();
	crateLeft.x = -235;
	crateLeft.y = -60;
	crateLeft.width = 40;
	crateLeft.height = 40;
	crateLeft.texture = loadTrackPNG(png3);
	crateLeft.setOBB1Points({ -235 , -60 }, { -235 , -60 + 40 }, { -235 + 40, -60 + 40 }, { -235 + 40, -60 });
	mapBarrierOBBs.push_back(crateLeft);
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

void Track::drawCheckPoints()
{
	for (Asset asset : checkPoints)
	{
		asset.drawAsset();
	}
}

void Track::setCheckPoints()
{
	// going up
	for (float i = 100; i < 1100; i += 50)
	{
		Asset asset = Asset();	
		
		asset.x = -200;
		asset.y = i;
		asset.width = 600;
		asset.height = 5;
		asset.setOBB1Points({ -200,i }, { -200,i + 5 }, { -200 + 600,i + 5 }, { -200 + 600, i });
		asset.OBB1.transformPoints(asset.OBB1matrix);
		asset.drawAsset();
		checkPoints.push_back(asset);
	}

	// going left
	for (float i = -200; i > -900; i -= 50)
	{
		Asset asset = Asset();	
		
		asset.x = i;
		asset.y = 1085;
		asset.width = 5;
		asset.height = 600;
		asset.setOBB1Points({ i , 1085 }, { i , 1085 + 600 }, { i + 5, 1085 + 600 }, { i + 5, 1085 });
		asset.OBB1.transformPoints(asset.OBB1matrix);
		asset.drawAsset();
		checkPoints.push_back(asset);
	}

	// going down
	for (float i = 1085; i > -1100; i -= 50)
	{
		Asset asset = Asset();
		
	
		asset.x = -1500;
		asset.y = i;
		asset.width = 600;
		asset.height = 5;	
		asset.setOBB1Points({ -1500,i }, { -1500,i + 5 }, { -1500 + 600,i + 5 }, { -1500 + 600, i });
		asset.OBB1.transformPoints(asset.OBB1matrix);
		asset.drawAsset();
		checkPoints.push_back(asset);
	}

	// going right
	for (float i = -900; i < 1400; i += 50)
	{
		Asset asset = Asset();
		
		asset.x = i;
		asset.y = -1600;
		asset.width = 5;
		asset.height = 600;
		asset.setOBB1Points({ i , -1600 }, { i , -1000 }, { i + 5 , -1000}, { i + 5, -1600 });
		asset.OBB1.transformPoints(asset.OBB1matrix);
		asset.drawAsset();
		checkPoints.push_back(asset);
	}

	// going up
	for (float i = -1060; i < 850; i += 50)
	{
		Asset asset = Asset();
		
		asset.x = 1361;
		asset.y = i;
		asset.width = 600;
		asset.height = 5;
		asset.setOBB1Points({ 1361, i }, { 1361, i + 5 }, { 1961, i + 5 }, { 1961, i });
		asset.OBB1.transformPoints(asset.OBB1matrix);
		asset.drawAsset();
		checkPoints.push_back(asset);
	}

	// going down (drawing up)
	for (float i = 850; i > -100; i -= 50)
	{
		Asset asset = Asset();
		
		asset.x = 760;
		asset.y = i;
		asset.width = 600;
		asset.height = 5;
		asset.setOBB1Points({ 820, i }, { 820, i + 5 }, { 1420, i + 5 }, {1420, i });
		asset.OBB1.transformPoints(asset.OBB1matrix);
		asset.drawAsset();
		checkPoints.push_back(asset);
	}

	// going left
	for (float i = 835; i > 300; i -= 50)
	{
		Asset asset = Asset();	
	
		asset.x = i;
		asset.y = -600;
		asset.width = 5;
		asset.height = 600;	
		asset.setOBB1Points({ i , -600 }, { i , 0 }, { i + 5, 0 }, { i + 5, -600 });
		asset.OBB1.transformPoints(asset.OBB1matrix);
		asset.drawAsset();
		checkPoints.push_back(asset);
	}

	Asset asset = Asset();
	asset.x = -200;
	asset.y = -50;
	asset.width = 600;
	asset.height = 5;
	asset.setOBB1Points({ -200,-50 }, { -200,-45 }, { -200 + 600,-45 }, { -200 + 600, -50 });
	asset.OBB1.transformPoints(asset.OBB1matrix);
	asset.drawAsset();
	checkPoints.push_back(asset);
	
}
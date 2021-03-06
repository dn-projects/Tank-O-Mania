#pragma comment(lib, "irrKlang.lib")
#include "UserTank.h"
#include "computerTank.h"
#include "Track.h"
#include "Asset.h"
#include <vector>
#include <stdio.h>
#include <chrono>
#include <string>
#include <irrKlang/irrKlang.h>

using namespace chrono;

using namespace std;

using namespace freetype;

using namespace irrklang;

#pragma region PREPLAY state methods 

int timeElapsed = 0;
time_point<steady_clock> beginCountDown;
time_point<steady_clock> endCountDown;

#pragma endregion

#pragma region Checkpoint and position variables

// userTank
int userTankLastCheckPoint = 0;
int userTankCheckPointTally = 0;
int userTankLapNumber = 1;

// compTank1
int compTank1LastCheckPoint = 0;
int compTank1CheckPointTally = 0;
int compTank1LapNumber = 1;

// compTank2
int compTank2LastCheckPoint = 0;
int compTank2CheckPointTally = 0;
int compTank2LapNumber = 1;

// compTank3
int compTank3LastCheckPoint = 0;
int compTank3CheckPointTally = 0;
int compTank3LapNumber = 1;

// compTank4
int compTank4LastCheckPoint = 0;
int compTank4CheckPointTally = 0;
int compTank4LapNumber = 1;

#pragma endregion

#pragma region gamePlaySpeed method variables 

__int64 previousTime = 0;
double gameSpeed = 0.000003;
double deltaTime;

#pragma endregion

#pragma region irrKlang sound variables 

ISoundEngine * SoundEngine = createIrrKlangDevice();

#pragma endregion

#pragma region game objects  

Asset background = Asset();
Track track = Track();
UserTank userTank = UserTank();
ComputerTank computerTank1 = ComputerTank();
ComputerTank computerTank2 = ComputerTank();
ComputerTank computerTank3 = ComputerTank();
ComputerTank computerTank4 = ComputerTank();
Asset mainMenu = Asset();
Asset plane1 = Asset();
Asset plane1Shadow = Asset();
UserTank greenMenuTank = UserTank();
ComputerTank beigeMenuTank1 = ComputerTank();
ComputerTank beigeMenuTank2 = ComputerTank();
Asset mouse = Asset();
Asset playButton = Asset();
Asset controlsButton = Asset();
Asset quitButton = Asset();
Asset backButton = Asset();
Asset finishLine = Asset();

#pragma endregion

#pragma region tank-o-mania local variables

const float PI = 3.1415926535897932384626433832795f;
int mouse_x = 0, mouse_y = 0;   
bool LeftPressed = false;
int screenWidth = 700, screenHeight = 700;
bool keys[256];
float timeKeeper = 0;
bool done = false;
float positionOfPlayer = 1;

#pragma endregion

#pragma region tank-o-mania local textures  

GLuint menuTexture = 0;
GLuint planeTexture = 0;
GLuint planeShadowTexture = 0;
GLuint button1 = 0;
GLuint finish = 0;

#pragma endregion

#pragma region Font variables  

font_data gameFont1;  
font_data gameFont2;  
font_data gameFont3;  
font_data gameFont4;  

#pragma endregion

#pragma region Game state variables  

enum GAME_STATE
{ 
	MAINMENU, 
	PREPLAY,
	PLAY, 
	PAUSE, 
	CONTROLS, 
	GAMEOVER,
	QUIT, 
};

GAME_STATE gameState = MAINMENU;
//GAME_STATE gameState = PLAY;
//GAME_STATE gameState = GAMEOVER;

bool playHover = false;
bool controlsHover = false;
bool quitHover = false;
bool backHover = false;

#pragma endregion

#pragma region function declarations  

void gamePlaySpeed();
void gameMechanics(double deltaTime);
void playerPosition();
void collision();
void resetGame();
void moveProjection();
bool outsideObject(Point P, Point V[], int n);
void initialiseMenuSprites();
void initialiseControlsSprites();
void beginGameCountDown();
static void pushScreenCoordinateMatrix()
{
	glPushAttrib(GL_TRANSFORM_BIT);
	GLint	viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(viewport[0], viewport[2], viewport[1], viewport[3]);
	glPopAttrib();
}
static void pop_projection_matrix()
{
	glPushAttrib(GL_TRANSFORM_BIT);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glPopAttrib();
}

#pragma endregion

#pragma region OPENGL FUNCTION PROTOTYPES 

void display();				//draws everything to the screen
void reshape(int width, int height);//called when the window is resized
void init();				//called in winmain when the program starts.
void processKeys();			//called in winmain to process keyboard controls

#pragma endregion



GLuint loadPNG(char* name)
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

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glClearColor(0.0, 0.0, 0.0, 0.0);  

	SoundEngine->play2D("Battle-Conflict.mp3", true);

	gameFont1.init("tankFont.ttf", 22);
	gameFont2.init("tankFont.ttf", 9);
	gameFont3.init("tankFont.ttf", 25);
	gameFont4.init("tankFont.ttf", 6);
	
	char grassPNG[] = "PNG/Assets/towerDefense_tile231.png";
	menuTexture = loadPNG(grassPNG);
	
	char plane1PNG[] = "PNG/Assets/towerDefense_tile271.png";
	planeTexture = loadPNG(plane1PNG);

	char plane1ShadowPNG[] = "PNG/Assets/towerDefense_tile294.png";
	planeShadowTexture = loadPNG(plane1ShadowPNG);

	char button1PNG[] = "PNG/Assets/towerDefense_tile060.png";
	button1 = loadPNG(button1PNG);

	char finishPNG[] = "PNG/Assets/finish.png";
	finish = loadPNG(finishPNG);

	background.height = 10000;
	background.width = 10000;
	background.x = -5000;
	background.y = -5000;
	background.texture = menuTexture;
	background.xTexture = 80;
	background.yTexture = 80;

	finishLine.x = -225;
	finishLine.y = -48;
	finishLine.width = 560;
	finishLine.height = 10;
	finishLine.xTexture = 5;
	finishLine.texture = finish;

	mouse.height = 1;
	mouse.width = 1;
	track.loadTexture();
	track.drawOffTrackOBB();
	track.drawTrackBarrierOBB();
	track.setCheckPoints();
	userTank.loadTexture();

	computerTank1.loadTexture();
	computerTank1.tank1SetPoints();
	computerTank1.setOBBPoints();
	computerTank1.speed = 8;

	computerTank2.loadTexture();
	computerTank2.tank2SetPoints();
	computerTank2.setOBBPoints();
	computerTank2.speed = 9;

	computerTank3.loadTexture();
	computerTank3.tank3SetPoints();
	computerTank3.setOBBPoints();
	computerTank3.speed = 7;

	computerTank4.loadTexture();
	computerTank4.tank4SetPoints();
	computerTank4.setOBBPoints();
	computerTank4.speed = 6;
	
	initialiseMenuSprites();
	initialiseControlsSprites();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
}

void display()
{	
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	background.drawAsset();
	moveProjection();

	switch (gameState)
	{
		case MAINMENU:

				pushScreenCoordinateMatrix();
				playButton.drawAsset();
				controlsButton.drawAsset();
				quitButton.drawAsset();
				mainMenu.drawAsset();
				plane1.drawAsset();
				plane1Shadow.drawAsset();
				greenMenuTank.drawTank();
				beigeMenuTank1.drawTank();
				beigeMenuTank2.drawTank();

				print(gameFont1, 88, 500, "Tank-O-Mania");

				playHover? print(gameFont1, 360, 350, "Play") : print(gameFont1, 350, 340, "Play");
				controlsHover? print(gameFont1, 270, 280, "Controls") : print(gameFont1, 260, 270, "Controls");
				quitHover? print(gameFont1, 360, 210, "Quit") : print(gameFont1, 350, 200, "Quit");

				pop_projection_matrix();

			break;
		case PREPLAY:
			beginGameCountDown();
			track.drawMapAssets();
			finishLine.drawAsset();

			break;
		case PLAY:
			SoundEngine->stopAllSounds();
			track.drawMapAssets();
			finishLine.drawAsset();
			//print(gameFont3, 200, 260, "v - %7.5f", userTank.v);
			//print(gameFont3, 200, 200, "s - %7.5f", userTank.speed);
			break;
		case GAMEOVER:
			SoundEngine->stopAllSounds();
			mainMenu.drawAsset();
			print(gameFont1, 170, 500, "GAME OVER");
			print(gameFont1, 195, 380, "you came");
			print(gameFont3, 338, 260, "%1.0f", positionOfPlayer);
			print(gameFont2, 125, 150, "Press enter to return to menu");
			break;
		case PAUSE:
			SoundEngine->stopAllSounds();
			mainMenu.drawAsset();
			print(gameFont1, 225, 500, "PAUSED");
			print(gameFont2, 140, 230, "Press up arrow to continue");		
			break;
		case CONTROLS:
			pushScreenCoordinateMatrix();
			mainMenu.drawAsset();
			backButton.drawAsset();
			
			print(gameFont1, 88, 500, "Tank-O-Mania");

			print(gameFont2, 105, 410, "Press RIGHT arrow to turn right");
			print(gameFont2, 115, 370, "Press DOWN arrow to decelrate");
			print(gameFont2, 125, 330, "Press LEFT arrow to turn left");
			print(gameFont2, 135, 290, "Press UP arrow to acelerate");
			print(gameFont2, 163, 250, "Press SPACE bar to pause");
			
		

			backHover ? print(gameFont1, 460, 80, "Back") : print(gameFont1, 450, 70, "Back");

			pop_projection_matrix();

			break;
		case QUIT:
			SoundEngine->stopAllSounds();
			done = true;
			break;
	}
	glFlush();
}

void resetGame()
{
	gameState = MAINMENU;
	timeKeeper = 0;

	userTankLapNumber = 1;
	userTankCheckPointTally = 0;
	userTankLastCheckPoint = 0;
	userTank.v = 0;
	userTank.x = 80;
	userTank.y = -70;
	userTank.direction = 0;
	userTank.speed = 0.06f;
	userTank.lastx = 0;
	userTank.lasty = 0;
	positionOfPlayer = 1;
	
	compTank1LapNumber = 1;
	compTank1CheckPointTally = 0;
	compTank1LastCheckPoint = 0;
	computerTank1.speed = 8;
	computerTank1.x = 150;
	computerTank1.y = 0;
	computerTank1.v = 0;
	computerTank1.lastx = 150;
	computerTank1.lasty = 0;
	computerTank1.direction = 0;
	computerTank1.ticks = 0;
	computerTank1.pIndex = 0;
	computerTank1.loadTexture();
	computerTank1.tank1SetPoints();
	

	compTank2LapNumber = 1;
	compTank2CheckPointTally = 0;
	compTank2LastCheckPoint = 0;
	computerTank2.pIndex = 0;
	computerTank2.speed = 9;
	computerTank2.x = 150;
	computerTank2.y = 0;
	computerTank2.v = 0;
	computerTank2.lastx = 150;
	computerTank2.lasty = 0;
	computerTank2.direction = 0;
	computerTank2.ticks = 0;
	computerTank2.loadTexture();
	computerTank2.tank2SetPoints();

	compTank3LapNumber = 1;
	compTank3CheckPointTally = 0;
	compTank3LastCheckPoint = 0;
	computerTank3.pIndex = 0;
	computerTank3.speed = 7;
	computerTank3.x = 150;
	computerTank3.y = 0;
	computerTank3.v = 0;
	computerTank3.lastx = 150;
	computerTank3.lasty = 0;
	computerTank3.direction = 0;
	computerTank3.ticks = 0;
	computerTank3.loadTexture();
	computerTank3.tank3SetPoints();

	compTank4LapNumber = 1;
	compTank4CheckPointTally = 0;
	compTank4LastCheckPoint = 0;
	computerTank4.pIndex = 0;
	computerTank4.speed = 6;
	computerTank4.x = 150;
	computerTank4.y = 0;
	computerTank4.v = 0;
	computerTank4.lastx = 150;
	computerTank4.lasty = 0;
	computerTank4.direction = 0;
	computerTank4.ticks = 0;
	computerTank4.loadTexture();
	computerTank4.tank4SetPoints();
}

void beginGameCountDown()
{
	endCountDown = steady_clock::now();

	duration<double, ratio<1, 1>> secondsGone = endCountDown - beginCountDown;
	timeElapsed = 5 - secondsGone.count();

	if (timeElapsed == -1)
	{
		beginCountDown = steady_clock::now();
		gameState = PLAY;
	}
	else if (timeElapsed == 0)
	{
		print(gameFont1, 300, 400, "GO!");
	}
	else 
	{
		print(gameFont1, 332, 400, "%d", timeElapsed);
	}
}

void gameMechanics(double deltaTime)
{
	if (userTankLapNumber > 3)
	{
		gameState = GAMEOVER;
	}

	mouse.x = mouse_x;
	mouse.y = mouse_y;
	
	mouse.setOBB1Points ({mouse.x, mouse.y},{mouse.x, mouse.y + 2},{mouse.x + 2, mouse.y + 2},{mouse.x + 2,mouse.y} );
	mouse.OBB1.transformPoints(mouse.OBB1matrix);
	mouse.drawAsset();

	playHover = false;
	controlsHover = false;
	quitHover = false;
	backHover = false;

	if (mouse.OBB1.SAT2D(playButton.OBB1))
	{
		playHover = true;
	}
	if (mouse.OBB1.SAT2D(controlsButton.OBB1))
	{
		controlsHover = true;
	}
	if (mouse.OBB1.SAT2D(quitButton.OBB1))
	{
		quitHover = true;
	}
	if (mouse.OBB1.SAT2D(backButton.OBB1))
	{
		backHover = true;
	}

	switch (gameState)
	{
		case MAINMENU:
		
		timeKeeper++;

		plane1.x += 0.15;
		plane1Shadow .x += 0.15;
		greenMenuTank.x -= 0.08;
		beigeMenuTank1.x -= 0.08;
		beigeMenuTank2.x -= 0.08;

		if (timeKeeper > 11750)
		{
			greenMenuTank.x = 750;
			beigeMenuTank1.x = 840;
			beigeMenuTank2.x = 900;
			
			plane1.x = -80;
			plane1Shadow.x = -145;

			timeKeeper = 0;
		}


			break;
		case PREPLAY:
			beginGameCountDown();
			userTank.drawTank();
			userTank.moveTank();
			computerTank1.drawTank();
			computerTank1.moveTank();

			computerTank2.drawTank();
			computerTank2.moveTank();

			computerTank3.drawTank();
			computerTank3.moveTank();

			computerTank4.drawTank();
			computerTank4.moveTank();
			

			playerPosition();
			collision();
			print(gameFont4, 50, 550, "Drive your green tank to victory! First tank to complete");
			print(gameFont4, 190, 520, "3 laps around the track wins.");
			break;
		case PLAY:

			userTank.drawTank();
			userTank.handleKeys(deltaTime);
			userTank.moveTank();
			computerTank1.drawTank();
			computerTank1.incrementMovement();
			computerTank1.moveTank();
			computerTank1.obb.transformPoints(computerTank1.compMatrix);

			computerTank2.drawTank();
			computerTank2.incrementMovement();
			computerTank2.moveTank();
			computerTank2.obb.transformPoints(computerTank2.compMatrix);

			computerTank3.drawTank();
			computerTank3.incrementMovement();
			computerTank3.moveTank();
			computerTank3.obb.transformPoints(computerTank3.compMatrix);
					
			computerTank4.drawTank();
			computerTank4.incrementMovement();
			computerTank4.moveTank();
			computerTank4.obb.transformPoints(computerTank4.compMatrix);

			playerPosition();
			collision();
			//track.drawCheckPoints();
			print(gameFont4, 20, 615, "Pos");
			print(gameFont3, 60, 615, "%1.0f", positionOfPlayer);

			print(gameFont4, 10, 550, "Laps");
			print(gameFont3, 60, 550, "%d", userTankLapNumber);
			break;
		case PAUSE:
			break;
		case CONTROLS:
			break;
		case QUIT:
			done = true;
			break;
	}
}

void playerPosition()
{
	if (userTankLastCheckPoint == 193)
	{
		userTankLastCheckPoint = 0;
		userTankLapNumber++;
	}

	if (compTank1LastCheckPoint == 193)
	{
		compTank1LastCheckPoint = 0;
		compTank1LapNumber++;
	}

	if (compTank2LastCheckPoint == 193)
	{
		compTank2LastCheckPoint = 0;
		compTank2LapNumber++;
	}

	if (compTank3LastCheckPoint == 193)
	{
		compTank3LastCheckPoint = 0;
		compTank3LapNumber++;
	}

	if (compTank4LastCheckPoint == 193)
	{
		compTank4LastCheckPoint = 0;
		compTank4LapNumber++;
	}

	if (userTankLastCheckPoint > -1)
	{
		if (userTank.tankOBB.SAT2D(track.checkPoints[userTankLastCheckPoint + 1].OBB1))
		{
			userTankLastCheckPoint++;
			userTankCheckPointTally++;
		}
		if (userTankLastCheckPoint != 0)
		{
			if (userTank.tankOBB.SAT2D(track.checkPoints[userTankLastCheckPoint - 1].OBB1))
			{
				userTankLastCheckPoint--;
				userTankCheckPointTally--;
			}
		}
	}

	if (compTank1LastCheckPoint > -1) 
	{
		if (computerTank1.obb.SAT2D(track.checkPoints[compTank1LastCheckPoint + 1].OBB1)) 
		{
			compTank1LastCheckPoint++;
			compTank1CheckPointTally++;
		}
		if (compTank1LastCheckPoint != 0) 
		{
			if (computerTank1.obb.SAT2D(track.checkPoints[compTank1LastCheckPoint - 1].OBB1)) 
			{
				compTank1LastCheckPoint--;
				compTank1CheckPointTally--;
			}
		}
	}

	if (compTank2LastCheckPoint > -1)
	{
		if (computerTank2.obb.SAT2D(track.checkPoints[compTank2LastCheckPoint + 1].OBB1))
		{
			compTank2LastCheckPoint++;
			compTank2CheckPointTally++;
		}
		if (compTank2LastCheckPoint != 0)
		{
			if (computerTank2.obb.SAT2D(track.checkPoints[compTank2LastCheckPoint - 1].OBB1))
			{
				compTank2LastCheckPoint--;
				compTank2CheckPointTally--;
			}
		}
	}

	if (compTank3LastCheckPoint > -1)
	{
		if (computerTank3.obb.SAT2D(track.checkPoints[compTank3LastCheckPoint + 1].OBB1))
		{
			compTank3LastCheckPoint++;
			compTank3CheckPointTally++;
		}
		if (compTank3LastCheckPoint != 0)
		{
			if (computerTank3.obb.SAT2D(track.checkPoints[compTank3LastCheckPoint - 1].OBB1))
			{
				compTank3LastCheckPoint--;
				compTank3CheckPointTally--;
			}
		}
	}

	if (compTank4LastCheckPoint > -1)
	{
		if (computerTank4.obb.SAT2D(track.checkPoints[compTank4LastCheckPoint + 1].OBB1))
		{
			compTank4LastCheckPoint++;
			compTank4CheckPointTally++;
		}
		if (compTank4LastCheckPoint != 0)
		{
			if (computerTank4.obb.SAT2D(track.checkPoints[compTank4LastCheckPoint - 1].OBB1))
			{
				compTank4LastCheckPoint--;
				compTank4CheckPointTally--;
			}
		}
	}

	if (userTankCheckPointTally > compTank1CheckPointTally &&
		userTankCheckPointTally > compTank2CheckPointTally &&
		userTankCheckPointTally > compTank3CheckPointTally &&
		userTankCheckPointTally > compTank4CheckPointTally)
	{
		positionOfPlayer = 1;
	}
	else if (userTankCheckPointTally > compTank1CheckPointTally &&
			    userTankCheckPointTally > compTank2CheckPointTally &&
			    userTankCheckPointTally > compTank3CheckPointTally &&
			    userTankCheckPointTally < compTank4CheckPointTally)
	{
		positionOfPlayer = 2;
	}
	else if (userTankCheckPointTally > compTank1CheckPointTally &&
				userTankCheckPointTally > compTank2CheckPointTally &&
			  	userTankCheckPointTally < compTank3CheckPointTally &&
				userTankCheckPointTally > compTank4CheckPointTally)
	{
		positionOfPlayer = 2;
	}
	else if (userTankCheckPointTally > compTank1CheckPointTally &&
			    userTankCheckPointTally < compTank2CheckPointTally &&
			    userTankCheckPointTally > compTank3CheckPointTally &&
			    userTankCheckPointTally > compTank4CheckPointTally)
	{
		positionOfPlayer = 2;
	}
	else if (userTankCheckPointTally < compTank1CheckPointTally &&
			    userTankCheckPointTally > compTank2CheckPointTally &&
		       	userTankCheckPointTally > compTank3CheckPointTally &&
			    userTankCheckPointTally > compTank4CheckPointTally)
	{
		positionOfPlayer = 2;
	}
	else if (userTankCheckPointTally > compTank1CheckPointTally &&
		userTankCheckPointTally > compTank2CheckPointTally &&
		userTankCheckPointTally > compTank3CheckPointTally &&
		userTankCheckPointTally < compTank4CheckPointTally)
	{
		positionOfPlayer = 3;
	}
	else if (userTankCheckPointTally > compTank1CheckPointTally &&
		userTankCheckPointTally > compTank2CheckPointTally &&
		userTankCheckPointTally < compTank3CheckPointTally &&
		userTankCheckPointTally < compTank4CheckPointTally)
	{
		positionOfPlayer = 3;
	}
	else if (userTankCheckPointTally > compTank1CheckPointTally &&
		userTankCheckPointTally < compTank2CheckPointTally &&
		userTankCheckPointTally > compTank3CheckPointTally &&
		userTankCheckPointTally < compTank4CheckPointTally)
	{
		positionOfPlayer = 3;
	}
	else if (userTankCheckPointTally < compTank1CheckPointTally &&
		userTankCheckPointTally > compTank2CheckPointTally &&
		userTankCheckPointTally > compTank3CheckPointTally &&
		userTankCheckPointTally < compTank4CheckPointTally)
	{
		positionOfPlayer = 3;
	}
	else if (userTankCheckPointTally > compTank1CheckPointTally &&
		userTankCheckPointTally < compTank2CheckPointTally &&
		userTankCheckPointTally < compTank3CheckPointTally &&
		userTankCheckPointTally > compTank4CheckPointTally)
	{
		positionOfPlayer = 3;
	}
	else if (userTankCheckPointTally < compTank1CheckPointTally &&
		userTankCheckPointTally > compTank2CheckPointTally &&
		userTankCheckPointTally < compTank3CheckPointTally &&
		userTankCheckPointTally > compTank4CheckPointTally)
	{
		positionOfPlayer = 3;
	}
	else if (userTankCheckPointTally < compTank1CheckPointTally &&
		userTankCheckPointTally < compTank2CheckPointTally &&
		userTankCheckPointTally > compTank3CheckPointTally &&
		userTankCheckPointTally > compTank4CheckPointTally)
	{
		positionOfPlayer = 3;
	}
	else if (userTankCheckPointTally > compTank1CheckPointTally &&
		userTankCheckPointTally < compTank2CheckPointTally &&
		userTankCheckPointTally < compTank3CheckPointTally &&
		userTankCheckPointTally < compTank4CheckPointTally)
	{
		positionOfPlayer = 4;
	}
	else if (userTankCheckPointTally < compTank1CheckPointTally &&
		userTankCheckPointTally > compTank2CheckPointTally &&
		userTankCheckPointTally < compTank3CheckPointTally &&
		userTankCheckPointTally < compTank4CheckPointTally)
	{
		positionOfPlayer = 4;
	}
	else if (userTankCheckPointTally < compTank1CheckPointTally &&
	userTankCheckPointTally < compTank2CheckPointTally &&
	userTankCheckPointTally > compTank3CheckPointTally &&
	userTankCheckPointTally < compTank4CheckPointTally)
	{
	positionOfPlayer = 4;
	}
	else if (userTankCheckPointTally < compTank1CheckPointTally &&
	userTankCheckPointTally < compTank2CheckPointTally &&
	userTankCheckPointTally < compTank3CheckPointTally &&
	userTankCheckPointTally > compTank4CheckPointTally)
	{
	positionOfPlayer = 4;
	}
	else if (userTankCheckPointTally < compTank1CheckPointTally &&
	userTankCheckPointTally < compTank2CheckPointTally &&
	userTankCheckPointTally < compTank3CheckPointTally &&
	userTankCheckPointTally < compTank4CheckPointTally)
	{
	positionOfPlayer = 5;
	}


		//print(gameFont4, 300, 340, "%d", userTankLapNumber);
		//print(gameFont4, 300, 320, "%d", compTank1LapNumber);
		//print(gameFont4, 300, 300, "%d", compTank2LapNumber);
		//print(gameFont4, 300, 280, "%d", compTank3LapNumber);
		//print(gameFont4, 300, 260, "%d", compTank4LapNumber);
}

void initialiseMenuSprites()
{
	greenMenuTank.loadTexture();
	beigeMenuTank1.loadTexture();
	beigeMenuTank2.loadTexture();

	greenMenuTank.x = 750;
	greenMenuTank.y = 100;
	greenMenuTank.direction = 90;
	
	beigeMenuTank1.x = 840;
	beigeMenuTank1.y = 135;
	beigeMenuTank1.direction = 90;

	beigeMenuTank2.x = 900;
	beigeMenuTank2.y = 65;
	beigeMenuTank2.direction = 90;

	plane1.x = -80;
	plane1.y = 100;
	plane1.rotation = 45;
	plane1.texture = planeTexture;

	plane1Shadow.x = -145;
	plane1Shadow.y = 25;
	plane1Shadow.rotation = 45;
	plane1Shadow.texture = planeShadowTexture;

	playButton.x = 350;
	playButton.y = 340;
	playButton.height = 52;
	playButton.width = 170;
	playButton.setOBB1Points({350,340},{350,402},{520,402},{520,350});
	playButton.texture = button1;

	controlsButton.x = 260;
	controlsButton.y = 270;
	controlsButton.height = 52;
	controlsButton.width = 345;
	controlsButton.setOBB1Points( {260,270},{260,322},{605,322},{605,270} );
	controlsButton.texture = button1;	
	
	quitButton.x = 350;
	quitButton.y = 200;
	quitButton.height = 52;
	quitButton.width = 170;
	quitButton.setOBB1Points( {350,200},{350,252},{520,252},{520,200} );
	quitButton.texture = button1;


	mainMenu.width = 1000;
	mainMenu.height = 1000;
	mainMenu.x = 0;
	mainMenu.y = 0;
	mainMenu.texture = menuTexture;
	mainMenu.xTexture = 6;
	mainMenu.yTexture = 6;
}

void initialiseControlsSprites()
{
	backButton.x = 450;
	backButton.y = 70;
	backButton.height = 52;
	backButton.width = 170;
	backButton.setOBB1Points({ 450,70 }, { 450,122 }, { 850,122 }, { 850,70 });
	backButton.texture = menuTexture;
}

void collision() 
{
	//Grass detection
	for (OBB obb : track.mapOffTrackOBBs)
	{
		if (obb.SAT2D(userTank.tankOBB))
		{
			userTank.handleOffTrack();
		}
		else
		{
			userTank.speed = 0.06f;
		}
	}

	//Barrier detection
	for (Asset asset : track.mapBarrierOBBs)
	{
		asset.drawAsset();
		if (userTank.tankOBB.SAT2D(asset.OBB1))
		{
			userTank.handleBarrierCollision();
		}
	}

	if (userTank.tankOBB.SAT2D(computerTank1.obb))
	{
		userTank.handleBarrierCollision();
	}
}

void gamePlaySpeed()
{
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	__int64 currentTime = time.QuadPart;

	__int64 ticksElapsed = currentTime - previousTime;
	deltaTime = double(ticksElapsed) * gameSpeed;


	gameMechanics(deltaTime);


	previousTime = currentTime;
}

bool outsideObject(Point P, Point V[], int n)
{
	int cn = 0; // the crossing number counter
	// loop through all edges of the polygon
	for (int i = 0; i < n; i++) // edge from V[i] to V[i+1]
	{
		if (((V[i].y <= P.y) && (V[i + 1].y > P.y)) //upward crossing
			|| ((V[i].y > P.y) && (V[i + 1].y <= P.y)))//downward crossing
		{
			//compute the actual edge-ray intersect x-coordinate
			float vt = (float)(P.y - V[i].y) / (V[i + 1].y - V[i].y);
			if (P.x < V[i].x + vt * (V[i + 1].x - V[i].x))
				++cn; // a valid crossing
		}
	}
	return (cn % 2 == 0); // true if even (out), and false if odd (in)	
}

void moveProjection() 
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
		gluOrtho2D(((userTank.x) - screenWidth / 1.5), 
			              ((userTank.x) + screenWidth / 1.5),
			              ((userTank.y) - screenHeight / 1.5),
			              ((userTank.y) + screenHeight / 1.5));
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void reshape(int width, int height)		// Resize the OpenGL window
{
	screenWidth = width; screenHeight = height;         // to ensure the mouse coordinates match 
														// we will use these values to set the coordinate system

	glViewport(0, 0, width, height);					// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	//gluOrtho2D(-200, 200, -200, 200);             // View whole map 
	gluOrtho2D(-8000, 8000, -8000, 8000);             // View whole map 

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

void processKeys()
{
	if (keys[VK_SPACE]) 
	{
		if (gameState == PLAY)
		{
			gameState = PAUSE;
		}
	}
	if (gameState == PAUSE)
	{
		if (keys[VK_UP])
		{
			gameState = PLAY;
		}
	}
	if(keys[VK_RETURN])
	{
		if (gameState == GAMEOVER)
		{
			resetGame();
		}
	}
}

























































/******************* WIN32 FUNCTIONS ***************************/
#pragma region WIN32 FUNCTIONS

//WIN32 functions
LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	 // Declaration For WndProc
void KillGLWindow();									 // releases and destroys the window
bool CreateGLWindow(char* title, int width, int height); //creates the window
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);    // Win32 main function


//win32 global variabless
HDC			hDC = NULL;		// Private GDI Device Context
HGLRC		hRC = NULL;		// Permanent Rendering Context
HWND		hWnd = NULL;	// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application
 

int WINAPI WinMain(HINSTANCE	hInstance,			// Instance
	HINSTANCE	hPrevInstance,		// Previous Instance
	LPSTR		lpCmdLine,			// Command Line Parameters
	int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure

	char title[] = "Tank-O-Mania";



	// Create Our OpenGL Window
	if (!CreateGLWindow(title, screenWidth, screenHeight))
	{
		return 0;								// Quit If Window Was Not Created
	}
	
	

	while (!done)									// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message == WM_QUIT)				// Have We Received A Quit Message?
			{
				done = true;							// If So done=TRUE
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else										// If There Are No Messages
		{
			if (keys[VK_ESCAPE])
				done = true;

			processKeys();
			display();					// Draw The Scene
			gamePlaySpeed();
			SwapBuffers(hDC);			// Swap Buffers (Double Buffering)
		}
	}

	// Shutdown
	KillGLWindow();									// Kill The Window
	return (int)(msg.wParam);						// Exit The Program
}

//WIN32 Processes function - useful for responding to user inputs or other events.
LRESULT CALLBACK WndProc(HWND	hWnd,			// Handle For This Window
	UINT	uMsg,			// Message For This Window
	WPARAM	wParam,			// Additional Message Information
	LPARAM	lParam)			// Additional Message Information
{
 

	switch (uMsg)									// Check For Windows Messages
	{
	case WM_CLOSE:								// Did We Receive A Close Message?
	{
		PostQuitMessage(0);						// Send A Quit Message
		return 0;								// Jump Back
	}
	break;

	case WM_SIZE:								// Resize The OpenGL Window
	{
		reshape(LOWORD(lParam), HIWORD(lParam));  // LoWord=Width, HiWord=Height
		return 0;								// Jump Back
	}
	break;

	case WM_LBUTTONDOWN:
	{
		mouse_x = LOWORD(lParam);
		mouse_y = screenHeight - HIWORD(lParam);
		LeftPressed = true;

		if (playHover)
		{
			if (gameState == PLAY  || gameState == PREPLAY ||
				gameState == PAUSE || gameState == CONTROLS)
			{
				return 0;
			}
			else
			{
				beginCountDown = steady_clock::now();
				gameState = PREPLAY;
			}
		}
		else if (controlsHover)
		{
			if (gameState == PLAY || gameState == PREPLAY ||
				gameState == PAUSE)
			{
				return 0;
			}
			else
			{
				gameState = CONTROLS;
			}
		}
		else if (quitHover)
		{
			if (gameState == PLAY  || gameState == PREPLAY ||
				gameState == PAUSE || gameState == CONTROLS)
			{
				return 0;
			}
			else
			{
				gameState = QUIT;
			}
		}
		else if (backHover)
		{
			if (gameState == PLAY  || gameState == PREPLAY ||
				gameState == PAUSE || gameState == MAINMENU)
			{
				return 0;
			}
			else
			{
				gameState = MAINMENU;
				greenMenuTank.x = 750;
				beigeMenuTank1.x = 840;
				beigeMenuTank2.x = 900;
				plane1.x = -80;
				plane1Shadow.x = -145;
				timeKeeper = 0;
			}
		}
	}
	break;

	case WM_LBUTTONUP:
	{
		LeftPressed = false;
	}
	break;

	case WM_MOUSEMOVE:
	{
		mouse_x = LOWORD(lParam);
		mouse_y = screenHeight - HIWORD(lParam);
	}
	break;
	case WM_KEYDOWN:							// Is A Key Being Held Down?
	{
		keys[wParam] = true;					// If So, Mark It As TRUE
		userTank.keys[wParam] = true;
		return 0;								// Jump Back
	}
	break;
	case WM_KEYUP:								// Has A Key Been Released?
	{
		keys[wParam] = false;					// If So, Mark It As FALSE
		userTank.keys[wParam] = false;
		return 0;								// Jump Back
	}
	break;
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void KillGLWindow()								// Properly Kill The Window
{
	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL, NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd, hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL", hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;									// Set hInstance To NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
 *	title			- Title To Appear At The Top Of The Window				*
 *	width			- Width Of The GL Window Or Fullscreen Mode				*
 *	height			- Height Of The GL Window Or Fullscreen Mode			*/

bool CreateGLWindow(char* title, int width, int height)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left = (long)0;			// Set Left Value To 0
	WindowRect.right = (long)width;		// Set Right Value To Requested Width
	WindowRect.top = (long)0;				// Set Top Value To 0
	WindowRect.bottom = (long)height;		// Set Bottom Value To Requested Height

	hInstance = GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc = (WNDPROC)WndProc;					// WndProc Handles Messages
	wc.cbClsExtra = 0;									// No Extra Window Data
	wc.cbWndExtra = 0;									// No Extra Window Data
	wc.hInstance = hInstance;							// Set The Instance
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground = NULL;									// No Background Required For GL
	wc.lpszMenuName = NULL;									// We Don't Want A Menu
	wc.lpszClassName = "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;											// Return FALSE
	}

	dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
	dwStyle = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;							// Windows Style

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd = CreateWindowEx(dwExStyle,							// Extended Style For The Window
		"OpenGL",							// Class Name
		title,								// Window Title
		dwStyle |							// Defined Window Style
		WS_CLIPSIBLINGS |					// Required Window Style
		WS_CLIPCHILDREN,					// Required Window Style
		280, 20,							// Window Position
		WindowRect.right - WindowRect.left,	// Calculate Window Width
		WindowRect.bottom - WindowRect.top,	// Calculate Window Height
		NULL,								// No Parent Window
		NULL,								// No Menu
		hInstance,							// Instance
		NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd =				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		24,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		24,											// 24Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	if (!(hDC = GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if (!SetPixelFormat(hDC, PixelFormat, &pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if (!(hRC = wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if (!wglMakeCurrent(hDC, hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	ShowWindow(hWnd, SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	reshape(width, height);					        // Set Up Our Perspective GL Screen


	init();

	return true;									// Success
}
#pragma endregion
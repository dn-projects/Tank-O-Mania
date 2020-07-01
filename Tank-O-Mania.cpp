
//includes areas for keyboard control, mouse control, resizing the window
//and draws a spinning rectangle
#include <windows.h>		// Header File For Windows
#include "glew.h"
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <math.h>
#include "FreeType.h"
#include "OBB.h"
#include "Image_Loading/nvImage.h"
#include <iostream>


using namespace freetype;

const float PI = 3.1415926535897932384626433832795f;

int	mouse_x = 0, mouse_y = 0;
bool LeftPressed = false;
int screenWidth = 480, screenHeight = 480;
bool keys[256];
float spin = 0;
POINT p;


OBB square, triangle;



/**************************** variables for font ****************************/
font_data our_font;



/**************************** variables for timer ****************************/
float number;



/**************************** variables for transformation matrix ****************************/
float squareTransformationMatrix[16];



/**************************** variables for spining points ****************************/
float squareX = 4;
float squareY = 4;


/**************************** variables for AABB ****************************/
float squareMinX = 0;
float squareMaxX = 0;
float squareMinY = 0;
float squareMaxY = 0;


float squareNewX1 = 0;
float squareNewY1 = 0;
float squareNewX2 = 0;
float squareNewY2 = 0;
float squareNewX3 = 0;
float squareNewY3 = 0;
float squareNewX4 = 0;
float squareNewY4 = 0;

/**************************** variables for colors ****************************/
float red = 0.0;
float green = 0.0;
float blue = 0.0;



/**************************** variables for arrow key transformation ****************************/
float tank1XMovement = 0;
float tank1YMovement = 0;	// transform triangle x and y by arrrow key transformation
float tank1Angle = 0.0;
float tank1Velocity = 0;

float squareXTransform = 0;
float squareYTransform = 0; // transform square x and y by arrrow key transformation



/**************************** functions ****************************/
void drawCircle(float x, float y, float radius); //prototype the draw function
void changeLineColor();
void spiningSquareCorner();
void circleCollison();
void shapesCollison();
void printFunctions();
void AABBCollision();

void drawDots();
void moveCamera();


/**************************** OPENGL FUNCTION PROTOTYPES ****************************/
void display();				//draws everything to the screen
void reshape(int width, int height);//called when the window is resized
void init();				//called in winmain when the program starts.
void processKeys();			//called in winmain to process keyboard controls



// This stores a handle to the texture
GLuint track1;
GLuint tank1Tracks;
GLuint tank1Body;
GLuint tank1Barrel;

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

	glClearColor(0.0, 0.0, 0.0, 0.0);						//sets the clear colour to yellow
														//glClear(GL_COLOR_BUFFER_BIT) in the display function
														//will clear the buffer to this colour.

	our_font.init("arialbd.TTF", 22);                   //Build the freetype font


	glClearColor(0.0, 0.0, 0.0, 0.0);

	char png1[] = "PNG/Environment/grass.png";
	char png2[] = "PNG/Tanks/tracksSmall.png";
	char png3[] = "PNG/Tanks/tankBlue_outline.png";
	char png4[] = "PNG/Tanks/barrelBlue.png";

	track1 = loadPNG(png1);

	tank1Tracks = loadPNG(png2);
	tank1Body   = loadPNG(png3);
	tank1Barrel = loadPNG(png4);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}



/*************    START OF OPENGL FUNCTIONS   ****************/
void display()
{	

		glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// white axis lines
		//glLineWidth(1.5);
		//glColor3f(1.0, 1.0, 1.0);
		//	glBegin(GL_LINES);
		//		glVertex2f(-3000, 3000);
		//		glVertex2f(3000, 3000);
		//		glVertex2f(3000, 3000);
		//		glVertex2f(3000, -3000);
		//	glEnd();
		
		glPushMatrix();
			glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			glBindTexture(GL_TEXTURE_2D, track1);
				glBegin(GL_POLYGON);
					glTexCoord2f(0, 0); glVertex2f(-3000, -3000);
					glTexCoord2f(0, 1); glVertex2f(-3000,  3000);
					glTexCoord2f(1, 1); glVertex2f( 3000,  3000);
					glTexCoord2f(1, 0); glVertex2f( 3000, -3000);
				glEnd();
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();


		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			glBindTexture(GL_TEXTURE_2D, tank1Tracks);
			glTranslatef(tank1XMovement, tank1YMovement, 0.0);
			glRotatef(tank1Angle, 0, 0, 1);
			glColor3f(1,1,1);
			glBegin(GL_POLYGON);
			glTexCoord2f(0,0);	glVertex2f(-36, -52);
			glTexCoord2f(0,1);	glVertex2f(-36,  52);
			glTexCoord2f(1,1);	glVertex2f( 36,  52);
			glTexCoord2f(1,0);	glVertex2f( 36, -52);
			glEnd();
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();

		glPushMatrix();
			glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			glBindTexture(GL_TEXTURE_2D, tank1Body);
			glTranslatef(tank1XMovement, tank1YMovement, 0.0);
			glRotatef(tank1Angle, 0, 0, 1);
			glColor3f(1, 1, 1);
			glBegin(GL_POLYGON);
				glTexCoord2f(0, 0);	glVertex2f(-33, -41);
				glTexCoord2f(0, 1);	glVertex2f(-33, 41);
				glTexCoord2f(1, 1);	glVertex2f(33, 41);
				glTexCoord2f(1, 0);	glVertex2f(33, -41);
			glEnd();
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();

		glPushMatrix();
			glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			glBindTexture(GL_TEXTURE_2D, tank1Barrel);
			glTranslatef(tank1XMovement, tank1YMovement, 0.0);
			glRotatef(tank1Angle, 0, 0, 1);
			glColor3f(1, 1, 1);
			glBegin(GL_POLYGON);
				glTexCoord2f(0, 0);	glVertex2f(-8,   0);
				glTexCoord2f(0, 1);	glVertex2f(-8,  80);
				glTexCoord2f(1, 1);	glVertex2f( 8,  80);
				glTexCoord2f(1, 0);	glVertex2f( 8,   0);
			glEnd();
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();





		//update the position of the user controlled object.
		tank1XMovement += tank1Velocity * cosf((90 + tank1Angle) * (PI / 180.0f));
		tank1YMovement += tank1Velocity * sinf((90 + tank1Angle) * (PI / 180.0f));

		// hard map		
		glPushMatrix();
			glColor3f(1,1,1);
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
		

		// medium map
		/*
		glPushMatrix();
			glColor3f(1,1,1);
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
		*/
		
		// easy map
		/*
		glPushMatrix();
		glColor3f(1, 1, 1);
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
		*/
		

		/*
		for (int i = 64; i < 2000; i+=64)
		{
			glPushMatrix();
			glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			glBindTexture(GL_TEXTURE_2D, track2);
			glBegin(GL_POLYGON);
			glTexCoord2f(0, 0); glVertex2f(i, i);
			glTexCoord2f(0, 1); glVertex2f(64 + i, i);
			glTexCoord2f(1, 1); glVertex2f(64 + i, 64 + i);
			glTexCoord2f(1, 0); glVertex2f(i, 64 + i);
			glEnd();
			glDisable(GL_TEXTURE_2D);
			glPopMatrix();
		}
		

		for (int i = 64; i > -640; i-=64)
		{
			glPushMatrix();
			glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			glBindTexture(GL_TEXTURE_2D, track2);
			glBegin(GL_POLYGON);
				glTexCoord2f(0, 0); glVertex2f(i, i);
				glTexCoord2f(0, 1); glVertex2f(i - 64, i);
				glTexCoord2f(1, 1); glVertex2f(i - 64, i - 64);
				glTexCoord2f(1, 0); glVertex2f(i, i - 64);
			glEnd();
			glDisable(GL_TEXTURE_2D);
			glPopMatrix();
		}
		*/

	glFlush();

	square.transformPoints(squareTransformationMatrix);


	if (square.SAT2D(triangle))
		glColor3f(1.0, 0.0, 1.0);
	else
		glColor3f(0.0, 0.0, 1.0);

	square.drawOBB();

	triangle.drawOBB();


	/**************************** methods ****************************/
	printFunctions();
	shapesCollison();
	AABBCollision();

	drawDots();
	moveCamera();


	spin += 0.05f;
	if (spin > 360)
		spin = 0;
}

void moveCamera() 
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
		gluOrtho2D((tank1XMovement - screenWidth / 0.5), (tank1XMovement + screenWidth / 0.5), (tank1YMovement - screenHeight / 0.5), (tank1YMovement + screenHeight / 0.5));
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void drawDots()
{
	float rgb = 0.0;

	for (int i = 20; i < 500; i += 30)
	{
		glPushMatrix();
			glColor3f(1.0, rgb, rgb);
			glPointSize(5.0);
			glBegin(GL_POINTS);
				glVertex2f(20, i);
			glEnd();
		glPopMatrix();

		rgb += 0.03;
	}
}

void printFunctions()
{
	//print(our_font, 20, 95, "p.x: %7.2f", p.x);
	//print(our_font, 20, 65, "p.y: %7.2f", p.y);
	//print(our_font, 20, 35, "squareMaxX: %7.2f", squareMaxX);
	//print(our_font, 20, 5,  "squareMinX: %7.2f", squareMinX);
}

void AABBCollision()
{
	square.vertOriginal[0].x = -4;
	square.vertOriginal[0].y = -4;

	square.vertOriginal[1].x = -4;
	square.vertOriginal[1].y = 4;

	square.vertOriginal[2].x = 4;
	square.vertOriginal[2].y = 4;

	square.vertOriginal[3].x = 4;
	square.vertOriginal[3].y = -4;

	triangle.vertOriginal[0].x = -4;
	triangle.vertOriginal[0].y = -4;

	triangle.vertOriginal[1].x = 4;
	triangle.vertOriginal[1].y = -4;

	triangle.vertOriginal[2].x = 0;
	triangle.vertOriginal[2].y = 5.65f;

	triangle.vertOriginal[3].x = 0;
	triangle.vertOriginal[3].y = 5.65f;
}

void shapesCollison()
{
	//determine the new min and max coordinates
	//float xmin = xnew1;
	//float xmax = xnew1;
	//float ymin = ynew1;
	//float ymax = ynew1;

	//if (xnew2 < xmin)
	//	xmin = xnew2;
	//if (xnew2 > xmax)
	//	xmax = xnew2;
	//if (xnew3 < xmin)
	//	xmin = xnew3;
	//if (xnew3 > xmax)
	//	xmax = xnew3;
	//if (xnew4 < xmin)
	//	xmin = xnew4;
	//if (xnew4 > xmax)
	//	xmax = xnew4;

	//if (ynew2 < ymin)
	//	ymin = ynew2;
	//if (ynew2 > ymax)
	//	ymax = ynew2;
	//if (ynew3 < ymin)
	//	ymin = ynew3;
	//if (ynew3 > ymax)
	//	ymax = ynew3;
	//if (ynew4 < ymin)
	//	ymin = ynew4;
	//if (ynew4 > ymax)
	//	ymax = ynew4;

	//if (xGreenMin < xmax &&
	//	xGreenMax > xmin &&
	//	yGreenMin < ymax &&
	//	yGreenMax > ymin)
	//{
	//	green = 1.0;
	//	red = 0.0;
	//}
	//else
	//{
	//	red = 0.0;
	//	green = 1.0;
	//}
}

void circleCollison()
{
	float localNum = (((squareXTransform - tank1XMovement) * (squareXTransform - tank1XMovement)) + (squareYTransform - (tank1YMovement)) * (squareYTransform - (tank1YMovement)));

	if (localNum < ((4 + 4) * (4 + 4)))
	{
		red = 1.0;
		green = 0.0;
	}
	else
	{
		green = 1.0;
		red = 0.0;
	}
}

void spiningSquareCorner()
{
	squareX = 4 * cos(spin * (PI / 180.0f)) + 4 * sin(spin * (PI / 180.0f)) + squareXTransform;
	squareY = 4 * sin(spin * (PI / 180.0f)) - 4 * cos(spin * (PI / 180.0f)) + squareYTransform;
}

void changeLineColor()
{
	//draw a line between the two points here!
	//glBegin(GL_LINES);
	//	glColor3f(red, green, blue);		
	//	glVertex2f(squareX, squareY);
	//	glVertex2f(Xtri,Ytri + 5.65);
	//glEnd();
	//end of code for drawing a line...

	number = (((squareXTransform - tank1XMovement) * (squareXTransform - tank1XMovement)) + (squareYTransform - (tank1YMovement + 5.65f)) * (squareYTransform - (tank1YMovement + 5.65f)));

	if (number < 30 || number < -30)
	{
		green = 0.0;
		red = 1.0;
	}
	else
	{
		red = 0.0;
		green = 1.0;
	}
}

void drawCircle(float x, float y, float radius)
{
	glBegin(GL_LINE_LOOP);
	for (float i = 0; i < 360; i += 5)
	{
		float xcoord = x + radius * cosf(i * (PI / 180.0f));
		float ycoord = y + radius * sinf(i * (PI / 180.0f));
		glVertex2f(xcoord, ycoord);
	}
	glEnd();
}

void reshape(int width, int height)		// Resize the OpenGL window
{
	screenWidth = width; screenHeight = height;         // to ensure the mouse coordinates match 
														// we will use these values to set the coordinate system

	glViewport(0, 0, width, height);					// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	//gluOrtho2D(-4000, 4000, -4000, 4000);             // View whole map 
	//gluOrtho2D(-300, 300, -300, 300);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}



void processKeys()
{
	if (keys[VK_LEFT])
	{
		tank1Angle += 0.4;
	}
	if (keys[VK_RIGHT])
	{
		tank1Angle -= 0.4;
	}
	if (keys[VK_UP])
	{
		tank1Velocity += 0.001f;
	}
	if (keys[VK_DOWN])
	{
		//tank1Velocity -= 0.0001f;
		tank1Velocity = 0;
	}
}











/******************* WIN32 FUNCTIONS ***************************/
#pragma region WIN32 FUNCTIONS

//WIN32 functions
LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	 // Declaration For WndProc
void KillGLWindow();									 // releases and destroys the window
bool CreateGLWindow(char* title, int width, int height); //creates the window
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);    // Win32 main function
void trackMousePos();                                    // tracks mouse position on window

//win32 global variabless
HDC			hDC = NULL;		// Private GDI Device Context
HGLRC		hRC = NULL;		// Permanent Rendering Context
HWND		hWnd = NULL;	// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application
                 // cursor position   

int WINAPI WinMain(HINSTANCE	hInstance,			// Instance
	HINSTANCE	hPrevInstance,		// Previous Instance
	LPSTR		lpCmdLine,			// Command Line Parameters
	int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	bool	done = false;								// Bool Variable To Exit Loop

	char title[] = "Tank-O-Mania";

	// Create Our OpenGL Window
	if (!CreateGLWindow(title, screenWidth, screenHeight))
	{
		return 0;									// Quit If Window Was Not Created
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
			SwapBuffers(hDC);				// Swap Buffers (Double Buffering)
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
		return 0;								// Jump Back
	}
	break;
	case WM_KEYUP:								// Has A Key Been Released?
	{
		keys[wParam] = false;					// If So, Mark It As FALSE
		return 0;								// Jump Back
	}
	break;
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void trackMousePos()
{
	if (GetCursorPos(&p))
	{
		print(our_font, 20, 95, "p.x: %7.2f", p.x);
		print(our_font, 20, 65, "p.y: %7.2f", p.y);
	}

	//if (ScreenToClient(hWnd, &p))
	//{
	//	print(our_font, 20, 95, "p.x: %7.2f", p.x);
	//	print(our_font, 20, 65, "p.y: %7.2f", p.y);
	//	std::cout << p.x;
	//}
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
	dwStyle = WS_OVERLAPPEDWINDOW;							// Windows Style

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd = CreateWindowEx(dwExStyle,							// Extended Style For The Window
		"OpenGL",							// Class Name
		title,								// Window Title
		dwStyle |							// Defined Window Style
		WS_CLIPSIBLINGS |					// Required Window Style
		WS_CLIPCHILDREN,					// Required Window Style
		0, 0,								// Window Position
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
	reshape(width, height);					// Set Up Our Perspective GL Screen

	init();

	return true;									// Success
}
#pragma endregion




/*double resultingPoint[2];
double point[3] = {-4,-4,0};
resultingPoint[0] = matrix[0]*point[0] + matrix[4]*point[1] + matrix[8]*point[2] + matrix[12];
resultingPoint[1] = matrix[1]*point[0] + matrix[5]*point[1] + matrix[9]*point[2] + matrix[13];

double matrix[16];
glGetDoublev(GL_MODELVIEW_MATRIX, matrix);*/

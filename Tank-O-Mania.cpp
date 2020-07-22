#include "UserTank.h"
#include "Track.h"

using namespace freetype;

const float PI = 3.1415926535897932384626433832795f;

POINT p;
int	mouse_x = 0, mouse_y = 0;
bool LeftPressed = false;
int screenWidth = 480, screenHeight = 480;
bool keys[256];

Track track = Track();
UserTank userTank = UserTank();



float speed = 0.1f;                                    // speed used as variable for tank1 speed
font_data our_font;                                 // font used to print message on display
float timer;                                        // timer used as game timer to calculate maths with time

float tank1XMovement = 0;                       // used to track transformation for tank X movement
float tank1YMovement = 0;	                        // used to track transformation for tank Y movement  
float tank1Angle = 0.0;
float tank1Velocity = 0;

//float tank1Matrix[16];

float squareXTransform = 0;
float squareYTransform = 0; // transform square x and y by arrrow key transformation


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


/**************************** function declarations ****************************/
void drawCircle(float x, float y, float radius, float angle); //prototype the draw function
void changeLineColor();
void circleCollison();
void printFunctions();

void drawUserTank();
void moveTank1Sprite();


void printCursor();
void moveCamera();
bool outsideObject(Point P, Point V[], int n);

/**************************** OPENGL FUNCTION PROTOTYPES ****************************/
void display();				//draws everything to the screen
void reshape(int width, int height);//called when the window is resized
void init();				//called in winmain when the program starts.
void processKeys();			//called in winmain to process keyboard controls


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

	glClearColor(0.0, 0.0, 0.0, 0.0);     // glClear(GL_COLOR_BUFFER_BIT) in 
	                                      // the display function will clear 
	                                      // the buffer to this colour.

	our_font.init("arialbd.TTF", 22);     //Build the freetype font

	track.loadTexture();


	userTank.loadTexture();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/*************    START OF OPENGL FUNCTIONS   ****************/
void display()
{	

		glClear(GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		track.drawTrackBackground();
		track.drawEasyTrack();

		
		int i = 200;
		/*
		glPushMatrix();
		glColor3f(1, 1, 1);
		glBegin(GL_LINE_LOOP);
			glVertex2f(-50 + i, 0);
			glVertex2f(-50 + i, 1500);
			glVertex2f(500 + i, 2000);
			glVertex2f(1000 + i, 2100);
			glVertex2f(1300 + i, 1300);
			glVertex2f(1300 + i, 0);
			glVertex2f(-50 + i, 0);
		glEnd();
		glPopMatrix();
		

		glPushMatrix();
		glColor3f(1, 1, 1);
		glBegin(GL_LINE_LOOP);
			glVertex2f(1000, 1000);
			glVertex2f(1000, -1000);
			glVertex2f(-1000, -1000);
			glVertex2f(-1000, 1000);
		glEnd();
		glPopMatrix();
		
		glPushMatrix();
		glColor3f(1, 1, 1);
		glBegin(GL_LINE_LOOP);
			glVertex2f(1500, 1500);
			glVertex2f(1500, -1500);
			glVertex2f(-1500, -1500);
			glVertex2f(-1500, 1500);
		glEnd();
		glPopMatrix();
		*/

		//Vertex v2[] = { {-50 + i,0}, {-50 + i, 1500}, {500 + i,2000}, {1000 + i, 2100}, {1300 + i,1300}, {1300 + i, 0}, {0 + i, 0} };
		//Vertex v2[] = { {-1000, -1000}, {-1000, 1000}, {1000, 1000}, {1000, -1000} };
		//Vertex p2 = { tank1XMovement, tank1YMovement };
	    //int n2 = sizeof(v2) / sizeof(v2[0]);

		/*
		glPushMatrix();
			glColor3f(1,1,1);
			glBegin(GL_LINE_LOOP);
			glVertex2f(100 + i, 100);
			glVertex2f(100 + i, 1100);
			glVertex2f(600 + i, 1600);
			glVertex2f(900 + i, 1900);
			glVertex2f(1100 + i, 1100);
			glVertex2f(1100 + i, 100);
			glVertex2f(100 + i, 100);
			glEnd();
		glPopMatrix();
		*/

		//Vertex v[] = { {100 + i,100}, {100 + i,1100}, {600 + i,1600}, {900 + i, 1900}, {1100 + i,1100}, {1100 + i,100}, {100 + i,100} };
		//Vertex v[] = { {-1500, -1500}, {-1500, 1500}, {1500, 1500}, {1500, -1500} };
		//Vertex p = {tank1XMovement, tank1YMovement};
		//int n = sizeof(v) / sizeof(v[0]);

		//if (!outsideObject(p, v, n) && outsideObject(p2, v2, n2))
		//{
			//speed = 1.5f;
			//print(our_font, 20, 35, "Inside");
		//}
		//else
		//{

			//speed = 1.5f;
			//print(our_font, 20, 35, "Outside");
		//}

		
		//drawCircle(0, 0, 2000, 179);

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

	float tempX = 0.0f;

	if (userTank.tankOBB.SAT2D(track.trackOBB))
	{
		print(our_font, 20, 95, "COllision!");

		tank1Angle = tank1Angle + 180;
		for(int i = 0; i < 100 ; i++)
		{
			tank1XMovement += tank1Velocity * cosf((90 + tank1Angle) * (PI / 180.0f));
			tank1YMovement += tank1Velocity * sinf((90 + tank1Angle) * (PI / 180.0f));
		} 
		//tank1Angle = tank1Angle + 180;
	}

	/**************************** methods ****************************/
	printFunctions();

	

	drawUserTank();
    moveTank1Sprite();
	
    moveCamera();

}

void moveTank1Sprite()
{
	//update the position of the user controlled object.
	tank1XMovement += tank1Velocity * cosf((90 + tank1Angle) * (PI / 180.0f));
	tank1YMovement += tank1Velocity * sinf((90 + tank1Angle) * (PI / 180.0f));
}

void drawUserTank()
{
	userTank.x = tank1XMovement;
	userTank.y = tank1YMovement;
	userTank.direction = tank1Angle;

	userTank.tankOBB.transformPoints(userTank.matrix);

	track.trackOBB.transformPoints(track.matrix);
	track.drawTrackOBB(100, -900, 100, 1000);
	
	userTank.drawTank();
	userTank.setOBBPoints();
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

void moveCamera() 
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
		gluOrtho2D((tank1XMovement - screenWidth / 2), (tank1XMovement + screenWidth / 2), (tank1YMovement - screenHeight / 2), (tank1YMovement + screenHeight / 2));
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void printFunctions()
{	
	print(our_font, 0, 65, "%7.2f", tank1Velocity);
	//print(our_font, 20, 65, "tank1YMovement: %7.2f", tank1YMovement);
	//print(our_font, 20, 35, "squareMaxX: %7.2f", squareMaxX);
	//print(our_font, 20, 5,  "speed: %7.2f", speed);
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

void changeLineColor()
{
	//draw a line between the two points here!
	//glBegin(GL_LINES);
	//	glColor3f(red, green, blue);		
	//	glVertex2f(squareX, squareY);
	//	glVertex2f(Xtri,Ytri + 5.65);
	//glEnd();
	//end of code for drawing a line...

	timer = (((squareXTransform - tank1XMovement) * (squareXTransform - tank1XMovement)) + (squareYTransform - (tank1YMovement + 5.65f)) * (squareYTransform - (tank1YMovement + 5.65f)));

	if (timer < 30 || timer < -30)
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

void drawCircle(float x, float y, float radius, float angle)
{
	glBegin(GL_LINE_LOOP);
	for (float i = 0; i < angle; i += 5)
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
		//tank1Velocity += speed;
		tank1Velocity = speed;
	}
	if (keys[VK_DOWN])
	{
		//tank1Velocity -= 0.0001f;
		//tank1Velocity = 0;
		tank1Velocity = -speed;
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
	bool	done = false;								// Bool Variable To Exit Loop

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
	reshape(width, height);					        // Set Up Our Perspective GL Screen


	init();

	return true;									// Success
}

void printCursor()
{
	if (GetClientRect)
	{
	
	}

	//ShowCursor(FALSE);//hides the cursor

	if (GetCursorPos(&p))
	{
		/*glPushMatrix();
		glRotatef((atan2(p.x,p.y) * 180 / PI),0,0,1);
		glBegin(GL_POLYGON);
		glVertex2f(0,0);
		glVertex2f(0,50);
		glVertex2f(50,50);
		glVertex2f(50,0);
		glEnd();
		glPopMatrix();*/

		//cursor position now in p.x and p.y
		print(our_font, 0, 95, "p.x: %ld", p.x);
		print(our_font, 0, 125, "p.y: %ld", p.y);
		print(our_font, 0, 65, "angle: %f", (atan2(p.y, p.x) * 180 / PI));

		//userTank.point.x = p.x;
		//userTank.point.y = p.y;
	}

	if (ScreenToClient(hWnd, &p))
	{
		//cursor position now in p.x and p.y
		print(our_font, 0, 35, "client p.x: %ld", p.x);
		print(our_font, 0, 5, "client p.y: %ld", p.y);
	}
}
#pragma endregion
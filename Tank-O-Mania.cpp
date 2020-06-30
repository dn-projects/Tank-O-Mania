
//includes areas for keyboard control, mouse control, resizing the window
//and draws a spinning rectangle
#include <windows.h>		// Header File For Windows
#include "glew.h"
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <math.h>
#include "FreeType.h"
#include "OBB.h"

using namespace freetype;

const float PI = 3.1415926535897932384626433832795f;

int	mouse_x = 0, mouse_y = 0;
bool LeftPressed = false;
int screenWidth = 480, screenHeight = 480;
bool keys[256];
float spin = 0;



OBB square, triangle;



/**************************** variables for font ****************************/
font_data our_font;



/**************************** variables for timer ****************************/
float number;



/**************************** variables for transformation matrix ****************************/
float squareTransformationMatrix[16];
float triangleTransformationMatrix[16];



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
float triangleXTransform = 0;
float triangleYTransform = 0;	// transform triangle x and y by arrrow key transformation

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



/**************************** OPENGL FUNCTION PROTOTYPES ****************************/
void display();				//draws everything to the screen
void reshape(int width, int height);//called when the window is resized
void init();				//called in winmain when the program starts.
void processKeys();			//called in winmain to process keyboard controls






/*************    START OF OPENGL FUNCTIONS   ****************/
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();




	// white axis lines
	glLineWidth(1.5);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	glVertex2f(-20, 0);
	glVertex2f(20, 0);
	glVertex2f(0, 20);
	glVertex2f(0, -20);
	glEnd();







	// square
	glPushMatrix();

	// square transformation 
	glTranslatef(squareXTransform, squareYTransform, 0);
	//glRotatef(spin, 0.0, 0.0, 1.0);

	// square color
	glColor3f(1.0, 0.0, 0.0);

	// square initalisation
	glBegin(GL_POLYGON);
	glVertex2f(-4, -4);
	glVertex2f(-4, 4);
	glVertex2f(4, 4);
	glVertex2f(4, -4);
	glEnd();

	// square centre point
	//glColor3f(0.0,1.0,1.0);
	//glPointSize(20.0);
	//glBegin(GL_POINTS);
	//	glVertex2f(0,0);
	//glEnd();
	//glPointSize(1.0);

	// square bounding box
	glColor3f(red, green, blue);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-4, -4);
	glVertex2f(-4, 4);
	glVertex2f(4, 4);
	glVertex2f(4, -4);
	glEnd();

	glGetFloatv(GL_MODELVIEW_MATRIX, squareTransformationMatrix);

	glPopMatrix();









	// triangle
	glPushMatrix();

	// triangle transformation
	glTranslatef(triangleXTransform, triangleYTransform, 0.0);

	// triangle color
	glColor3f(0, 1, 0);

	// triangle initialisation
	glBegin(GL_TRIANGLES);
	glVertex2f(-4, -4);
	glVertex2f(4, -4);
	glVertex2f(0, 5.65f);
	glEnd();

	// triangle centre point
	//glColor3f(0.0,0.0,1.0);
	//glPointSize(20.0);
	//glBegin(GL_POINTS);
	//	glVertex2f(0,0);
	//glEnd();
	//glPointSize(1.0);

	// triangle bounding box
	glColor3f(1, 1, 1);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-4, -4);
	glVertex2f(4, -4);
	glVertex2f(4, 5.65F);
	glVertex2f(-4, 5.65F);
	glEnd();

	glGetFloatv(GL_MODELVIEW_MATRIX, triangleTransformationMatrix);

	glPopMatrix();

	glFlush();

	square.transformPoints(squareTransformationMatrix);
	triangle.transformPoints(triangleTransformationMatrix);

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


	spin += 0.05f;
	if (spin > 360)
		spin = 0;
}

void printFunctions()
{
	print(our_font, 20, 95, "squareMaxY: %7.2f", squareMaxY);
	//print(our_font, 20, 65, "squareMinY: %7.2f", squareMinY);
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
	float localNum = (((squareXTransform - triangleXTransform) * (squareXTransform - triangleXTransform)) + (squareYTransform - (triangleYTransform)) * (squareYTransform - (triangleYTransform)));

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

	number = (((squareXTransform - triangleXTransform) * (squareXTransform - triangleXTransform)) + (squareYTransform - (triangleYTransform + 5.65f)) * (squareYTransform - (triangleYTransform + 5.65f)));

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
	screenWidth = width; screenHeight = height;           // to ensure the mouse coordinates match 
														// we will use these values to set the coordinate system

	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	gluOrtho2D(-20, 20, -20, 20);           // set the coordinate system for the window

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);						//sets the clear colour to yellow
														//glClear(GL_COLOR_BUFFER_BIT) in the display function
														//will clear the buffer to this colour.

	our_font.init("arialbd.TTF", 22);                   //Build the freetype font
}

void processKeys()
{
	if (keys[VK_LEFT])
	{
		triangleXTransform -= 0.05f;
	}
	if (keys[VK_RIGHT])
	{
		triangleXTransform += 0.05f;
	}
	if (keys[VK_UP])
	{
		triangleYTransform += 0.05f;
	}
	if (keys[VK_DOWN])
	{
		triangleYTransform -= 0.05f;
	}

	if (keys[0x41])
	{
		squareXTransform -= 0.05f;
	}
	if (keys[0x44])
	{
		squareXTransform += 0.05f;
	}
	if (keys[0x57])
	{
		squareYTransform += 0.05f;
	}
	if (keys[0x53])
	{
		squareYTransform -= 0.05f;
	}

}











/******************* WIN32 FUNCTIONS ***************************/
#pragma region WIN32 FUNCTIONS

//WIN32 functions
LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc
void KillGLWindow();									// releases and destroys the window
bool CreateGLWindow(char* title, int width, int height); //creates the window
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);  // Win32 main function

//win32 global variabless
HDC			hDC = NULL;		// Private GDI Device Context
HGLRC		hRC = NULL;		// Permanent Rendering Context
HWND		hWnd = NULL;		// Holds Our Window Handle
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

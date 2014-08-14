#define WIN32_LEAN_AND_MEAN 
// sets it up without extras and bloat 
  
//allows setting in code rather than properties 
#pragma comment(lib, "opengl32.lib") 
#pragma comment(lib, "glu32.lib") 
  
#pragma comment(linker, "/subsystem:console") 
  
#include "windows.h" 
#include <stdlib.h> //import standard C library 
  
#include <gl/gl.h>           // standard OpenGL include# 
#include <gl/glu.h>         // OpenGL utilties 
#include "glut.h"        // OpenGL utilties 
#include <time.h>

#include <iostream> 
  
using namespace std; 

#include "world.h"
  
//prototypes for our callback functions 
void DisplayScene(void);    //our drawing routine 
void idle(void);    //what to do when nothing is happening 
void key(unsigned char k, int x, int y);  //handle key presses 
void reshape(int width, int height);      //when the window is resized 
void init_drawing(void);                  //drawing intialisation 
void renderString(float x, float y, float z, void *font, char *string); //to render text strings to the screen 
void OnMouseClick(int, int, int, int);
void ConvertToArrayPos(int, int, int); 

//global variables
float GRID_SIZE = 10; 
const int GRID_X = 50; 
const int GRID_Y = 50; 
float X_START = 0;
float Y_START = 0;

int WIN_X = 600;
int WIN_Y = 600;

World world;

//Mouse clicks variables 
int xmouse = NULL;
int ymouse = NULL;

int test = 1;

int timeCurrent = 0; //time variables for use in timer function
int timePrevious = 0;
int msPerUpdate = 100;

//our main routine 
int main(int argc, char *argv[]) 
{ 
  //Initialise Glut and create a window 
  glutInit(&argc, argv); 
  //sets up our display mode 
  //here we've selected an RGBA display with depth testing  
  //and double buffering enabled 

  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE); 
  //create a window and pass through the windows title 
  glutCreateWindow("Pirate Tower Defense - Ian Evans"); 
  
  //run our own drawing initialisation routine 
  init_drawing(); 

  //tell glut the names of our callback functions point to our  
  //functions that we defined at the start of this file 
  glutReshapeFunc(reshape); 
  glutKeyboardFunc(key); 
  glutIdleFunc(idle); 
  glutDisplayFunc(DisplayScene); 
  
  //request a window size 
  glutInitWindowSize(WIN_X, WIN_Y); 
  glutReshapeWindow(WIN_X, WIN_Y); 
  
  glutMouseFunc(OnMouseClick);

  srand (time(NULL));
  world.CreateNodes();

  //world.RandomizeNodes();
  //world.nodes[1].isAlive = true;
  //world.nodes[41].isAlive = true;
  //world.nodes[81].isAlive = true;
  //go into the main loop 
  //this loop won't terminate until the user exits the  
  //application 
  glutMainLoop(); 
  
  return 0; 
} 
  
  
/***************************************************************************** 
 DisplayScene() 
  
 The work of the application is done here. This is called by glut whenever the  
//window needs to be redrawn 
*****************************************************************************/
  
void DisplayScene(void) 
{ 
    //clear the current window 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    //make changes to the modelview matrix 
    glMatrixMode(GL_MODELVIEW); 
    //initialise the modelview matrix to the identity matrix 
    glLoadIdentity(); 


	world.DrawNodes();
	world.DrawDefenses();
	world.baseGrid->DrawGrid();
	world.oceanGrid->DrawGrid();

    //flush what we've drawn to the buffer 
    glFlush(); 
    //swap the back buffer with the front buffer 
    glutSwapBuffers(); 
  
} 
  
//idle callback function - this is called when there is nothing  
//else to do 
void idle(void) 
{ 
	glutPostRedisplay();
} 
  
//key callback function - called whenever the user presses a  
//key 
void key(unsigned char k, int x, int y) 
{ 
  switch(k) 
  { 
    case 27: //27 is the ASCII code for the ESCAPE key 
      exit(0); 
      break; 
  } 
} 
  
//reshape callback function - called when the window size changed 
void reshape(int width, int height) 
{ 
    //set the viewport to be the same width and height as the window 
    glViewport(0,0,width, height); 
    //make changes to the projection matrix 
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 
  
    //set up our projection type 
    //we'll be using a perspective projection, with a 90 degree  
    //field of view 
    gluOrtho2D(0, (float) width , (float) height, 0.0); 
    //redraw the view during resizing 
    DisplayScene(); 
} 
  
//set up OpenGL before we do any drawing 
//this function is only called once at the start of the program 
void init_drawing(void) 
{ 
    //blend colours across the surface of the polygons 
    //another mode to try is GL_FLAT which is flat shading 
    glShadeModel(GL_SMOOTH); 
    //turn lighting off 
    glDisable(GL_LIGHTING); 
    //enable OpenGL hidden surface removal 
    glDepthFunc(GL_LEQUAL); 
    glEnable(GL_DEPTH_TEST); 
} 

//used by the glut mouse function - only need x and y for this game to know where the user clicks
void OnMouseClick(int button, int state, int x, int y)
{
	//only return if button is pushed down, stops repeated
	if(state != GLUT_DOWN)
		return;
	xmouse = x;
	ymouse = y;
	world.CreateDefense(world.oceanNodeList[0], 1);
	world.CreateDefense(world.oceanNodeList[6], 0);
	world.CreateDefense(world.oceanNodeList[12], 1);
	world.CreateDefense(world.oceanNodeList[18], 0);

	std::cout << "Button pressed: " << button << std::endl;
	std::cout << "Mouse x: " << xmouse << std::endl;
	std::cout << "Mouse y: " << ymouse << std::endl;

	//ConvertToArrayPos(xmouse, ymouse, button);
}
/*
//takes the x and y co ord and gives the row, column and position in the grid.objectList (if within the grid area)
void ConvertToArrayPos(int ymouse, int xmouse, int button)
{
	if(xmouse >= X_START && xmouse <= GRID_X * GRID_SIZE + X_START
		&& ymouse >= Y_START && ymouse <= GRID_Y * GRID_SIZE + Y_START)
	{
		//convert x and y co-ord to the row and column clicked
		int row = floor(((xmouse - X_START) / GRID_SIZE));
		int column = floor(((ymouse - Y_START) / GRID_SIZE));

		std::cout << "Row: " << row << std::endl;
		std::cout << "Column: " << column << std::endl;

		//convert row and column to pos in the array on the objects
		int pos = (row) + (column * GRID_X);
		std::cout << "Array position of clicked node: " << pos << std::endl;
		
		if(button == 0)
			world.nodes[pos].isAlive = true;
		else if(button == 2) //right click
			world.nodes[pos].isAlive = false;
	}
}

//timer function to count up to a second
void timer(void)
{
	
}*/
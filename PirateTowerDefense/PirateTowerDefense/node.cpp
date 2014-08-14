#include "node.h"


void Node::DrawNode()
{
	glPushMatrix();

	switch(nodeType){
	case 0:
		glColor3f(0.0, 0.0, 1.0);
		break;
	case 1:
		glColor3f(1.0, 1.0, 1.0);
		break;
	}
	glBegin(GL_QUADS);
		glVertex2f(float(x - size), float(y - size));
		glVertex2f(float(x + size), float(y - size));
		glVertex2f(float(x + size), float(y + size));
		glVertex2f(float(x - size), float(y + size));
	glEnd();

	glPopMatrix();
}

//LoadTexture function - Allows the use of pictures on disk to be used as textures in OpenGL via SOIL
//SOIL available from http://www.lonesock.net/soil.html - coded by Sam Barrett
void Node::LoadTexture(void)
{
	/* load an image file directly as a new OpenGL texture */
    texture[0] = SOIL_load_OGL_texture
        (
        "ocean.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
        );
	
	 texture[1] = SOIL_load_OGL_texture
        (
        "sand.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
        );
		
    glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[1]);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);                                    
}

void Node::DrawNodeTexture(void)
{
	//load the textures needed for drawing
	LoadTexture();
	
		glPushMatrix();
			glEnable(GL_TEXTURE_2D); //enable texturing
			glAlphaFunc(GL_GREATER, 0.1); //use alpha values so no black background
			glEnable(GL_ALPHA_TEST);
			glColor4f(1.0, 1.0, 1.0, 1.0); // reset gl color

			//depending on object type, use certain texture
			if(nodeType == 0)
				glBindTexture(GL_TEXTURE_2D, texture[0]);
			else if(nodeType == 1)
				glBindTexture(GL_TEXTURE_2D, texture[1]);
			
			//draw the sqaure
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 1.0f); glVertex2f(float(x - size), float(y - size));
				glTexCoord2f(1.0f, 1.0f); glVertex2f(float(x + size), float(y - size));
				glTexCoord2f(1.0f, 0.0f); glVertex2f(float(x + size), float(y + size));
				glTexCoord2f(0.0f, 0.0f); glVertex2f(float(x - size), float(y + size));
			glEnd();
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
}
#include <GL/glut.h>  
#include <stdlib.h>
#include<stdio.h>
#include<camera.h>
/*
http://blog.csdn.net/hobbit1988/article/details/7956838
*/

/*
g++ main.cpp camera.cpp -Iinclude -lGL -lglut -lGLU
*/
static int shoulder = 0, elbow = 0;  
static int nearplane=1;
static int eyez=0;
    
void init(void)   
{  
   glClearColor (0.0, 0.0, 0.0, 0.0);  
   glShadeModel (GL_FLAT);  
}  
  void display(void)  
{  
   glClear (GL_COLOR_BUFFER_BIT);  
     glPushMatrix();//保存的是单位矩阵  
      
     glTranslatef (1.0, 0.0, 0.0);
   glutWireCube (1.0);  
  glPopMatrix();
  glutSwapBuffers(); 
    
}  
void reshape (int w, int h)  
{  
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);    
   glMatrixMode (GL_PROJECTION);  
   glLoadIdentity ();
   gluPerspective(65.0, (GLfloat) w*1/(GLfloat) h, nearplane, 20.0);  
   glMatrixMode(GL_MODELVIEW);
   
   glLoadIdentity();
   gluLookAt(0, 0, 2, 0, 0,-1, 0, 1, 0); 
    glTranslatef (0.0, 0.0, -5.0);  
}  
  
void keyboard (unsigned char key, int x, int y)  
{  
    static int angle=5;  
   switch (key) {
        case 'w':
        glMatrixMode(GL_MODELVIEW);
        eyez++;
        glLoadIdentity();
        
        gluLookAt(0, 0, eyez, 0, 0,-1, 0, 1, 0); 
          glTranslatef (0.0, 0.0, -5.0);
        glutPostRedisplay();
         break;  
         case 's':
        glMatrixMode(GL_MODELVIEW);
        eyez--;
        glLoadIdentity();
        gluLookAt(0, 0, eyez, 0, 0,-1, 0, 1, 0); 
        glTranslatef (0.0, 0.0, -5.0);  
        glutPostRedisplay();
         break;  
      case 27:  
         exit(0);  
         break;
        
      default:  
         break;  
   }  
}  
  
int main(int argc, char** argv)  
{  
   glutInit(&argc, argv);  
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);  
   glutInitWindowSize (500, 500);   
   glutInitWindowPosition (100, 100);   
   glutCreateWindow (argv[0]);  
   init ();  
   glutDisplayFunc(display);   
   glutReshapeFunc(reshape);  
   glutKeyboardFunc(keyboard);  
   glutMainLoop();  
   return 0;  
} 

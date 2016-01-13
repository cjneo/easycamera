#include <GL/glut.h>  
#include <stdlib.h>
#include<stdio.h>
#include<camera.h>
#include<iostream>
using namespace std;
/*
http://blog.csdn.net/hobbit1988/article/details/7956838
*/

/*
g++ main.cpp camera.cpp -Iinclude -lGL -lglut -lGLU
*/
static int shoulder = 0, elbow = 0;  
static int nearplane=1;
Camera camera;
   float dxx=10;
   float dyy=-0.2;
   void  RotateY(float angle);
   void  RotateX(float angle) ;
void init(void)   
{  
   glClearColor (0.0, 0.0, 0.0, 0.0);  
   glShadeModel (GL_FLAT);  
}  
  void display(void)  
{  
    camera.roll(0);
   glClear (GL_COLOR_BUFFER_BIT);  
     glPushMatrix();//保存的是单位矩阵  
     //glTranslatef (0.0, 0.0, -6.0);
    // glTranslatef (-1.0, -1.0, -1.0);
   glutWireCube (1.0);  
  glPopMatrix();
  glutSwapBuffers(); 
    
}  
void reshape (int w, int h)  
{  
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);  
   camera.setShape( 65, 1, 1, 20); 
   /*
   glMatrixMode (GL_PROJECTION);  
   glLoadIdentity ();
   
   gluPerspective(65.0, (GLfloat) w*1/(GLfloat) h, nearplane, 20.0);  
   glMatrixMode(GL_MODELVIEW);  
   glLoadIdentity();
   */  
   //glTranslatef (0.0, 0.0, -5.0);  
}  
  
void keyboard (unsigned char key, int x, int y)  
{  
    static int angle=5;  
   switch (key) {
        case 'w':
        // nearplane = (nearplane+1) % 18; 
        // glMatrixMode (GL_PROJECTION);
        //  glLoadIdentity ();  
        // gluPerspective(65.0, 1, nearplane, 20.0);  
      
         camera.roll(dxx);
         camera.u.dump();
        camera.v.dump();
         //camera.slide(0,0,-dyy);  
         glutPostRedisplay();
         printf("nearplane %d\n",nearplane);
         break; 
         
         case 'a':
         camera.yaw(dxx);
         glutPostRedisplay();
          
         break;
         case 's':
         camera.pitch(dxx); 
         glutPostRedisplay();
          
         break; 
         
      case 27:  
         exit(0);  
         break;
        
      default:  
         break;  
   }  
}  
//button:GLUT_LEFT_BUTTON GLUT_MIDDLE_BUTTON GLUT_RIGHT_BUTTON

void mouse(int button ,int state,int x, int y){
    static int ddx,ddy,udx,udy;
    if(button == GLUT_LEFT_BUTTON){
        if(state ==GLUT_DOWN){
            cout<<"down "<< x<<" "<<y<<endl;
            ddx=x;
            ddy=y;
        }
        else if(state == GLUT_UP){
            cout<<"up " << x << " " <<y<<endl;
            int dx,dy;
            dx=x-ddx;
            dy=y-ddy;
            RotateX(dx);  
            RotateY(dy); 
            glutPostRedisplay();
        }
    }
    static int rdx,rdy ;
    if(button == GLUT_RIGHT_BUTTON){
        if(state ==GLUT_DOWN){
            //cout<<"down "<< x<<" "<<y<<endl;
            rdx=x;
            rdy=y;
        }
        else if(state == GLUT_UP){
            //cout<<"up " << x << " " <<y<<endl;
            int dx,dy;
            dx=x-rdx;
            dy=y-rdy;
            //camera.roll(dx);  
            camera.slide(0,0,-dy);  
            glutPostRedisplay();
        }
    }
}
void RotateX(float angle)  
{  
    Camera &cam=camera;
    float d=cam.getDist();  
    cout<<"d "<<d<<endl;
    int cnt=100;  
    float theta=angle/cnt;  
    float slide_d=-2*d*sin(theta*3.14159265/360);  
    cam.yaw(theta/2);              
    for(;cnt!=0;--cnt)  
    {  
        cam.slide(slide_d,0,0);  
        cam.yaw(theta);  
    }    
    cam.yaw(-theta/2);  
}  
  
void  RotateY(float angle)  
{  
    Camera &cam=camera;
    float d=cam.getDist();  
    int cnt=100;  
    float theta=angle/cnt;  
    float slide_d=2*d*sin(theta*3.14159265/360);
    
    
    cam.pitch(theta/2);  
    for(;cnt!=0;--cnt)  
    {  
        cam.slide(0,slide_d,0);  
        cam.pitch(theta);  
    }  
    cam.pitch(-theta/2);
    
}  

int main(int argc, char** argv)  
{  
camera.setCamera( 0, 0, 2,0, 0, 0, 0, 1, 2); 
   glutInit(&argc, argv);  
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);  
   glutInitWindowSize (500, 500);   
   glutInitWindowPosition (100, 100);   
   glutCreateWindow (argv[0]);  
   init ();  
   glutMouseFunc(mouse);
   
   glutDisplayFunc(display);   
   glutReshapeFunc(reshape);  
   glutKeyboardFunc(keyboard);  
   glutMainLoop();  
   return 0;  
} 

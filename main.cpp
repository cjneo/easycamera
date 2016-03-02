#include <GL/glut.h>  
#include <stdlib.h>
#include<stdio.h>
#include<camera.h>
#include<iostream>
#include<checkImage.h>
#include<pngreader.h>
using namespace std;
 extern GLubyte checkImage[checkImageHeight][checkImageWidth][4];
 extern GLuint texName;
 extern float ewidth ,height ,width ;
 extern char dun[500][500];
 bool collision_test(float du, float dv, float dn);
/*
http://blog.csdn.net/hobbit1988/article/details/7956838
*/

/*
g++ main.cpp camera.cpp -Iinclude -lGL -lglut -lGLU
g++ main.cpp camera.cpp pngreader.cpp checkimage.cpp randomMaze.cpp -lpng -Iinclude -lGL -lglut -lGLU
*/
static int shoulder = 0, elbow = 0;  
static int nearplane=1;
bool first=true,second=true,third=true;
Camera camera;
   float dxx=10;
   float dyy=-0.2;
   void  RotateY(float angle);
   void  RotateX(float angle) ;
void init(void)   
{  
    glClearDepth(1.0);
   glClearColor (0.0, 0.0, 0.0, 0.0);  
  // glShadeModel (GL_FLAT);  
}  
  void display(void)  
{  
    camera.roll(0);
   glEnable(GL_DEPTH_TEST);
   glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    glDepthFunc(GL_LEQUAL);  
    // glPushMatrix();//保存的是单位矩阵  
     //glTranslatef (0.0, 0.0, -6.0);
    // glTranslatef (-1.0, -1.0, -1.0);
    /*
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.5,-0.5,0.0);
    glVertex3f(0.5,-0.0,0.0);
    glVertex3f(0.0,0.5,0.0);
    glEnd();
    */
    /*
    
    */
    /*
    const int num_indices=4;
    float vertices[]=
    {-0.5,-0.0,0.0,
     0.0,-0.5,0.0,
   0.5,-0.0,0.0,
   0.0,0.5,0.0
   };
   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(
   3,       //dimention of each vertices 
   GL_FLOAT,// type of vertices
   0,       //gap of each vertices
   vertices //pointer of first vertices
   );
   //glDrawArrays(GL_TRIANGLES,0,num_indices);
   */
   /*
    glDrawArrays(
    GL_LINE_LOOP,//type to draw
    0,           //offset of the pointer
    num_indices  //count of the vertices  
    );
    */
     GLushort indices[] = { 0, 1, 2, 1, 2, 3 };
    // glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices );
   //  glDrawElements ( GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_SHORT, indices );
   //glutWireCube (1.0);  
  // cidisplay();
  glBindTexture(GL_TEXTURE_2D, CreateTextureFromPng("brick.png"));
  //float *ver=malloc(sizeof(float)*8);
  
 // glEnable(GL_CULL_FACE);
//GL_FRONT,GL_BACK,GL_FRONT_AND_BACK
 //   glCullFace(GL_BACK);
    //drawWallMap();
    createMap();
    /*
    if(third){
    if(first)
    drawWall(0,0,0);
    if(second)
    vdrawWall(0,0,0);
    }
    */
    
 // glPopMatrix();
  glutSwapBuffers(); 
    
}  
void reshape (int w, int h)  
{  
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);  
   camera.setShape( 65, 1, 0.1, 20); 
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
    float slidestep=0.1; 
   switch (key) {
        case 'w':
        if(collision_test(0,0,-slidestep)){
         camera.slide(0,0,-slidestep); 
         glutPostRedisplay();
         }
         break; 
         
         case 'a':
         if(collision_test(-slidestep,0,0)){
         camera.slide(-slidestep,0,0);
         glutPostRedisplay( );
          }
         break;
         
         case 'd':
          if(collision_test(slidestep,0,0)){
         camera.slide(slidestep,0,0);
         glutPostRedisplay( );
          }
         break;
         
         case 's':
          if(collision_test(0,0,slidestep )){
         camera.slide(0,0,slidestep); 
         glutPostRedisplay();
         }
         break;
         
         case '1':
         first=!first;
         cout<<"first "<<first<<std::endl;
         glutPostRedisplay();
         break; 
         
         case '2':
         second=!second;
         glutPostRedisplay();
         break; 
         
         case '3':
         third=!third;
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
            //cout<<"down "<< x<<" "<<y<<endl;
            ddx=x;
            ddy=y;
        }
        else if(state == GLUT_UP){
            //cout<<"up " << x << " " <<y<<endl;
            int dx,dy;
            dx=x-ddx;
            dy=y-ddy;
            camera.yaw(-dx/10);
          //  RotateX(dx/10);  
            //RotateY(dy); 
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
    int cnt=1000;  
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
//camera.setCamera( 0, 0, 2,0, 0, 0, 0, 1, 2); 
    float sx=width*2+0+width;
    float sy=0.6;
    float sz=0-width*2-width;
camera.setCamera( sx, sy, sz,sx, sy, sz-1, sx, 1+sy, sz); 
   glutInit(&argc, argv);  
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB|GLUT_DEPTH);  
   glutInitWindowSize (500, 500);   
   glutInitWindowPosition (100, 100);   
   glutCreateWindow (argv[0]);  
   init ();  
   //ciinit( );
   glutMouseFunc(mouse);
   
   glutDisplayFunc(display);   
   glutReshapeFunc(reshape);  
   glutKeyboardFunc(keyboard);  
   glutMainLoop();  
   return 0;  
} 
bool collision_test(float du, float dv, float dn){
    float curx,curz;
    camera.trySlide(  du*3,   dv*3,   dn*3);
    int i=camera.tryeye.x/2;
    int j=camera.tryeye.z/-2;
    if(dun[i][j]=='1'){
         
        return true;
    }
    
     
    return false;   
}

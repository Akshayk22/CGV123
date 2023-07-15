#include<GL/glut.h>
#include<stdio.h>
#include<math.h>

#define PI 3.1416
      
	typedef struct point
	{ 
    	GLfloat x, y, z;
	 }; 
	 
 int fact(int n)
 {
   if (n<=1) 
       return (1);
    else
      n = n * fact( n-1 );
     return n;
 }

void bino(int n, int *c)
 {
    int r;
    for (r=0; r<=n; r++) //start from nC0, then nC1, nC2, nC3 till nCn
    {
       c [r] = fact(n) / ( fact(n-r) * fact(r) );
    }
 }
 void computeBezPt(GLfloat u, point *bezPt, GLint nCtrlPts, point *ctrlPts, GLint *C) 
  {
      GLint k, n=nCtrlPts-1;
	  GLfloat bezBlendFcn;
	  bezPt ->x =bezPt ->y = bezPt->z=0.0;
	   for(k=0; k< nCtrlPts; k++) 
		 { 
		     bezBlendFcn = C[k] * pow(u, k) * pow( 1-u, n-k); //Bernstein Polynomials
		     bezPt ->x += ctrlPts[k].x * bezBlendFcn;
		     bezPt ->y += ctrlPts[k].y * bezBlendFcn;
	         bezPt ->z += ctrlPts[k].z * bezBlendFcn;
	     }
  } 
   void bezier(point *ctrlPts, GLint nCtrlPts, GLint nBezCurvePts) 
	{
	   point bezCurvePt;
	   GLfloat u;
	   GLint *C, k;
	   C= new GLint[nCtrlPts];
	   bino(nCtrlPts-1, C); 
	   glBegin(GL_LINE_STRIP);
		 for(k=0; k<=nBezCurvePts; k++) 
		  { 
		      u=GLfloat(k)/GLfloat(nBezCurvePts);
		      computeBezPt(u, &bezCurvePt, nCtrlPts, ctrlPts, C); 
		      glVertex2f(bezCurvePt.x, bezCurvePt.y);
		  } 
		  glEnd(); 
		  delete[]C;
    }
	void mydisplay()
	 {
	     GLint nCtrlPts = 4, nBezCurvePts =20; 
		 static float theta = 0;
		 point ctrlPts[4] = { {20, 100, 0}, {30, 110, 0}, {50, 90, 0}, {60, 100, 0}};
		  // To animate the Indian flag 
		  ctrlPts[1].x +=10*sin(theta * PI/180.0);
		  ctrlPts[1].y +=5*sin(theta * PI/180.0); 
		  ctrlPts[2].x -= 10*sin((theta+30) * PI/180.0);
		  ctrlPts[2].y -= 10*sin((theta+30) * PI/180.0); 
		  ctrlPts[3].x-= 4*sin((theta) * PI/180.0); 
		  ctrlPts[3].y += sin((theta-30) * PI/180.0); 
		  theta+=0.1;
		  glClear(GL_COLOR_BUFFER_BIT); 
		  glColor3f(1.0, 1.0, 1.0);
		  glPointSize(5); 
		  glPushMatrix();
		  glLineWidth(5); 
		  
		  glColor3f(255/255, 153/255.0, 51/255.0); //Orange color of Indian flag 
		  for(int i=0;i<8;i++)
		   {
		      glTranslatef(0, -0.8, 0);
		      bezier(ctrlPts, nCtrlPts, nBezCurvePts);
		   }
		   
		   glColor3f(1, 1, 1); //white color of Indian flag  
		   for(int i=0;i<8;i++)
			 {
			    glTranslatef(0, -0.8, 0);
			    bezier(ctrlPts, nCtrlPts, nBezCurvePts);
			 }
			
			 glColor3f(19/255.0, 136/255.0, 8/255.0); //green color of Indian flag 
			 for(int i=0;i<8;i++)
			  { 
			     glTranslatef(0, -0.8, 0);
			     bezier(ctrlPts, nCtrlPts, nBezCurvePts);
			  } 
			  glPopMatrix();
			  glColor3f(0.7, 0.5,0.3);
			  glLineWidth(5);
			  glBegin(GL_LINES); // draws pole
			     glVertex2f(20,100); 
			     glVertex2f(20,40); 
			  glEnd(); 
			  glFlush();
			  glutPostRedisplay(); // calls mydisplay function multiple times
			  glutSwapBuffers(); // swaps the colors of viewport and flag
	}
	void init()
	  { 
	      glViewport(0, 0, 600, 600);
		  glMatrixMode(GL_PROJECTION);
		  glLoadIdentity(); 
		  gluOrtho2D(0, 130,0, 130); 
		  glClear(GL_COLOR_BUFFER_BIT); 
      }
	  int main(int argc, char **argv)
	   { 
			  glutInit(&argc, argv); 
			  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
			  glutInitWindowPosition(50, 50); 
			  glutInitWindowSize(600, 600); 
			  glutCreateWindow("Bezier Curve"); 
			  glutDisplayFunc(mydisplay);
			  init(); 
			  glutMainLoop();
	   }

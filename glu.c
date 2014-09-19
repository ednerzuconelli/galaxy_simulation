/* programa teste-make.c */
/* Desenha um quadrado preto em uma janela com fundo branco 
apt-get install freeglut3-dev
gcc -o glu glu.c -lglut -lGLU -lGL -lm
*/

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

void display(void);
void CriaPonto(float x, float y, float m);
int t=99;
int v=1;

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (800, 600); 
	glutInitWindowPosition (100, 100); 
	glutCreateWindow (argv[0]);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glShadeModel (GL_FLAT);
	glOrtho (0, 1, 0, 1, -1 ,1);
	glutDisplayFunc(display);	
	glutMainLoop();
	return 0;
}


void display(void){
	int i;
		
	glClear(GL_COLOR_BUFFER_BIT);
	
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_POLYGON);
		glVertex2f(0.0,0.0);
		glVertex2f(1.0,0.0);
		glVertex2f(1.0,1.0);
		glVertex2f(0.0,1.0);
	glEnd();
	glPointSize(30.0f);
	glColor3f (0.0f, 1.0f, 0.0f);
	glEnable(GL_POINT_SMOOTH);  
	glBegin(GL_POINTS);
		CriaPonto((i/10), ((t-i)/10), (i*2));
	glEnd();	
	glFlush();
}
void CriaPonto(float x, float y, float m){
	int i;	
	//for (i=v; i<t;i+2){
		glVertex3f((i/10),((t-i)/10),0.5f);
	//}
	
}
	

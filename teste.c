#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/glut.h>
//#include <cstdlib>

typedef struct{
	float x;
	float y;
} point;

point points[50];

float i = 1.0;
float b = 1.0;


//GLuint drawMode = GL_POINTS;


void init()
{
	//defina a cor de fundo da janela	
	glClearColor(0.0, 0.0, 0.0, 0.0);

}


void display()
{
	//limpa a janela de visualiçao
	glClear(GL_COLOR_BUFFER_BIT);

	//especifica a cor do objeto
	glColor3f(1.0, 0.0, 0.0);

	//tamnho do ponto
	glPointSize(i);

	//forma do ponto(arredondado)
	glEnable(GL_POINT_SMOOTH);

	glBegin(GL_POINTS);
		int count;
		int n = sizeof(points)/sizeof(point);
		//printf("n=%d",n);
		for (count=0; count<=n; count++)
		{
			//srand(time(NULL));
			//int p1 = rand() % 650 + 1;
			//int p2 = rand() % 650 + 1;
			//glVertex2f(p1, p2);
			points[count].x = rand() % 650 + 1;
			points[count].y = rand() % 650 + 1;
			glVertex2f(points[count].x,points[count].y);
		}
	glEnd();


	glFlush();
}

//funçao chamda quando o tamanho da janela for alterado
void reshape(int w, int h)
{
	//especifica as dimensões da Viewport	
	glViewport(0,0,w,h);
	 //inicializa sistema de cordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//estabelece a janela deselacao(left, right, bottom, top)
	gluOrtho2D(0.0,w,0.0,h);
}


void keyboard (unsigned char key, int x, int y) 
{

	switch(key)
	{
	case 'P'://GLUT_KEY_UP:
		i++;
	break;
	case 'p'://GLUT_KEY_DOWN:
		i--;
	break;

	default:
		i = 1.0;

	}

	glutPostRedisplay();
    
}


int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Galaxy Simulation");
	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);//the call for the keyboard function
	glutMainLoop();
	return 0;

}

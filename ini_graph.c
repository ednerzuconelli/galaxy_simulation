#include<stdio.h>
#include<GL/glut.h>
#include<stdlib.h>

void opengraph(void){

int driver, mode;

detectgraph(&driver, &mode);
initgraph(&driver, &mode, "");

}

void main(void){

int opcao, driver, mode;
char *GDrivers[] = {"DETECT",
		    "CGA",
		    "MCGA",
		    "EGA",
		    "EGA64",
		    "EGAMONO",
		    "IBM8514",
		    "HERCMONO",
		    "ATT400",
		    "VGA",
		    "PC3270"};

opengraph();

detectgraph(&driver, &mode);
printf("%s", GDrivers[driver]);

setcolor(1);
circle(100, 100, 50);

setcolor(2);
circle(200, 100, 50);

setcolor(3);
circle(300, 100, 50);

setcolor(4);
circle(400, 100, 50);

getche();

closegraph();

}

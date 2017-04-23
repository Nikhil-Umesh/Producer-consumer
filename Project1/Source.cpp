#include<stdio.h>
#include<stdlib.h>
#include<glut.h>
typedef float point[2];
void myinit()
{
	glClearColor(1, 1, 1, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10, 10, -10, 10, -10, 10);
	glMatrixMode(GL_MODELVIEW);
}
void triangle(GLfloat *a, GLfloat *b, GLfloat *c)
{
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
}
void draw_triangle(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d)
{
	glColor3f(0, 1, 0);
	triangle(a, b, c);
	glColor3f(0, 1, 1);
	triangle(a, b, d);
	glColor3f(0, 0, 1);
	triangle(a, d, c);
	glColor3f(1, 1, 0);
	triangle(b, c, d);
}
void draw_tetrahedron(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d, int k)
{
	int j;
	GLfloat ab[3], bc[3], ac[3], ad[3], bd[3], cd[3];
	if (k>0)
	{
		for (j = 0;j<3;j++)
			ab[j] = (a[j] + b[j]) / 2;
		for (j = 0;j<3;j++)
			bc[j] = (b[j] + c[j]) / 2;
		for (j = 0;j<3;j++)
			ac[j] = (a[j] + c[j]) / 2;
		for (j = 0;j<3;j++)
			ad[j] = (a[j] + d[j]) / 2;
		for (j = 0;j<3;j++)
			bd[j] = (b[j] + d[j]) / 2;
		for (j = 0;j<3;j++)
			cd[j] = (c[j] + d[j]) / 2;
		draw_tetrahedron(a, ab, ac, ad, k - 1);
		draw_tetrahedron(ab, b, bc, bd, k - 1);
		draw_tetrahedron(ac, bc, c, cd, k - 1);
		draw_tetrahedron(ad, bd, cd, d, k - 1);
	}
	else(draw_triangle(a, b, c, d));
}
void display()
{
	GLfloat a[3] = { 0.0,4.0,0.0 }, b[3] = { 0.0,0.0,-7.0 }, c[3] = { 4.0,7.0,6.0 }, d[3] = { -6.0,6.0,-4.0 };
	//GLfloat a[3]={0.0,0.0,1.0},b[3]={0.0,0.942809,-0.333333},c[3]={-0.816497,-0.471405,-0.333333},d[3]={0.816497,-0.471405,-0.333333};
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	draw_tetrahedron(a, b, c, d, 2);
	glEnd();
	glFlush();
}
void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 0);
	glutCreateWindow("3D shape of Tetrahedron");
	glutDisplayFunc(display);
	myinit();
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}
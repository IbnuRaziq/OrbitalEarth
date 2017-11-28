#include <gl/glut.h>
#include <math.h>

int j = 0;

typedef struct {
	float x;
	float y;
} point2D_t;

typedef struct {
	float r;
	float g;
	float b;
} color_t;

point2D_t titikDalam[100];
point2D_t titikLuar[100];

void setColor(color_t color) {
	glColor3f(color.r, color.g, color.b);
}

void drawPolygon(point2D_t pnt[], int n)
{
	int i;
	glBegin(GL_LINE_LOOP);
	for (i = 0; i<n; i++) {
		glVertex2f(pnt[i].x, pnt[i].y);
	}
	glEnd();
}

void drawPolygonWarna(point2D_t pnt[], int n)
{
	int i;
	glBegin(GL_LINE_LOOP);
	for (i = 0; i<n; i++) {
		glVertex2f(pnt[i].x, pnt[i].y);
	}
	glEnd();
}

void fillPolygon(point2D_t pnt[], int n, color_t color)
{
	int i;
	setColor(color);
	glBegin(GL_POLYGON);
	for (i = 0; i<n; i++) {
		glVertex2f(pnt[i].x, pnt[i].y);
	}
	glEnd();
}

point2D_t lk[100];
void drawBumi(float r, int n, float tick, point2D_t sudut) {
	point2D_t p[360];
	float a = 6.28 / n;
	for (int i = 0; i<n; i++) {
		p[i].x = r*(float)cos((float)(tick + i)*a) + sudut.x;
		p[i].y = r*(float)sin((float)(tick + i)*a) + sudut.y;
	}
	fillPolygon(p, n, { 0,0,0.5 });
}

void drawBulan(float r, int n, float tick, point2D_t sudut) {
	point2D_t p[360];
	float a = 6.28 / n;
	for (int i = 0; i<n; i++) {
		p[i].x = r*(float)cos((float)(tick + i)*a) + sudut.x;
		p[i].y = r*(float)sin((float)(tick + i)*a) + sudut.y;
	}
	fillPolygon(p, n, { 1,1,0 });
}

void drawOrbitBulan(point2D_t p[], point2D_t p0, float r, int n, int sudutKecil, float tick) {
	point2D_t sudut;
	float a = 6.28 / n;
	for (int i = 0; i<n; i++) {
		p[i].x = p0.x + r*cos((tick + i)*a);
		p[i].y = p0.y + r*sin((tick + i)*a);

		if (i % sudutKecil == 0) {
			sudut.x = p[i].x;
			sudut.y = p[i].y;
		}
	}
	drawBulan(10, 360, tick, sudut);
	drawPolygon(p, n);
}

void drawCircle2(point2D_t p[], point2D_t p0, float r, int n, int sudutKecil, float tick, float tickBulan) {
	point2D_t sudut;
	float a = 6.28 / n;
	for (int i = 0; i<n; i++) {
		p[i].x = p0.x + r*cos((tick + i)*a);
		p[i].y = p0.y + r*sin((tick + i)*a);

		if (i % sudutKecil == 0) {
			sudut.x = p[i].x;
			sudut.y = p[i].y;
		}
	}
	drawBumi(20, 60, tick, sudut);
	point2D_t shape[360];
	point2D_t titik = { 0.0,0.0 };
	drawOrbitBulan(shape, sudut, 40, 360, 45, tickBulan);
	drawPolygon(p, n);
}

void drawPorosBintang(point2D_t p[], point2D_t p0, float r, int n, int sudutKecil, float tick, color_t col) {
	point2D_t sudut;
	float a = 6.28 / n;
	int sudutTitik = sudutKecil;
	j = 0;
	for (int i = 0; i<n; i++) {
		setColor(col);
		p[i].x = p0.x + r*cos((tick + i)*a);
		p[i].y = p0.y + r*sin((tick + i)*a);

		if (i == sudutTitik) {
			titikDalam[j].x = p[i].x;
			titikDalam[j].y = p[i].y;
			j++;
			sudutTitik += 72;
		}
	}
	drawPolygon(p, n);
}

void drawLingkaranLuarBintang(point2D_t p[], point2D_t p0, float r, int n, int sudutKecil, float tick, color_t col) {
	point2D_t sudut;
	float a = 6.28 / n;
	int sudutTitik = sudutKecil;
	j = 0;
	for (int i = 0; i<n; i++) {
		setColor(col);
		p[i].x = p0.x + r*cos((tick + i)*a);
		p[i].y = p0.y + r*sin((tick + i)*a);

		if (i == sudutTitik) {
			titikLuar[j].x = p[i].x;
			titikLuar[j].y = p[i].y;
			j++;
			sudutTitik += 72;
		}
	}
	drawPolygon(p, n);
}

void drawBintang(color_t warna) {
	point2D_t bintang[10];
	int loop;
	int h, i;
	i = 0;
	h = 1;
	for (loop = 0; loop < 10; loop++) {
		if (loop % 2 == 0) {
			bintang[loop] = { titikDalam[i].x, titikDalam[i].y };
			i++;
		}
		else
		{
			bintang[loop] = { titikLuar[h].x, titikLuar[h].y };
			h++;
		}
	}
	bintang[9] = { titikLuar[0].x, titikLuar[0].y };
	fillPolygon(bintang, 10, warna);
}


void userdraw(void) {
	static float tick = 0.0, tickBulan = 0.0, tickBintang = 0.0;
	color_t yellow = { 1.0, 1.0, 0.0 };
	color_t hitam = { 0.0, 0.0, 0.0 };
	color_t green = { 0.5, 1.0, 0.0 };
	point2D_t shape[360];
	point2D_t titik = { 0.0,0.0 };
	drawCircle2(shape, titik, 150.0, 360, 45, tick, tickBulan);
	drawPorosBintang(shape, titik, 40, 360, 54, tickBintang, green);
	drawLingkaranLuarBintang(shape, titik, 75, 360, 18, tickBintang, yellow);

	//Bintang
	/*point2D_t bintang[10] = { { 18,22 },{ 75,22 },
	{ 26,-16 },{ 50,-75 },{ -0,-40 },{ -50,-75 },
	{ -26,-16 },{ -75,22 },{ -18,22 },{ 0, 75 } };
	fillPolygon(bintang, 10, kuning);*/

	drawBintang(green);

	tick -= 0.04;
	tickBulan += 0.07;
	tickBintang += 0.06;
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	userdraw();
	glutSwapBuffers();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Orbital-Ibnu/2103151041");
	glClearColor(0.0, 0.0, 0.0, 0.0);
	gluOrtho2D(-320, 320, -240, 240);
	glutIdleFunc(display);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
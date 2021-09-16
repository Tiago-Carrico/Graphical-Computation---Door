#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/Glut.h>
#include <windows.h>

#include "RgbImage.h"
#include "RgbImage.cpp"

//Textura de madeira: <a href="https://www.vecteezy.com/free-vector/line-texture">Line Texture Vectors by Vecteezy</a>



//--------------------------------- Definir cores
#define BLUE     0.0, 0.0, 1.0, 1.0
#define RED		 1.0, 0.0, 0.0, 1.0
#define YELLOW	 1.0, 1.0, 0.0, 1.0
#define GREEN    0.0, 1.0, 0.0, 1.0
#define ORANGE   1.0, 0.5, 0.1, 1.0
#define CYAN     0.0, 1.0, 1.0, 1.0
#define WHITE    1.0, 1.0, 1.0, 1.0
#define BLACK    0.0, 0.0, 0.0, 1.0
#define GRAY     0.3, 0.3, 0.3, 1.0
#define PI		 3.14159

//================================================================================
//===========================================================Variaveis e constantes
GLint     msec = 10;
char      texto[30];						//.. texto a ser escrito no ecran



//-------------------- Porta
//
GLfloat ang = 0.0;	//angulo para abrir a porta
GLfloat abertura = 0.0;
GLfloat doorKnobOp = 0.0;

//------------------------------------------------------------ Sistema Coordenadas + objectos
GLint		wScreen = 1000, hScreen = 900;		//.. janela
GLfloat		yC = 100.0;	//.. Mundo

GLfloat	 viewHeight = 1;
GLfloat	 posHeight = 1;

//------------------------------------------------------------ Observador 
GLfloat  rVisao = 8, aVisao = PI, incVisao = 0.05;
GLfloat  obsP[] = { rVisao * cos(aVisao), posHeight, rVisao * sin(aVisao) };
GLfloat  obsT[] = { obsP[0] - rVisao * cos(aVisao), viewHeight, obsP[2] - rVisao * sin(aVisao) };

float anguloZ = 95;
int   tipoProjeccao = 0;

GLint dim = 20;
GLint med_dim = dim / 2;

GLfloat Lightred = 0.5;
GLfloat Lightgreen = 0.5;
GLfloat Lightblue = 0.5;
GLfloat WhiteRed = 0.5;
GLfloat WhiteGreen = 0.5;
GLfloat WhiteBlue = 0.5;
GLfloat WhiteCustom[] = { WhiteRed, WhiteGreen, WhiteBlue , 1.0};
GLfloat WhiteCustom2[] = { WhiteRed + 0.2, WhiteGreen + 0.2, WhiteBlue + 0.2, 1.0 };
GLfloat corBranco[] = { 1.0, 1.0, 1.0, 0.0 };
GLfloat corCinza[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat mat_specular[] = { 0.296648f, 0.296648f, 0.296648f, 1.0 };

//--------------------------------------------- Escada
static GLuint    poligono[] = { 0, 0, 0, 0 };
static GLfloat vertices[] = {
-0.5,  0.0,  0.5,
 0.5,  0.0,  0.5,
 0.5,  0.0, -0.5,
-0.5,  0.0, -0.5 };
static GLfloat normais[] = {
0.0, 1.0, 0.0,
0.0, 1.0, 0.0,
0.0, 1.0, 0.0,
0.0, 1.0, 0.0 };
static GLfloat cores[] = {
0.0, 1.0, 0.0,
0.0, 1.0, 0.0,
0.0, 1.0, 1.0,
1.0, 1.0, 0.0 };

//Definição funçoes
float boundaries(GLfloat number, float change);


void setupLuzes() {
	/*
	GLfloat Pos1[] = { 8.0f, 48.0f,  -3.0f, 1.0f };   // Foco 1
	GLfloat Pos2[] = { 8.0f, 48.0f,  3.0f, 1.0f };   // Foco 2 
	*/
	GLfloat Pos1[] = { (16.5/2), 55.0f,  -12.0f, 1.0f };   // Foco 1
	GLfloat Pos2[] = { (16.5/2), 55.0f,  2.0f, 1.0f };   // Foco 2 

	GLfloat		aberturaFoco = 20.0;		//.. angulo inicial do foco
	GLfloat		aberturaFoco2 = 20.0;

	GLfloat corBranco[] = {1.0, 1.0, 1.0, 1};
	GLfloat corRosa[] = { 0.5, 0.0, 0.5, 1 };

	GLfloat Foco_direccao[] = { 0.0, -15.0, 3.0, 1 };	//funciona em base da posição inicial, ou seja, se estiver em 10,20,20 e aqui estiver 10,0,0 vai apontar para 20,20,20
	//GLfloat Foco_direccao2[] = { 0.0, -10.0, 6.0, 1 };
	GLfloat Foco1_cor[] = { Lightred, Lightgreen, Lightblue, 1 };	//……… Cor da luz 1
	GLfloat Foco2_cor[] = { 0.5, 0.5,  0.5, 1.0 };	//……… Cor da luz 2
	GLfloat Foco2_cor2[] = { 0.7, 0.7, 0.7, 1.0 };
	GLfloat Foco1_cor2[] = { boundaries(Foco1_cor[0], -0.2), boundaries(Foco1_cor[1], -0.2), boundaries(Foco1_cor[2], -0.2), 1.0};
	GLfloat Cor_ambiente[] = { 0.7, 0.7, 0.7, 1 };	//cor ambiente
	GLfloat Foco_ak1 = 1.0;
	GLfloat Foco_al1 = 0.1f;
	GLfloat Foco_aq1 = 0.001f;
	GLfloat Foco_ak2 = 1.0;
	GLfloat Foco_al2 = 0.1f;
	GLfloat Foco_aq2 = 0.001f;
	GLfloat Foco_Expon1 = 2.0;
	GLfloat Foco_Expon2 = 1.0;		// Foco, SPOT_Exponent

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Cor_ambiente);

	//……………………………………………………………………………………………………………………………Foco Esquerda
	glLightfv(GL_LIGHT0, GL_POSITION, Pos1);					//posição da fonte de luz
	glLightfv(GL_LIGHT1, GL_AMBIENT, Foco1_cor);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Foco1_cor2);				//cor da luz
	glLightfv(GL_LIGHT1, GL_SPECULAR, corBranco);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, Foco_ak1);		//atenuação da luz
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, Foco_al1);		//atenuação da luz
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, Foco_aq1);		//atenuação da luz
	//glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, aberturaFoco2);			//angulo da fonte de luz (do feixe)
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Foco_direccao2);		//direção para que a luz aponta
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, Foco_Expon1);			//força do foco da luz

	//……………………………………………………………………………………………………………………………Foco Direita
	glLightfv(GL_LIGHT1, GL_POSITION, Pos2);
	glLightfv(GL_LIGHT1, GL_AMBIENT, WhiteCustom);		
	glLightfv(GL_LIGHT1, GL_DIFFUSE, WhiteCustom2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, corBranco);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, Foco_ak2);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, Foco_al2);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, Foco_aq2);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, aberturaFoco);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, Foco_direccao);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, Foco_Expon2);
}


//================================================================================
//=========================================================================== INIT
void initialize(void)
{
	glClearColor(BLACK);		//………………………………………………………………………………Apagar
	glEnable(GL_DEPTH_TEST);	//………………………………………………………………………………Profundidade
	glShadeModel(GL_SMOOTH);	//………………………………………………………………………………Interpolacao de cores	


	//Ligar o blend, para que transparência seja possivel
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	//Setup do Fog/Nevoeiro
	glEnable(GL_FOG);
	glFogi(GL_FOG_MODE, GL_EXP2);
	glFogfv(GL_FOG_COLOR, corCinza);
	glFogf(GL_FOG_DENSITY, 0.03);
	glHint(GL_FOG_HINT, GL_NICEST);

	//Setup da textura da madeira
	RgbImage imag;
	//glEnable(GL_TEXTURE_2D);		//foi movida para a função drawDoor para não afetar as cores daquilo que não fosse texturado
	GLuint texture[5];
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	imag.LoadBmpFile("wood.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//imag.LoadBmpFile("metal.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());




	glEnable(GL_CULL_FACE);		//………………………………………………………………………………Faces visiveis
	glCullFace(GL_BACK);		//………………………………………………………………………………Mostrar so as da frente

	glVertexPointer(3, GL_FLOAT, 0, vertices); //………………………………………Vertex arrays
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normais);
	glEnableClientState(GL_NORMAL_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, cores);
	glEnableClientState(GL_COLOR_ARRAY);

	
	//setup das luzes
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);		
	setupLuzes();

	


	srand(1);
}

float aleatorio(GLint minimo, GLint maximo) {
	GLfloat y;
	y = rand() % 1000;
	return (minimo + 0.001 * y * (maximo - minimo));
}

void desenhaTexto(char* string, GLfloat x, GLfloat y)
{
	glPushMatrix();
	glTranslatef(x, 0, y);
	glRasterPos2f(0, 0);
	while (*string)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *string++);
	glPopMatrix();
}

//desenha paralelipipedo com uma cor
void drawParC(GLfloat xSize, GLfloat height, GLfloat zSize, GLfloat xStart, GLfloat yStart, GLfloat zStart, GLfloat r, GLfloat g, GLfloat b) {

	float cor[] = { r, g, b, 1};
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, cor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cor);
	glBegin(GL_QUADS);
	// top
	//glColor3f(r, g, b);
	/*
	glMaterialfv(GL_FRONT, GL_AMBIENT, cor);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, cor);
	glMaterialfv(GL_FRONT, GL_SPECULAR, cor);
	*/
	glNormal3f(1.0f, 1.0f, 1.0f);
	glVertex3f(xStart, yStart + height, zStart + zSize);
	glVertex3f(xStart + xSize, yStart + height, zStart + zSize);
	glVertex3f(xStart + xSize, yStart + height, zStart);
	glVertex3f(xStart, yStart + height, zStart);
	glEnd();

	glBegin(GL_QUADS);
	// front
	//glColor3f(r, g, b);
	/*
	glMaterialfv(GL_FRONT, GL_AMBIENT, cor);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, cor);
	glMaterialfv(GL_FRONT, GL_SPECULAR, cor);
	*/
	glNormal3f(0.0f, 0.0f, 0.0f);
	glVertex3f(xStart + xSize, yStart, zStart + zSize);
	glVertex3f(xStart + xSize, yStart + height, zStart + zSize);
	glVertex3f(xStart, yStart + height, zStart + zSize);
	glVertex3f(xStart, yStart, zStart + zSize);
	glEnd();

	glBegin(GL_QUADS);
	// right
	//glColor3f(r, g, b);
	/*
	glMaterialfv(GL_FRONT, GL_AMBIENT, cor);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, cor);
	glMaterialfv(GL_FRONT, GL_SPECULAR, cor);
	*/
	glNormal3f(0.0f, 0.0f, 0.0f);
	glVertex3f(xStart + xSize, yStart + height, zStart);
	glVertex3f(xStart + xSize, yStart + height, zStart + zSize);
	glVertex3f(xStart + xSize, yStart, zStart + zSize);
	glVertex3f(xStart + xSize, yStart, zStart);
	glEnd();

	glBegin(GL_QUADS);
	// left
	//glColor3f(r, g, b);
	/*
	glMaterialfv(GL_FRONT, GL_AMBIENT, cor);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, cor);
	glMaterialfv(GL_FRONT, GL_SPECULAR, cor);
	*/
	glNormal3f(0.0f, 0.0f, 0.0f);
	glVertex3f(xStart, yStart, zStart + zSize);
	glVertex3f(xStart, yStart + height, zStart + zSize);
	glVertex3f(xStart, yStart + height, zStart);
	glVertex3f(xStart, yStart, zStart);
	glEnd();

	glBegin(GL_QUADS);
	// bottom
	//glColor3f(r, g, b);
	/*
	glMaterialfv(GL_FRONT, GL_AMBIENT, cor);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, cor);
	glMaterialfv(GL_FRONT, GL_SPECULAR, cor);
	*/
	glNormal3f(0.0f, 0.0f, 0.0f);
	glVertex3f(xStart + xSize, yStart, zStart + zSize);
	glVertex3f(xStart, yStart, zStart + zSize);
	glVertex3f(xStart, yStart, zStart);
	glVertex3f(xStart + xSize, yStart, zStart);
	glEnd();

	glBegin(GL_QUADS);
	// back
	//glColor3f(r, g, b);
	/*
	glMaterialfv(GL_FRONT, GL_AMBIENT, cor);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, cor);
	glMaterialfv(GL_FRONT, GL_SPECULAR, cor);
	*/
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(xStart + xSize, yStart + height, zStart);
	glVertex3f(xStart + xSize, yStart, zStart);
	glVertex3f(xStart, yStart, zStart);
	glVertex3f(xStart, yStart + height, zStart);
	glEnd();
}

void drawParCMesh(GLfloat xSize, GLfloat height, GLfloat zSize, GLfloat xStart, GLfloat yStart, GLfloat zStart, GLfloat r, GLfloat g, GLfloat b, GLfloat alpha) {

	float cor[] = { r, g, b, alpha };
	float corDiffuse[] = {boundaries(cor[0], -0.2), boundaries(cor[1], -0.2), boundaries(cor[2], -0.2), alpha};
	//float pink[] = { 0.5, 0, 0.5, 1 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, cor);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, corDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, corBranco);
	glMaterialf(GL_FRONT, GL_SHININESS, 2.0);
	glBegin(GL_QUADS);
	// top				//Y stays constant in max

	glNormal3f(1.0f, 1.0f, 1.0f);
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			glVertex3f((xStart)+(j * (xSize / dim)), yStart + height, (zStart)+(i * (zSize / dim)) + (zSize / dim));
			glVertex3f((xStart)+(j * (xSize / dim)) + (xSize / dim), yStart + height, (zStart)+(i * (zSize / dim)) + (zSize / dim));
			glVertex3f((xStart)+(j * (xSize / dim)) + (xSize / dim), yStart + height, (zStart)+(i * (zSize / dim)));
			glVertex3f((xStart)+(j * (xSize / dim)), yStart + height, (zStart)+(i * (zSize / dim)));
		}
	}
	glEnd();

	glBegin(GL_QUADS);
	// front			//Z stays constant in max

	glNormal3f(0.0f, 0.0f, 1.0f);
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			glVertex3d((xStart)+(j * (xSize / dim )) + (xSize / dim), (yStart)+(i * (height / dim)), zStart + zSize);
			glVertex3d((xStart)+(j * (xSize / dim)) + (xSize / dim), (yStart)+(i * (height / dim)) + (height / dim), zStart + zSize);
			glVertex3d((xStart)+(j * (xSize / dim)), (yStart)+(i * (height / dim)) + (height / dim), zStart + zSize);
			glVertex3d((xStart)+(j * (xSize / dim)), (yStart)+(i * (height / dim)), zStart + zSize);

		}
	}
	glEnd();

	glBegin(GL_QUADS);
	// right			//X stays constant in max

	glNormal3f(1.0f, 0.0f, 0.0f);
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			glVertex3d(xStart + xSize, (yStart)+(i * (height / dim)) + (height / dim), (zStart)+(j * (zSize / dim)));
			glVertex3d(xStart + xSize, (yStart)+(i * (height / dim)) + (height / dim), (zStart)+(j * (zSize / dim)) + (zSize / dim));
			glVertex3d(xStart + xSize, (yStart)+(i * (height / dim)), (zStart)+(j * (zSize / dim)) + (zSize / dim));
			glVertex3d(xStart + xSize, (yStart)+(i * (height / dim)), (zStart)+(j * (zSize / dim)));

		}
	}
	glEnd();

	glBegin(GL_QUADS);
	// left				//X stays constant in minimum

	glNormal3f(-1.0f, 0.0f, 0.0f);
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			glVertex3f(xStart, (yStart)+(i * (height / dim)), (zStart)+(j * (zSize / dim)) + (zSize / dim));
			glVertex3f(xStart, (yStart)+(i * (height / dim)) + (height / dim), (zStart)+(j * (zSize / dim)) + (zSize / dim));
			glVertex3f(xStart, (yStart)+(i * (height / dim)) + (height / dim), (zStart)+(j * (zSize / dim)));
			glVertex3f(xStart, (yStart)+(i * (height / dim)), (zStart)+(j * (zSize / dim)));
		}
	}
	glEnd();

	glBegin(GL_QUADS);
	// bottom			//Y stays cosntant in minimum

	glNormal3f(0.0f, -1.0f, 0.0f);
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			glVertex3f((xStart)+(i * (xSize / dim)) + (xSize / dim), yStart, (zStart)+(j * (zSize / dim)) + (zSize / dim));
			glVertex3f((xStart)+(i * (xSize / dim)), yStart, (zStart)+(j * (zSize / dim)) + (zSize / dim));
			glVertex3f((xStart)+(i * (xSize / dim)), yStart, (zStart)+(j * (zSize / dim)));
			glVertex3f((xStart)+(i * (xSize / dim)) + (xSize / dim), yStart, (zStart)+(j * (zSize / dim)));
		}
	}
	glEnd();

	glBegin(GL_QUADS);
	// back				//Z stays constant in minimum

	glNormal3f(0.0f, 0.0f, -1.0f);
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			glVertex3f((xStart)+(i * (xSize / dim)) + (xSize / dim), (yStart)+(j * (height / dim)) + (height / dim), zStart);
			glVertex3f((xStart)+(i * (xSize / dim)) + (xSize / dim), (yStart)+(j * (height / dim)), zStart);
			glVertex3f((xStart)+(i * (xSize / dim)), (yStart)+(j * (height / dim)), zStart);
			glVertex3f((xStart)+(i * (xSize / dim)), (yStart)+(j * (height / dim)) + (height / dim), zStart);
		}
	}
	glEnd();
}

void drawParCMesh2(GLfloat xSize, GLfloat height, GLfloat zSize, GLfloat xStart, GLfloat yStart, GLfloat zStart, GLfloat ambient, GLfloat diffuse, GLfloat specular, GLfloat shine, GLfloat alpha) {

	//float cor[] = { r, g, b, alpha };
	//float corDiffuse[] = { boundaries(cor[0], -0.2), boundaries(cor[1], -0.2), boundaries(cor[2], -0.2), alpha };
	//float pink[] = { 0.5, 0, 0.5, 1 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, &ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, &diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, &specular);
	glMaterialf(GL_FRONT, GL_SHININESS, shine);
	glBegin(GL_QUADS);
	// top				//Y stays constant in max

	glNormal3f(1.0f, 1.0f, 1.0f);
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			glVertex3f((xStart)+(j * (xSize / dim)), yStart + height, (zStart)+(i * (zSize / dim)) + (zSize / dim));
			glVertex3f((xStart)+(j * (xSize / dim)) + (xSize / dim), yStart + height, (zStart)+(i * (zSize / dim)) + (zSize / dim));
			glVertex3f((xStart)+(j * (xSize / dim)) + (xSize / dim), yStart + height, (zStart)+(i * (zSize / dim)));
			glVertex3f((xStart)+(j * (xSize / dim)), yStart + height, (zStart)+(i * (zSize / dim)));
		}
	}
	glEnd();

	glBegin(GL_QUADS);
	// front			//Z stays constant in max

	glNormal3f(0.0f, 0.0f, 1.0f);
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			glVertex3d((xStart)+(j * (xSize / dim)) + (xSize / dim), (yStart)+(i * (height / dim)), zStart + zSize);
			glVertex3d((xStart)+(j * (xSize / dim)) + (xSize / dim), (yStart)+(i * (height / dim)) + (height / dim), zStart + zSize);
			glVertex3d((xStart)+(j * (xSize / dim)), (yStart)+(i * (height / dim)) + (height / dim), zStart + zSize);
			glVertex3d((xStart)+(j * (xSize / dim)), (yStart)+(i * (height / dim)), zStart + zSize);

		}
	}
	glEnd();

	glBegin(GL_QUADS);
	// right			//X stays constant in max

	glNormal3f(1.0f, 0.0f, 0.0f);
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			glVertex3d(xStart + xSize, (yStart)+(i * (height / dim)) + (height / dim), (zStart)+(j * (zSize / dim)));
			glVertex3d(xStart + xSize, (yStart)+(i * (height / dim)) + (height / dim), (zStart)+(j * (zSize / dim)) + (zSize / dim));
			glVertex3d(xStart + xSize, (yStart)+(i * (height / dim)), (zStart)+(j * (zSize / dim)) + (zSize / dim));
			glVertex3d(xStart + xSize, (yStart)+(i * (height / dim)), (zStart)+(j * (zSize / dim)));

		}
	}
	glEnd();

	glBegin(GL_QUADS);
	// left				//X stays constant in minimum

	glNormal3f(-1.0f, 0.0f, 0.0f);
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			glVertex3f(xStart, (yStart)+(i * (height / dim)), (zStart)+(j * (zSize / dim)) + (zSize / dim));
			glVertex3f(xStart, (yStart)+(i * (height / dim)) + (height / dim), (zStart)+(j * (zSize / dim)) + (zSize / dim));
			glVertex3f(xStart, (yStart)+(i * (height / dim)) + (height / dim), (zStart)+(j * (zSize / dim)));
			glVertex3f(xStart, (yStart)+(i * (height / dim)), (zStart)+(j * (zSize / dim)));
		}
	}
	glEnd();

	glBegin(GL_QUADS);
	// bottom			//Y stays cosntant in minimum

	glNormal3f(0.0f, -1.0f, 0.0f);
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			glVertex3f((xStart)+(i * (xSize / dim)) + (xSize / dim), yStart, (zStart)+(j * (zSize / dim)) + (zSize / dim));
			glVertex3f((xStart)+(i * (xSize / dim)), yStart, (zStart)+(j * (zSize / dim)) + (zSize / dim));
			glVertex3f((xStart)+(i * (xSize / dim)), yStart, (zStart)+(j * (zSize / dim)));
			glVertex3f((xStart)+(i * (xSize / dim)) + (xSize / dim), yStart, (zStart)+(j * (zSize / dim)));
		}
	}
	glEnd();

	glBegin(GL_QUADS);
	// back				//Z stays constant in minimum

	glNormal3f(0.0f, 0.0f, -1.0f);
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			glVertex3f((xStart)+(i * (xSize / dim)) + (xSize / dim), (yStart)+(j * (height / dim)) + (height / dim), zStart);
			glVertex3f((xStart)+(i * (xSize / dim)) + (xSize / dim), (yStart)+(j * (height / dim)), zStart);
			glVertex3f((xStart)+(i * (xSize / dim)), (yStart)+(j * (height / dim)), zStart);
			glVertex3f((xStart)+(i * (xSize / dim)), (yStart)+(j * (height / dim)) + (height / dim), zStart);
		}
	}
	glEnd();
}


//TODO tirar argumentos desnecessarios e mudar os valores edntro da função para serem usados argumentos
void drawParCMesh2Test(GLfloat xSize, GLfloat height, GLfloat zSize, GLfloat xStart, GLfloat yStart, GLfloat zStart, GLfloat alpha) {

	//float cor[] = { r, g, b, alpha };
	//float corDiffuse[] = { boundaries(cor[0], -0.2), boundaries(cor[1], -0.2), boundaries(cor[2], -0.2), alpha };
	//float pink[] = { 0.5, 0, 0.5, 1 };

	GLfloat mat_ambient[] = { 0.25f, 0.20725f, 0.20725f, alpha };
	GLfloat mat_diffuse[] = { 1.0f, 0.829f, 0.829f, alpha };
	//GLfloat mat_specular[] = { 0.296648f, 0.296648f, 0.296648f, alpha };
	GLfloat shine = 11.264f;

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, shine);

	glBegin(GL_QUADS);
	// top				//Y stays constant in max

	glNormal3f(0.0f, 1.0f, 0.0f);
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			glVertex3f((xStart)+(j * (xSize / dim)), yStart + height, (zStart)+(i * (zSize / dim)) + (zSize / dim));
			glVertex3f((xStart)+(j * (xSize / dim)) + (xSize / dim), yStart + height, (zStart)+(i * (zSize / dim)) + (zSize / dim));
			glVertex3f((xStart)+(j * (xSize / dim)) + (xSize / dim), yStart + height, (zStart)+(i * (zSize / dim)));
			glVertex3f((xStart)+(j * (xSize / dim)), yStart + height, (zStart)+(i * (zSize / dim)));
		}
	}
	glEnd();

	glBegin(GL_QUADS);
	// front			//Z stays constant in max

	glNormal3f(0.0f, 0.0f, 1.0f);
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			glVertex3d((xStart)+(j * (xSize / dim)) + (xSize / dim), (yStart)+(i * (height / dim)), zStart + zSize);
			glVertex3d((xStart)+(j * (xSize / dim)) + (xSize / dim), (yStart)+(i * (height / dim)) + (height / dim), zStart + zSize);
			glVertex3d((xStart)+(j * (xSize / dim)), (yStart)+(i * (height / dim)) + (height / dim), zStart + zSize);
			glVertex3d((xStart)+(j * (xSize / dim)), (yStart)+(i * (height / dim)), zStart + zSize);

		}
	}
	glEnd();

	glBegin(GL_QUADS);
	// right			//X stays constant in max

	glNormal3f(1.0f, 0.0f, 0.0f);
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			glVertex3d(xStart + xSize, (yStart)+(i * (height / dim)) + (height / dim), (zStart)+(j * (zSize / dim)));
			glVertex3d(xStart + xSize, (yStart)+(i * (height / dim)) + (height / dim), (zStart)+(j * (zSize / dim)) + (zSize / dim));
			glVertex3d(xStart + xSize, (yStart)+(i * (height / dim)), (zStart)+(j * (zSize / dim)) + (zSize / dim));
			glVertex3d(xStart + xSize, (yStart)+(i * (height / dim)), (zStart)+(j * (zSize / dim)));

		}
	}
	glEnd();

	glBegin(GL_QUADS);
	// left				//X stays constant in minimum

	glNormal3f(-1.0f, 0.0f, 0.0f);
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			glVertex3f(xStart, (yStart)+(i * (height / dim)), (zStart)+(j * (zSize / dim)) + (zSize / dim));
			glVertex3f(xStart, (yStart)+(i * (height / dim)) + (height / dim), (zStart)+(j * (zSize / dim)) + (zSize / dim));
			glVertex3f(xStart, (yStart)+(i * (height / dim)) + (height / dim), (zStart)+(j * (zSize / dim)));
			glVertex3f(xStart, (yStart)+(i * (height / dim)), (zStart)+(j * (zSize / dim)));
		}
	}
	glEnd();

	glBegin(GL_QUADS);
	// bottom			//Y stays cosntant in minimum

	glNormal3f(0.0f, -1.0f, 0.0f);
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			glVertex3f((xStart)+(i * (xSize / dim)) + (xSize / dim), yStart, (zStart)+(j * (zSize / dim)) + (zSize / dim));
			glVertex3f((xStart)+(i * (xSize / dim)), yStart, (zStart)+(j * (zSize / dim)) + (zSize / dim));
			glVertex3f((xStart)+(i * (xSize / dim)), yStart, (zStart)+(j * (zSize / dim)));
			glVertex3f((xStart)+(i * (xSize / dim)) + (xSize / dim), yStart, (zStart)+(j * (zSize / dim)));
		}
	}
	glEnd();

	glBegin(GL_QUADS);
	// back				//Z stays constant in minimum

	glNormal3f(0.0f, 0.0f, -1.0f);
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			glVertex3f((xStart)+(i * (xSize / dim)) + (xSize / dim), (yStart)+(j * (height / dim)) + (height / dim), zStart);
			glVertex3f((xStart)+(i * (xSize / dim)) + (xSize / dim), (yStart)+(j * (height / dim)), zStart);
			glVertex3f((xStart)+(i * (xSize / dim)), (yStart)+(j * (height / dim)), zStart);
			glVertex3f((xStart)+(i * (xSize / dim)), (yStart)+(j * (height / dim)) + (height / dim), zStart);
		}
	}
	glEnd();
}

//Desenha um paralelipipedo com a textura atual
void drawParT(GLfloat xSize, GLfloat height, GLfloat zSize, GLfloat xStart, GLfloat yStart, GLfloat zStart) {


	glBegin(GL_QUADS);
	// top
	glColor3f(0.5, 0.5, 0.5);
	glNormal3f(1.0f, 1.0f, 1.0f);		//for lightning after or something?

	glTexCoord2f(0.0f, 0.0f);	glVertex3f(xStart, yStart + height, zStart + zSize);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(xStart + xSize, yStart + height, zStart + zSize);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(xStart + xSize, yStart + height, zStart);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(xStart, yStart + height, zStart);

	glEnd();

	glBegin(GL_QUADS);
	// front
	glColor3f(0.5, 0.5, 0.5);
	glNormal3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(xStart + xSize, yStart, zStart + zSize);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(xStart + xSize, yStart + height, zStart + zSize);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(xStart, yStart + height, zStart + zSize);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(xStart, yStart, zStart + zSize);
	glEnd();

	glBegin(GL_QUADS);
	// right
	glColor3f(0.5, 0.5, 0.5);
	glNormal3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(xStart + xSize, yStart + height, zStart);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(xStart + xSize, yStart + height, zStart + zSize);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(xStart + xSize, yStart, zStart + zSize);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(xStart + xSize, yStart, zStart);
	glEnd();

	glBegin(GL_QUADS);
	// left
	glColor3f(0.5, 0.5, 0.5);
	glNormal3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(xStart, yStart, zStart + zSize);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(xStart, yStart + height, zStart + zSize);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(xStart, yStart + height, zStart);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(xStart, yStart, zStart);
	glEnd();

	glBegin(GL_QUADS);
	// bottom
	glColor3f(0.5, 0.5, 0.5);
	glNormal3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(xStart + xSize, yStart, zStart + zSize);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(xStart, yStart, zStart + zSize);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(xStart, yStart, zStart);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(xStart + xSize, yStart, zStart);
	glEnd();

	glBegin(GL_QUADS);
	// back
	glColor3f(0.5, 0.5, 0.5);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(xStart + xSize, yStart + height, zStart);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(xStart + xSize, yStart, zStart);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(xStart, yStart, zStart);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(xStart, yStart + height, zStart);
	glEnd();
}

//TODO fazer com que as texturas sejam afetadas pela mesh
void drawParTMesh(GLfloat xSize, GLfloat height, GLfloat zSize, GLfloat xStart, GLfloat yStart, GLfloat zStart) {

	GLfloat mat_ambient[] = { 0.25f, 0.20725f, 0.20725f, 1.0 };
	GLfloat mat_diffuse[] = { 1.0f, 0.829f, 0.829f, 1.0 };
	//GLfloat mat_specular[] = { 0.296648f, 0.296648f, 0.296648f, alpha };
	GLfloat shine = 11.264f;

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, shine);

	glBegin(GL_QUADS);
	// top				//Y stays constant in max
	glNormal3f(0.0f, 1.0f, 0.0f);
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			glTexCoord2f((0 + i) / dim, 0);		glVertex3f((xStart)+(j * (xSize / dim)), yStart + height, (zStart)+(i * (zSize / dim)) + (zSize / dim));
			glTexCoord2f((1 + i) / dim, 0);		glVertex3f((xStart)+(j * (xSize / dim)) + (xSize / dim), yStart + height, (zStart)+(i * (zSize / dim)) + (zSize / dim));
			glTexCoord2f((1 + i) / dim, 1);		glVertex3f((xStart)+(j * (xSize / dim)) + (xSize / dim), yStart + height, (zStart)+(i * (zSize / dim)));
			glTexCoord2f((0 + i) / dim, 1);		glVertex3f((xStart)+(j * (xSize / dim)), yStart + height, (zStart)+(i * (zSize / dim)));
		}
	}
	glEnd();

	glBegin(GL_QUADS);
	// front			//Z stays constant in max

	glNormal3f(0.0f, 0.0f, 1.0f);
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			glTexCoord2f((0 + i) / dim, 0);		glVertex3d((xStart)+(j * (xSize / dim)) + (xSize / dim), (yStart)+(i * (height / dim)), zStart + zSize);
			glTexCoord2f((1 + i) / dim, 0);		glVertex3d((xStart)+(j * (xSize / dim)) + (xSize / dim), (yStart)+(i * (height / dim)) + (height / dim), zStart + zSize);
			glTexCoord2f((1 + i) / dim, 1);		glVertex3d((xStart)+(j * (xSize / dim)), (yStart)+(i * (height / dim)) + (height / dim), zStart + zSize);
			glTexCoord2f((0 + i) / dim, 1);		glVertex3d((xStart)+(j * (xSize / dim)), (yStart)+(i * (height / dim)), zStart + zSize);

		}
	}
	glEnd();

	glBegin(GL_QUADS);
	// right			//X stays constant in max

	glNormal3f(1.0f, 0.0f, 0.0f);
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			glTexCoord2f((0 + i) / dim, 0);		glVertex3d(xStart + xSize, (yStart)+(i * (height / dim)) + (height / dim), (zStart)+(j * (zSize / dim)));
			glTexCoord2f((1 + i) / dim, 0);		glVertex3d(xStart + xSize, (yStart)+(i * (height / dim)) + (height / dim), (zStart)+(j * (zSize / dim)) + (zSize / dim));
			glTexCoord2f((1 + i) / dim, 1);		glVertex3d(xStart + xSize, (yStart)+(i * (height / dim)), (zStart)+(j * (zSize / dim)) + (zSize / dim));
			glTexCoord2f((0 + i) / dim, 1);		glVertex3d(xStart + xSize, (yStart)+(i * (height / dim)), (zStart)+(j * (zSize / dim)));

		}
	}
	glEnd();

	glBegin(GL_QUADS);
	// left				//X stays constant in minimum
															//TODO problem seems to be running all i iterations an then only j iterations?
	glNormal3f(-1.0f, 0.0f, 0.0f);
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			glTexCoord2f((0 + i) / dim, 0);		glVertex3f(xStart, (yStart)+(i * (height / dim)), (zStart)+(j * (zSize / dim)) + (zSize / dim));
			glTexCoord2f((1 + i) / dim, 0);		glVertex3f(xStart, (yStart)+(i * (height / dim)) + (height / dim), (zStart)+(j * (zSize / dim)) + (zSize / dim));
			glTexCoord2f((1 + i) / dim, 1);		glVertex3f(xStart, (yStart)+(i * (height / dim)) + (height / dim), (zStart)+(j * (zSize / dim)));
			glTexCoord2f((0 + i) / dim, 1);		glVertex3f(xStart, (yStart)+(i * (height / dim)), (zStart)+(j * (zSize / dim)));
		}
	}
	glEnd();

	glBegin(GL_QUADS);
	// bottom			//Y stays cosntant in minimum

	glNormal3f(0.0f, -1.0f, 0.0f);
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			glTexCoord2f((0 + i) / dim, 0);		glVertex3f((xStart)+(i * (xSize / dim)) + (xSize / dim), yStart, (zStart)+(j * (zSize / dim)) + (zSize / dim));
			glTexCoord2f((1 + i) / dim, 0);		glVertex3f((xStart)+(i * (xSize / dim)), yStart, (zStart)+(j * (zSize / dim)) + (zSize / dim));
			glTexCoord2f((1 + i) / dim, 1);		glVertex3f((xStart)+(i * (xSize / dim)), yStart, (zStart)+(j * (zSize / dim)));
			glTexCoord2f((0 + i) / dim, 1);		glVertex3f((xStart)+(i * (xSize / dim)) + (xSize / dim), yStart, (zStart)+(j * (zSize / dim)));
		}
	}
	glEnd();

	glBegin(GL_QUADS);
	// back				//Z stays constant in minimum

	glNormal3f(0.0f, 0.0f, -1.0f);
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			glTexCoord2f((0 + i) / dim, 0 );		glVertex3f((xStart)+(i * (xSize / dim)) + (xSize / dim), (yStart)+(j * (height / dim)) + (height / dim), zStart);
			glTexCoord2f((1 + i) / dim, 0 );		glVertex3f((xStart)+(i * (xSize / dim)) + (xSize / dim), (yStart)+(j * (height / dim)), zStart);
			glTexCoord2f((1 + i) / dim, 1 );		glVertex3f((xStart)+(i * (xSize / dim)), (yStart)+(j * (height / dim)), zStart);
			glTexCoord2f((0 + i) / dim, 1 );		glVertex3f((xStart)+(i * (xSize / dim)), (yStart)+(j * (height / dim)) + (height / dim), zStart);
		}
	}
	glEnd();
}

//for ultimate testing purposes
void drawParT2(GLfloat xSize, GLfloat height, GLfloat zSize, GLfloat xStart, GLfloat yStart, GLfloat zStart) {
	glBegin(GL_QUADS);
	// top
	glColor3f(0.5, 0.5, 0.5);
	glNormal3f(1.0f, 1.0f, 1.0f);		//for lightning after or something?
	glVertex3f(xStart, yStart + height, zStart + zSize);
	glVertex3f(xStart + xSize, yStart + height, zStart + zSize);
	glVertex3f(xStart + xSize, yStart + height, zStart);
	glVertex3f(xStart, yStart + height, zStart);
	glEnd();

	glBegin(GL_QUADS);
	// front
	glColor3f(1, 0, 1);
	glNormal3f(0.0f, 0.0f, 0.0f);
	glVertex3f(xStart + xSize, yStart, zStart + zSize);
	glVertex3f(xStart + xSize, yStart + height, zStart + zSize);
	glVertex3f(xStart, yStart + height, zStart + zSize);
	glVertex3f(xStart, yStart, zStart + zSize);
	glEnd();

	glBegin(GL_QUADS);
	// right
	glColor3f(0, 1, 1);
	glNormal3f(0.0f, 0.0f, 0.0f);
	glVertex3f(xStart + xSize, yStart + height, zStart);
	glVertex3f(xStart + xSize, yStart + height, zStart + zSize);
	glVertex3f(xStart + xSize, yStart, zStart + zSize);
	glVertex3f(xStart + xSize, yStart, zStart);
	glEnd();

	glBegin(GL_QUADS);
	// left
	glColor3f(1, 1, 0);
	glNormal3f(0.0f, 0.0f, 0.0f);
	glVertex3f(xStart, yStart, zStart + zSize);
	glVertex3f(xStart, yStart + height, zStart + zSize);
	glVertex3f(xStart, yStart + height, zStart);
	glVertex3f(xStart, yStart, zStart);
	glEnd();

	glBegin(GL_QUADS);
	// bottom
	glColor3f(0.75, 0.6, 0.2);
	glNormal3f(0.0f, 0.0f, 0.0f);
	glVertex3f(xStart + xSize, yStart, zStart + zSize);
	glVertex3f(xStart, yStart, zStart + zSize);
	glVertex3f(xStart, yStart, zStart);
	glVertex3f(xStart + xSize, yStart, zStart);
	glEnd();

	glBegin(GL_QUADS);
	// back
	glColor3f(0.1, 0.2, 0.7);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(xStart + xSize, yStart + height, zStart);
	glVertex3f(xStart + xSize, yStart, zStart);
	glVertex3f(xStart, yStart, zStart);
	glVertex3f(xStart, yStart + height, zStart);
	glEnd();
}

//was supposed to be used for colors several components to vary off eachother automatically, not used since it is supposed to be manually defined
float boundaries(GLfloat number, float change) {
	GLfloat retValue;
	retValue = number + change;
	if (retValue < 0) {
		retValue = 0.0;
		return retValue;
	}
	else if(retValue > 1){
		retValue = 1.0;
		return retValue;
	}
	else {
		return retValue;
	}
}

void drawEixos()
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo
	glColor4f(ORANGE);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(10, 0, 0);
	glEnd();
	glColor4f(GREEN);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(0, 10, 0);
	glEnd();
	glColor4f(CYAN);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(0, 0, 10);
	glEnd();

}

void drawObservador_Local()
{
	glColor4f(GREEN);
	glPushMatrix();
	glTranslatef(obsP[0], obsP[1], obsP[2]);
	//glutSolidCube(1);
	glPopMatrix();
}
void drawObservador_Target()
{
	glColor4f(YELLOW);
	glPushMatrix();
	glTranslatef(obsT[0], obsT[1], obsT[2]);
	//glutSolidCube(0.8);
	glPopMatrix();
}

void draw_Informacao()
{
	if (tipoProjeccao)
		sprintf_s(texto, 30, "Projecao = Ortogonal");
	else
		sprintf_s(texto, 30, "Projecao = Perspectiva");
	desenhaTexto(texto, -15, -15);


}

//======================================
void drawScene() {
	poligono[0] = 0;
	poligono[1] = 1;
	poligono[2] = 2;
	poligono[3] = 3;
	glPushMatrix();
	glScalef(6, 3, 6);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, poligono);
	glPopMatrix();
}

/*
void BetaDrawDoor(){

	drawParT(5, 4.8, 0.5, 4.1, 40, 0);

	glBegin(GL_QUADS);
	// front
	glColor3f(0.5, 0.5, 0.5);
	glNormal3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.1 + 13, 0, 0 + 0.5);
	glVertex3f(0.1 + 13, 0 + 35, 0 + 0.5);
	glVertex3f(0.1, 0 + 35, 0 + 0.5);
	glVertex3f(0.1, 0, 0 + 0.5);
	glEnd();

	glBegin(GL_QUADS);
	// front
	glColor3f(0.5, 0.5, 0.5);
	glNormal3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.1 + 4, 35, 0 + 0.5);
	glVertex3f(0.1 + 4, 35 + 9.8, 0 + 0.5);
	glVertex3f(0.1, 35 + 9.8, 0 + 0.1);
	glVertex3f(0.1, 35, 0 + 0.1);
	glEnd();

	glBegin(GL_QUADS);
	// front
	glColor3f(0.5, 0.5, 0.5);
	glNormal3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(9.1 + 4, 35, 0 + 0.5);
	glVertex3f(9.1 + 4, 35 + 9.8, 0 + 0.5);
	glVertex3f(9.1, 35 + 9.8, 0 + 0.5);
	glVertex3f(9.1, 35, 0 + 0.5);
	glEnd();

	glBegin(GL_QUADS);
	// front
	glColor3f(0.5, 0.5, 0.5);
	glTexCoord2f(0.0f, 1.0f);
	glNormal3f(0.0f, 0.0f, 0.0f);
	glVertex3f(4.1 + 5, 40, 0 + 0.5);
	glVertex3f(4.1 + 5, 40 + 4.8, 0 + 0.5);
	glVertex3f(4.1, 40 + 4.8, 0 + 0.5);
	glVertex3f(4.1, 40, 0 + 0.5);
	glEnd();

};

*/

void drawDoor() {

	float grey[] = { 0.3, 0.3, 0.3, 1 };

	//glScalef(0.1, 0.1, 0.1);
	glEnable(GL_TEXTURE_2D);	//ao usar isto e o diable as texturas so sao aplicadas a esta parte da porta e nao afeta a cor dos restantes elementos
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
//door frame
	drawParTMesh(1.5, 45, 1.5, 0, 0, 0);
	drawParTMesh(1.5, 45, 1.5, 15, 0, 0);
	drawParTMesh(16.5, 1.5, 1.5, 0, 45, 0);

	glDisable(GL_TEXTURE_2D);	//referencia a chamada do enable

	//one piece simple door
	//drawPar(13, 44.5, 0.5, 1.7, 0, 1);

	//unmovable hinges
	glPushMatrix();
		glTranslatef(1.5, 0, 0);
		drawParCMesh(0.1, 0.3, 0.5, 0, 15, 0, 0.3f, 0.3f, 0.3f, 1.0f);
		drawParCMesh(0.1, 0.3, 0.5, 0, 30, 0, 0.3f, 0.3f, 0.3f, 1.0f);
	glPopMatrix();

	glPushMatrix();

	glTranslatef(1.6, 0, 0);
	glRotatef(ang, 0, 1, 0);

	//door by pieces with animations(tecla v para abrir/c para fechar)	//old version without customizable material values
	/*
	drawParCMesh(13, 35, 0.5, 0.1, 0, 0, 0.7, 0.5, 0.3, 1.0f);		//0.7, 0.5, 0.3
	drawParCMesh(4, 9.8, 0.5, 0.1, 35, 0, 0.7, 0.5, 0.3, 1.0f);
	drawParCMesh(4, 9.8, 0.5, 9.1, 35, 0, 0.7, 0.5, 0.3, 1.0f);
	drawParCMesh(5, 4.8, 0.5, 4.1, 40, 0, 0.7, 0.5, 0.3, 1.0f);
	*/

	drawParCMesh2Test(13, 35, 0.5, 0.1, 0, 0, 1.0f);		//0.7, 0.5, 0.3
	drawParCMesh2Test(4, 9.8, 0.5, 0.1, 35, 0, 1.0f);
	drawParCMesh2Test(4, 9.8, 0.5, 9.1, 35, 0, 1.0f);
	drawParCMesh2Test(5, 4.8, 0.5, 4.1, 40, 0, 1.0f);

	//visor door with animation(tecla b para abrir/n para fechar)
	glPushMatrix();
		glTranslatef(abertura, 0, 0);
		drawParCMesh(5, 5, 0.3, 4.1, 35, 0.1, 0.0, 0.8, 0.9, 0.5f);
	glPopMatrix();

	//doorknob
	glPushMatrix();
			//glColor3f(0.3, 0.3, 0.3);
			glMaterialfv(GL_FRONT, GL_AMBIENT, grey);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, grey);
			glMaterialfv(GL_FRONT, GL_SPECULAR, grey);
			glTranslatef(12.1, 20, 0.5);
			glRotatef(doorKnobOp, 0.0, 0.0, 1.0);
			glPushMatrix();
				glTranslatef(0, 0, 1.0);
				gluDisk(gluNewQuadric(), 0, 0.3, 20, 1);
			glPopMatrix();
			gluCylinder(gluNewQuadric(), 0.3, 0.3, 1.0, 20, 20);
			glPushMatrix();
				//glColor3f(0.3f, 0.3f, 0.3f);
			glMaterialfv(GL_FRONT, GL_AMBIENT, grey);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, grey);
			glMaterialfv(GL_FRONT, GL_SPECULAR, grey);
				glRotatef(-90, 0, 1.0, 0);
				glTranslatef(0.8, 0, 0.1);
				gluCylinder(gluNewQuadric(), 0.2, 0.2, 1.5, 20, 20);
				glPushMatrix();
					glTranslatef(0, 0, 1.5);
					gluDisk(gluNewQuadric(), 0, 0.2, 20, 1);
				glPopMatrix();
				//glutSolidSphere(0.5, 5, 5);
			glPopMatrix();
		glPopMatrix();

		//TODO hinges are not completely fine tuned to position, check later ----------> a porta roda em função da porta em si, e nao das dobradiças como devia -> xStart= -0.1 before
		//door hinges
		drawParCMesh(0.1, 0.3, 0.5, 0, 15, 0, 0.3, 0.3, 0.3, 1.0f);		//movable hinge
		drawParCMesh(0.1, 0.3, 0.5, 0, 30, 0, 0.3, 0.3, 0.3, 1.0f);		//movable hinge
	glPopMatrix();
}


//====================================================== 
//====================================================== 
void display(void) {

	//================================================================= APaga 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float pink[] = { 0.5, 0, 0.5, 1 };

	//================================================================= Viewport 1 MAPA
	// projecao ortogonal
	glViewport(0, 0, 0.25 * wScreen, 0.25 * hScreen);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-20, 20, -20, 20, -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 30, 0, 0, 0, 0, 0, 0, -1);
	//…………………………………………………………………………………………………………………………………………………………Objectos
	drawEixos();
	drawDoor();
	drawObservador_Local();
	drawObservador_Target();
	drawScene();
	draw_Informacao();

	//================================================================= Viewport 2
	glViewport(0.25 * wScreen, 0.25 * hScreen, 0.75 * wScreen, 0.75 * hScreen);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (tipoProjeccao == 0)
		gluPerspective(anguloZ, (float)wScreen / hScreen, 0.1, 9999);
	if (tipoProjeccao == 1)
		glOrtho(-20, 20, -20, 20, -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(obsP[0], obsP[1], obsP[2], obsT[0], obsT[1], obsT[2], 0, 1, 0);		//mudei o 1 para viewHeight para poder mudar o angulo y com que olha para a porta, modificação do angulo esta nas teclas ascii(1 = cima/2 = baixo)

	//…………………………………………………………………………………………………………………………………………………………Objectos
	drawEixos();
	drawDoor();
	setupLuzes();			//ERA AQUI QUE ISTO DEVIA ESTAR PARA A LUZ NAO ANDAR DE UM LADO PARA O OUTRO E NAO NO DRAWSCENE, POR QUE È QUE RAIO È QUE ESTAVA LÁ!!!!!!!!
	drawScene();

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Actualizacao
	glutSwapBuffers();
}


void Timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(msec, Timer, 1);
}

//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y) {


	switch (key) {

		//------------------------------ zoom
	case 'z': 	case 'Z':
		break;
	case 'x':	case 'X':
		break;


		//As minahs teclas
		   //Depois do quao mal isto funciona, mas mesmo assim funcionando, só Deus me pode julgar

		   //controlos eixo Y
	case '1':
		obsT[1] += 0.5;
		break;
	case '2':
		obsT[1] -= 0.5;
		break;

	case 'q':	case'Q':
		obsP[1] += 0.5;
		obsT[1] += 0.5;
		break;

	case 'e':	case'E':
		obsP[1] -= 0.5;
		obsT[1] -= 0.5;
		break;

		//controlos eixo X
	case 'w':	case 'W':
		obsP[0] += 0.5;
		obsT[0] += 0.5;
		break;
	case 's':	case'S':
		obsP[0] -= 0.5;
		obsT[0] -= 0.5;
		break;

	case 'a':	case 'A':
		obsT[0] += 0.5;
		break;
	case 'd':	case'D':
		obsT[0] -= 0.5;
		break;

		//controlos eixo Z
	case 'i':	case'I':
		obsP[2] += 0.5;
		obsT[2] += 0.5;
		break;

	case 'k':	case'K':
		obsP[2] -= 0.5;
		obsT[2] -= 0.5;
		break;

	case 'j':	case'J':
		obsT[2] -= 0.5;
		break;

	case 'l':	case'L':
		obsT[2] += 0.5;
		break;

	case 'v':	case 'V':
		if (ang >= 5) {
			ang -= 5;
		}
		break;
	case 'c':	case 'C':
		if (ang <= 85) {
			ang += 5;
		}
		break;

	case 'b':	case 'B':
		if (abertura > -4.0) {
			abertura -= 0.5;
		}
		break;

	case 'n':	case 'N':
		if (abertura < 0.0) {
			abertura += 0.5;
		}
		break;

	case 'y':	case 'Y':
		if (doorKnobOp > 0.0) {
			doorKnobOp -= 2.0;
		}
		break;

	case 't':	case 'T':
		if (doorKnobOp <= 30.0) {
			doorKnobOp += 2.0;
		}
		break;

	case '3':	
		if (Lightred < 1.0) {
			Lightred += 0.05;
		}
		break;

	case '4':
		if (Lightgreen < 1.0) {
			Lightgreen += 0.05;
		}
		break;

	case '5':
		if (Lightblue < 1.0) {
			Lightblue += 0.05;
		}
		break;

	case '6':
		if (Lightred > 0.0) {
			Lightred -= 0.05;
		}
		break;

	case '7':
		if (Lightgreen > 0.0) {
			Lightgreen -= 0.05;
		}
		break;

	case '8':
		if (Lightblue > 0.0) {
			Lightblue -= 0.05;
		}
		break;

	case '9':
		if (WhiteCustom[0] < 1.0) {
			WhiteCustom[0] += 0.1;
			WhiteCustom[1] += 0.1;
			WhiteCustom[2] += 0.1;
		}
		break;

	case '0':
		if (WhiteCustom[0] > 0.0) {
			WhiteCustom[0] -= 0.1;
			WhiteCustom[1] -= 0.1;
			WhiteCustom[2] -= 0.1;
		}
		break;

	case 'r':	case 'R':
		if (mat_specular[0] < 1.0) {
			mat_specular[0] += 0.1;
			mat_specular[1] += 0.1;
			mat_specular[2] += 0.1;
		}
		break;

	case 'u':	case 'U':
		if (mat_specular[0] > 0.0) {
			mat_specular[0] -= 0.1;
			mat_specular[1] -= 0.1;
			mat_specular[2] -= 0.1;
		}
		break;

		//fim das minahs teclas

			//------------------------------ projeccao
	case 'p': 	case 'P':
		tipoProjeccao = (tipoProjeccao + 1) % 2;
		glutPostRedisplay();
		break;


		//--------------------------- Escape
	case 27:
		exit(0);
		break;
	}

}



void teclasNotAscii(int key, int x, int y) {


	//------------------------------- olhar para a origem
	obsT[0] = 0; obsT[1] = 0; obsT[2] = 0;

	if (key == GLUT_KEY_UP)    obsP[1] = obsP[1] + 0.5;
	if (key == GLUT_KEY_DOWN)  obsP[1] = obsP[1] - 0.5;
	if (key == GLUT_KEY_LEFT)  aVisao = aVisao + 0.1;
	if (key == GLUT_KEY_RIGHT) aVisao = aVisao - 0.1;

	if (obsP[1] > yC)   obsP[1] = yC;
	if (obsP[1] < -yC)  obsP[1] = -yC;
	obsP[0] = rVisao * cos(aVisao);
	obsP[2] = rVisao * sin(aVisao);

	glutPostRedisplay();

}




//======================================================= MAIN
//======================================================= MAIN
int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(wScreen, hScreen);
	glutInitWindowPosition(400, 100);
	glutCreateWindow("{jh,ct,ep}@dei.uc.pt|    |Observador:'SETAS'|  |Projecao -'p'| ");

	initialize();

	glutSpecialFunc(teclasNotAscii);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(msec, Timer, 1);

	glutMainLoop();

	return 0;
}


/*GUIA DOS CONTROLOS
* SETAS: rodar à volta da porta
* W/S: Avançar/Recuar no eixo X
* A/D: Olhar no sentido do X positivo/negativo
* Q/E: Subir/Descer o observador
* 1/2: olhar para um ponto mais alto/baixo
* I/K: Avançar/Recuar no eixo Z
* J/L: Olhar para um ponto mais avançado/menos avançado no eixo Z
* C/V: Abrir/Fechar a porta
* B/N: Abrir/Fechar a portinhola
* T/Y: Rodar positivamente/negativamente a maçaneta
* 3/4/5: Subir os valores RGB (respetivamente) da luz pontual do lado de trás da porta
* 6/7/8: Descer os valores RGB (respetivamente) da luz pontual do lado de trás da porta
* 9/0: Aumentar/Diminuir a intensidade da luz focal na parte da frente da porta
* R/U: Aumentar/Diminuir a componente especular da porta
*/

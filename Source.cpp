#include <SDL2/SDL.h>
#include <math.h>
#include <iostream>
#include "triangle.h"
SDL_Window* window;
SDL_Renderer* renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

//Rotation 
float fTheta = M_PI/12.;

const int iN_triangles = 12 + 1;

//Window Parameters

int iScreenWidth = 800;
int iScreenHeight = 600;

// Cube Parameters
int iCube_PositionX = 300;
int iCube_PositionY = 200;
int iCube_Size = 200;

//functions
void Draw_Black_Screen();
void Draw_Pixel(float x, float y);
void Draw_Line(float x1, float y1, float x2, float y2);
void Draw_Cube(triangle x[]);
void Mult_tringl_by_matr(triangle M[], float fRotation_mat[3][3]);

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(iScreenWidth, iScreenHeight, 0, &window, &renderer);
	
	bool running = true;
	SDL_Event X_is_pressed;
	
	triangle tPolygon_Mass[iN_triangles];

	//Defining cube's polygins by hand
	//{

	//1,2,6						1,5,6						2,3,7						2,6,7						1,2,3					
	tPolygon_Mass[1].x1 = 0;	tPolygon_Mass[2].x1 = 0;	tPolygon_Mass[3].x1 = 1;	tPolygon_Mass[4].x1 = 1;	tPolygon_Mass[5].x1 = 0;
	tPolygon_Mass[1].y1 = 0;	tPolygon_Mass[2].y1 = 0;	tPolygon_Mass[3].y1 = 0;	tPolygon_Mass[4].y1 = 0;	tPolygon_Mass[5].y1 = 0;
	tPolygon_Mass[1].z1 = 0;	tPolygon_Mass[2].z1 = 0;	tPolygon_Mass[3].z1 = 0;	tPolygon_Mass[4].z1 = 0;	tPolygon_Mass[5].z1 = 0;

	tPolygon_Mass[1].x2 = 1;	tPolygon_Mass[2].x2 = 0;	tPolygon_Mass[3].x2 = 1;	tPolygon_Mass[4].x2 = 1;	tPolygon_Mass[5].x2 = 1;
	tPolygon_Mass[1].y2 = 0;	tPolygon_Mass[2].y2 = 1;	tPolygon_Mass[3].y2 = 0;	tPolygon_Mass[4].y2 = 1;	tPolygon_Mass[5].y2 = 0;
	tPolygon_Mass[1].z2 = 0;	tPolygon_Mass[2].z2 = 0;	tPolygon_Mass[3].z2 = 1;	tPolygon_Mass[4].z2 = 0;	tPolygon_Mass[5].z2 = 0;

	tPolygon_Mass[1].x3 = 1;	tPolygon_Mass[2].x3 = 1;	tPolygon_Mass[3].x3 = 1;	tPolygon_Mass[4].x3 = 1;	tPolygon_Mass[5].x3 = 1;
	tPolygon_Mass[1].y3 = 1;	tPolygon_Mass[2].y3 = 1;	tPolygon_Mass[3].y3 = 1;	tPolygon_Mass[4].y3 = 1;	tPolygon_Mass[5].y3 = 0;
	tPolygon_Mass[1].z3 = 0;	tPolygon_Mass[2].z3 = 0;	tPolygon_Mass[3].z3 = 1;	tPolygon_Mass[4].z3 = 1;	tPolygon_Mass[5].z3 = 1;


	//1,4,3						1,5,4						4,8,5						4,8,3						8,7,3					
	tPolygon_Mass[6].x1 = 0;	tPolygon_Mass[7].x1 = 0;	tPolygon_Mass[8].x1 = 0;	tPolygon_Mass[9].x1 = 0;	tPolygon_Mass[10].x1 = 0;
	tPolygon_Mass[6].y1 = 0;	tPolygon_Mass[7].y1 = 0;	tPolygon_Mass[8].y1 = 0;	tPolygon_Mass[9].y1 = 0;	tPolygon_Mass[10].y1 = 1;
	tPolygon_Mass[6].z1 = 0;	tPolygon_Mass[7].z1 = 0;	tPolygon_Mass[8].z1 = 1;	tPolygon_Mass[9].z1 = 1;	tPolygon_Mass[10].z1 = 1;

	tPolygon_Mass[6].x2 = 0;	tPolygon_Mass[7].x2 = 0;	tPolygon_Mass[8].x2 = 0;	tPolygon_Mass[9].x2 = 0;	tPolygon_Mass[10].x2 = 1;
	tPolygon_Mass[6].y2 = 0;	tPolygon_Mass[7].y2 = 1;	tPolygon_Mass[8].y2 = 1;	tPolygon_Mass[9].y2 = 1;	tPolygon_Mass[10].y2 = 1;
	tPolygon_Mass[6].z2 = 1;	tPolygon_Mass[7].z2 = 0;	tPolygon_Mass[8].z2 = 1;	tPolygon_Mass[9].z2 = 1;	tPolygon_Mass[10].z2 = 1;

	tPolygon_Mass[6].x3 = 1;	tPolygon_Mass[7].x3 = 0;	tPolygon_Mass[8].x3 = 0;	tPolygon_Mass[9].x3 = 1;	tPolygon_Mass[10].x3 = 1;
	tPolygon_Mass[6].y3 = 0;	tPolygon_Mass[7].y3 = 0;	tPolygon_Mass[8].y3 = 1;	tPolygon_Mass[9].y3 = 0;	tPolygon_Mass[10].y3 = 0;
	tPolygon_Mass[6].z3 = 1;	tPolygon_Mass[7].z3 = 1;	tPolygon_Mass[8].z3 = 0;	tPolygon_Mass[9].z3 = 1;	tPolygon_Mass[10].z3 = 1;


	//5, 8, 7						5, 6, 7					
	tPolygon_Mass[11].x1 = 0;	tPolygon_Mass[12].x1 = 0;
	tPolygon_Mass[11].y1 = 1;	tPolygon_Mass[12].y1 = 1;
	tPolygon_Mass[11].z1 = 0;	tPolygon_Mass[12].z1 = 0;

	tPolygon_Mass[11].x2 = 0;	tPolygon_Mass[12].x2 = 1;
	tPolygon_Mass[11].y2 = 1;	tPolygon_Mass[12].y2 = 1;
	tPolygon_Mass[11].z2 = 1;	tPolygon_Mass[12].z2 = 0;

	tPolygon_Mass[11].x3 = 1;	tPolygon_Mass[12].x3 = 1;
	tPolygon_Mass[11].y3 = 1;	tPolygon_Mass[12].y3 = 1;
	tPolygon_Mass[11].z3 = 1;	tPolygon_Mass[12].z3 = 1;


	//}
	//Rotatin matrix 
	triangle Rotated[iN_triangles];


	Draw_Black_Screen();
	while (running) {
		
		float fRotation_matXZ[3][3] =
		{
			{cosf(fTheta)*cosf(fTheta),-sinf(fTheta),cosf(fTheta) * sinf(fTheta)},
			{cosf(fTheta) * sinf(fTheta), cosf(fTheta),sinf(fTheta)* sinf(fTheta)},
			{ -sinf(fTheta),0,cosf(fTheta)}
		};

		SDL_PollEvent(&X_is_pressed);
		Mult_tringl_by_matr(tPolygon_Mass, fRotation_matXZ); //Rotating and drawing cube
		Draw_Black_Screen();
		SDL_Delay(10);

		if (X_is_pressed.type == SDL_QUIT) { running = false; }
	}

	SDL_Quit();
	return 0;
}



void Draw_Line(float x1, float y1, float x2, float y2)
{
	float lenght = sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));
	float angle = atan2((y2 - y1), (x2 - x1));
	for (int i = 0; i<int(lenght); i++)
		Draw_Pixel(x1 + cos(angle) * i, y1 + sin(angle) * i);
}
void Draw_Black_Screen()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

}
void Draw_Pixel(float x, float y)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawPointF(renderer, (int)x, (int)y);
	SDL_RenderPresent(renderer);
}

void Mult_tringl_by_matr(triangle M[], float fRotation_mat[3][3])
{
	triangle Multyplied[iN_triangles];
	for (int i = 1; i < iN_triangles; i++)
	{
		Multyplied[i].x1 = M[i].x1 * fRotation_mat[0][0] + M[i].y1 * fRotation_mat[0][1] + M[i].z1 * fRotation_mat[0][2];
		Multyplied[i].y1 = M[i].x1 * fRotation_mat[1][0] + M[i].y1 * fRotation_mat[1][1] + M[i].z1 * fRotation_mat[1][2];
		Multyplied[i].z1 = M[i].x1 * fRotation_mat[1][0] + M[i].y1 * fRotation_mat[1][1] + M[i].z1 * fRotation_mat[1][2];

		Multyplied[i].x2 = M[i].x2 * fRotation_mat[0][0] + M[i].y2 * fRotation_mat[0][1] + M[i].z2 * fRotation_mat[0][2];
		Multyplied[i].y2 = M[i].x2 * fRotation_mat[1][0] + M[i].y2 * fRotation_mat[1][1] + M[i].z2 * fRotation_mat[1][2];
		Multyplied[i].z2 = M[i].x2 * fRotation_mat[2][0] + M[i].y2 * fRotation_mat[2][1] + M[i].z2 * fRotation_mat[1][2];

		Multyplied[i].x3 = M[i].x3 * fRotation_mat[0][0] + M[i].y3 * fRotation_mat[0][1] + M[i].z3 * fRotation_mat[0][2];
		Multyplied[i].y3 = M[i].x3 * fRotation_mat[1][0] + M[i].y3 * fRotation_mat[1][1] + M[i].z3 * fRotation_mat[1][2];
		Multyplied[i].z3 = M[i].x3 * fRotation_mat[2][0] + M[i].y3 * fRotation_mat[2][1] + M[i].z3 * fRotation_mat[2][2];

	}
	fTheta += M_PI /24.;
	Draw_Cube(Multyplied);
}


void Draw_Cube(triangle M[])
{
	//Projection Matrix
	float fProjection_mat[3][3] =
	{
		{1,0,0},
		{0,1,0},
		{0,0,0}

	};

	triangle Display[iN_triangles];
	//Projecting cube onto sceen
	for (int i = 1; i < iN_triangles; i++)
	{
		Display[i].x1 = M[i].x1 * fProjection_mat[0][0] + M[i].y1 * fProjection_mat[0][1] + M[i].z1 * fProjection_mat[0][2];
		Display[i].y1 = M[i].x1 * fProjection_mat[1][0] + M[i].y1 * fProjection_mat[1][1] + M[i].z1 * fProjection_mat[1][2];
		Display[i].z1 = M[i].x1 * fProjection_mat[2][0] + M[i].y1 * fProjection_mat[2][1] + M[i].z1 * fProjection_mat[2][2];

		Display[i].x2 = M[i].x2 * fProjection_mat[0][0] + M[i].y2 * fProjection_mat[0][1] + M[i].z2 * fProjection_mat[0][2];
		Display[i].y2 = M[i].x2 * fProjection_mat[1][0] + M[i].y2 * fProjection_mat[1][1] + M[i].z2 * fProjection_mat[1][2];
		Display[i].z3 = M[i].x2 * fProjection_mat[2][0] + M[i].y2 * fProjection_mat[2][1] + M[i].z2 * fProjection_mat[2][2];

		Display[i].x3 = M[i].x3 * fProjection_mat[0][0] + M[i].y3 * fProjection_mat[0][1] + M[i].z3 * fProjection_mat[0][2];
		Display[i].y3 = M[i].x3 * fProjection_mat[1][0] + M[i].y3 * fProjection_mat[1][1] + M[i].z3 * fProjection_mat[1][2];
		Display[i].z3 = M[i].x3 * fProjection_mat[2][0] + M[i].y3 * fProjection_mat[2][1] + M[i].z2 * fProjection_mat[2][2];
	}
	//Drawing each polygon
	for (int i = 1; i < iN_triangles; i++)
	{
		Draw_Line((Display[i].x1 * iCube_Size) + iCube_PositionX, (Display[i].y1 * iCube_Size) + iCube_PositionY, (Display[i].x2 * iCube_Size) + iCube_PositionX, (Display[i].y2 * iCube_Size) + iCube_PositionY);
		Draw_Line((Display[i].x2 * iCube_Size) + iCube_PositionX, (Display[i].y2 * iCube_Size) + iCube_PositionY, (Display[i].x3 * iCube_Size) + iCube_PositionX, (Display[i].y3 * iCube_Size) + iCube_PositionY);
		Draw_Line((Display[i].x1 * iCube_Size) + iCube_PositionX, (Display[i].y1 * iCube_Size) + iCube_PositionY, (Display[i].x3 * iCube_Size) + iCube_PositionX, (Display[i].y3 * iCube_Size) + iCube_PositionY);
	}

}
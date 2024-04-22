/****************************************************************************
 ** 3D_Jason.c - display a 3D rotating cube                                **
 ** Copyright (c) 31/12/2022 Jason Bou-Samra [Paragon]                     **
 **                                                                        **
 ** This program is free software: you can redistribute it and/or modify   **
 ** it under the terms of the GNU General Public License as published by   **
 ** the Free Software Foundation, either version 3 of the License, or      **
 ** (at your option) any later version.                                    **
 **                                                                        **
 ** This program is distributed in the hope that it will be useful,        **
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of         **
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          **
 ** GNU General Public License for more details.                           **
 **                                                                        **
 ** You should have received a copy of the GNU General Public License      **
 ** along with this program.  If not, see <https://www.gnu.org/licenses/>. **
 ****************************************************************************/

#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <stdbool.h>

int initSDL(void);
int shutdownSDL(void);
int rotate (void);
int draw (void);

double x[8], y[8], z[8];
double xt[8], yt[8], zt[8];
double xu[8], yu[8], zu[8];
double angle = 0.0;
bool quit = false;

SDL_Window *window = NULL;
SDL_Renderer *s;
SDL_Event event;

/* window paramaters */
#define WIDTH 640       /* pixels */
#define HEIGHT 512      /* pixels */
#define DELAY 3000      /* milliseconds */
#define TITLE "3Dcube"  /* title */
#define RAD 3.14159265/180
#define SPEED 3

int main(void)
{
  initSDL();
  SDL_RenderSetScale(s, 2.0, 2.0);          /* scale x2 */

while (quit==false){

while (SDL_PollEvent(&event)) {
  if (event.type==SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {quit = true;}
}
if(quit) {break;}

 rotate();
 draw();

}
 shutdownSDL();
}

/* rotation & projection routine */
int rotate()
{

for (int i=7; i>=0; i--){

/* x angle (Roll) */
  xt[i]=x[i];
  yt[i]=y[i]*cos(RAD*angle)-z[i]*sin(RAD*angle);
  zt[i]=y[i]*sin(RAD*angle)+z[i]*cos(RAD*angle);

/* y angle (Pitch) */
  xu[i]=zt[i]*sin(RAD*angle)+xt[i]*cos(RAD*angle);
  yu[i]=yt[i];
  zu[i]=xt[i]*-sin(RAD*angle)+zt[i]*cos(RAD*angle);

/* z angle (Yaw) */
  xt[i]=xu[i]*cos(RAD*angle)-yu[i]*sin(RAD*angle);
  yt[i]=xu[i]*sin(RAD*angle)+yu[i]*cos(RAD*angle);
  zt[i]=zu[i];

/* 2d perspective projection */
xt[i]=(xt[i]*200)/(zt[i]+800)+160;
yt[i]=(yt[i]*200)/(zt[i]+800)+128;
}

angle = angle + SPEED;
}

/* render cube */
 int draw()
 {
  SDL_SetRenderDrawColor(s, 0x00, 0x00, 0x00, 255);   /* background */
  SDL_RenderClear(s);                                 /* clear screen (black) */
  SDL_SetRenderDrawColor(s, 0x80, 0x00,0x80,255);     /* pen */
  SDL_RenderDrawLine(s, xt[0], yt[0], xt[1], yt[1]);
  SDL_RenderDrawLine(s, xt[1], yt[1], xt[2], yt[2]);
  SDL_RenderDrawLine(s, xt[2], yt[2], xt[3], yt[3]);
  SDL_RenderDrawLine(s, xt[3], yt[3], xt[0], yt[0]);

  SDL_RenderDrawLine(s, xt[4], yt[4], xt[5], yt[5]);
  SDL_RenderDrawLine(s, xt[5], yt[5], xt[6], yt[6]);
  SDL_RenderDrawLine(s, xt[6], yt[6], xt[7], yt[7]);
  SDL_RenderDrawLine(s, xt[7], yt[7], xt[4], yt[4]);

  SDL_RenderDrawLine(s, xt[0], yt[0], xt[4], yt[4]);
  SDL_RenderDrawLine(s, xt[1], yt[1], xt[5], yt[5]);
  SDL_RenderDrawLine(s, xt[2], yt[2], xt[6], yt[6]);
  SDL_RenderDrawLine(s, xt[3], yt[3], xt[7], yt[7]);

  SDL_RenderPresent(s);
 }

/* initialise SDL */
int initSDL(){
  SDL_Init(SDL_INIT_EVERYTHING);

/* new window */
  window = SDL_CreateWindow(
    TITLE,                              /* title*/
		SDL_WINDOWPOS_UNDEFINED,        /* x pos */
		SDL_WINDOWPOS_UNDEFINED,        /* w pos */
		WIDTH,                          /* width */
		HEIGHT,                         /* height */
		0);                             /* Additional flag(s) */

  /* deal with errors */
  if (window == NULL) {
    fprintf(stderr, "SDL window failed to initialise: %s\n", SDL_GetError());
    return 1;
  }

/* create renderer */
s = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

}

/* shutdown routine */
int shutdownSDL()
{

//  SDL_Delay(DELAY);           /* pause sdl sub-system */
  SDL_DestroyWindow(window);    /* free memory */
  SDL_Quit();                   /* shutdown entire sdl sub-systems */
  return 0;
}

/* cube verticies */
/* x component */
double x[]={-80.0, 80.0, 80.0, -80.0, -80.0, 80.0, 80.0, -80.0
};

/* y component */
double y[]={80.0, 80.0, -80.0, -80.0, 80.0, 80.0, -80.0, -80.0
};

/* z component */
double z[]={80.0, 80.0, 80.0, 80.0, -80.0, -80.0, -80.0, -80.0
};

/* perspective projection table */
double ProjPos[]={
};

/* message */
char author[]={"3d vector graphics demo"};
const char* text = "c version 1";

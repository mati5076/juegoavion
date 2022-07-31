#include <allegro.h>

#include<stdio.h>

#include<stdlib.h>

#include<time.h>

#include "bala.h"

#define MAXCOL 15

#define MAXFIL 20

BITMAP *pared;

BITMAP *buffer;

void init();

void deinit();

char escena[MAXFIL][MAXCOL];

void Menu()
{
	BITMAP *menu =load_bitmap("MENU.bmp",NULL);
	
	if(key[KEY_ENTER])
	{
		blit(menu,screen,0,0,0,0,440,680);
		
		blit(menu,buffer,0,0,0,0,menu->w,menu->h);
	}
}
void leer()//codigo de ayuda por mi compañero francisco
{
	int i,j;
	
	char prueba;
	
	FILE * archivo = fopen ("Mapa2.txt" , "r");//lectura de archivo de texto
	if(archivo==NULL)
	{
		printf("error al abrir el archivo");
		system ("pause");
	}
	i=0;
	j=0;
	while(!feof (archivo) )
	{

	prueba = fgetc(archivo);
	if(prueba=='\n')
	{	
		i++;
		j=0;
	}
	else
	{
		escena[i][j]=prueba;
		j++;
	
	}
	}
  for(i=0;i<MAXFIL;i++)
  {
  	for(j=0;j<MAXCOL;j++)
	{
		printf("%c" ,escena[i][j]);
	}
	printf("\n");
	}
}

void dibujar()
{
	int i,j;
	
	leer();
	
	for(i=0;i<MAXFIL;i++)
	{
		for(j=0;j<MAXCOL;j++)
		{
			if(escena[i][j] == 'X' )
			{
				draw_sprite(screen,pared,20*j,15*i);
			}
		}
	}
}

int main()
{
	init();
	
	int x=200,y=450,x1=0,y1=155,x2=200,y2=450,der=200,izq=450;
	float vida = 100;
	BITMAP *buffer = create_bitmap(440,680);
	//se declara el bitmap para poder insertar la imagen del avion que usara el usuario
	
	BITMAP *avion;
	
	avion=load_bitmap("IMG/ask.bmp",NULL); //insertar imagen en la ventana
	
	BITMAP *fondo;//insertar la imagen de fondo 

	fondo=load_bitmap("azul.bml.bmp",NULL); 
	
	BITMAP *sprite;//insertar las balas para el jugador 
	
	sprite = load_bitmap("disp2.bmp",NULL);
	
	pared= load_bitmap("disp2.bmp",NULL);
	
	BITMAP *enemigo;
		
	enemigo = load_bitmap("enemigo.bmp",NULL);
	
	set_window_title("1945");
	
	while (!key[KEY_ESC]) // ciclo que ayuda amover el avion y deja la imagen de fondo 
	{
		Menu();
		
		blit(fondo,screen,0,0,x1,y1,440,680);
		
		blit(fondo,buffer,0,0,0,0,fondo->w,fondo->h);//deja el fondo estatico y deja sobre poner el personaje 
		
		//avion
		blit(buffer,screen,0,0,0,0,440,680);
		
		blit(avion,buffer,0,0,x,y,avion->w,avion->h);//deja el fondo estatico y deja sobre poner el personaje 

		//blit(disparr,fondo,0,0,x1,y1,disparr->w,disparr->h);
		
		blit(buffer,screen,0,0,0,0,440,680);

		blit(enemigo,screen,0,0,0,0,enemigo->w,enemigo->h);
		
		if(der = x)
		{
			der+=50;
			blit(buffer,screen,0,0,0,0,440,680);
			blit(enemigo,screen,0,0,der,izq,enemigo->w,enemigo->h);
		}
		if(key[KEY_SPACE])
		{
			y2-=6;//esto hace que el disparo ocurra hacia adelante y a su vez hace que aparezca la bala 
			blit(buffer,screen,0,0,0,0,440,680);
			blit(sprite,screen,0,0,x2,y2,sprite->w,sprite->h);
		}
		else if(key[KEY_RIGHT])//teclas de movimiento del avion 
		{
			x+=50;//hace que se mueva hacia la derecha
			blit(buffer,screen,0,0,0,0,440,680);
			blit(avion,screen,0,0,x,y,100,112);
		}
		else if(key[KEY_LEFT])
		{
			x-=50;//hace que se mueva hacia la izquierda
			blit(buffer,screen,0,0,0,0,440,680);
			blit(avion,screen,0,0,x,y,100,112);
		}
		else if(key[KEY_UP])
		{
			y-=50;//hace que se mueva hacia arriba , el signo menos es porque allegro tiene invertido las direcciones de arriba y abajo 
			blit(buffer,screen,0,0,0,0,440,680);
			blit(avion,screen,0,0,x,y,100,112);
		}
		else if(key[KEY_DOWN])
		{
			y+=50;//se mueve hacia abajo
			blit(buffer,screen,0,0,0,0,440,680);
			blit(avion,screen,0,0,x,y,100,112);
		}
		// "botones de reserva"
		if(key[KEY_D])
		{
			x+=50;
			blit(buffer,screen,0,0,0,0,440,680);
			blit(avion,screen,0,0,x,y,100,112);
		}
		else if(key[KEY_A])
		{
			x-=50;
			blit(buffer,screen,0,0,0,0,440,680);
			blit(avion,screen,0,0,x,y,100,112);
		}
		else if(key[KEY_W])
		{
			y-=50;
			blit(buffer,screen,0,0,0,0,440,680);
			blit(avion,screen,0,0,x,y,100,112);
		}
		else if(key[KEY_S])
		{
			y+=50;
			blit(buffer,screen,0,0,0,0,440,680);
			blit(avion,screen,0,0,x,y,100,112);
		}
		
		dibujar();//funcion que sirve para leer y ejecutar un archivo de txt

		rest(10);
	}
	deinit();
	
	return 0;
}
END_OF_MAIN()

void init() 
{
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res=set_gfx_mode(GFX_AUTODETECT_WINDOWED, 440,680, 0, 0);
	if (res != 0) 
	{
		allegro_message(allegro_error);
		exit(-1);
	}

	install_timer();
	install_keyboard(); 
	install_mouse();
}

void deinit() 
{
	clear_keybuf();
}

void barra_de_vida()
{
	float vida;
	if(vida == 100)
	{
		rectfil();
	}
}

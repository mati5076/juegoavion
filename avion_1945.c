#include <allegro.h>

#include<stdio.h>

#include<stdlib.h>

#include "bala.h"

#define MAXCOL 35
#define MAXFIL 25

BITMAP *fondo;//insertar la imagen de fondo 

BITMAP *avion;

BITMAP *pared;

BITMAP *buffer;

void init();

void deinit();

int i,j;

char prueba;
	
char escena[MAXFIL][MAXCOL];

void leer()//codigo de ayuda por mi compa�ero francisco
{	
	FILE * archivo = fopen ("generar.txt" , "r");//lectura de archivo de texto
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
	blit(fondo,buffer,0,0,0,0,fondo->w,fondo->h);

	draw_sprite(buffer,fondo,0,0);
	
    for(i=0;i<MAXFIL;i++)
	{
        for(j=0;j<MAXCOL;j++)
		{
			if (escena[i][j] == 'X')
			{
				draw_sprite(buffer,fondo,i*2,j*2);
            }
        }
    }
}

int main()
{
	init();
	int x=200;
	int y=450;
	int x1=0;
	int y1=155;
	int x2=200;
	int y2=450;
	int cont=0;
	
	BITMAP *buffer = create_bitmap(440,580);
	//se declara el bitmap para poder insertar la imagen del avion que usara el usuario

	avion=load_bitmap("IMG/ask.bmp",NULL); //insertar imagen en la ventana
		
	fondo=load_bitmap("azul.bml.bmp",NULL); 
	
	BITMAP *sprite;//insertar las balas para el jugador 
	
	sprite = load_bitmap("disp2.bmp",NULL);
	
	pared= load_bitmap("roca.bmp",NULL);

	set_window_title("1945");
		
	while (!key[KEY_ESC]) // ciclo que ayuda amover el avion y deja la imagen de fondo 
	{
		blit(fondo,screen,0,0,x1,y1,440,680);
		
		blit(fondo,buffer,0,0,0,0,fondo->w,fondo->h);//deja el fondo estatico y deja sobre poner el personaje 
		
		//avion
		blit(buffer,screen,0,0,0,0,700,600);
		
		blit(avion,screen,0,0,x,y,avion->w,avion->h);
		if(key[KEY_SPACE])
		{
			y2-=6;//esto hace que el disparo ocurra hacia adelante y a su vez hace que aparezca la bala 
			blit(buffer,screen,0,0,0,0,700,600);
			blit(sprite,screen,0,0,x2,y2,sprite->w,sprite->h);
			cont++;
		}
		else if(key[KEY_RIGHT])//teclas de movimiento del avion 
		{
			x+=50;//hace que se mueva hacia la derecha
			blit(buffer,screen,0,0,0,0,440,580);
			blit(avion,screen,0,0,x,y,100,112);
		}
		else if(key[KEY_LEFT])
		{
			x-=50;//hace que se mueva hacia la izquierda
			blit(buffer,screen,0,0,0,0,700,600);
			blit(avion,screen,0,0,x,y,100,112);
		}
		else if(key[KEY_UP])
		{
			y-=50;//hace que se mueva hacia arriba , el signo menos es porque allegro tiene invertido las direcciones de arriba y abajo 
			blit(buffer,screen,0,0,0,0,700,600);
			blit(avion,screen,0,0,x,y,100,112);
		}
		else if(key[KEY_DOWN])
		{
			y+=50;//se mueve hacia abajo
			blit(buffer,screen,0,0,0,0,700,600);
			blit(avion,screen,0,0,x,y,100,112);
		}
		// "botones de reserva"
		if(key[KEY_D])
		{
			x+=50;
			blit(buffer,screen,0,0,0,0,700,600);
			blit(avion,screen,0,0,x,y,100,112);
		}
		else if(key[KEY_A])
		{
			x-=50;
			blit(buffer,screen,0,0,0,0,700,600);
			blit(avion,screen,0,0,x,y,100,112);
		}
		else if(key[KEY_W])
		{
			y-=50;
			blit(buffer,screen,0,0,0,0,700,600);
			blit(avion,screen,0,0,x,y,100,112);
		}
		else if(key[KEY_S])
		{
			y+=50;
			blit(buffer,screen,0,0,0,0,700,600);
			blit(avion,screen,0,0,x,y,100,112);
		}
		rest(30);
	}
	destroy_bitmap(buffer);
	destroy_bitmap(avion);
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
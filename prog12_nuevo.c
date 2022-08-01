#include <allegro.h>

#include<stdio.h>

#include<stdlib.h>

#include<time.h>

#define MAXCOL 15

#define MAXFIL 20

void init();

void deinit();

char escena[MAXFIL][MAXCOL];

struct Avion{
	
	int mover_der;
	
	int mover_arriba;
	
}jugador1;

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
	
	BITMAP *pared = load_bitmap("disp2.bmp",NULL);
	
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
	int x=200;
	int y=450;
	int x1=0;
	int y1=155;
	int x2=200;
	int y2=450;
	int mov,mos;
	jugador1.mover_der=200;
	
	jugador1.mover_arriba=450;
	
	srand(time(0));
	
	mov=rand()%150;
	
	mos=rand()%160;
	
	BITMAP *buffer = create_bitmap(440,680);
	//se declara el bitmap para poder insertar la imagen del avion que usara el usuario
	
	BITMAP *menu = load_bitmap("menu.bmp",NULL);
	
	BITMAP *avion = load_bitmap("IMG/ask.bmp",NULL); //insertar imagen en la ventana
	
	BITMAP *fondo = load_bitmap("azul.bml.bmp",NULL); 
	
	BITMAP *sprite;//insertar las balas para el jugador 
	
	sprite = load_bitmap("disp2.bmp",NULL);
	
	BITMAP *pared= load_bitmap("disp2.bmp",NULL);
	
	BITMAP *enemigo = load_bitmap("enemigo.bmp",NULL);

	set_window_title("1945");//le da nombre a la ventana 
	
	while (!key[KEY_ESC]) 
	{
		//////////////////////////////////////////////////////////////////
		
		blit(fondo,screen,0,0,x1,y1,440,680);
		
		blit(fondo,buffer,0,0,0,0,fondo->w,fondo->h);//deja el fondo estatico y deja sobre poner el personaje 
			
		//avion
		blit(buffer,screen,0,0,0,0,440,680);
		
		blit(avion,screen,0,0,jugador1.mover_der,jugador1.mover_arriba,avion->w,avion->h);
		
		//enemigo 
		blit(enemigo,screen,0,0,mov,mos,enemigo->w,enemigo->h);
		
		//blit(disparr,fondo,0,0,x1,y1,disparr->w,disparr->h);				
		if(mov != jugador1.mover_der && mov < jugador1.mover_der)
		{
			mov+=130;
		}
		else if(mov != jugador1.mover_der && mov > jugador1.mover_der)
		{
			mov-=130;
		}
		else if(mos != jugador1.mover_arriba && mos < jugador1.mover_arriba)
		{
			mos+=140;
		}
		else if(mos != jugador1.mover_arriba && mos > jugador1.mover_arriba)
		{
			mos-=140;
		}
		if(key[KEY_SPACE])
		{
			y2-=6;//esto hace que el disparo ocurra hacia adelante y a su vez hace que aparezca la bala 
		}
		else if(key[KEY_RIGHT])//teclas de movimiento del avion 
		{
			jugador1.mover_der+=50;//hace que se mueva hacia la derecha
		}
		else if(key[KEY_LEFT])
		{
			jugador1.mover_der-=50;//hace que se mueva hacia la izquierda
		}
		else if(key[KEY_UP])
		{
			jugador1.mover_arriba-=50;//hace que se mueva hacia arriba , el signo menos es porque allegro tiene invertido las direcciones de arriba y abajo 
		}
		else if(key[KEY_DOWN])
		{
			jugador1.mover_arriba+=50;
		}
		// "botones de reserva"
		if(key[KEY_D])
		{
			x+=50;
		}
		else if(key[KEY_A])
		{
			x-=50;
		}
		else if(key[KEY_W])
		{
			y-=50;
		}
		else if(key[KEY_S])
		{
			y+=50;
		}
		
		dibujar();//funcion que sirve para leer y ejecutar un archivo de txt

		rest(40);
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

void vida()
{
	int combustible=100;
	
}

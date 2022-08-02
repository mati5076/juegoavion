#include <allegro.h>

#include<stdio.h>

#include<stdlib.h>

#include<time.h>

#define MAXCOL 15

#define MAXFIL 20

void init();

void deinit();

char escena[MAXFIL][MAXCOL];

struct bala
{
	int x;
	
	int y;
	
	int bandera;
};

struct Avion{

	struct bala  disparo;

	int mover_der;
	
	int mover_arriba;
	

}jugador1;

struct Enemigo{
	int seguir_derech;
	
	int seguir_arriba;
	
	int size_imgx;
	
	int size_imgy;
}jug2;

void leer()//codigo de ayuda por mi compa�ero francisco
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
	jugador1.disparo.x=200;
	jugador1.disparo.y=450;
	int x1=0;
	int y1=155;
	int x2=200;
	int y2=450;
	int mov,mos;
	int posicion=680;
	//avion 
	jugador1.mover_der=200;
	
	jugador1.mover_arriba=450;
	
	//bala 
	jugador1.disparo.x=200;	
	jugador1.disparo.y=450;
		
	//enemigo 
	srand(time(0));
	
	jug2.seguir_derech=rand()%300;
	
	jug2.seguir_arriba=rand()%460;
	
	jug2.size_imgx=150;
	
	jug2.size_imgy=150;
	
	BITMAP *buffer = create_bitmap(440,680);
	//se declara el bitmap para poder insertar la imagen del avion que usara el usuario
	
	BITMAP *menu = load_bitmap("IMG/menu.bmp",NULL);
	
	BITMAP *avion = load_bitmap("IMG/ask.bmp",NULL); //insertar imagen en la ventana
	
	BITMAP *fondo = load_bitmap("IMG/azul.bml.bmp",NULL); 
	
	BITMAP *bala = load_bitmap("IMG/disp2.bmp",NULL);
	
	BITMAP *pared= load_bitmap("IMG/disp2.bmp",NULL);
	
	BITMAP *enemigo = load_bitmap("IMG/enemigo.bmp",NULL);

	set_window_title("1945");//le da nombre a la ventana 
	
	jugador1.disparo.bandera=0;
	
	while (!key[KEY_ESC]) 
	{
		//////////////////////////////////////////////////////////////////
		
		
		blit(fondo,buffer,0,0,0,0,fondo->w,fondo->h);//deja el fondo estatico y deja sobre poner el personaje 
		
		//avion
		blit(buffer,screen,0,0,0,0,440,680);
		blit(avion,screen,0,0,jugador1.mover_der,jugador1.mover_arriba,avion->w,avion->h);
						
		//enemigo 
		blit(enemigo,screen,0,0,jug2.seguir_derech,jug2.seguir_arriba,enemigo->w,enemigo->h);
		
		blit(bala,screen,0,0,jugador1.disparo.x,jugador1.disparo.y,bala->w,bala->h);	
		
		if(jug2.seguir_derech < jugador1.mover_der+jug2.size_imgx) 
		{
			jug2.seguir_derech+=40;
		}
		if(jug2.seguir_derech > jugador1.mover_der-jug2.size_imgx)
		{
			jug2.seguir_derech-=40;
		}
		if(jug2.seguir_arriba < jugador1.mover_arriba+jug2.size_imgy)
		{
			jug2.seguir_arriba+=40;
		}	
		if(jug2.seguir_arriba > jugador1.mover_arriba-jug2.size_imgy)
		{
			jug2.seguir_arriba-=40;
		}
		if(jugador1.disparo.bandera == 1 )
		{
			jugador1.disparo.y-=60;//esto hace que el disparo ocurra hacia adelante y a su vez hace que aparezca la bala
		}
		if(jugador1.disparo.y < 0-100 )
		{
			jugador1.disparo.bandera=0;
			jugador1.disparo.y=jugador1.mover_arriba;
		}
		if(key[KEY_SPACE])
		{
			jugador1.disparo.bandera = 1;
		}
		if(key[KEY_RIGHT])//teclas de movimiento del avion 
		{
			jugador1.disparo.x+=50;;
			jugador1.mover_der+=50;//hace que se mueva hacia la derecha
		}
		else if(key[KEY_LEFT])
		{
			jugador1.disparo.x-=50;
			jugador1.mover_der-=50;//hace que se mueva hacia la izquierda
		}
		else if(key[KEY_UP])
		{
			jugador1.disparo.y-=50;
			jugador1.mover_arriba-=50;//hace que se mueva hacia arriba , el signo menos es porque allegro tiene invertido las direcciones de arriba y abajo 
		}
		else if(key[KEY_DOWN])
		{
			jugador1.disparo.y+=50;
			jugador1.mover_arriba+=50;
		}
		// "botones de reserva"
		if(key[KEY_D])
		{
			jugador1.mover_der+=50;
		}
		else if(key[KEY_A])
		{
			jugador1.mover_der-=50;
		}
		else if(key[KEY_W])
		{
			jugador1.mover_arriba-=50;
		}
		else if(key[KEY_S])
		{
			jugador1.mover_arriba+=50;
		}
		
		//dibujar();//funcion que sirve para leer y ejecutar un archivo de txt

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

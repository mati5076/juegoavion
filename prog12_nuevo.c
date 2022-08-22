#include <allegro.h>

#include<stdio.h>

#include<stdlib.h>

#include<time.h>

#define MAXCOL 15

#define MAXFIL 20
//logre sacar el fondo , pintando les el fondo de las imagenes con el color azul ya que ese es el color de mi ventana del videojuego

void init();

void deinit();

char escena[MAXFIL][MAXCOL];

void menu()
{
	BITMAP *menu = load_bitmap("IMG/MENU.bmp",NULL);

	while(!key[KEY_ENTER])
	{
		blit(menu,screen,0,0,0,0,menu->w,menu->h);
	}
}

void nombre()
{
	int escribir;
	
	BITMAP *escriba = load_bitmap("IMG/barra_texto.bmp",NULL);
	
	blit(escriba,screen,20,20,0,0,escriba->w,escriba->h);
}

void gameover()
{
	BITMAP *perdida = load_bitmap("IMG/gameover.bmp",NULL);
	while(!key[KEY_Q])
	{
		blit(perdida,screen,0,0,0,0,perdida->w,perdida->h);
	}
}
struct barra
{
	int gastar;
	
	int  reponer;
};

struct bala
{
	int x;
	
	int y;
	
	int bandera;
};

struct Avion{
	
	struct barra combustible;
	
	struct bala  disparo;

	int mover_der;
	
	int mover_arriba;
	

}jugador1;

struct disparar
{
	int autmatico_x;
	
	int automatico_y;
	
	int bandera_enemigo;
};
struct Enemigo{
	
	struct disparar dispara;
	
	int seguir_derech;
	
	int seguir_arriba;
	
	int size_imgx;
	
	int size_imgy;
}jug2;

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

	BITMAP *pared = load_bitmap("IMG/paredd.bmp",NULL);
	
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
	int x1=0;
	int y1=155;
	int x2=200;
	int y2=450;
	int mov,mos;
	int posicion=680;
	//avion 
	jugador1.mover_der=200;
	
	jugador1.mover_arriba=450;
	
	jugador1.disparo.x=200;
	
	jugador1.disparo.y=450;
	// vida 
	jugador1.combustible.gastar=100;
	
	jugador1.combustible.reponer=50;

	//bala 
	jugador1.disparo.x=200;
		
	jugador1.disparo.y=450;
		
	//enemigo 
	srand(time(0));
	
	jug2.seguir_derech=rand()%300;
	
	jug2.seguir_arriba=rand()%460;
	
	jug2.size_imgx=150;
	
	jug2.size_imgy=150;
	//bala  del enemigo
	jug2.dispara.autmatico_x=rand()%200;
	
	jug2.dispara.automatico_y=rand()%450;
	
	
	BITMAP *buffer = create_bitmap(440,680);
	//se declara el bitmap para poder insertar la imagen del avion que usara el usuario
		
	BITMAP *avion = load_bitmap("IMG/ask.bmp",NULL); //insertar imagen en la ventana
	
	BITMAP *fondo = load_bitmap("IMG/azul.bml.bmp",NULL); 
	
	BITMAP *bala = load_bitmap("IMG/disp2.bmp",NULL);
	
	BITMAP *pared= load_bitmap("IMG/disp2.bmp",NULL);
	
	BITMAP *enemigo = load_bitmap("IMG/enemigo.bmp",NULL);
	
	BITMAP *disparo2 = load_bitmap("IMG/enemigdisp1.bmp",NULL);
	//nombre de la ventana 
	set_window_title("1945");//le da nombre a la ventana 
	
	//musica
	if(install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,NULL))//condicional para unstallar la musica
	{
		allegro_message("ERROR AL INICIAR AUDIO",allegro_error);
		return 1;
	}
	
	set_volume(100,100);//volumen de la musica
	
	MIDI *musica_fondo = load_midi("musica/midi.mar.midi");//inserta la cancion 
	
	play_midi(musica_fondo,1);//reproductor de musica
	
	//sonido
	
	SAMPLE *sound = load_wav("musica/sound_bala.wav");
	
	//bandera , se le da valores entre 0 y 1
	jugador1.disparo.bandera=0;		
	
	//bandera del enemigo
	jug2.dispara.bandera_enemigo=0;
	
	menu();

	while (!key[KEY_ESC]) 
	{	
	//////////////////////////////////////////////////////////////////	
		blit(fondo,buffer,0,0,0,0,fondo->w,fondo->h);//deja el fondo estatico y deja sobre poner el personaje 
		
		//avion
		blit(buffer,screen,0,0,0,0,440,680);
		
		draw_sprite(screen,avion,jugador1.mover_der,jugador1.mover_arriba);
		
		//enemigo
		blit(enemigo,screen,0,0,jug2.seguir_derech,jug2.seguir_arriba,enemigo->w,enemigo->h);
		
		//bala jugador
		draw_sprite(screen,bala,jugador1.disparo.x,jugador1.disparo.y);	
		
		//bala enemigo
		draw_sprite(screen,disparo2,jug2.dispara.autmatico_x,jug2.dispara.automatico_y);	
		
		//barra de vida del jugador
		textout_ex(screen,font,"Vida", 100, 30, 0x9999, 0xFFFFFF);
	
		rectfill(screen,40,40,40+jugador1.combustible.gastar,45,0xFFFFFF);
				
		if(jug2.seguir_derech < jugador1.mover_der+jug2.size_imgx) 
		{
			//bala 
			jug2.dispara.autmatico_x+=50;
			//movimiento
			jug2.seguir_derech+=40;
		}
		if(jug2.seguir_derech > jugador1.mover_der-jug2.size_imgx)
		{
			//bala
			jug2.dispara.autmatico_x-=50;
			//movimiento
			jug2.seguir_derech-=40;
		}
		if(jug2.seguir_arriba < jugador1.mover_arriba+jug2.size_imgy)
		{
			//bala
			jug2.dispara.automatico_y+=50;
			//movimiento
			jug2.seguir_arriba+=40;
		}
		if(jug2.seguir_arriba > jugador1.mover_arriba-jug2.size_imgy)
		{
			//bala
			jug2.dispara.automatico_y-=50;
			jug2.seguir_arriba-=40;
		}
		if(jug2.dispara.bandera_enemigo == 1 )
		{
			jug2.dispara.automatico_y-=60;//esto hace que el disparo ocurra hacia adelante y a su vez hace que aparezca la bala
		}
		if(jug2.dispara.automatico_y < 0 )
		{
			//bala del jugador 
			jug2.dispara.bandera_enemigo=0;
			jug2.dispara.automatico_y=jug2.seguir_arriba;
		}
		//jugador del usuario
		
		if(jugador1.disparo.bandera == 1 )
		{
			jugador1.disparo.y-=60;//esto hace que el disparo ocurra hacia adelante y a su vez hace que aparezca la bala
		}
		if(jugador1.disparo.y < 0 )
		{
			//bala del jugador 
			jugador1.disparo.bandera=0;
			jugador1.disparo.y=jugador1.mover_arriba;
		}
		if(key[KEY_SPACE])
		{
			jugador1.disparo.bandera = 1;
			//sonido
			play_sample(sound,100,150,1000,0);
		}
		if(key[KEY_RIGHT] && jugador1.combustible.reponer > 0)//teclas de movimiento del avion 
		{
			jugador1.disparo.x+=50;
			jugador1.mover_der+=50;//hace que se mueva hacia la derecha
			jugador1.combustible.gastar-=0.2;
		}
		else if(key[KEY_LEFT] && jugador1.combustible.reponer > 0)
		{
			jugador1.disparo.x-=50;
			jugador1.mover_der-=50;//hace que se mueva hacia la izquierda
			jugador1.combustible.gastar-=0.2;

		}
		else if(key[KEY_UP] && jugador1.combustible.reponer  > 0)
		{
			jugador1.disparo.y-=50;		
			jugador1.mover_arriba-=50;//hace que se mueva hacia arriba , el signo menos es porque allegro tiene invertido las direcciones de arriba y abajo 
			jugador1.combustible.gastar-=0.2;

		}
		else if(key[KEY_DOWN] && jugador1.combustible.reponer > 0) 
		{
			jugador1.disparo.y+=50;
			jugador1.mover_arriba+=50;
			jugador1.combustible.gastar-=0.2;
		}
		if(jugador1.combustible.gastar == 0)
		{
			nombre();
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

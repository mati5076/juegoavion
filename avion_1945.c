#include <allegro.h>

void init();
void deinit();

int main() {
	init();
	
	int x=200;
	int y=450;
	int x1=0;
	int y1=155;
	
	BITMAP *buffer = create_bitmap(440,580); 

	BITMAP *avion;//se declara el bitmap para poder insertar la imagen del avion que usara el usuario

	avion=load_bitmap("IMG/ask.bmp",NULL); //insertar imagen en la ventana
	
	BITMAP *fondo;//insertar la imagen de fondo 
	
	fondo=load_bitmap("azul.bml.bmp",NULL); 
	
	
	while (!key[KEY_ESC]) // ciclo que ayuda a mover el avion y deja la imagen de fondo 
	{
		blit(fondo,buffer,0,0,0,0,fondo->w,fondo->h);

		blit(fondo,screen,0,0,x1,y1,440,680);
		
		//avion
		
		blit(buffer,screen,0,0,0,0,700,600);
		
		blit(avion,screen,0,0,x,y,100,112);

		if(key[KEY_RIGHT])//teclas de movimiento del avion 
		{
			x+=50;
			blit(buffer,screen,0,0,0,0,440,580);
			blit(avion,screen,0,0,x,y,100,112);
		}
		else if(key[KEY_LEFT])
		{
			x-=50;
			blit(buffer,screen,0,0,0,0,700,600);
			blit(avion,screen,0,0,x,y,100,112);
		}
		else if(key[KEY_UP])
		{
			y-=50;
			blit(buffer,screen,0,0,0,0,700,600);
			blit(avion,screen,0,0,x,y,100,112);
		}
		else if(key[KEY_DOWN])
		{
			y+=50;
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

	deinit();
	return 0;
}
END_OF_MAIN()

void init() {
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}

	install_timer();
	install_keyboard();
	install_mouse();
	/* add other initializations here */
}

void deinit() {
	clear_keybuf();
	/* add other deinitializations here */
}

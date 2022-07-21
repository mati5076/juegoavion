#include<stdio.h>

BITMAP *lienzo;

void Bala();

struct Bala
{
	
int x;

int y;	

BITMAP *sprite;

}bala;

void Bala(int x,int y)
{
	BITMAP *sprite;
	
	sprite = load_bitmap("bala",NULL);
	
	BITMAP *buffer = create_bitmap(440,580);
	
	while(!key[KEY_ESC])

	if(key[KEY_SPACE])
	{
		blit(buffer,screen,0,0,0,0,700,600);
		
		blit(sprite,screen,0,0,x,y,sprite->w,sprite->h);
	}
	draw_sprite(lienzo,sprite,x,y);
}

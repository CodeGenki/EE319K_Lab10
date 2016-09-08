//Collision.c
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "ST7735.h"
#include "Movement.h"
#include "Sound.h"

enum{STAND, STANDL, RUN, RUNL, JUMP, JUMPFL, JUMPL, JUMPR, MELEE, MELEEL, PROJ, PROJL, DEAD};
enum{NULL, LNULL, SHOOT, SHOOTL};	//projectile actions
enum{PIKACHU, LUCARIO};
extern player_t Player[2];
extern player_t Enemy[2];
extern uint8_t P1;
extern uint8_t P2;
extern const uint16_t thunder0;
extern uint32_t Index;
extern uint32_t counter;
// *********************** Attack Hit boxes **************************
uint16_t PA1x;
uint16_t PA1y;
uint16_t PA2x;
uint16_t PA2y;
uint16_t PA3x;
uint16_t PA3y;
uint16_t PA4x;
uint16_t PA4y;

uint16_t EA1x;
uint16_t EA1y;
uint16_t EA2x;
uint16_t EA2y;
uint16_t EA3x;
uint16_t EA3y;
uint16_t EA4x;
uint16_t EA4y;

// *********************** Player Hit boxes ****************************
uint16_t PH1x;
uint16_t PH3x;
uint16_t PH4x;
uint16_t PH6x;
uint16_t PH7x;
uint16_t PH1y;
uint16_t PH3y;
uint16_t PH4y;
uint16_t PH6y;
uint16_t PH7y;

uint16_t EH1x;
uint16_t EH3x;
uint16_t EH4x;
uint16_t EH6x;
uint16_t EH7x;
uint16_t EH1y;
uint16_t EH3y;
uint16_t EH4y;
uint16_t EH6y;
uint16_t EH7y;

//returns a 1 if collision is detected
//returns a 2 if critical hit
uint8_t DetectCollision(player_t sprite, player_t enemy){
	uint8_t hit = 0;
	
	// Set up hit boxes for player
	PH1x = sprite.x + 3;
	PH1y = sprite.y - sprite.h + 5;
	PH3x = sprite.x + 3;
	PH3y = sprite.y - sprite.h/2 + 2;
	PH4x = sprite.x + sprite.w/2;
	PH4y = sprite.y - sprite.h/2;
	PH6x = sprite.x + sprite.w - 5;
	PH6y = sprite.y - 3;
	PH7x = sprite.x + sprite.w - 5;
	PH7y = sprite.y - sprite.h/2 + 2;
	
	EH1x = enemy.x + 3;
	EH1y = enemy.y - enemy.h + 5;
	EH3x = enemy.x + 3;
	EH3y = enemy.y - enemy.h/2;
	EH4x = enemy.x + enemy.w/2;
	EH4y = enemy.y - enemy.h/2;
	EH6x = enemy.x + enemy.w - 5;
	EH6y = enemy.y - 3;
	EH7x = enemy.x + enemy.w - 5;
	EH7y = enemy.y - enemy.h/2;
	ST7735_FillRect(PH7x, PH7y, 2, 2, 0x07E0);
	ST7735_FillRect(PH1x, PH1y, 2, 2, 0x07E0);
	ST7735_FillRect(PH3x, PH3y, 2, 2, 0x07E0);
	ST7735_FillRect(PH4x, PH4y, 2, 2, 0x07E0);
	ST7735_FillRect(PH6x, PH6y, 2, 2, 0x07E0);
	
	ST7735_FillRect(EH7x, EH7y, 2, 2, 0x07E0);
	ST7735_FillRect(EH1x, EH1y, 2, 2, 0x07E0);
	ST7735_FillRect(EH3x, EH3y, 2, 2, 0x07E0);
	ST7735_FillRect(EH4x, EH4y, 2, 2, 0x07E0);
	ST7735_FillRect(EH6x, EH6y, 2, 2, 0x07E0);
	
	//projectile hitboxes
	PA1x = sprite.px + 2;
	PA1y = sprite.py - sprite.ph + 3;
	PA2x = sprite.px + 2;
	PA2y = sprite.py - sprite.ph/2;
	PA3x = sprite.px + sprite.pw - 2;
	PA3y = sprite.py - sprite.ph/2;
	PA4x = sprite.px + sprite.pw - 2;
	PA4y = sprite.py - 2;
	
	EA1x = enemy.px + 2;
	EA1y = enemy.py - enemy.ph + 3;
	EA2x = enemy.px + 2;
	EA2y = enemy.py - enemy.ph/2;
	EA3x = enemy.px + enemy.pw - 2;
	EA3y = enemy.py - enemy.ph/2;
	EA4x = enemy.px + enemy.pw - 2;
	EA4y = enemy.py - 2;
	//Check collision
	if(sprite.action == MELEE){
		if((PH7x == EH4x)&&(PH7y == EH4y)){
			enemy.hp -= sprite.dmg + (sprite.dmg/2);
			if((enemy.x > 4)&&(enemy.x < (159-enemy.w-4))){
				ST7735_FillRect(enemy.x, enemy.y-enemy.h-3, enemy.w, 7, 0xEEF8);
				enemy.x += 3;
			}
			hit = 1;		//critical hit!
		}
		else if(((PH7x >= EH1x)&&(PH7x <= EH6x))&&((PH7y >= EH1y)&&(PH7y <= EH6y))){
			enemy.hp -= sprite.dmg;	//damage = 1.5*base damage
			enemy.action = STANDL;		//cancel enemy's attack/movement and force to face you
			if((enemy.x > 4)&&(enemy.x < (159-enemy.w-4))){
				ST7735_FillRect(enemy.x, enemy.y-enemy.h-3, enemy.w, 7, 0xEEF8);
				enemy.x += 3;
			}
			hit = 1;
		}
	}
	else if(sprite.action == MELEEL){
		if((PH3x == EH4x)&&(PH3y == EH4y)){
			enemy.hp -= sprite.dmg + (sprite.dmg/2);		//damage = 1.5*base damage
			if((enemy.x > 4)&&(enemy.x < (159-enemy.w-4))){
				ST7735_FillRect(enemy.x, enemy.y-enemy.h-3, enemy.w, 7, 0xEEF8);
				enemy.x -= 3;
			}
			hit = 1;
		}
		else if(((PH3x >= EH1x)&&(PH3x <= EH6x))&&((PH3y >= EH1y)&&(PH3y <= EH6y))){
			enemy.hp -= sprite.dmg;
			enemy.action = STAND;	//cancel enemy's attack/movement and force to face you
			if((enemy.x > 4)&&(enemy.x < (159-enemy.w-4))){
				ST7735_FillRect(enemy.x, enemy.y-enemy.h-3, enemy.w, 7, 0xEEF8);
				enemy.x -= 3;
			}
			hit = 1;
		}
	}
	else if(sprite.paction == SHOOT){
		if(((PA3x >= EH1x)&&(PA3x <= EH6x))&&((PA3y >= EH1y)&&(PA3y <= EH6y))){
			enemy.hp -= sprite.pdmg;
			enemy.action = STANDL;
			//sprite.paction = NULL;
			if((enemy.x > 5)&&(enemy.x < (159-enemy.w-5))){
				ST7735_FillRect(enemy.x, enemy.y-enemy.h-3, enemy.w, 7, 0xEEF8);
				enemy.x += 5;
			}
			hit = 2;
			/*
			if(sprite.poke == PIKACHU){
				Sound_Stop();
				Sound_Init(7256);
				Sound_Thunder();
			}
			else if(sprite.poke == LUCARIO){
				Sound_Stop();
				Sound_Init(7256);
				Sound_Hit();
			}
			*/
		}
	}
	else if(sprite.paction == SHOOTL){
		if(((PA2x >= EH1x)&&(PA2x <= EH6x))&&((PA2y >= EH1y)&&(PA2y <= EH6y))){
			enemy.hp -= sprite.pdmg;
			enemy.action = STAND;
			//sprite.paction = NULL;
			sprite.pImage = &thunder0;
			sprite.pw = 1;
			sprite.ph = 1;
			sprite.px = 2;
			sprite.py = 0;
			if((enemy.x > 5)&&(enemy.x < (159-enemy.w-5))){
				ST7735_FillRect(enemy.x, enemy.y-enemy.h-3, enemy.w, 7, 0xEEF8);
				enemy.x -= 5;
			}
			hit = 2;
			/*
			if(sprite.poke == PIKACHU){
				Sound_Stop();
				Sound_Init(7256);
				Sound_Thunder();
			}
			else if(sprite.poke == LUCARIO){
				Sound_Stop();
				Sound_Init(7256);
				Sound_Hit();
			}
			*/
		}
	}
	
	
	//ENEMY ATTACK *********************************************
		if(enemy.action == MELEE){
		if((EH7x == PH4x)&&(EH7y == PH4y)){
			sprite.hp -= enemy.dmg + (enemy.dmg/2);	
			if((sprite.x > 3)&&(sprite.x < (159-enemy.w-3))){
				ST7735_FillRect(sprite.x, sprite.y-sprite.h-3, sprite.w, 7, 0xEEF8);
				sprite.x += 3;
			}
			hit = 2;		//critical hit!
		}
		else if(((EH7x >= PH1x)&&(EH7x <= PH6x))&&((EH7y >= PH1y)&&(EH7y <= PH6y))){
			sprite.hp -= enemy.dmg;	
			if((sprite.action == JUMP)||(sprite.action == JUMPR)||(sprite.action == JUMPL))
				sprite.y = 104;
			sprite.action = STANDL;
			if((sprite.x > 3)&&(sprite.x < (159-enemy.w-3))){		
				ST7735_FillRect(sprite.x, sprite.y-sprite.h-3, sprite.w, 7, 0xEEF8);
				sprite.x += 3;
			}
			hit = 1;
		}
	}
	else if(enemy.action == MELEEL){
		if((EH3x == PH4x)&&(EH3y == PH4y)){
			sprite.hp -= enemy.dmg + (enemy.dmg/2);		//damage = 1.5*base damage
			if((sprite.x > 3)&&(sprite.x < (159-enemy.w-3))){
				ST7735_FillRect(sprite.x, sprite.y-sprite.h-3, sprite.w, 7, 0xEEF8);
				sprite.x -= 3;
			}
			hit = 2;
		}
		else if(((EH3x >= PH1x)&&(EH3x <= PH6x))&&((EH3y >= PH1y)&&(EH3y <= PH6y))){
			sprite.hp -= enemy.dmg;
			if((sprite.action == JUMP)||(sprite.action == JUMPR)||(sprite.action == JUMPL))
				sprite.y = 104;
			sprite.action = STAND;	//cancel enemy's attack/movement and force to face you
			if((sprite.x > 3)&&(sprite.x < (159-enemy.w-3))){
				ST7735_FillRect(sprite.x, sprite.y-sprite.h-5, sprite.w, 10, 0xEEF8);
				sprite.x -= 3;
			}
			hit = 1;
		}
	}
	else if(enemy.paction == SHOOT){
		if(((EA3x >= PH1x)&&(EA3x <= PH6x))&&((EA3y >= PH1y)&&(EA3y <= PH6y))){
			sprite.hp -= enemy.pdmg;
			if((sprite.action == JUMP)||(sprite.action == JUMPR)||(sprite.action == JUMPL))
				sprite.y = 104;
			sprite.action = STANDL;
			//enemy.paction = NULL;
			if((sprite.x > 5)&&(sprite.x < (159-enemy.w-5))){
				ST7735_FillRect(sprite.x, sprite.y-sprite.h-5, sprite.w, 10, 0xEEF8);
				sprite.x += 5;
			}
			hit = 2;
			/*
			if(sprite.poke == PIKACHU){
				Sound_Stop();
				Sound_Init(7256);
				Sound_Thunder();
			}
			else if(sprite.poke == LUCARIO){
				Sound_Stop();
				Sound_Init(7256);
				Sound_Hit();
			}
			*/
		}
	}
	else if(enemy.paction == SHOOTL){
		if(((EA2x >= PH1x)&&(EA2x <= PH6x))&&((EA2y >= PH1y)&&(EA2y <= PH6y))){
			sprite.hp -= enemy.pdmg;
			if((sprite.action == JUMP)||(sprite.action == JUMPR)||(sprite.action == JUMPL))
				sprite.y = 104;
			sprite.action = STAND;
			//enemy.paction = NULL;
			if((sprite.x > 5)&&(sprite.x < (159-enemy.w-5))){
				ST7735_FillRect(sprite.x, sprite.y-sprite.h-3, sprite.w, 7, 0xEEF8);
				sprite.x -= 5;
			}
			hit = 2;
			/*
			if(sprite.poke == PIKACHU){
				Sound_Stop();
				Sound_Init(7256);
				Sound_Thunder();
			}
			else if(sprite.poke == LUCARIO){
				Sound_Stop();
				Sound_Init(7256);
				Sound_Hit();
			}
			*/
		}
	}
	
	
	Player[P1] = sprite;
	Enemy[P2] = enemy;
	if(sprite.hp >= 0)
		Player[P1].hp = sprite.hp;
	else if(sprite.hp < 0){
		Player[P1].hp = 0;
		Player[P1].action = DEAD;
	}
	
	if(enemy.hp >= 0)
		Enemy[P2].hp = enemy.hp;
	else if(enemy.hp < 0){
		Enemy[P2].hp = 0;
		Enemy[P2].action = DEAD;
	}
	/*
	if(hit == 2){
		Sound_Init(14512);
		Sound_Battle1();
		Sound_Resume();
	}
	*/
	return(hit);
}


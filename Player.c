//Player.c
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "Movement.h"
#include "ST7735.h"

enum{STAND, STANDL, RUN, RUNL, JUMP, JUMPFL, JUMPL, JUMPR, MELEE, MELEEL, PROJ, PROJL, DEAD};
enum{NULL, LNULL, SHOOT, SHOOTL};	//projectile actions
enum{PIKACHU, LUCARIO};
extern uint8_t P1;
extern uint8_t P2;
extern uint8_t disp1;
extern player_t Player[2];
extern player_t Enemy[2];
extern const unsigned short stand1x;
extern const unsigned short lstand1;
extern const unsigned short thunder0;

extern const unsigned short standing2;
extern const unsigned short lstanding2;
extern const unsigned short sphere;

uint8_t input;
//uint8_t in2;
uint16_t CAct;
uint16_t PAct;
uint8_t refl = 0;
uint8_t pkmn;

//Periodic Function
//Gets Player's input and changes the player's state based on input
void Player_Update(void){
	//assuming buttons jump(pe0), slidepot(pe1), right(pe2), left(pe3), melee attack(pe4), ranged attack(pe5)
	input = (GPIO_PORTE_DATA_R&0x3F);
	//in2 = GPIO_PORTF_DATA_R&0x11;
	CAct = Player[P1].action;
	PAct = Player[P1].paction;
	pkmn = Player[P1].poke;
	if((PAct == SHOOT)||(PAct == SHOOTL)){
		Player[P1] = Atk2(Player[P1], Enemy[P2]);
	}
	else if(PAct == NULL){
		Player[P1].pImage = &thunder0;		//just a pixel
	}
	if((CAct == STAND)||(CAct == STANDL)||(CAct == RUN)||(CAct == RUNL)){	//Any input can be used if standing or just running
		if(Player[P1].y < 104)		//jump fix
			Player[P1].y = 104;
		if(input == 0x00){		//No buttons pressed
		//if(in2 == 0x00){		//No buttons pressed
			if((CAct == STAND)||(CAct == RUN)){		//face right
				Player[P1].action = STAND;
				if(Player[P1].poke == PIKACHU){
					Player[P1].image = &stand1x;
					Player[P1].w = 34;
					Player[P1].h = 31;
				}
				else if(Player[P1].poke == LUCARIO){
					Player[P1].image = &standing2;
					Player[P1].w = 42;
					Player[P2].h = 49;
				}
				//may or may not need these for lucario
				ST7735_FillRect((Player[P1].x + Player[P1].w), (Player[P1].y-Player[P1].h), 8, Player[P1].h, 0xEEF8);
				ST7735_FillRect((Player[P1].x + 2), (Player[P1].y-Player[P1].h-2), 8, 4, 0xEEF8);
			}
			else{																	//face left
				Player[P1].action = STANDL;
				if(pkmn == PIKACHU){
					Player[P1].image = &lstand1;
					Player[P1].w = 34;
					Player[P1].h = 31;
				}
				else if(pkmn == LUCARIO){
					Player[P1].image = &lstanding2;
					Player[P1].w = 42;
					Player[P1].h = 49;
				}
				ST7735_FillRect((Player[P1].x + Player[P1].w), (Player[P1].y-Player[P1].h), 8, Player[P1].h, 0xEEF8);
				ST7735_FillRect((Player[P1].x + Player[P1].w - 8), (Player[P1].y-Player[P1].h-2), 6, 4, 0xEEF8);
			}
		}
		else if(input == 0x02){	//right button pressed (PE2)
		//else if(in2 == 0x10){
			if(Player[P1].x < (159-Player[P1].w)){
				Player[P1] = MoveR(Player[P1]);
				Player[P1].action = RUN;
				ST7735_FillRect((Player[P1].x + Player[P1].w), (Player[P1].y-Player[P1].h), 8, Player[P1].h, 0xEEF8);
			}
		}
		else if(input == 0x08){	//left button pressed (PE3)
		//else if(in2 == 0x01){
			if(Player[P1].x > 0){
				Player[P1] = MoveL(Player[P1]);
				Player[P1].action = RUNL;
				ST7735_FillRect((Player[P1].x + Player[P1].w), (Player[P1].y-Player[P1].h), 8, Player[P1].h, 0xEEF8);
			}
		}
		else if((input == 0x10)||(input == 0x12)||(input == 0x18)){	//atk button pressed (PE4)
			//Meelee Attack here
			if((CAct == RUN)||(CAct == STAND)){
				if(Player[P1].x < (159 - Player[P1].w)){
					Player[P1] = Atk1(Player[P1], Enemy[P2]);
					Player[P1].action = MELEE;
				}
			}
			else{
				if(Player[P1].x > 0){
					Player[P1] = Atk1(Player[P1], Enemy[P2]);
					Player[P1].action = MELEEL;
				}
			}
		}
		else if((input == 0x20)||(input == 0x22)||(input == 0x28)){	//proj button pressed (PE5)
			//Projectile Attack here
			if((CAct == RUN)||(CAct == STAND)){
				if(Player[P1].x < (159 - 27)){
					Player[P1] = Atk2(Player[P1], Enemy[P2]);
					Player[P1].action = PROJ;
				}
			}
			else{
				if(Player[P1].x > 20){
					Player[P1] = Atk2(Player[P1], Enemy[P2]);
					Player[P1].action = PROJL;
				}
			}
		}
		else if(input == 0x01){	//jump button pressed (PE0)
		//else if(in2 == 0x01){
			if((Player[P1].action == RUN)||(Player[P1].action == STAND))
				Player[P1].action = JUMP;				//jump facing the right
			else
				Player[P1].action = JUMPFL;			//jump facing the left
			Player[P1] = Jump(Player[P1]);
		}
		else if(input == 0x03){	//Jump + right pressed
			refl = 0;
			if(Player[P1].x < (159 - Player[P1].w)){
				Player[P1].action = JUMPR;
				Player[P1] = MoveR(Player[P1]);
				Player[P1] = Jump(Player[P1]);
			}
			ST7735_FillRect((Player[P1].x), 102, Player[P1].w, 3, 0xEEF8);
		}
		else if(input == 0x09){	//Jump + left pressed
			refl = 0;
			if(Player[P1].x > 0){
				Player[P1].action = JUMPL;
				Player[P1] = MoveL(Player[P1]);
				Player[P1] = Jump(Player[P1]);
			}
			ST7735_FillRect((Player[P1].x), 102, Player[P1].w, 3, 0xEEF8);
		}
	}
	// *** if user is in process of an action that cannot be canceled: ***
	else {	
		if((CAct == JUMP)||(CAct == JUMPFL)){			//if in process of jumping straight up
			Player[P1] = Jump(Player[P1]);
		}
		else if(CAct == JUMPR){										//in process of jumping right
			if((Player[P1].x + 1) >= (159 - Player[P1].w)){
				refl = 1;
			}
			if(refl == 1)
				Player[P1] = MoveL(Player[P1]);
			else
				Player[P1] = MoveR(Player[P1]);
			Player[P1] = Jump(Player[P1]);
		}
		else if(CAct == JUMPL){										//in process of jumping left
			if((Player[P1].x + 1) <= 0)
				refl = 1;
			if(refl == 1)
				Player[P1] = MoveR(Player[P1]);
			else
				Player[P1] = MoveL(Player[P1]);
			Player[P1] = Jump(Player[P1]);
		}
		else if((CAct == MELEE)||(CAct == MELEEL)){									//in process of right melee atk
			if(((Player[P1].x + 1) < (159 - Player[P1].w))&&((Player[P1].x + 1) > 0))
				Player[P1] = Atk1(Player[P1], Enemy[P2]);
			else
				Player[P1].action = STAND;
		}
		else if((CAct == PROJ)||(CAct == PROJL)){
			Player[P1] = Atk2(Player[P1], Enemy[P2]);
		}
		else if(CAct == DEAD){
			Player[P1] = Dead(Player[P1]);
		}
	}
	disp1 = 1; //Player semaphore is set
}




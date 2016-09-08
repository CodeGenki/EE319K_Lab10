//Enemy.c
//Uses Player's position to determine its next move

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "Movement.h"
#include "ST7735.h"
#include "Random.h"

enum{STAND, STANDL, RUN, RUNL, JUMP, JUMPFL, JUMPL, JUMPR, MELEE, MELEEL, PROJ, PROJL, DEAD};
enum{NULL, LNULL, SHOOT, SHOOTL};	//projectile actions
enum{PIKACHU, LUCARIO};
extern uint8_t P1;
extern uint8_t P2;
extern uint8_t disp2;
extern player_t Player[2];
extern player_t Enemy[2];
extern const unsigned short stand1x;
extern const unsigned short lstand1;
extern const unsigned short thunder0;
extern const unsigned short standing2;
extern const unsigned short lstanding2;
extern const unsigned short sphere;
uint16_t EAct;
uint8_t EPAct;
int32_t dist;
int32_t negd;
uint32_t random1;
uint8_t epkmn;
uint8_t erefl;
void Enemy_Update(void){
	dist = Enemy[P2].x - Player[P1].x;
	negd = dist*(-1);
	EAct = Enemy[P2].action;
	EPAct = Enemy[P2].paction;
	epkmn = Enemy[P2].poke;
	if((EPAct == SHOOT)||(EPAct == SHOOTL)){
		Enemy[P2] = Atk2(Enemy[P2], Player[P1]);
	}
	else if(EAct == NULL){
		Enemy[P2].pImage = &thunder0;
	}
	if((EAct == STAND)||(EAct == STANDL)||(EAct == RUN)||(EAct == RUNL)){
		if(Enemy[P2].y < 104)		//jump fix
			Enemy[P2].y = 104;
		if(dist > 0){	//standing to the right of player
			if(dist > 45){
				random1 = Random()%5;
				if(random1 == 0){
					if((EAct == STAND)||(EAct == RUN)){		//face right
						Enemy[P2].action = STAND;
						if(Enemy[P2].poke == PIKACHU){
							Enemy[P2].image = &stand1x;
							Enemy[P2].w = 34;
							Enemy[P2].h = 31;
						}
						else if(Enemy[P2].poke == LUCARIO){
							Enemy[P2].image = &standing2;
							Enemy[P2].w = 42;
							Enemy[P2].h = 49;
						}
						//may or may not need these for lucario
						ST7735_FillRect((Enemy[P2].x + Enemy[P2].w), (Enemy[P2].y-Enemy[P2].h), 8, Enemy[P2].h, 0xEEF8);
						ST7735_FillRect((Enemy[P2].x + 2), (Enemy[P2].y-Enemy[P2].h-2), 8, 4, 0xEEF8);
					}
					else{																	//face left
						Enemy[P2].action = STANDL;
						if(epkmn == PIKACHU){
							Enemy[P2].image = &lstand1;
							Enemy[P2].w = 34;
							Enemy[P2].h = 31;
						}
						else if(epkmn == LUCARIO){
							Enemy[P2].image = &lstanding2;
							Enemy[P2].w = 42;
							Enemy[P2].h = 49;
						}
						ST7735_FillRect((Enemy[P2].x + Enemy[P2].w), (Enemy[P2].y-Enemy[P2].h), 8, Enemy[P2].h, 0xEEF8);
						ST7735_FillRect((Enemy[P2].x + Enemy[P2].w - 8), (Enemy[P2].y-Enemy[P2].h-2), 6, 4, 0xEEF8);
					}
				}
				else if(random1 == 1){
					if(Enemy[P2].x > 0){
						Enemy[P2] = MoveL(Enemy[P2]);
						Enemy[P2].action = RUNL;
						ST7735_FillRect((Enemy[P2].x + Enemy[P2].w), (Enemy[P2].y-Enemy[P2].h), 8, Enemy[P2].h, 0xEEF8);
					}
				}
				else if(random1 == 2){
					if(Enemy[P2].x > 0){
						Enemy[P2] = Atk1(Enemy[P2], Player[P1]);
						Enemy[P2].action = MELEEL;
					}
				}
				else if(random1 == 3){
		//			if(Enemy[P2].x > 20){
		//				Enemy[P2] = Atk2(Enemy[P2], Player[P1]);
		//				Enemy[P2].action = PROJL;
		//			}
				}
				else{
					erefl = 0;
					if(Enemy[P2].x > 0){
						Enemy[P2].action = JUMPL;
						Enemy[P2] = MoveL(Enemy[P2]);
						Enemy[P2] = Jump(Enemy[P2]);
					}
					ST7735_FillRect((Enemy[P2].x), 102, Enemy[P2].w, 3, 0xEEF8);
				}
			}
			else if((dist >= 12)&&(dist <= 45)){
				random1 = Random()%4;
				if(random1 == 0){
					if((EAct == STAND)||(EAct == RUN)){		//face right
						Enemy[P2].action = STAND;
						if(Enemy[P2].poke == PIKACHU){
							Enemy[P2].image = &stand1x;
							Enemy[P2].w = 34;
							Enemy[P2].h = 31;
						}
						else if(Enemy[P2].poke == LUCARIO){
							Enemy[P2].image = &standing2;
							Enemy[P2].w = 42;
							Enemy[P2].h = 49;
						}
						//may or may not need these for lucario
						ST7735_FillRect((Enemy[P2].x + Enemy[P2].w), (Enemy[P2].y-Enemy[P2].h), 8, Enemy[P2].h, 0xEEF8);
						ST7735_FillRect((Enemy[P2].x + 2), (Enemy[P2].y-Enemy[P2].h-2), 8, 4, 0xEEF8);
					}
					else{																	//face left
						Enemy[P2].action = STANDL;
						if(epkmn == PIKACHU){
							Enemy[P2].image = &lstand1;
							Enemy[P2].w = 34;
							Enemy[P2].h = 31;
						}
						else if(epkmn == LUCARIO){
							Enemy[P2].image = &lstanding2;
							Enemy[P2].w = 42;
							Enemy[P2].h = 49;
						}
						ST7735_FillRect((Enemy[P2].x + Enemy[P2].w), (Enemy[P2].y-Enemy[P2].h), 8, Enemy[P2].h, 0xEEF8);
						ST7735_FillRect((Enemy[P2].x + Enemy[P2].w - 8), (Enemy[P2].y-Enemy[P2].h-2), 6, 4, 0xEEF8);
					}
				}
				else if(random1 == 1){
					if(Enemy[P2].x > 0){
						Enemy[P2] = MoveL(Enemy[P2]);
						Enemy[P2].action = RUNL;
						ST7735_FillRect((Enemy[P2].x + Enemy[P2].w), (Enemy[P2].y-Enemy[P2].h), 8, Enemy[P2].h, 0xEEF8);
					}
				}
				else if(random1 == 2){
					if(Enemy[P2].x > 0){
						Enemy[P2] = Atk1(Enemy[P2], Player[P1]);
						Enemy[P2].action = MELEEL;
					}
				}
				else if(random1 == 3){
		//			if(Enemy[P2].x > 20){
		//				Enemy[P2] = Atk2(Enemy[P2], Player[P1]);
		//				Enemy[P2].action = PROJL;
		//			}
				}
			}
			else if((dist >= 0)&&(dist < 12)){
				random1 = Random()%5;
				if(random1 == 0){
					if((EAct == STAND)||(EAct == RUN)){		//face right
						Enemy[P2].action = STAND;
						if(Enemy[P2].poke == PIKACHU){
							Enemy[P2].image = &stand1x;
							Enemy[P2].w = 34;
							Enemy[P2].h = 31;
						}
						else if(Enemy[P2].poke == LUCARIO){
							Enemy[P2].image = &standing2;
							Enemy[P2].w = 42;
							Enemy[P2].h = 49;
						}
						//may or may not need these for lucario
						ST7735_FillRect((Enemy[P2].x + Enemy[P2].w), (Enemy[P2].y-Enemy[P2].h), 8, Enemy[P2].h, 0xEEF8);
						ST7735_FillRect((Enemy[P2].x + 2), (Enemy[P2].y-Enemy[P2].h-2), 8, 4, 0xEEF8);
					}
					else{																	//face left
						Enemy[P2].action = STANDL;
						if(epkmn == PIKACHU){
							Enemy[P2].image = &lstand1;
							Enemy[P2].w = 34;
							Enemy[P2].h = 31;
						}
						else if(epkmn == LUCARIO){
							Enemy[P2].image = &lstanding2;
							Enemy[P2].w = 42;
							Enemy[P2].h = 49;
						}
						ST7735_FillRect((Enemy[P2].x + Enemy[P2].w), (Enemy[P2].y-Enemy[P2].h), 8, Enemy[P2].h, 0xEEF8);
						ST7735_FillRect((Enemy[P2].x + Enemy[P2].w - 8), (Enemy[P2].y-Enemy[P2].h-2), 6, 4, 0xEEF8);
					}
				}
				else if(random1 == 1){
					if(Enemy[P2].x > 0){
						Enemy[P2] = MoveL(Enemy[P2]);
						Enemy[P2].action = RUNL;
						ST7735_FillRect((Enemy[P2].x + Enemy[P2].w), (Enemy[P2].y-Enemy[P2].h), 8, Enemy[P2].h, 0xEEF8);
					}
				}
				else if(random1 == 2){
					if(Enemy[P2].x > 0){
						Enemy[P2] = Atk1(Enemy[P2], Player[P1]);
						Enemy[P2].action = MELEEL;
					}
				}
				else if(random1 == 3){
					if(Enemy[P2].x < (159-Enemy[P2].w)){
						Enemy[P2] = MoveR(Enemy[P2]);
						Enemy[P2].action = RUN;
						ST7735_FillRect((Enemy[P2].x + Enemy[P2].w), (Enemy[P2].y-Enemy[P2].h), 8, Enemy[P2].h, 0xEEF8);
					}
				}
				else{
					erefl = 0;
					if(Enemy[P2].x < (159 - Enemy[P2].w)){
						Enemy[P2].action = JUMPR;
						Enemy[P2] = MoveR(Enemy[P2]);
						Enemy[P2] = Jump(Enemy[P2]);
					}
					ST7735_FillRect((Enemy[P2].x), 102, Enemy[P2].w, 3, 0xEEF8);
				}
			}
		}
		else if(dist < 0){
			if(negd > 45){
				random1 = Random()%5;
				if(random1 == 0){
					if((EAct == STAND)||(EAct == RUN)){		//face right
						Enemy[P2].action = STAND;
						if(Enemy[P2].poke == PIKACHU){
							Enemy[P2].image = &stand1x;
							Enemy[P2].w = 34;
							Enemy[P2].h = 31;
						}
						else if(Enemy[P2].poke == LUCARIO){
							Enemy[P2].image = &standing2;
							Enemy[P2].w = 42;
							Enemy[P2].h = 49;
						}
						//may or may not need these for lucario
						ST7735_FillRect((Enemy[P2].x + Enemy[P2].w), (Enemy[P2].y-Enemy[P2].h), 8, Enemy[P2].h, 0xEEF8);
						ST7735_FillRect((Enemy[P2].x + 2), (Enemy[P2].y-Enemy[P2].h-2), 8, 4, 0xEEF8);
					}
					else{																	//face left
						Enemy[P2].action = STANDL;
						if(epkmn == PIKACHU){
							Enemy[P2].image = &lstand1;
							Enemy[P2].w = 34;
							Enemy[P2].h = 31;
						}
						else if(epkmn == LUCARIO){
							Enemy[P2].image = &lstanding2;
							Enemy[P2].w = 42;
							Enemy[P2].h = 49;
						}
						ST7735_FillRect((Enemy[P2].x + Enemy[P2].w), (Enemy[P2].y-Enemy[P2].h), 8, Enemy[P2].h, 0xEEF8);
						ST7735_FillRect((Enemy[P2].x + Enemy[P2].w - 8), (Enemy[P2].y-Enemy[P2].h-2), 6, 4, 0xEEF8);
					}
				}
				else if(random1 == 1){		
					if(Enemy[P2].x < (159-Enemy[P2].w)){
						Enemy[P2] = MoveR(Enemy[P2]);
						Enemy[P2].action = RUN;
						ST7735_FillRect((Enemy[P2].x + Enemy[P2].w), (Enemy[P2].y-Enemy[P2].h), 8, Enemy[P2].h, 0xEEF8);
					}
				}
				else if(random1 == 2){
					if(Enemy[P2].x < (159 - Enemy[P2].w)){
						Enemy[P2] = Atk1(Enemy[P2], Player[P1]);
						Enemy[P2].action = MELEE;
					}
				}
				else if(random1 == 3){
		//			if(Enemy[P2].x < (159 - 27)){
		//				Enemy[P2] = Atk2(Enemy[P2], Player[P1]);
		//				Enemy[P2].action = PROJ;
		//			}
				}
				else{
					erefl = 0;
					if(Enemy[P2].x < (159 - Enemy[P2].w)){
						Enemy[P2].action = JUMPR;
						Enemy[P2] = MoveR(Enemy[P2]);
						Enemy[P2] = Jump(Enemy[P2]);
					}
					ST7735_FillRect((Enemy[P2].x), 102, Enemy[P2].w, 3, 0xEEF8);
				}
			}
			else if((negd >= 12)&&(negd <= 45)){
				random1 = Random()%4;
				if(random1 == 0){
					if((EAct == STAND)||(EAct == RUN)){		//face right
						Enemy[P2].action = STAND;
						if(Enemy[P2].poke == PIKACHU){
							Enemy[P2].image = &stand1x;
							Enemy[P2].w = 34;
							Enemy[P2].h = 31;
						}
						else if(Enemy[P2].poke == LUCARIO){
							Enemy[P2].image = &standing2;
							Enemy[P2].w = 42;
							Enemy[P2].h = 49;
						}
						//may or may not need these for lucario
						ST7735_FillRect((Enemy[P2].x + Enemy[P2].w), (Enemy[P2].y-Enemy[P2].h), 8, Enemy[P2].h, 0xEEF8);
						ST7735_FillRect((Enemy[P2].x + 2), (Enemy[P2].y-Enemy[P2].h-2), 8, 4, 0xEEF8);
					}
					else{																	//face left
						Enemy[P2].action = STANDL;
						if(epkmn == PIKACHU){
							Enemy[P2].image = &lstand1;
							Enemy[P2].w = 34;
							Enemy[P2].h = 31;
						}
						else if(epkmn == LUCARIO){
							Enemy[P2].image = &lstanding2;
							Enemy[P2].w = 42;
							Enemy[P2].h = 49;
						}
						ST7735_FillRect((Enemy[P2].x + Enemy[P2].w), (Enemy[P2].y-Enemy[P2].h), 8, Enemy[P2].h, 0xEEF8);
						ST7735_FillRect((Enemy[P2].x + Enemy[P2].w - 8), (Enemy[P2].y-Enemy[P2].h-2), 6, 4, 0xEEF8);
					}
				}
				else if(random1 == 1){
					if(Enemy[P2].x < (159-Enemy[P2].w)){
						Enemy[P2] = MoveR(Enemy[P2]);
						Enemy[P2].action = RUN;
						ST7735_FillRect((Enemy[P2].x + Enemy[P2].w), (Enemy[P2].y-Enemy[P2].h), 8, Enemy[P2].h, 0xEEF8);
					}
				}
				else if(random1 == 2){
					if(Enemy[P2].x < (159 - Enemy[P2].w)){
						Enemy[P2] = Atk1(Enemy[P2], Player[P1]);
						Enemy[P2].action = MELEE;
					}
				}
				else if(random1 == 3){
		//			if(Enemy[P2].x < (159 - 27)){
		//				Enemy[P2] = Atk2(Enemy[P2], Player[P1]);
		//				Enemy[P2].action = PROJ;
		//			}
				}
			}
			else if((negd >= 0)&&(negd < 12)){
				random1 = Random()%5;
				if(random1 == 0){
					if((EAct == STAND)||(EAct == RUN)){		//face right
						Enemy[P2].action = STAND;
						if(Enemy[P2].poke == PIKACHU){
							Enemy[P2].image = &stand1x;
							Enemy[P2].w = 34;
							Enemy[P2].h = 31;
						}
						else if(Enemy[P2].poke == LUCARIO){
							Enemy[P2].image = &standing2;
							Enemy[P2].w = 42;
							Enemy[P2].h = 49;
						}
						//may or may not need these for lucario
						ST7735_FillRect((Enemy[P2].x + Enemy[P2].w), (Enemy[P2].y-Enemy[P2].h), 8,Enemy[P2].h, 0xEEF8);
						ST7735_FillRect((Enemy[P2].x + 2), (Enemy[P2].y-Enemy[P2].h-2), 8, 4, 0xEEF8);
					}
					else{																	//face left
						Enemy[P2].action = STANDL;
						if(epkmn == PIKACHU){
							Enemy[P2].image = &lstand1;
							Enemy[P2].w = 34;
							Enemy[P2].h = 31;
						}
						else if(epkmn == LUCARIO){
							Enemy[P2].image = &lstanding2;
							Enemy[P2].w = 42;
							Enemy[P2].h = 49;
						}
						ST7735_FillRect((Enemy[P2].x + Enemy[P2].w), (Enemy[P2].y-Enemy[P2].h), 8, Enemy[P2].h, 0xEEF8);
						ST7735_FillRect((Enemy[P2].x + Enemy[P2].w - 8), (Enemy[P2].y-Enemy[P2].h-2), 6, 4, 0xEEF8);
					}
				}
				else if(random1 == 1){
					if(Enemy[P2].x > 0){
						Enemy[P2] = MoveL(Enemy[P2]);
						Enemy[P2].action = RUNL;
						ST7735_FillRect((Enemy[P2].x + Enemy[P2].w), (Enemy[P2].y-Enemy[P2].h), 8, Enemy[P2].h, 0xEEF8);
					}
				}
				else if(random1 == 2){
					if(Enemy[P2].x < (159 - Enemy[P2].w)){
						Enemy[P2] = Atk1(Enemy[P2], Player[P1]);
						Enemy[P2].action = MELEE;
					}
				}
				else if(random1 == 3){
					if(Enemy[P2].x < (159-Enemy[P2].w)){
						Enemy[P2] = MoveR(Enemy[P2]);
						Enemy[P2].action = RUN;
						ST7735_FillRect((Enemy[P2].x + Enemy[P2].w), (Enemy[P2].y-Enemy[P2].h), 8, Enemy[P2].h, 0xEEF8);
					}
				}
				else{
					erefl = 0;
					if(Enemy[P2].x > 0){
						Enemy[P2].action = JUMPL;
						Enemy[P2] = MoveL(Enemy[P2]);
						Enemy[P2] = Jump(Enemy[P2]);
					}
					ST7735_FillRect((Enemy[P2].x), 102, Enemy[P2].w, 3, 0xEEF8);
				}
			}
		}
	}
	else{
		if((EAct == MELEE)||(EAct == MELEEL)){									//in process of right melee atk
			if(((Enemy[P2].x + 1) < (159 - Enemy[P2].w))&&((Enemy[P2].x + 1) > 0))
				Enemy[P2] = Atk1(Enemy[P2], Player[P1]);
			else
				Enemy[P2].action = STAND;
		}
		else if(EAct == JUMPR){										//in process of jumping right
			if((Enemy[P2].x + 1) >= (159 - Enemy[P2].w)){
				erefl = 1;
			}
			if(erefl == 1)
				Enemy[P2] = MoveL(Enemy[P2]);
			else
				Enemy[P2] = MoveR(Enemy[P2]);
			Enemy[P2] = Jump(Enemy[P2]);
		}
		else if(EAct == JUMPL){										//in process of jumping left
			if((Enemy[P2].x + 1) <= 0)
				erefl = 1;
			if(erefl == 1)
				Enemy[P2] = MoveR(Enemy[P2]);
			else
				Enemy[P2] = MoveL(Enemy[P2]);
			Enemy[P2] = Jump(Enemy[P2]);
		}
		else if((EAct == PROJ)||(EAct == PROJL)){
			Enemy[P2] = Atk2(Enemy[P2], Player[P1]);
		}
		else if(EAct == DEAD){
			Enemy[P2] = Dead(Enemy[P2]);
		}
	}
	disp2 = 1;
}

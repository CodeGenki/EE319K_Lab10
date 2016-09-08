//Movement.c
//function that makes the character move
//includes fsm for different states of the sprites

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "ST7735.h"
#include "Movement.h"
#include "Collision.h"
void Delay10ms(uint32_t count);
void Delayms(uint32_t count);

uint32_t x;
uint32_t y;
uint32_t w;
uint32_t h;
//right facing Pikachu
extern const uint16_t stand1x;
extern const uint16_t run1a;
extern const uint16_t run2;
extern const uint16_t run3a;
extern const uint16_t jump1;
extern const uint16_t bash1;
extern const uint16_t bash2;
extern const uint16_t bash3;
extern const uint16_t thunder0;
extern const uint16_t thunder1;
extern const uint16_t thunder2;
extern const uint16_t pthunder1;
extern const uint16_t pthunder2;
//left facing Pikachu
extern const uint16_t lstand1;
extern const uint16_t lrun1;
extern const uint16_t lrun2;
extern const uint16_t lrun3;
extern const uint16_t ljump1;
extern const uint16_t lbash1;
extern const uint16_t lbash2;
extern const uint16_t lbash3;
extern const uint16_t lthunder1;
extern const uint16_t lthunder2;
extern const uint16_t lpthunder1;
extern const uint16_t lpthunder2;
extern const uint16_t dead;

// ************ right facing Lucario ***************
extern const uint16_t standing2;
extern const uint16_t run3;
extern const uint16_t punch2;
extern const uint16_t punch3;
extern const uint16_t aura1;
extern const uint16_t aura2;
extern const uint16_t aura3;
extern const uint16_t jump2;
// ************ right facing Lucario ***************
extern const uint16_t lstanding2;
extern const uint16_t laura1;
extern const uint16_t laura2;
extern const uint16_t laura3;
extern const uint16_t lpunch2;
extern const uint16_t lpunch3;
extern const uint16_t lrunx;
extern const uint16_t sphere;
// ************ Move Struct/FSM *******************
enum{RUN1, RUN2, RUN3};
enum{LRUN1, LRUN2, LRUN3, LRUN4};
struct Move{
	const uint16_t *image;
	uint8_t next;
	uint32_t w;
	uint32_t h;
};

typedef struct Move state_t;
const state_t pmovR[] = {
	{&run1a, RUN2, 34, 28},
	{&run2, RUN3, 34, 28},
	{&run3a, RUN1, 34, 28}
};
const state_t pmovL[] = {
	{&lrun1, RUN2, 34, 28},
	{&lrun2, RUN3, 34, 28},
	{&lrun3, RUN1, 34, 28}
};

const state_t lmovR[] = {
	{&run3, LRUN2, 42, 49},
	{&run3, LRUN3, 42, 49},
	{&standing2, LRUN4, 42, 49},
	{&standing2, LRUN1, 42, 49}
};
const state_t lmovL[] = {
	{&lrunx, LRUN2, 42, 49},
	{&lrunx, LRUN3, 42, 49},
	{&lstanding2, LRUN4, 42, 49},
	{&lstanding2, LRUN1, 42, 49}
};

// *********************** ATK Struct/FSM **********************
enum{BASH1, rBASH1, BASH2, rBASH2, BASH3, rBASH3, BACK, DONE1, DONE2};
enum{CHARGE, CHARGE1, CHARGE2, CHARGE3, CHARGE4, RELEASE, RELEASE1, RELEASE2, RELEASE3, RELEASE4, RELEASE5, DONE};
enum{PRE, PRE1, PRE2, PRE3, PRE4, FULL};
enum{NCHARGE, NCHARGE1, NCHARGE2, NCHARGE3, NCHARGE4, YCHARGE, YCHARGE1, YCHARGE2, YCHARGE3, YCHARGE4, NRELEASE, NRELEASE1, NRELEASE2, NRELEASE3, NRELEASE4, NRELEASE5, DONE3};
enum{PUNCH10, PUNCH11, PUNCH12, PUNCH13, PUNCH14, PUNCH15, PUNCH21, PUNCH22, PUNCH23, PUNCH24, PUNCH25, PUNCH26, PUNCHR};
struct ATK{
	int8_t x;		//x to add by 
	uint8_t y;		//y to add by 
	const uint16_t *image;
	uint32_t w;
	uint32_t h;
	uint8_t next;
	uint8_t done;
};

typedef struct ATK atk_t;
const atk_t patk1r[] = {		//Pikachu melee atk
	{0, 0, &bash1, 41, 27, rBASH1, 0},
	{0, 0, &bash1, 41, 27, BASH2, 0},
	{0, 0, &bash2, 45, 23, rBASH2, 0},
	{1, 0, &bash2, 45, 23, BASH3, 0},
	{0, 0, &bash3, 46, 29, rBASH3, 0},
	{1, 0, &bash3, 46, 29, BACK, 0},
	{0, 0, &bash2, 45, 23, DONE1, 0},
	{1, 0, &stand1x, 34, 31, DONE2, 0},
	{1, 0, &stand1x, 34, 31, BASH1, 1}
};
const atk_t patk1l[] = {		//Pikachu melee atk
	{0, 0, &lbash1, 41, 27, rBASH1, 0},
	{0, 0, &lbash1, 41, 27, BASH2, 0},
	{0, 0, &lbash2, 45, 23, rBASH2, 0},
	{1, 0, &lbash2, 45, 23, BASH3, 0},
	{0, 0, &lbash3, 46, 29, rBASH3, 0},
	{1, 0, &lbash3, 46, 29, BACK, 0},
	{0, 0, &lbash2, 45, 23, DONE1, 0},
	{1, 0, &lstand1, 34, 31, DONE2, 0},
	{1, 0, &lstand1, 34, 31, BASH1, 1}
};

const atk_t latk1r[] = {
	{0, 0, &punch2, 42, 49, PUNCH11, 0},
	{0, 0, &punch2, 42, 49, PUNCH12, 0},
	{0, 0, &punch2, 42, 49, PUNCH13, 0},
	{0, 0, &punch2, 42, 49, PUNCH14, 0},
	{0, 0, &punch2, 42, 49, PUNCH15, 0},
	{0, 0, &punch2, 42, 49, PUNCH21, 0},
	{0, 0, &punch3, 42, 49, PUNCH22, 0},
	{0, 0, &punch3, 42, 49, PUNCH23, 0},
	{0, 0, &punch3, 42, 49, PUNCH24, 0},
	{0, 0, &punch3, 42, 49, PUNCH25, 0},
	{0, 0, &punch3, 42, 49, PUNCH26, 0},
	{0, 0, &punch3, 42, 49, PUNCHR, 0},
	{0, 0, &punch3, 42, 49, PUNCH22, 1}
};
const atk_t latk1l[] = {
	{0, 0, &lpunch2, 42, 49, PUNCH11, 0},
	{0, 0, &lpunch2, 42, 49, PUNCH12, 0},
	{0, 0, &lpunch2, 42, 49, PUNCH13, 0},
	{0, 0, &lpunch2, 42, 49, PUNCH14, 0},
	{0, 0, &lpunch2, 42, 49, PUNCH15, 0},
	{0, 0, &lpunch2, 42, 49, PUNCH21, 0},
	{0, 0, &lpunch3, 42, 49, PUNCH22, 0},
	{0, 0, &lpunch3, 42, 49, PUNCH23, 0},
	{0, 0, &lpunch3, 42, 49, PUNCH24, 0},
	{0, 0, &lpunch3, 42, 49, PUNCH25, 0},
	{0, 0, &lpunch3, 42, 49, PUNCH26, 0},
	{0, 0, &lpunch3, 42, 49, PUNCHR, 0},
	{0, 0, &lpunch3, 42, 49, PUNCH22, 1}
};

const atk_t patk2r[] = {		//Pikachu thunder atk (sprite mvmt)
	{0, 0, &pthunder1, 34, 33, CHARGE1, 0},
	{0, 0, &pthunder1, 34, 33, CHARGE2, 0},
	{0, 0, &pthunder1, 34, 33, CHARGE3, 0},
	{0, 0, &pthunder1, 34, 33, CHARGE4, 0},
	{0, 0, &pthunder1, 34, 33, RELEASE, 0},
	{0, 0, &pthunder2, 34, 33, RELEASE1, 0},
	{0, 0, &pthunder2, 34, 33, RELEASE2, 0},
	{0, 0, &pthunder2, 34, 33, RELEASE3, 0},
	{0, 0, &pthunder2, 34, 33, RELEASE4, 0},
	{0, 0, &pthunder2, 34, 33, RELEASE5, 0},
	{0, 0, &pthunder2, 34, 33, DONE, 0},
	{0, 0, &stand1x, 34, 31, DONE, 1}
};

const atk_t pprojr[] = {		//Pikachu thunder - image mvmt
	{0, 0, &thunder1, 15, 20, PRE1, 0},
	{0, 0, &thunder1, 15, 20, PRE2, 0},
	{0, 0, &thunder1, 15, 20, PRE3, 0}, 
	{0, 0, &thunder1, 15, 20, PRE4, 0},
	{0, 0, &thunder1, 15, 20, FULL, 0},
	{2, 0, &thunder2, 27, 18, FULL, 0}		//goes on forever. Will be stopped externally by flag change.
};

const atk_t patk2l[] = {		//Pikachu thunder atk (sprite mvmt)
	{0, 0, &lpthunder1, 34, 33, CHARGE1, 0},
	{0, 0, &lpthunder1, 34, 33, CHARGE2, 0},
	{0, 0, &lpthunder1, 34, 33, CHARGE3, 0},
	{0, 0, &lpthunder1, 34, 33, CHARGE4, 0},
	{0, 0, &lpthunder1, 34, 33, RELEASE, 0},
	{0, 0, &lpthunder2, 34, 33, RELEASE1, 0},
	{0, 0, &lpthunder2, 34, 33, RELEASE2, 0},
	{0, 0, &lpthunder2, 34, 33, RELEASE3, 0},
	{0, 0, &lpthunder2, 34, 33, RELEASE4, 0},
	{0, 0, &lpthunder2, 34, 33, RELEASE5, 0},
	{0, 0, &lpthunder2, 34, 33, DONE, 0},
	{0, 0, &lstand1, 34, 31, DONE, 1}
};

const atk_t pprojl[] = {		//Pikachu thunder - image mvmt
	{0, 0, &lthunder1, 15, 20, PRE1, 0},
	{0, 0, &lthunder1, 15, 20, PRE2, 0},
	{0, 0, &lthunder1, 15, 20, PRE3, 0}, 
	{0, 0, &lthunder1, 15, 20, PRE4, 0},
	{0, 0, &lthunder1, 15, 20, FULL, 0},
	{2, 0, &lthunder2, 27, 18, FULL, 0}		//goes on forever. Will be stopped externally by flag change.
};

const atk_t latk2r[] = {
	{0, 0, &aura1, 42, 49, NCHARGE1, 0},
	{0, 0, &aura1, 42, 49, NCHARGE2, 0},
	{0, 0, &aura1, 42, 49, NCHARGE3, 0},
	{0, 0, &aura1, 42, 49, NCHARGE4, 0},
	{0, 0, &aura1, 42, 49, YCHARGE, 0},
	{0, 0, &aura2, 42, 49, YCHARGE1, 0},
	{0, 0, &aura2, 42, 49, YCHARGE2, 0},
	{0, 0, &aura2, 42, 49, YCHARGE3, 0},
	{0, 0, &aura2, 42, 49, YCHARGE4, 0},
	{0, 0, &aura2, 42, 49, NRELEASE1, 0},
	{0, 0, &aura3, 42, 49, NRELEASE2, 0},
	{0, 0, &aura3, 42, 49, NRELEASE3, 0},
	{0, 0, &aura3, 42, 49, NRELEASE4, 0},
	{0, 0, &aura3, 42, 49, NRELEASE5, 0},
	{0, 0, &standing2, 42, 49, DONE3, 1},
	{0, 0, &standing2, 42, 49, DONE3, 1}
};
const atk_t latk2l[] = {
	{0, 0, &laura1, 42, 49, NCHARGE1, 0},
	{0, 0, &laura1, 42, 49, NCHARGE2, 0},
	{0, 0, &laura1, 42, 49, NCHARGE3, 0},
	{0, 0, &laura1, 42, 49, NCHARGE4, 0},
	{0, 0, &laura1, 42, 49, YCHARGE, 0},
	{0, 0, &laura2, 42, 49, YCHARGE1, 0},
	{0, 0, &laura2, 42, 49, YCHARGE2, 0},
	{0, 0, &laura2, 42, 49, YCHARGE3, 0},
	{0, 0, &laura2, 42, 49, YCHARGE4, 0},
	{0, 0, &laura2, 42, 49, NRELEASE1, 0},
	{0, 0, &laura3, 42, 49, NRELEASE2, 0},
	{0, 0, &laura3, 42, 49, NRELEASE3, 0},
	{0, 0, &laura3, 42, 49, NRELEASE4, 0},
	{0, 0, &laura3, 42, 49, NRELEASE5, 0},
	{0, 0, &lstanding2, 42, 49, DONE3, 1},
	{0, 0, &lstanding2, 42, 49, DONE3, 1}
};

const atk_t lprojr[] = {		
	{2, 0, &sphere, 19, 19, PRE, 0}
};
const atk_t lprojl[] = {		
	{2, 0, &sphere, 19, 19, PRE, 0}
};

enum{STAND, STANDL, RUN, RUNL, JUMP, JUMPFL, JUMPL, JUMPR, MELEE, MELEEL, PROJ, PROJL, DEAD};
enum{NULL, LNULL, SHOOT, SHOOTL};	//projectile actions
const uint8_t jumpArr[] = {0,0,0,0,1,0,1,0,1,1,2,1,2,1,2,1,2,2,1,2,2,1};	//how much to change y by
enum{PIKACHU, LUCARIO};
	
// **************** DEAD ******************
player_t Dead(player_t sprite){
	if(sprite.image != &dead)
		ST7735_FillRect(sprite.x - 3, sprite.y+sprite.h, sprite.w + 6, sprite.h, 0xEEF8);
	sprite.image = &dead;
	sprite.h = 31;
	sprite.w = 34;
	return sprite;
}

uint8_t pCstateR = RUN1;
uint8_t lCstateR = LRUN1;
// **************** MoveR - Move the sprite right *********************
//Updates player's coordinates and image
player_t MoveR(player_t sprite){
	if(sprite.poke == PIKACHU){
		sprite.image = pmovR[pCstateR].image;
		pCstateR = pmovR[pCstateR].next;
		sprite.w = pmovR[pCstateR].w;	
		sprite.h = pmovR[pCstateR].h;	
	}
	else if(sprite.poke == LUCARIO){
		sprite.image = lmovR[lCstateR].image;
		lCstateR = lmovR[lCstateR].next;
		sprite.w = lmovR[lCstateR].w;	
		sprite.h = lmovR[lCstateR].h;	
	}
	x = sprite.x;
	x++;
	sprite.x = x;
	ST7735_FillRect((sprite.x - 2), (sprite.y-sprite.h-5), (sprite.w + 2), 10, 0xEEF8);
	return sprite;
}

uint8_t pCstateL = RUN1;
uint8_t lCstateL = LRUN1;
// **************** MoveL - Move the sprite left **********************
//Updates player's coordinates and image
player_t MoveL(player_t sprite){
	if(sprite.poke == PIKACHU){
		sprite.image = pmovL[pCstateL].image;
		pCstateL = pmovL[pCstateL].next;
		sprite.w = pmovL[pCstateL].w;
		sprite.h = pmovL[pCstateL].h;
	}
	else if(sprite.poke == LUCARIO){
		sprite.image = lmovL[lCstateL].image;
		lCstateL = lmovL[lCstateL].next;
		sprite.w = lmovL[lCstateL].w;
		sprite.h = lmovL[lCstateL].h;
	}
	x = sprite.x;
	x--;
	sprite.x = x;
	ST7735_FillRect((sprite.x - 2), (sprite.y-sprite.h-5), (sprite.w + 2), 10, 0xEEF8);
	return sprite;	
}

// ****************** Jump - Jump vertically ***************************
uint8_t jumpCt = 0;
uint8_t dir = 1;
extern uint8_t refl;
player_t Jump(player_t sprite){
	if((sprite.action == JUMPR)||(sprite.action == JUMP)){
		if(sprite.poke == PIKACHU)
			sprite.image = &jump1;
		else if(sprite.poke == LUCARIO)
			sprite.image = &jump2;
	}
	else{
		if(sprite.poke == PIKACHU)
			sprite.image = &ljump1;
		else if(sprite.poke == LUCARIO)
			sprite.image = &jump2;
	}
	x = sprite.x;
	y = sprite.y;
	if(sprite.poke == PIKACHU){
		sprite.w = 35;
		sprite.h = 35;
	}
	else if(sprite.poke == LUCARIO){
		sprite.w = 42;		//must change for lucario
		sprite.h = 49;		//must change for lucario
	}
	if(dir == 1){
		if(y > 83){
			y--;
			y--;
			y += jumpArr[jumpCt];
			jumpCt++;
			ST7735_FillRect(sprite.x, (sprite.y-1), sprite.w, 1, 0xEEF8);
			sprite.y = y;
		}
	}
	else if(dir == 0){
		if(y < 104){
			y++;
			y++;
			ST7735_FillRect(sprite.x, (sprite.y-sprite.h-3), sprite.w, 5, 0xEEF8);
			sprite.y = y;
		}
	}
	if(y <= 83)
		dir = 0;
	if(y >= 104){
		jumpCt = 0;
		sprite.y = 104;
		dir = 1;
		if((sprite.action == JUMPR)||(sprite.action == JUMP))
			sprite.action = STAND;
		else
			sprite.action = STANDL;
	}
	return sprite;
}

//************** Attack 1 - Melee attack *********************
uint8_t pcsAtkr = BASH1;
uint8_t pcsAtkl = BASH1;
uint8_t lcsAtkr = PUNCH10;
uint8_t lcsAtkl = PUNCH10;
player_t Atk1(player_t sprite, player_t enemy){
	if(sprite.action == MELEE){
		if(sprite.poke == PIKACHU){
			if(patk1r[pcsAtkr].done){
				sprite.action = STAND;
				pcsAtkr = BASH1;
			}
		}
		else if(sprite.poke == LUCARIO){
			if(latk1r[lcsAtkr].done){
				sprite.action = STAND;
				lcsAtkr = PUNCH10;
			}
		}
		if(sprite.poke == PIKACHU)
			ST7735_FillRect((sprite.x), (sprite.y-sprite.h-5), (patk1r[pcsAtkr - 1].w), (sprite.h), 0xEEF8);
		else if(sprite.poke == LUCARIO)
			ST7735_FillRect((sprite.x), (sprite.y-sprite.h-5), (latk1r[lcsAtkr - 1].w), (sprite.h), 0xEEF8);
		if(sprite.poke == PIKACHU){
			sprite.image = patk1r[pcsAtkr].image;
			sprite.x += patk1r[pcsAtkr].x;
			sprite.y += patk1r[pcsAtkr].y;
			sprite.w = patk1r[pcsAtkr].w;
			sprite.h = patk1r[pcsAtkr].h;
			pcsAtkr = patk1r[pcsAtkr].next;		//change current state
		}
		
		else if(sprite.poke == LUCARIO){
			sprite.image = latk1r[lcsAtkr].image;
			sprite.x += latk1r[lcsAtkr].x;
			sprite.y += latk1r[lcsAtkr].y;
			sprite.w = latk1r[lcsAtkr].w;
			sprite.h = latk1r[lcsAtkr].h;
			lcsAtkr = latk1r[lcsAtkr].next;		//change current state
		}
	}
	else if(sprite.action == MELEEL){
		if(sprite.poke == PIKACHU){
			if(patk1l[pcsAtkl].done){
				sprite.action = STANDL;
				pcsAtkl = BASH1;
			}
		}
		else if(sprite.poke == LUCARIO){
			if(latk1l[lcsAtkl].done){
				sprite.action = STANDL;
				lcsAtkl = PUNCH10;
			}
		}
		if(sprite.poke == PIKACHU)
			ST7735_FillRect((sprite.x), (sprite.y-sprite.h-5), (patk1r[pcsAtkr - 1].w), (sprite.h), 0xEEF8);
		else if(sprite.poke == LUCARIO)
			ST7735_FillRect((sprite.x), (sprite.y-sprite.h-5), (latk1r[lcsAtkr - 1].w), (sprite.h), 0xEEF8);
		ST7735_FillRect((sprite.x), (sprite.y-sprite.h), (sprite.w), (sprite.h), 0xEEF8);
		if(sprite.poke == PIKACHU){
			sprite.image = patk1l[pcsAtkl].image;
			sprite.x -= patk1l[pcsAtkl].x;
			sprite.y += patk1l[pcsAtkl].y;
			sprite.w = patk1l[pcsAtkl].w;
			sprite.h = patk1l[pcsAtkl].h;
			pcsAtkl = patk1l[pcsAtkl].next;		//change current state
		}
		else if(sprite.poke == LUCARIO){
			sprite.image = latk1l[lcsAtkl].image;
			sprite.x -= latk1l[lcsAtkl].x;
			sprite.y += latk1l[lcsAtkl].y;
			sprite.w = latk1l[lcsAtkl].w;
			sprite.h = latk1l[lcsAtkl].h;
			lcsAtkl = latk1l[lcsAtkl].next;		//change current state
		}
	}
	return sprite;	
}

// ************** Attack 2 - Projectile Attack **********************
uint8_t pcspr = CHARGE;
uint8_t pProjcsr = PRE;
uint8_t pcspl = CHARGE;
uint8_t pProjcsl = PRE;
uint8_t lcspr = NCHARGE;
uint8_t lProjcsr = PRE;
uint8_t lcspl = NCHARGE;
uint8_t lProjcsl = PRE;
player_t Atk2(player_t sprite, player_t enemy){
	if(sprite.action == PROJ){
			sprite.paction = SHOOT;
		if(pProjcsr == PRE){
			if(sprite.poke == PIKACHU){
				sprite.px = (sprite.x + sprite.w);
				sprite.py = sprite.y - 5;
			}
			else if(sprite.poke == LUCARIO){
				sprite.px = (sprite.x + sprite.w);
				sprite.py = sprite.y - 7;
			}
		}
		if(sprite.poke == PIKACHU){
			sprite.image = patk2r[pcspr].image;
			sprite.x += patk2r[pcspr].x;
			sprite.y += patk2r[pcspr].y;
			sprite.w = patk2r[pcspr].w;
			sprite.h = patk2r[pcspr].h;
			pcspr = patk2r[pcspr].next;
			if(patk2r[pcspr].done){
				pcspr = CHARGE;
				sprite.action = STAND;
			}
		}
		else if(sprite.poke == LUCARIO){										
			sprite.image = latk2r[lcspr].image;
			sprite.x += latk2r[lcspr].x;
			sprite.y += latk2r[lcspr].y;
			sprite.w = latk2r[lcspr].w;
			sprite.h = latk2r[lcspr].h;
			lcspr = latk2r[lcspr].next;
			if(latk2r[lcspr].done){
				lcspr = CHARGE;
				sprite.action = STAND;
			}
		}
	}
	else if(sprite.action == PROJL){
			sprite.paction = SHOOTL;
		if(pProjcsl == PRE){
			if(sprite.poke == PIKACHU){
				sprite.px = sprite.x - sprite.pw + 8;
				sprite.py = sprite.y - 5;
			}
			else if(sprite.poke == LUCARIO){
				sprite.px = sprite.x - sprite.pw + 8;
				sprite.py = sprite.y - 7;
			}
		}
		if(sprite.poke == PIKACHU){
			sprite.image = patk2l[pcspl].image;
			sprite.x -= patk2l[pcspl].x;
			sprite.y += patk2l[pcspl].y;
			sprite.w = patk2l[pcspl].w;
			sprite.h = patk2l[pcspl].h;
			pcspl = patk2l[pcspl].next;
			if(patk2l[pcspl].done){
				pcspl = CHARGE;
				sprite.action = STANDL;
			}
		}
		else if(sprite.poke == LUCARIO){
			sprite.image = latk2l[lcspl].image;
			sprite.x -= latk2l[lcspl].x;
			sprite.y += latk2l[lcspl].y;
			sprite.w = latk2l[lcspl].w;
			sprite.h = latk2l[lcspl].h;
			lcspl = latk2l[lcspl].next;
			if(latk2l[lcspl].done){
				lcspl = CHARGE;
				sprite.action = STANDL;
			}
		}
	}
		if((sprite.px >= 159)||DetectCollision(sprite, enemy)){
			if(sprite.poke == PIKACHU)
				pProjcsr = PRE;
			else if(sprite.poke == LUCARIO)
				lProjcsr = PRE;
			sprite.paction = NULL; //reset the projectile to be "invisible"
			sprite.px = 2;	
			sprite.py = 0;
		}
		if(sprite.paction == SHOOT){
			ST7735_FillRect(sprite.px, (sprite.py - sprite.ph), sprite.pw, sprite.ph, 0xEEF8);
			if(sprite.poke == PIKACHU){
				sprite.pImage = pprojr[pProjcsr].image;
				sprite.px += pprojr[pProjcsr].x;
				sprite.py += pprojr[pProjcsr].y;
				sprite.pw = pprojr[pProjcsr].w;
				sprite.ph = pprojr[pProjcsr].h;
				pProjcsr = pprojr[pProjcsr].next;
			}
			else if(sprite.poke == LUCARIO){
				sprite.pImage = lprojr[lProjcsr].image;
				sprite.px += lprojr[lProjcsr].x;
				sprite.py += lprojr[lProjcsr].y;
				sprite.pw = lprojr[lProjcsr].w;
				sprite.ph = lprojr[lProjcsr].h;
				lProjcsr = lprojr[lProjcsr].next;
			}
		}

		if(((sprite.px + 27) <= 0)||DetectCollision(sprite, enemy)){		
			if(sprite.poke == PIKACHU)
				pProjcsl = PRE;
			else if(sprite.poke == LUCARIO)
				lProjcsl = PRE;
			sprite.paction = NULL; //reset the projectile to be "invisible"
			sprite.px = 2;	
			sprite.py = 0;
		}
		if(sprite.paction == SHOOTL){
			ST7735_FillRect(sprite.px, (sprite.py - sprite.ph), (sprite.pw), sprite.ph, 0xEEF8);
			if(sprite.poke == PIKACHU){
				sprite.pImage = pprojl[pProjcsl].image;
				sprite.px -= pprojl[pProjcsl].x;
				sprite.py += pprojl[pProjcsl].y;
				sprite.pw = pprojl[pProjcsl].w;
				sprite.ph = pprojl[pProjcsl].h;
				pProjcsl = pprojl[pProjcsl].next;
			}
			else if(sprite.poke == LUCARIO){
				sprite.pImage = lprojl[lProjcsl].image;
				sprite.px -= lprojl[lProjcsl].x;
				sprite.py += lprojl[lProjcsl].y;
				sprite.pw = lprojl[lProjcsl].w;
				sprite.ph = lprojl[lProjcsl].h;
				lProjcsl = lprojl[lProjcsl].next;
			}
		}
	return sprite;
}

void Delay10ms(uint32_t count){uint32_t volatile time;
  while(count>0){
    time = 72724;  // 0.01sec at 80 MHz
    while(time){
	  	time--;
    }
    count--;
  }
}

void Delayms(uint32_t count){uint32_t volatile time;
  while(count>0){
    time = 7273;  // 0.001sec at 80 MHz
    while(time){
	  	time--;
    }
    count--;
  }
}

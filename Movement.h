//Movement.h

struct Sprite{
	char poke;
	const uint16_t *image;		//going to be stand for now
	uint8_t action;
	int32_t x;
	uint32_t y;
	uint32_t w;
	uint32_t h;
	int32_t hp;
	uint32_t dmg;
	const uint16_t *pImage;		//going to be stand for now
	uint8_t paction;
	int32_t px;
	uint32_t py;
	uint32_t pw;
	uint32_t ph;
	uint32_t pdmg;
};
typedef struct Sprite player_t;
//typedef struct State state_t;

player_t MoveR(player_t);
player_t MoveL(player_t);
player_t Jump(player_t);
player_t Atk1(player_t, player_t);
player_t Atk2(player_t, player_t);
player_t Dead(player_t);
void Delay10ms(uint32_t);
void Delayms(uint32_t);

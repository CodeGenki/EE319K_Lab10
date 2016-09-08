#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "ST7735.h"
#include "Random.h"
#include "TExaS.h"
#include "ADC.h"

#include "Movement.h"
#include "Random.h"

/*const unsigned short heart[] = {
 0xEEF8, 0xEEF8, 0xEEF8, 0xEEF8, 0xEEF8, 0xEEF8, 0xEEF8, 0xEEF8, 0xEEF8, 0xEEF8, 0xEEF8, 0xEEF8, 0xEF19, 0x39C6, 0xEF19, 0xEEF8,
 0xEEF8, 0xEEF8, 0xEEF8, 0xEEF8, 0xEF18, 0x0861, 0x52B6, 0x4208, 0xEEF9, 0xEEF8, 0xEEF8, 0xEEF8, 0xEEF8, 0x0861, 0x8439, 0x5AD7,
 0x52B7, 0x2945, 0xEEF8, 0xEEF8, 0xEF18, 0x10A3, 0x7BB7, 0x4A76, 0x4236, 0x52B7, 0x83F8, 0x18E3, 0xEEF9, 0x1082, 0x6337, 0x5AD7,
 0x8419, 0x6317, 0x5296, 0x4A76, 0x4A56, 0x2945, 0x18C4, 0x5296, 0x6317, 0x6317, 0x6B78, 0x4A76, 0xFFFF, 0x5AD7, 0x2946, 0x10A3,
 0x5296, 0x6317, 0x6B78, 0x1082, 0x5AF7, 0x5AD7, 0x6337, 0x1082, 0xF739, 0x2965, 0x31A6, 0x39A6, 0xEF19, 0x2965, 0x2946, 0x2945,
 0xF73A,

};
*/
extern player_t Player[2];
extern player_t Enemy[2];
extern uint8_t P1;
extern uint8_t P2;

uint16_t width;
uint16_t charX;

uint32_t HPConvertPlayer(int32_t hp){ //converts current hp to starting x location
	uint32_t final;
	final=(hp*40)/100;//40 will be 50
	return (final+12);//12 should stay same unless you change starting position of hp bar
}

uint32_t HPConvertAI(int32_t hp){
	uint32_t final;
	final=(hp*40)/100;//40 will be 50
	return(40-final);//40 should be 50
}

void DrawHP(void){
	char hpstring[3]={0x50, 0x31, 0x00};
	uint16_t black = ST7735_Color565(0, 0, 0);
	uint16_t green = ST7735_Color565(0, 204, 102);
	
	//P1's HP Bar
	ST7735_DrawCharS(1, 30, 0x50, black, 0xEEF8, 1);
	ST7735_DrawCharS(7, 30, 0x31, black, 0xEEF8, 1);
	ST7735_DrawFastHLine(12, 29, 51, 0x0000);
	ST7735_DrawFastVLine(12, 29, 9, 0x0000);
	ST7735_DrawFastHLine(12, 37, 51, 0x0000);
	ST7735_DrawFastVLine(63, 29, 9, 0x0000);
	
	//P2's HP Bar
	ST7735_DrawCharS(148, 30, 0x50, black, 0xEEF8, 1);
	ST7735_DrawCharS(154, 30, 0x32, black, 0xEEF8, 1);
	ST7735_DrawFastHLine(95, 29, 51, 0x0000);
	ST7735_DrawFastVLine(95, 29, 9, 0x0000);
	ST7735_DrawFastHLine(95, 37, 51, 0x0000);
	ST7735_DrawFastVLine(146, 29, 9, 0x0000);
	
	//ST7735_DrawString(19, 3, &hpstring[0], black);//19 will be 14, 7 will be 5ish depending on clouds
	//ST7735_FillRect(97, 30, 50, 7, green);//73 will be 95ish, 71 will be 51ish
	
	/*if(Pikachu.lives==3){ //may or may not want this here
	ST7735_DrawBitmap(12, 86, &heart[0], 9, 9); //player's hearts, 86 will be 59ish
	ST7735_DrawBitmap(22, 86, &heart[0], 9, 9);//86 will be 59ish
	ST7735_DrawBitmap(32, 86, &heart[0], 9, 9);//86 will be 59ish
	}
	if(Pikachu.lives==2){
	ST7735_DrawBitmap(12, 86, &heart[0], 9, 9); //player's hearts
	ST7735_DrawBitmap(22, 86, &heart[0], 9, 9);

	}
	if(Pikachu.lives==1){
	ST7735_DrawBitmap(12, 86, &heart[0], 9, 9); //player's hearts
	
	}
	if(Lucario.lives==3){
	ST7735_DrawBitmap(84, 86, &heart[0], 9, 9);//AI's hearts, 86 will be 59ish
	ST7735_DrawBitmap(94, 86, &heart[0], 9, 9);//86 will be 59ish
	ST7735_DrawBitmap(104, 86, &heart[0], 9, 9);//86 will be 59ish
	}
	if(Lucario.lives==2){
	ST7735_DrawBitmap(84, 86, &heart[0], 9, 9);//AI's hearts
	ST7735_DrawBitmap(94, 86, &heart[0], 9, 9);
	
	}
	if(Lucario.lives==1){
	ST7735_DrawBitmap(84, 86, &heart[0], 9, 9);//AI's hearts
	
	}
	*/
	
	//Pikachu.hp=100; //this is test function, remove when done
	//hpConverted1 = HPConvertPlayer(p1HP);
	//hpConverted2 = 40-(hpConverted1-12); //40 will be 50, 12 should stay 12 unless change starting position of hp bar
	//ST7735_FillRect(hpConverted1, 71, hpConverted2, 7, 0xEEF8);//71 will be 51ish
	
	//Lucario.hp=100;//this is test function, remove when done
	//hpConverted2=HPConvertAI(p2HP);
	//ST7735_FillRect(73, 71, hpConverted2, 7, 0xEEF8);//73 will be 95ish, 71 will be 51ish
	if(Player[P1].hp%2 == 0){
		width = (100 - Player[P1].hp)/2;
		charX = Player[P1].hp/2;
		ST7735_FillRect(13, 30, 50-width, 7, green);//71 will be 51ish, 40 will be 50
		ST7735_FillRect((13+charX), 30, width, 7, 0xEEF8);
	}
	else if(Player[P1].hp%2 != 0){
		Player[P1].hp++;
		width = (100 - Player[P1].hp)/2;
		charX = Player[P1].hp/2;
		ST7735_FillRect(13, 30, 50-width, 7, green);//71 will be 51ish, 40 will be 50
		ST7735_FillRect((13+charX), 30, width, 7, 0xEEF8);
		Player[P1].hp--;
	}
	if(Enemy[P2].hp%2 == 0){
		width = (100 - Enemy[P2].hp)/2;
		ST7735_FillRect(96 + width, 30, 50 - width, 7, green);//73 will be 95ish, 71 will be 51ish
		ST7735_FillRect(96, 30, width, 7, 0xEEF8);
	}
	else if(Enemy[P2].hp%2 != 0){
		Enemy[P2].hp++;
		width = (100 - Enemy[P2].hp)/2;
		ST7735_FillRect(96 + width, 30, 50 - width, 7, green);//73 will be 95ish, 71 will be 51ish
		ST7735_FillRect(96, 30, width, 7, 0xEEF8);
		Enemy[P2].hp--;
	}
}




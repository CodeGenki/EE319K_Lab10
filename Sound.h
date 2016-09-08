// Sound.h
// Runs on TM4C123 or LM4F120
// Prototypes for basic functions to play sounds from the
// original Space Invaders.
// Jonathan Valvano
// November 17, 2014


void Sound_Init(uint32_t);
void Sound_Play(const uint8_t *pt, uint32_t count);
void Sound_Open(void);
void Sound_Battle1(void);
void Sound_Stop(void);
void Sound_Select(void);
void Sound_Win(void);
void Sound_Lose(void);
void Sound_Obtain(void);
void Sound_Resume(void);
void Sound_Thunder(void);
void Sound_Hit(void);

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "ST7735.h"
#include "Random.h"
#include "TExaS.h"
#include "ADC.h"
#include "Timer0.h"
#include "Random.h"
#include "Movement.h"
#include "Sound.h"

enum{TITLE, CHARSEL, READY, FIGHT, RESULT};

const unsigned short P1wins[] = {
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0xCD56, 0xCD56, 0x0000, 0x0000, 0x0000, 0x0000, 0xCD56, 0xCD56, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x7AE6, 0xB65E, 0x0000, 0x0000, 0x0000, 0x0000, 0xB65E,
 0x7AE6, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x52A7, 0x52A7, 0x0000, 0x0000, 0x52A7, 0x52A7, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x52A7, 0x52A7, 0x31A5, 0x31A5, 0x52A7, 0x52A7, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x31A5, 0x0000, 0xD5D5, 0xD5D5,
 0x0000, 0x31A5, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x18C2, 0x31AD, 0x2977, 0x0000, 0x0000, 0x2977, 0x31AD, 0x18C2, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x21AA, 0xB65E, 0x6479, 0x0000, 0x0000, 0x0000, 0x310F, 0x0000, 0x2977, 0x2977, 0x2977, 0x310F, 0xCD56, 0x0000,
 0x0000, 0x6479, 0xB65E, 0x21AA, 0x0000, 0x0000, 0x0000, 0x0000, 0x21AA, 0xB65E, 0x2977, 0x2977, 0x0000, 0xCD56, 0x0000, 0x2977,
 0xCD56, 0xCD56, 0x2977, 0x310F, 0xCD56, 0x0000, 0x2977, 0x2977, 0xB65E, 0x21AA, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x21AA,
 0x0000, 0x2977, 0x2977, 0x0000, 0x0000, 0xCD56, 0x31A5, 0x31A5, 0xCD56, 0x2977, 0x0000, 0x2977, 0x2977, 0x0000, 0x21AA, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x31A5, 0x0000, 0x0000, 0x21AA, 0x21AA, 0x0000, 0x0000,
 0x31A5, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x2A91,
 0x6CB9, 0xB67E, 0x6CB9, 0x6CB9, 0xB67E, 0x6CB9, 0x2A91, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x2A91, 0xB67E, 0xB67E, 0xB67E, 0xB67E, 0xB67E, 0xB67E, 0xB67E, 0xB67E, 0x2A91, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x52A7, 0x0000, 0xF77D, 0x0000, 0x6CB9, 0x6CB9, 0x6CB9,
 0x6CB9, 0x0000, 0xF77D, 0xB67E, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3948,
 0x52A7, 0x0000, 0x2924, 0x0000, 0x2A91, 0x2A91, 0x2A91, 0x2924, 0xD5D5, 0x6CB9, 0x2924, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x52A7, 0x3948, 0x52A7, 0x0000, 0x52A7, 0x0000, 0x1B36, 0x1B36, 0x1B36, 0x324F, 0x324F,
 0x2924, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x2A91, 0x6CB9, 0x3948, 0x0000, 0x52A7, 0x52A7, 0x52A7, 0x52A7,
 0x52A7, 0x0000, 0x31A5, 0x1B36, 0x1B36, 0x31A5, 0x0000, 0x2924, 0x6CB9, 0x2A91, 0x0000, 0x0000, 0x0000, 0x0000, 0x2A91, 0x6CB9,
 0x0000, 0x31A5, 0x0000, 0x52A7, 0x52A7, 0x52A7, 0x0000, 0x31A5, 0x1B36, 0x1B36, 0x1B36, 0x31A5, 0x31A5, 0x0000, 0x6CB9, 0x2A91,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x31A5, 0x31A5, 0x31A5, 0x0000, 0x0000, 0x0000, 0x1B36, 0x1B36, 0x1B36, 0x1B36,
 0x1B36, 0x31A5, 0x31A5, 0x31A5, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x31A5, 0x31A5, 0x31A5, 0x1D5E,
 0x1D5E, 0x1D5E, 0x1D5E, 0x1D5E, 0x1D5E, 0x1D5E, 0x1D5E, 0x31A5, 0x31A5, 0x31A5, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x31A5, 0x31A5, 0x52A7, 0x1D5E, 0x1D5E, 0x1D5E, 0x1D5E, 0x1D5E, 0x1D5E, 0x1D5E, 0x1D5E, 0x52A7, 0x31A5, 0x31A5,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x31A5, 0x52A7, 0x1D5E, 0x1D5E, 0x1D5E, 0x1D5E, 0x1D5E,
 0x1D5E, 0x1D5E, 0x1D5E, 0x52A7, 0x31A5, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x31A5,
 0x52A7, 0x1D5E, 0x1D5E, 0x1D5E, 0x1D5E, 0x1D5E, 0x1D5E, 0x1D5E, 0x1D5E, 0x52A7, 0x31A5, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x2904, 0x31A5, 0x1D5E, 0x1D5E, 0x1D5E, 0x1D5E, 0x1D5E, 0x1D5E, 0x1D5E, 0x1D5E, 0x31A5,
 0x2904, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x2904, 0x2904, 0x1D5E, 0x1D5E,
 0x1D5E, 0x1D5E, 0x1D5E, 0x1D5E, 0x2904, 0x2904, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x2904, 0x2904, 0x2904, 0x2904, 0x2904, 0x2904, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000,

};

const unsigned short P2wins[] = {
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x4B72, 0x324C, 0x0000, 0x0000, 0x0000,
 0x0000, 0x324C, 0x4B72, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x8C6E, 0x8C6E, 0x6B6A, 0x0000, 0x0000, 0x6B6A, 0x8C6E, 0x8C6E, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x6B6A, 0x8C6E, 0x8C6E,
 0x8C6E, 0x8C6E, 0x8C6E, 0x8C6E, 0x6B6A, 0x2A2D, 0x2A2D, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x6B6A, 0x8C6E, 0x4C5D, 0x4C5D, 0x43CC, 0x4C5D, 0x8C6E, 0x2A2D, 0x4355, 0x4355,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0xC536, 0xF77D, 0x43CC, 0x5511, 0xF77D, 0x2A2D, 0x4355, 0x4355, 0x4355, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0xB67E, 0xB67E, 0x0000, 0x0000, 0x0000, 0x133D, 0x4C5D, 0x5511, 0x5511, 0x2A2D, 0x133D, 0x2A2D,
 0x4355, 0x0000, 0xB67E, 0xB67E, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xB67E, 0x6CB9, 0x0000,
 0x0000, 0x0000, 0xC536, 0xF77D, 0x5511, 0x5511, 0x4355, 0xC536, 0x2A2D, 0x2A2D, 0x0000, 0x6CB9, 0xB67E, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x6CB9, 0x6CB9, 0x0000, 0x0000, 0x133D, 0x133D, 0x5511, 0x5511, 0x133D,
 0x133D, 0x0000, 0x0000, 0x6CB9, 0x6CB9, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x6CB9, 0x133D, 0xF77D, 0xC536, 0x4355, 0x43CC, 0x43CC, 0xF77D, 0xC536, 0xF77D, 0x133D, 0x6CB9, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x133D, 0x8C72, 0x4355, 0x0000, 0x4A50,
 0x4A50, 0x0000, 0xF77D, 0x8C72, 0x133D, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x4A50, 0x6CB9, 0xB67E, 0x6CB9, 0x6CB9, 0xB67E, 0x6CB9, 0x4A50, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x4A50, 0xB67E, 0xB67E,
 0xB67E, 0xB67E, 0xB67E, 0xB67E, 0xB67E, 0xB67E, 0x4A50, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xB67E, 0xF77D, 0x0000, 0xB67E, 0xB67E, 0xB67E, 0xB67E, 0x0000, 0xF77D, 0xB67E,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x4A50, 0x6CB9,
 0xF77D, 0x2989, 0xB67E, 0x3437, 0xB67E, 0xB67E, 0x2989, 0xF77D, 0x6CB9, 0x4A50, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3437, 0x6CB9, 0x3437, 0x1105, 0x3437, 0x6E5C, 0x3437, 0x6CB9, 0x3437,
 0x3437, 0x3437, 0x3437, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x4A50, 0x6CB9, 0x3437,
 0x6E5C, 0x3437, 0x6E5C, 0x3437, 0x6E5C, 0x6E5C, 0x6E5C, 0x3437, 0x6E5C, 0x6E5C, 0x3437, 0x6E5C, 0x0000, 0x6CB9, 0x4A50, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x4A50, 0x3437, 0x6E5C, 0x3437, 0x6E5C, 0x6E5C, 0x3437, 0x6E5C, 0x7F5E, 0x7F5E,
 0x6E5C, 0x7F5E, 0x6E5C, 0x3437, 0x6E5C, 0x7F5E, 0x6CB9, 0x4A50, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3437, 0x4A50,
 0x3437, 0x6E5C, 0x3437, 0x6E5C, 0x7F5E, 0x3437, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x6E5C, 0x7F5E, 0x7F5E, 0x7F5E, 0x6CB9,
 0x4A50, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3437, 0x7F5E, 0x7F5E, 0x6E5C, 0x7F5E, 0x3437, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E,
 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x6E5C, 0x7F5E, 0x3437, 0x0000, 0x0000, 0x0000, 0x0000, 0x3437,
 0x3437, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E,
 0x7F5E, 0x6E5C, 0x7F5E, 0x7F5E, 0x3437, 0x0000, 0x0000, 0x0000, 0x0000, 0x3437, 0x6E5C, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E,
 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x3437, 0x0000, 0x0000,
 0x0000, 0x3437, 0x6E5C, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E,
 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x3437, 0x0000, 0x0000, 0x0000, 0x3437, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E,
 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x3437, 0x7F5E, 0x7F5E, 0x3437,
 0x0000, 0x0000, 0x0000, 0x3437, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E,
 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x3437, 0x7F5E, 0x3437, 0x0000, 0x0000, 0x0000, 0x3437, 0x7F5E, 0x7F5E, 0x3437,
 0x6E5C, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x7F5E, 0x3437, 0x3437, 0x7F5E, 0x3437,
 0x3437, 0x3437, 0x0000, 0x0000, 0x0000, 0x0000, 0x3437, 0x7F5E, 0x3437, 0x7F5E, 0x7F5E, 0x3437, 0x3437, 0x7F5E, 0x7F5E, 0x7F5E,
 0x7F5E, 0x7F5E, 0x7F5E, 0x3437, 0x3437, 0x0000, 0x0000, 0x3437, 0x3437, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x3437, 0x0000, 0x3437, 0x7F5E, 0x3437, 0x0000, 0x3437, 0x3437, 0x3437, 0x3437, 0x3437, 0x3437, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3437, 0x3437, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,

};



//inputs: none
//outputs: CHARSEL if play again. Else, stay and output thank you
uint32_t DisplayResults(uint8_t p1wins, uint8_t p2wins){
	
	uint16_t white = ST7735_Color565(250, 250, 250);
	uint16_t black = ST7735_Color565(0, 0, 0);
	uint32_t pos;
	uint8_t select;

	if(p1wins > p2wins){ //player wins scenario
		Sound_Win();
		ST7735_DrawChar(54, 5, 'W', 0x20FD, 0x0000, 3);
		ST7735_DrawChar(73, 5, 'I', 0x20FD, 0x0000, 3);
		ST7735_DrawChar(92, 5, 'N', 0x20FD, 0x0000, 3);
		//ST7735_DrawBitmap(57, 56, P1wins, 22, 30);
	}
	
	else if(p1wins < p2wins){ //player loses scenario
		Sound_Lose();
		ST7735_DrawChar(47, 5, 'L', 0xF800, 0x0000, 3);
		ST7735_DrawChar(65, 5, 'O', 0xF800, 0x0000, 3);
		ST7735_DrawChar(83, 5, 'S', 0xF800, 0x0000, 3);
		ST7735_DrawChar(101, 5, 'E', 0xF800, 0x0000, 3);
		//ST7735_DrawBitmap(57, 56, P2wins, 25, 30);
	}
	
	ST7735_DrawChar(54, 30, (p1wins + 0x30), 0xFFFF, 0x0000, 2);
	ST7735_DrawChar(75, 30, '-', 0xFFFF, 0x0000, 2);
	ST7735_DrawChar(97, 30, (p2wins + 0x30), 0xFFFF, 0x0000, 2);
	Delay10ms(40);
	while((GPIO_PORTE_DATA_R&0x3B) == 0);
	Sound_Init(7256);
	Sound_Select();
	Delay10ms(50);
	ST7735_FillScreen(0x0000);
	ST7735_SetCursor(8, 5);
	ST7735_OutString("Play again?");
	ST7735_SetCursor(9, 6);
	ST7735_OutString("Yes");
	ST7735_SetCursor(9, 7);
	ST7735_OutString("No");
	while((GPIO_PORTE_DATA_R&0x3B) == 0){
		pos = ADC_In();
		if(pos <= 2047){
			ST7735_SetCursor(8, 6);
			ST7735_OutString(">");
			ST7735_SetCursor(8, 7);
			ST7735_OutChar(' ');
			select = TITLE;
		}
		else{
			ST7735_SetCursor(8, 7);
			ST7735_OutString(">");
			ST7735_SetCursor(8, 6);
			ST7735_OutChar(' ');
			select = 0xFF;
		}
	}
	Sound_Select();
	ST7735_FillScreen(0x0000);
	while(select == 0xFF){
		ST7735_DrawChar(6, 10, 'T', 0xFFFF, 0x0000, 1);
		ST7735_DrawChar(14, 10, 'h', 0xFFFF, 0x0000, 1);
		ST7735_DrawChar(22, 10, 'a', 0xFFFF, 0x0000, 1);
		ST7735_DrawChar(30, 10, 'n', 0xFFFF, 0x0000, 1);
		ST7735_DrawChar(38, 10, 'k', 0xFFFF, 0x0000, 1);
		ST7735_DrawChar(46, 10, 's', 0xFFFF, 0x0000, 1);
		ST7735_DrawChar(54, 10, ' ', 0xFFFF, 0x0000, 1);
		ST7735_DrawChar(62, 10, 'f', 0xFFFF, 0x0000, 1);
		ST7735_DrawChar(70, 10, 'o', 0xFFFF, 0x0000, 1);
		ST7735_DrawChar(78, 10, 'r', 0xFFFF, 0x0000, 1);
		ST7735_DrawChar(86, 10, ' ', 0xFFFF, 0x0000, 1);
		ST7735_DrawChar(94, 10, 'p', 0xFFFF, 0x0000, 1);
		ST7735_DrawChar(102, 10, 'l', 0xFFFF, 0x0000, 1);
		ST7735_DrawChar(110, 10, 'a', 0xFFFF, 0x0000, 1);
		ST7735_DrawChar(118, 10, 'y', 0xFFFF, 0x0000, 1);
		ST7735_DrawChar(126, 10, 'i', 0xFFFF, 0x0000, 1);
		ST7735_DrawChar(134, 10, 'n', 0xFFFF, 0x0000, 1);
		ST7735_DrawChar(142, 10, 'g', 0xFFFF, 0x0000, 1);
		ST7735_DrawChar(150, 10, '!', 0xFFFF, 0x0000, 1);
		
		ST7735_SetCursor(1, 5);
		ST7735_OutString(" -Genki Oji");
		ST7735_SetCursor(1, 8);
		ST7735_OutString(" -David Yu");
	}
	return select;
}

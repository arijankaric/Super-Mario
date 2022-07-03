#pragma once

#define PRITISNUTO(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

#define COIN 101
#define QUESTIONMARK 102
#define PIPE 103
#define STANDING 104
#define UNKNOWN 105 // state that's to be decided in the next for loop
#define GROUND 106
#define DEATHGROUND 107
#define FLOWER_ENEMY 108
#define FIREBALL_ENEMY 109
#define FIREBALL_FRIENDLY 110
#define GOOMBA 111
#define WALKING 112
#define WALKING_RIGHT 113
#define WALKING_LEFT 114
#define FALLING 115
#define JUMPING 116
#define NEUTRAL 117
#define LEFT 118
#define RIGHT 119
#define UP 120
#define DOWN 121
#define HILL 122


#define SIRINAPROZORA 240
#define VISINAPROZORA 320





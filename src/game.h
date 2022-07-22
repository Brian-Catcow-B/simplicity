#ifndef GAME_H
#define GAME_H

#include "creature.h"

typedef enum e_state_t {
	e_state_naming_character,
	e_state_fighting_creature,
	e_state_exiting,
} e_state_t;

typedef struct context_t {
	int text_pause_length_s;
	char *character_name;
	int character_hp;
	int character_dodge_chance_percent;
	int character_dmg_per_attack;
	creature_t *enemy_creature;
	bool characters_turn;
	e_state_t state;
	e_creature_t input_creature_type;
} context_t;

void init_context(context_t *self);

#endif // GAME_H


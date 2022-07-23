#include "creature.h"
#include "creature_luts.h"
#include <stdlib.h>
#include "misc.h"

void init_creature(creature_t *self, e_creature_t type_in) {
	if (type_in < 0 || type_in >= e_creature_NUM_VALUES)
		self->type = rand() % e_creature_NUM_VALUES;
	else
		self->type = type_in;

	self->name = creature_names[self->type];
	self->hp = rand_between(creature_min_hps[self->type], creature_max_hps[self->type]);
	self->dmg_per_attack = rand_between(creature_min_dpas[self->type], creature_max_dpas[self->type]);
	self->dodge_chance_percent = creature_dodge_chance_percents[self->type];
}


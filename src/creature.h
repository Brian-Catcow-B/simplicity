#ifndef CREATURE_H
#define CREATURE_H

typedef enum e_creature_t {
	e_creature_whale,
	e_creature_kangaroo,
	e_creature_bionic_squid,
	e_creature_crazed_wizard,
	e_creature_wild_josh,
	e_creature_mosquito,
	e_creature_chester,
	e_creature_NUM_VALUES,
} e_creature_t;

typedef struct creature_t {
	e_creature_t type;
	const char *name;
	int hp;
	int dmg_per_attack;
	int dodge_chance_percent;
} creature_t;

void init_creature(creature_t *self, e_creature_t type_in);

#endif // CREATURE_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "game.h"

#define GET_RAND_LUT_STR(lut) \
	lut[rand() % (sizeof(lut) / sizeof(char *))];

void get_user_input(char *into);

static const char *places[] = {
	"The pagoda that holds the Biggest Ball of Twine in Minnesota",
	"Wisconsin",
	"Russia",
	"a box under the stairs in the corner of the basement of the house half a block down the street from Jerry's Bait Shop",
};

static const char *person_titles[] = {
	"woman",
	"man",
	"weasel",
	"idiot",
	"genius",
	"fiend",
	"coder",
};

static const char *describers[] = {
	"elderly",
	"young",
	"colorful",
	"pathetic",
	"cute",
	"triumphant",
};

static const char *careless_verbs[] = {
	"strolling along a path",
	"hanging out in a brothel",
	"playing Minecraft",
	"coding a hentai game",
	"thinking about big mommy milkers",
	"counting to one million for the third time that day",
	"constructing new ligma jokes",
	"daydreaming in the car",
	"drinking gamer fuel",
	"picking up beach babes",
};

// =============================================

void init_context(context_t *self) {
	self->text_pause_length_s = 2;
	self->character_name = malloc(sizeof(char) * (CHARNAME_MAX_LEN + 1));
	self->character_hp = rand_between(100, 150);
	self->character_dodge_chance_percent = rand_between(5, 20);
	self->character_dmg_per_attack = rand_between(20, 35);
	self->enemy_creature = NULL;
	self->characters_turn = false;
	self->state = e_state_naming_character;
	self->input_creature_type = -1;
}

void deinit_context(context_t *self) {
	free(self->character_name);
}

// ====================================================

void name_character(context_t *c) {
	printf("Enter this character's name\n");
	get_user_input(c->character_name);
}

#define TEXT_SLEEP(__cp) fflush(NULL); usleep(20000 * __cp)
void story_telling(context_t *c) {
	const char *describer = GET_RAND_LUT_STR(describers);
	const char *person_title = GET_RAND_LUT_STR(person_titles);
	const char *place = GET_RAND_LUT_STR(places);
	const char *careless_verb = GET_RAND_LUT_STR(careless_verbs);

	int cp;
	cp = printf("%s", c->character_name);
	TEXT_SLEEP(cp);
	cp = printf(" is a %s", describer);
	TEXT_SLEEP(cp);
	cp = printf(" %s", person_title);
	TEXT_SLEEP(cp);
	cp = printf(" from %s.\n", place);
	TEXT_SLEEP(cp);
	sleep(1);
	cp = printf("One day, ");
	TEXT_SLEEP(cp);
	cp = printf("%s was", c->character_name);
	TEXT_SLEEP(cp);
	cp = printf(" %s,", careless_verb);
	TEXT_SLEEP(cp);
	cp = printf(" when suddenly...\n");
	TEXT_SLEEP(cp);
	sleep(1);
}

typedef enum e_player_statmod_t {
	e_player_statmod_none          = 0x00,
	e_player_statmod_dodge         = 0x01,
	e_player_statmod_dodge_success = 0x02,
	e_player_statmod_focus         = 0x04,
	e_player_statmod_raisedef      = 0x08,
} e_player_statmod_t;

void debug_print_player_statmod(e_player_statmod_t s) {
	printf("statmod: 0x%02x\n", s);
	printf("\tdodge:\t%d\n", (s & e_player_statmod_dodge) != 0);
	printf("\td_success:\t%d\n", (s & e_player_statmod_dodge_success) != 0);
	printf("\tfocus:\t%d\n", (s & e_player_statmod_focus) != 0);
	printf("\traisedef:\t%d\n", (s & e_player_statmod_raisedef) != 0);
	printf("\n");
}

void fight_sequence_start(context_t *c);

void creature_fight_sequence(context_t *c) {
	creature_t enemy;
	init_creature(&enemy, c->input_creature_type);
	c->enemy_creature = &enemy;

	char user_input[100];
	e_player_statmod_t statmod = e_player_statmod_none;
	int focus_turns = 0;
	int raisedef_turns = 0;
	c->characters_turn = rand() % 4;

	usleep(30000 * printf("%s notices an aggressive %s!\n", c->character_name, enemy.name));
	sleep(1);
	if (c->characters_turn)
		printf("%s approaches the %s with initiative!\n", c->character_name, enemy.name);
	else
		printf("%s stumbles as the %s approaches!\n", c->character_name, enemy.name);

	printf("\n\n");

	while (enemy.hp > 0 && c->character_hp > 0) {
		sleep(c->text_pause_length_s);
		if (c->characters_turn) {
			printf("%s has %d hp\n", c->character_name, c->character_hp);
			printf("%s thinks the %s has about %d hp\n", c->character_name, enemy.name, max(1, enemy.hp + (rand() % 20 - 10)));

j_user_action_input:
			printf("Choose an action:\n"
					"\tattack \t[a] -- Deals damage, given that the target doesn't dodge\n"
					"\tdodge \t[d] -- Increases dodge chance this turn; gives crit chance and hit chance on success for the next turn\n"
					"\tfocus \t[f] -- Increases attack for the next 2 turns; does not stack\n"
					"\traiseD \t[r] -- Increases defense for this turn and the next 2 turns; does not stack\n");
			get_user_input(user_input);
			if (strcmp(user_input, "attack") == 0 || strcmp(user_input, "a") == 0) {
				sleep(c->text_pause_length_s);
				if (statmod & e_player_statmod_dodge_success)
				{
					printf("%s seems to follow the %s's movements better this attack\n", c->character_name, enemy.name);
				}
				if (rand() % 100 >= enemy.dodge_chance_percent && (!(statmod & e_player_statmod_dodge_success) || rand() % 100 >= enemy.dodge_chance_percent))
				{
					int output_damage = c->character_dmg_per_attack;
					if (statmod & e_player_statmod_focus)
					{
						printf("%s's focus powers up the attack!\n", c->character_name);
						output_damage += output_damage / 4;
					}
					if ((statmod & e_player_statmod_dodge_success) && !(rand() % 4))
					{
						printf("CRITICAL HIT!!\n");
						printf("The %s took huge damage!\n", enemy.name);
						enemy.hp -= output_damage * rand_between(2, 4);
					} else {
						printf("The %s got hit!\n", enemy.name);
						enemy.hp -= output_damage;
					}
				}
				else
				{
					printf("The %s dodged!\n", enemy.name);
				}
			} else if (strcmp(user_input, "dodge") == 0 || strcmp(user_input, "d") == 0) {
				sleep(c->text_pause_length_s);
				printf("%s is dodging\n", c->character_name);
				statmod |= e_player_statmod_dodge;
			} else if (strcmp(user_input, "focus") == 0 || strcmp(user_input, "f") == 0) {
				sleep(c->text_pause_length_s);
				printf("%s is focusing for their next attack.\n", c->character_name);
				statmod |= e_player_statmod_focus;
				focus_turns = 3;
			} else if (strcmp(user_input, "raiseD") == 0 || strcmp(user_input, "r") == 0) {
				sleep(c->text_pause_length_s);
				printf("%s increases their defense for the next 3 turns.\n", c->character_name);
				statmod |= e_player_statmod_raisedef;
				raisedef_turns = 3;
			} else {
				printf("invalid option: %s\n", user_input);
				goto j_user_action_input;
			}
		} else {
			statmod &= ~e_player_statmod_dodge_success;
			switch (rand() % 5) {
				case 0:
				case 1:
					printf("%s attacks!\n", enemy.name);
					sleep(c->text_pause_length_s);
					if (rand() % 100 >= c->character_dodge_chance_percent) {
						if (!(statmod & e_player_statmod_dodge) || rand() % 100 >= c->character_dodge_chance_percent) {
							int output_damage = enemy.dmg_per_attack;
							if (statmod & e_player_statmod_raisedef) {
								output_damage -= output_damage / 4;
							}
							c->character_hp -= output_damage;
							printf("%s got slammed for %d hp!\n", c->character_name, output_damage);
							break;
						}
					}
					enemy.dmg_per_attack = max(1, enemy.dmg_per_attack - 3);
					printf("%s dodged! The %s loses some confidence!\n", c->character_name, enemy.name);
					if (statmod & e_player_statmod_dodge) {
						printf("%s gains attack stats for successful dodge\n", c->character_name);
						statmod |= e_player_statmod_dodge_success;
					}
					break;
				case 2:
				case 3:
					enemy.dmg_per_attack += 11;
					printf("The %s is going Super Saiyan!\n", enemy.name);
					break;
				case 4:
					printf("The %s is derping around. Idiot.\n", enemy.name);
					break;
				default:
					break;
			}
			focus_turns = max(0, focus_turns - 1);
			raisedef_turns = max(0, raisedef_turns - 1);

			if (!focus_turns) {
				statmod &= ~e_player_statmod_focus;
			}
			if (!raisedef_turns) {
				statmod &= ~e_player_statmod_raisedef;
			}
			statmod &= ~e_player_statmod_dodge;
		}

		c->characters_turn = !c->characters_turn;
		printf("\n\n");
	}

	if (c->character_hp <= 0) {
		printf("%s slowly bled out... Unfortunate!\n", c->character_name);
	} else if (enemy.hp <= 0) {
		printf("The %s suffered a terrible, greusome death at the hand of %s!\n", enemy.name, c->character_name);
	}

	sleep(c->text_pause_length_s);
	c->state = e_state_exiting;
	c->enemy_creature = NULL;
}

void fight_creature_start(context_t *c) {

}


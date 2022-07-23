#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "misc.h"
#include "game.h"
#include "creature_luts.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

int main(int argc, char **argv)
{
	assert(e_creature_NUM_VALUES == (sizeof(creature_names) / sizeof(char *)));

	srand(time(0));

	struct context_t c;
	init_context(&c);

	int opt;
	while ((opt = getopt(argc, argv, ":e:h")) != -1) {
		switch (opt) {
			case 'h':
				printf("usage: %s [options]\n\t-h -- print help\n\t-e <enemy_name> -- play with specified enemy\n", argv[0]);
				return EXIT_SUCCESS;
			case 'e':
				for (size_t i = 0; i < e_creature_NUM_VALUES; i++) {
					if (strcmp(creature_names[i], optarg) == 0) {
						c.input_creature_type = (e_creature_t) i;
						goto break_case_e;
					}
				}
				printf("invalid enemy name: %s\n\tvalid values: ", optarg);
				for (size_t i = 0; i < e_creature_NUM_VALUES; i++) {
					printf("%s, ", creature_names[i]);
				}
				printf("\n");
				return EXIT_FAILURE;
break_case_e:
				break;
			case '?':
				printf("unknown value: %c\n", opt);
				return EXIT_FAILURE;
		}
	}

	while (1) {
		switch (c.state) {
			case e_state_naming_character:
				name_character(&c);
				story_telling(&c);
				c.state = e_state_fighting_creature;
				break;
			case e_state_fighting_creature:
				creature_fight_sequence(&c);
				break;
			case e_state_exiting:
				goto clean_exit;
		}
	}

clean_exit:
	deinit_context(&c);
	return EXIT_SUCCESS;
}


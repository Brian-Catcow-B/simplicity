#ifndef CREATURE_LUTS_H
#define CREATURE_LUTS_H

static const char *creature_names[] = {
	"whale",
	"kangaroo",
	"bionic squid",
	"crazed wizard",
	"wild Josh",
	"mosquito",
	"Chester",
};

static const int creature_min_hps[] = {
	250,
	80,
	120,
	50,
	150,
	10,
	60,
};

static const int creature_max_hps[] = {
	400,
	120,
	200,
	70,
	200,
	20,
	100,
};

static const int creature_min_dpas[] = {
	10,
	13,
	18,
	9,
	20,
	1,
	15,
};

static const int creature_max_dpas[] = {
	15,
	30,
	35,
	69,
	50,
	5,
	30,
};

static const int creature_dodge_chance_percents[] = {
	5,
 	40,
	25,
	30,
	15,
	90,
	1,
};

#endif // CREATURE_LUTS_H


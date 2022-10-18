#include "commons.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static data_t flags_get_value(uint8_t type, char *v) {
	switch (type) {
		case 0: return NEW_DATA(uint64, atoi(v));
		case 1: return NEW_DATA(ptr, v);
	}

	return DATA_NULL;
}

int commons_get_flags(flags_info_t flags_info, int argc, char **argv) {
	int i = 1;
	int fi;

	for (; i < argc && argv[i][fi = 0] == '-'; i++) {
		if (argv[i][++fi] == '-') {
			int se = fi++;
			while (argv[i][++se] && argv[i][se] != '=') {}

			int h = 0;
			for (; h < flags_info.flags_n; h++) {
				if (!(strncmp(argv[i] + fi, flags_info.flags_fullname[h], se - fi))) {
					if (argv[i][se]) {
						flags_info.flags[h] = flags_get_value(flags_info.flags_type[h], argv[i] + se + 1);
						break;
					}
					flags_info.flags[h] = flags_info.flags_iival[h];
					/*if (argv[i][se]) {
						flags[h] = argv[i][se + 1] - 48;
						break;
					}
					flags[h] = 1;*/
				}
			}
			continue;
		}

		int h = 0;
		for (; h < flags_info.flags_n; h++) {
			if (argv[i][fi] == flags_info.flags_name[h]) {
				if (argv[i][++fi]) {
					flags_info.flags[h] = flags_get_value(flags_info.flags_type[h], argv[i] + fi + 1);
					break;
				}
				flags_info.flags[h] = flags_info.flags_iival[h];
				/*if (argv[i][++fi]) {
					flags[h] = argv[i][fi + 1] - 48;
					break;
				}
				flags[h] = 1;*/
			}
		}
	}

	return i;
}

void commons_print_flags(flags_info_t flags_info) {
	int i = 0;
	for (; i < flags_info.flags_n; i++) {
		printf("--%s (-%c) = ", flags_info.flags_fullname[i], flags_info.flags_name[i]);
		switch (flags_info.flags_type[i]) {
			case 0: printf("" ENV_FORMAT_INT64_DEC "\n", flags_info.flags[i].uint64); break;
			case 1: printf("'%s'\n", (char*) flags_info.flags[i].ptr); break;
		}
	}
}
#include "file.h"

#include <stdlib.h>
#include <string.h>
//#include <unistd.h>
//#include <limits.h>

bfr_t* file_read_bfile_from_file(FILE *file) {
	if (file == NULL) return NULL;

	fseek(file, 0L, SEEK_END);

	size_t size = ftell(file);
	bfr_t *bfr = bfr_init((uint8_t*) malloc(size * sizeof(uint8_t)), size);

	rewind(file);

	fread(bfr->bfr, size, sizeof(uint8_t), file);

	return bfr;
}

bfr_t* file_read_tfile_from_file(FILE *file) {
	bfr_t *bfr;
	if ((bfr = file_read_bfile_from_file(file)) == NULL) return NULL;

	bfr->bfr = realloc(bfr->bfr, (bfr->size + 1) * sizeof(char));
	bfr->bfr[bfr->size++] = 0;
	bfr->index++;

	return bfr;
}

bfr_t* file_read_bfile(const char *name) {
	FILE *file = fopen(name, "r");
	bfr_t *bfr = file_read_bfile_from_file(file);

	fclose(file);
	return bfr;
}

bfr_t* file_read_tfile(const char *name) {
	FILE *file = fopen(name, "r");

	bfr_t *bfr = file_read_tfile_from_file(file);
	if (bfr == NULL) return NULL;

	fclose(file);
	return bfr;
}

/*bfr_t* file_read_bfile_spath(char *dir_path, char *file_path) {
	char cwd[PATH_MAX];
	if (getcwd(cwd, PATH_MAX) != NULL) {
		chdir(dir_path);
		bfr_t *bfr = file_read_bfile(file_path);
		chdir(cwd);

		return bfr;
	}

	return NULL;
}

bfr_t* file_read_tfile_spath(char *dir_path, char *file_path) {
	char cwd[PATH_MAX];
	if (getcwd(cwd, PATH_MAX) != NULL) {
		chdir(dir_path);
		bfr_t *bfr = file_read_tfile(file_path);
		chdir(cwd);

		return bfr;
	}

	return NULL;
}*/



uint8_t file_write_file_from_file(FILE *file, bfr_t *bfr) {
	if (file == NULL)
		return 0;

	fwrite(bfr->bfr, 1, bfr->size, file);
	return 1;
}

uint8_t file_write_file(const char *name, bfr_t *bfr) {
	FILE *file = fopen(name, "w+");

	if (!file_write_file_from_file(file, bfr))
		return 0;

	fclose(file);
	return 1;
}



char* file_get_extension(const char *name) {
    char *dot = strrchr(name, '.');

    if(dot == NULL || dot == name)
		return "";
    return dot + 1;
}



size_t file_get_line(char **line, FILE *file) {
	*line = malloc(FILE_GET_LINE_BFR_START_SIZE * sizeof(char));
	size_t line_i = 0, line_s = FILE_GET_LINE_BFR_START_SIZE;
	int ch;

	while ((ch = fgetc(file)) != EOF && ch != '\n') {
		(*line)[line_i++] = (char) ch;

		if (line_i == line_s) //by doing this after the increment, we will be sure to always have space for the null terminator, because we are still doing it even if the new current character is a '\n' or an eof and would be discarded on the next iteration
			*line = realloc(*line, (line_s <<= 2) * sizeof(char));
	}

	(*line)[line_i] = 0;

	return line_i;
}
#pragma once

#ifndef __FILE_H
#define __FILE_H

#define FILE_GET_LINE_BFR_START_SIZE								10 //always greater than 0

#include "commons.h"
#include "bfr.h"

#include <stdio.h>

bfr_t* file_read_bfile_from_file(FILE *file);
bfr_t* file_read_tfile_from_file(FILE *file);

bfr_t* file_read_bfile(const char *name);
bfr_t* file_read_tfile(const char *name);
//bfr_t* file_read_bfile_spath(char *dir_path, char *file_path);
//bfr_t* file_read_tfile_spath(char *dir_path, char *file_path);

uint8_t file_write_file_from_file(FILE *file, bfr_t *bfr);
uint8_t file_write_file(const char *name, bfr_t *bfr);

char* file_get_extension(const char *name);

size_t file_get_line(char **line, FILE *file);

#endif
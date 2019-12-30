#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ff.h"


int parseoct(const char *p, size_t n);
int is_end_of_archive(const char *p);
void create_dir(char *pathname);
FIL create_file(char *pathname);
int verify_checksum(const char *p);
void untar(char *srcBuf, unsigned int srcSize, const char *path);

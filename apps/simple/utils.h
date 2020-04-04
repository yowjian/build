#pragma once

extern int display_interval;

extern enclave_t *all_enclaves;

unsigned long long get_time();
char *center(char *str, int width, char **dst);
long long get_interval(int hz);
int get_int(char *str);
char *trim(char *str);
void *init_hal();
void init_time(stats_type *nums);
void close_time(stats_type *nums);
void encode_timestamp(trailer_datatype *trailer);
unsigned long long decode_timestamp(trailer_datatype *trailer);
void cal_char(stats_type *nums, trailer_datatype *trailer);
void init_locks();

void show_stats();
void init_stats(int hz_dis, int hz_pos);

void usage();
void parse(int argc, char **argv);

flow_t *find_flow(int id);
enclave_t *find_enclave(char *name);

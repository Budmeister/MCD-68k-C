#ifndef SREC_H
#define SREC_H

void run_program_as_user(void* start);
void parse_srec();
void load_srec();

extern usize_t (*loaded_program)();

#endif
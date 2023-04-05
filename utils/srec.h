#ifndef SREC_H
#define SREC_H

void parse_srec();
void load_srec();

extern usize_t (*loaded_program)(usize_t, char**);

#endif
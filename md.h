#pragma once
bool file2str(const char* fname, char* str);
state* str2state(const char* str);
int solve(state* s, bool verbose);


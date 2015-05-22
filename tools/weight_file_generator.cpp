// Code by duck

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

//using namespace std;

#include "Session.cpp"

char s[BUF_SIZE];
int main(int argc, char **argv) {
    if (argc!=4) {
        puts("Usage:");
        puts("\tweight_file_generator libsvm_fmt_data 0_weight 1_weight");
        return 0;
    }
    FILE *in = fopen(argv[1], "r"), *out = fopen(strcat(strcpy(s,argv[1]), ".weight"), "w");
    int label;
    float weight[2];
    if (!in)  { puts("libsvm_fmt_data open error."); return 0; }
    if (!out) { puts("weight file open error."); return 0; }
    if (sscanf(argv[2], "%f", weight+0)!=1) { puts("0_weight wrong."); return 0; }
    if (sscanf(argv[3], "%f", weight+1)!=1) { puts("1_weight wrong."); return 0; }
    
    puts("initializing ok.");
    while (!feof(in)) {
        if (!fgets(s, BUF_SIZE, in)) break;
        sscanf(s, "%d", &label);
        fprintf(out, "%.2f\n", weight[label]);
    }
    fclose(in);
    fclose(out);
    puts("Done");


	return 0;
}


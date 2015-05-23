// Code by duck

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <ctime>

//using namespace std;
const int BUF_SIZE = 10000000;
char s[BUF_SIZE];
int main(int argc, char **argv) {
    if (argc!=2) {
        puts("Usage:");
        puts("\tmake_partial_valid_data svm_fmt_data");
        puts("\t\tThis is NOT RANDOM. You will get same output every time you use it.");
        return 0;
    }
    FILE *in = fopen(argv[1], "r"), *outp, *outv;
    if (!in) { puts("item_id_table.txt open error."); return 0; }
    strcpy(s, argv[1]);
    s[strlen(s)-4] = '\0';
    strcat(s, "-parital.dat");
    outp = fopen(s, "w");
    if (!outp) { puts("out partial file open error."); return 0; }
    strcpy(s, argv[1]);
    s[strlen(s)-4] = '\0';
    strcat(s, "-valid.dat");
    outv = fopen(s, "w");
    if (!outv) { puts("out valod file open error."); return 0; }
    //srand(time(NULL));

    while (!feof(in)) {
        fgets(s, BUF_SIZE, in);
        if (rand()%5)
            fputs(s, outp);
        else 
            fputs(s, outv);
    }
    puts("Done");
    
	return 0;
}


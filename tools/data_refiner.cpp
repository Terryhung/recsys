// Code by duck

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

#include "Session.cpp"

//using namespace std;

int main(int argc, char **argv) {
    
    Session sn = Session(Session::CLICK);
    int thres = 1;
    
    if (argc!=4) {
        puts("usage:");
        puts("\tdata_refiner bin_data_name out_data_name threshold");
        puts("\t\twill only save session with num_click>threshold");
        return 0;
    }
    FILE *f = fopen(argv[1], "rb"), *out = fopen(argv[2], "wb");
    if (f)
        puts("ready to read");
    else {
        puts("file open error");
        exit(0);
    }
    sscanf(argv[3], "%d", &thres);
    while (sn.read_binary(f), sn.id()!=0) {
        if (sn.len()>thres) {
            sn.write_binary(out);
        }
    }
    sn.write_binary(out);
    puts("done");
    fclose(out);
    
	return 0;
}


// Code by duck

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

//using namespace std;

#include "Session.cpp"

int print_table(int *tab, int sy, int sx) {
    for (int i=0; i<sy; i++ ){
        printf("    ");
        for (int j=0; j<sx; j++)
            printf("  %2d:%8d", i*sx+j, tab[i*sx+j]);
        puts("");
    }
}

int main(int argc, char** argv) {
    Session sn = Session(Session::CLICK);
    if (argc!=2) {
        puts("usage:");
        puts("\tbindata_reader_no_output_file bin_data_name");
        return 0;
    }
    FILE *f = fopen(argv[1], "rb");
    if (f)
        fprintf(stderr, "ready to read");
    else {
        fprintf(stderr, "file open error");
        exit(0);
    }
    int cate[16];
    int month[12];
    int hour[24];
    memset(cate, 0, sizeof(cate));
    memset(month, 0, sizeof(month));
    memset(hour, 0, sizeof(hour));
    fprintf(stderr, "reading data...");
    int num_session=0, num_click=0;
    while (sn.read_binary(f), !sn.empty()) {
        num_session++;
        for (int i=0; i<sn.len(); i++) {
            num_click++;
            cate[sn.click(i).cate<=12 ? (sn.click(i).cate>=0 ? sn.click(i).cate : 13) : 14 ]++;
            month[sn.click(i).m()]++;
            hour[sn.click(i).h()]++;
        }
    }
    printf("#Session : %d\n", num_session);
    printf("#clicks : %d\n", num_click);
    printf("# of items in each cate:\n\
\t(13 for special offers, 14 for # items of other brand)\n");
    print_table(cate, 4, 4);
    printf("# of items in each month:\n");
    print_table(month, 3, 4);
    printf("# of items in each hour:\n");
    print_table(hour, 6, 4);
	return 0;
}


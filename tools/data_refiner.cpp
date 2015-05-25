// Code by duck

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

#include "Session.cpp"

using namespace std;

#include <map>

map<unsigned int,int> get_item_id_click_map() {
    FILE *f = fopen("./item_id_table.txt", "r");
    int pos, id, num;
    map<unsigned int,int> res;
    while (!feof(f)) {
        if (fscanf(f, "%d:%d:%d", &pos, &id, &num)<3) break;
        res[id] = num;
    }
    fclose(f);
    return res;
}

int thres_se = 1, thres_it = 0;
map<unsigned int,int> beclick_mp;

bool comp_func(ClickInfo ci) {
    return beclick_mp[ci.item_id]<=thres_it;
}

int main(int argc, char **argv) {
    
    Session sn = Session(Session::CLICK);
    
    if (argc!=5) {
        puts("usage:");
        puts("\tdata_refiner bin_data_name out_data_name threshold1 threshold2");
        puts("\t\twill only save session with legal_num_click>threshold1");
        puts("\t\tlegal_num_click means only item with #(be clicked)>threshold2 will be counted.");
        puts("\t\tthreshold2=0 is ok.");
        puts("\t\tAlso, imformation of #(be clicked)<=threshold2 will be discarded.");
        puts("\tShould execute this program in \'recsys\' folder.");
        return 0;
    }

    FILE *f = fopen(argv[1], "rb"), *out = fopen(argv[2], "wb");
    if (f)
        puts("ready to read");
    else {
        puts("file open error");
        exit(0);
    }
    beclick_mp = get_item_id_click_map();
    sscanf(argv[3], "%d", &thres_se);
    sscanf(argv[4], "%d", &thres_it);
    while (sn.read_binary(f), sn.id()!=0) {
        sn.remove_items(comp_func);
        if (sn.len()>thres_se) {
            sn.write_binary(out);
        }
    }
    sn.write_binary(out);
    puts("done");
    fclose(out);
    
	return 0;
}


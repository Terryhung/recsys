// Code by duck

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

#include <map>
#include <vector>


#include "Session.cpp"

using namespace std;

int print_table(int *tab, int sy, int sx) {
    for (int i=0; i<sy; i++ ){
        printf("    ");
        for (int j=0; j<sx; j++)
            printf("  %2d:%8d", i*sx+j, tab[i*sx+j]);
        puts("");
    }
}
vector<int> make_mapping_table(map<int, int> mp) {
    vector<int> res;
    for (map<int, int>::iterator it=mp.begin(); it!=mp.end(); it++)
        res.push_back(it->first);
    sort(res.begin(), res.end());
    return res;
}
int main(int argc, char** argv) {
    Session sn = Session(Session::CLICK);
    if (argc!=2) {
        puts("usage:");
        puts("\tbindata_reader bin_data_name");
    }
    FILE *f = fopen(argv[1], "rb");
    if (f)
        puts("ready to read");
    else {
        puts("file open error");
        exit(0);
    }
    unsigned int mn = ~0, mx=0;
    map<int, int> mp_item_id, mp_brand;
    int cate[16];
    int month[12];
    int hour[24];
    vector<int> item_id_table, brand_table;
    memset(cate, 0, sizeof(cate));
    memset(month, 0, sizeof(month));
    memset(hour, 0, sizeof(hour));
    FILE *out_item_id = fopen("item_id_table.txt", "w");
    FILE *out_brand = fopen("brand_table.txt", "w");
    if (!out_item_id) { puts("fopen item_id error"); return 0; }
    if (!out_brand) { puts("fopen brand error"); return 0; }
    while (sn.read_binary(f), !sn.empty()) {
        for (int i=0; i<sn.len(); i++ ) {
            mn = std::min(mn, sn.click(i).item_id); 
            mx = std::max(mx, sn.click(i).item_id); 
            if (mp_item_id.find(sn.click(i).item_id)!=mp_item_id.end()) {
                mp_item_id[sn.click(i).item_id] = mp_item_id[sn.click(i).item_id] + 1;
            } else {
                mp_item_id[sn.click(i).item_id] = 1;
            }
            if (sn.click(i).cate>12) {
                if (mp_brand.find(sn.click(i).cate)!=mp_brand.end()) {
                    mp_brand[sn.click(i).cate] = mp_brand[sn.click(i).item_id] + 1;
                } else {
                    mp_brand[sn.click(i).item_id] = 1;
                }
            }
            cate[sn.click(i).cate<=12 ? sn.click(i).cate>=1 ? sn.click(i).cate : 13 : 14 ]++;
            month[sn.click(i).m()]++;
            hour[sn.click(i).h()]++;
        }
    }
    printf("min of item id:%d\n", mn);
    printf("max of item id:%d\n", mx);
    printf("total number of item:%lu\n", mp_item_id.size());
    printf("# of items in each cate:\n\
\t(13 for special offers, 14 for # of other brand, 15 for # items of other brand)\n");
    print_table(cate, 4, 4);
    printf("# of items in each month:\n");
    print_table(month, 3, 4);
    printf("# of items in each hour:\n");
    print_table(hour, 6, 4);
    item_id_table = make_mapping_table(mp_item_id);
    brand_table = make_mapping_table(mp_brand);
    for (int i=0; i<item_id_table.size(); i++)
        fprintf(out_item_id, "%d:%d:%d\n", i+1, item_id_table[i], mp_item_id[item_id_table[i]]);
    for (int i=0; i<brand_table.size(); i++)
        fprintf(out_brand, "%d:%d:%d\n", i+1, brand_table[i], mp_brand[brand_table[i]]);
	return 0;
}


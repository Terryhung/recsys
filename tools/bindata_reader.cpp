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
    return 0;
}
vector<int> make_mapping_table(map<int, int> mp) {
    vector<int> res;
    for (map<int, int>::iterator it=mp.begin(); it!=mp.end(); it++)
        res.push_back(it->first);
    sort(res.begin(), res.end());
    return res;
}
struct Unioner{
    vector<int> ary;
    Unioner() { ary=vector<int>(); }
    void add(int a) { ary.push_back(a); }
    vector<pair<int,int> > res() {
        vector<pair<int,int> > res = vector<pair<int,int> >();
        sort(ary.begin(), ary.end());
        ary.push_back(-1);
        for (int i=0,j=1; i<ary.size()-1; i++, j++)
            if (ary[i]!=ary[i+1]) {
                res.push_back(make_pair(ary[i], j));
                j = 1;
            }
        return res;
    }
};
int main(int argc, char** argv) {
    Session sn = Session(Session::CLICK);
    if (argc!=2) {
        puts("usage:");
        puts("\tbindata_reader bin_data_name");
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
    vector<pair<int, int> > item_id_table, brand_table;
    Unioner item_id_unioner, brand_unioner;
    memset(cate, 0, sizeof(cate));
    memset(month, 0, sizeof(month));
    memset(hour, 0, sizeof(hour));
    FILE *out_item_id = fopen("item_id_table.txt", "w");
    FILE *out_brand = fopen("brand_table.txt", "w");
    if (!out_item_id) { puts("fopen item_id error"); return 0; }
    if (!out_brand) { puts("fopen brand error"); return 0; }
    fprintf(stderr, "reading data...\n");
    while (sn.read_binary(f), !sn.empty()) {
        for (int i=0; i<sn.len(); i++ ) {
            item_id_unioner.add(sn.click(i).item_id);
            if (sn.click(i).cate>12)
                brand_unioner.add(sn.click(i).cate);
            cate[sn.click(i).cate<=12 ? sn.click(i).cate>=0 ? sn.click(i).cate : 13 : 14 ]++;
            month[sn.click(i).m()]++;
            hour[sn.click(i).h()]++;
        }
    }
    
    fprintf(stderr, "sorting %lu item id and %lu brand...\n", item_id_unioner.ary.size(), brand_unioner.ary.size());
    item_id_table = item_id_unioner.res();
    brand_table = brand_unioner.res();
    fprintf(stderr, "sort done\n");
    printf("min of item id:%d\n", item_id_table[0].first);
    printf("max of item id:%d\n", item_id_table[item_id_table.size()-1].first);
    printf("total number of item:%lu\n", item_id_unioner.ary.size());
    printf("total number of different item:%lu\n", item_id_table.size());
    printf("total number of different brand:%lu\n", brand_table.size());
    printf("# of items in each cate:\n\
\t(13 for special offers, 14 for # items of brand, 15 for # of brand)\n");
    cate[15] = brand_table.size();
    print_table(cate, 4, 4);
    printf("# of items in each month:\n");
    print_table(month, 3, 4);
    printf("# of items in each hour:\n");
    print_table(hour, 6, 4);
    for (int i=0; i<item_id_table.size(); i++)
        fprintf(out_item_id, "%d:%d:%d\n", i+1, item_id_table[i].first, item_id_table[i].second);
    for (int i=0; i<brand_table.size(); i++)
        fprintf(out_brand, "%d:%d:%d\n", i+1, brand_table[i].first, brand_table[i].second);
	return 0;
}


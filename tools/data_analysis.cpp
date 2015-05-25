// Code by duck

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

#include <vector>

#include "Session.cpp"

using namespace std;

char s[BUF_SIZE];
int main(int argc, char **argv) {
    FILE *item_id_f, *click_f, *buy_f;
    if (argc!=2) {
        puts("Usage:");
        puts("\tdata_analysis click_dat_name");
        return 0;
    }

    puts("Should execute this program in \'recsys\' folder.");
    item_id_f = fopen("item_id_table.txt", "rb");
    click_f = fopen(argv[1], "rb");
    buy_f = fopen("out-buy-all.dat", "rb");
    if (!item_id_f) { puts("item_id_table.txt open error."); return 0; }
    if (!click_f) { puts("click_dat open error."); return 0; }
    if (!buy_f) { puts("out-buy-all.dat open error."); return 0; }
    int pos, id, num;
    vector<int> ary;

    while (!feof(item_id_f)) {
        if (fscanf(item_id_f, "%d:%d:%d", &pos, &id, &num)<3) break;
        ary.push_back(num);
    }
    fclose(item_id_f);
    sort(ary.begin(), ary.end());
    printf("total : %lu items\n", ary.size());
    int p = 0, acc = 0, total = 0;
    for (int i=0; i<ary.size(); i++)
        total += ary[i];
    for (int i=1; p!=ary.size()-1; i*=2) {
        while (p<ary.size()-1 && ary[p]<i) {
            acc += ary[p];
            p++;
        }
        printf("%5lu item got more than %8d clicks. (total %9d clicks) (if it\'s thres, purity:%f)\n", (ary.size()-p-1), ary[p], acc, (ary.size()*1.0/(ary.size()-p-1)) * (total-acc)*1.0/total);
    }
    ary = vector<int>();

    vector<pair<int, int> > se_ary;
    vector<int> buy_ary;
    Session se;
    puts("reading data...");
    se = Session(Session::CLICK);
    while (se.read_binary(click_f).id()!=0) {
        se_ary.push_back(make_pair(se.id(), se.len()));
    }
    fclose(click_f);
    se = Session(Session::BUY);
    while (se.read_binary(buy_f).id()!=0) {
        buy_ary.push_back(se.id());
    }
    fclose(buy_f);
    puts("reading done");
    sort(se_ary.begin(), se_ary.end());
    sort(buy_ary.begin(), buy_ary.end());
    buy_ary.push_back(0);
    p = 0;
    // se_ary = [(id, len) ... ]
    for (unsigned int i=0; i<se_ary.size(); i++) {
        while (p<buy_ary.size()-1 && buy_ary[p]<se_ary[i].first)
            p++;
        if (buy_ary[p]==se_ary[i].first)
            se_ary[i].first = -se_ary[i].first;
        std::swap(se_ary[i].first, se_ary[i].second);
    }
    sort(se_ary.begin(), se_ary.end());
    puts("sorting done");
    printf("%lu session clicks, %lu sessions buy.\n", se_ary.size(), buy_ary.size());
    // se_ary = [(len, +-id) ... ]
    p = 0;
    acc = 0;
    for (float i=2; p<se_ary.size()-1; i*=1.5) {
        while (p<se_ary.size()-1 && se_ary[p].first<i) {
            acc += (se_ary[p].second<0);
            p++;
        }
        printf("There are %d sessions with #click<=%.0f. Have %d session buys. (ratio:%.3f%%)\n", p-1, i, acc, acc*100.0/p);
    }
    
    


	return 0;
}


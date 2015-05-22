// Code by duck

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

#include <vector>

using namespace std;

const int BUF_SIZE = 10000;
char s[BUF_SIZE];
int main() {
    FILE *item_id_f;
    puts("Should execute this program in \'recsys\' folder.");
    item_id_f = fopen("item_id_table.txt", "rb");
    if (!item_id_f) { puts("item_id_table.txt open error."); return 0; }
    int pos, id, num;
    vector<int> ary;
    fseek(item_id_f, 0, SEEK_SET);
    while (!feof(item_id_f)) {
        if (fscanf(item_id_f, "%d:%d:%d", &pos, &id, &num)<3) break;
        ary.push_back(num);
    }
    fclose(item_id_f);
    sort(ary.begin(), ary.end());
    printf("total : %lu items\n", ary.size());
    int p = 0, acc = 0;
    for (int i=1; p!=ary.size()-1; i*=2) {
        while (p<ary.size()-1 && ary[p]<i) {
            acc += ary[p];
            p++;
        }
        printf("%5d item got less than %8d clicks. (total %9d clicks)\n", p+1, ary[p], acc);
    }
    

	return 0;
}


// Code by duck

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

//using namespace std;
const int BUF_SIZE = 1000000;
char s[BUF_SIZE];

int main(int argc, char **argv) {
    int ans[2][2], a, b;
    if (argc!=3) {
        puts("Usage:");
        puts("\tresult_01_grid dat_name res_name");
    }
    FILE *fa = fopen(argv[1], "r"), *fb = fopen(argv[2], "r");
    if (!fa) { printf("open %s error...", argv[1]); return 0; }
    if (!fb) { printf("open %s error...", argv[2]); return 0; }
    memset(ans, 0, sizeof(ans));
    while (!feof(fa) && !feof(fb)) {
        if (!fgets(s, BUF_SIZE, fa)) break;
        if (!(s[0]=='1'||s[0]=='0')) break;
        a = (s[0]=='1');

        if (!fgets(s, BUF_SIZE, fb)) break;
        if (!(s[0]=='1'||s[0]=='0')) break;
        b = (s[0]=='1');

        ans[b][a]++;
    }
    puts(  "          predict 0   predict 1");
    printf("answer 0  %9d   %9d\n", ans[0][0], ans[1][0]);
    printf("answer 1  %9d   %9d\n", ans[0][1], ans[1][1]);
    printf("(a1 p1) / (a0 p1) = %f   (>1 then get positive score)\n", ans[1][1]*1.0/ans[1][0]);
    printf("#answer 1 = %d\n", ans[0][1]+ans[1][1]);
    printf("a1/all = %f\n", (ans[0][1]+ans[1][1])*1.0/(ans[0][1]+ans[1][1]+ans[1][0]+ans[0][0]));
	return 0;
}


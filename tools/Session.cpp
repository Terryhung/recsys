// Code by duck

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

static const int BUF_SIZE = 3000;
/*
 * an example of read all data:
 
    FILE *f = fopen("./compress_click.dat", "rb");
    Session sn;
    while (sn.read_binary(f), sn.empty()) {
        printf("%d\n", sn.id());
    }
 */

// catagory==13 if it's special offer
struct ClickInfo {
    static const int sec_off=0;
    static const int sec_len=6;
    static const int min_off=sec_len;
    static const int min_len=6;
    static const int h_off=min_off+min_len;
    static const int h_len=5;
    static const int d_off=h_off+h_len;
    static const int d_len=5;
    static const int m_off=d_off+d_len;
    static const int m_len=4;
    static const int y_off=m_off+m_len;
    static const int y_len=1;
    unsigned int date;
    int cate;
                         // year=2014/2015
    //unsigned char month; //16
    //unsigned char day;   //32
    //unsigned char hour;  //32
    //unsigned char minute;//64
    //unsigned char second;//64
    //unsigned char category;//16
    
    unsigned int item_id;
    ClickInfo() {
        //year=month=day=hour=minute=second=item_id=category=-1;
        date = item_id = cate = -1;
    }
    ClickInfo(char *text) {
        // YYYY-MM-DDThh:mm:ss.SSS 
        int _y, _m, _d, _h, _min, _s, _cate;
        static char s[BUF_SIZE];
        static char s2[BUF_SIZE];
        char *tmps, *date, *item_s, *cate_s;
        tmps = strtok(text, ",");
        date = strtok(NULL, ",");
        item_s = strtok(NULL, ",");
        cate_s = strtok(NULL, "\0");
        sscanf(item_s, "%d", &item_id);
        sscanf(date, "%d-%d-%dT%d:%d:%d.%*dZ", &_y, &_m, &_d, &_h, &_min, &_s);
        date = 0;
        setsec(_s);
        setmin(_min);
        seth(_h);
        setd(_d);
        setm(_m);
        sety(_y);
        if (cate_s[0]=='S') {
            cate = -1;
        } else {
            sscanf(cate_s, "%d", &cate);
        }
    }
    void print() {
        printf("%u\n", item_id);
    }
    inline void setsec(int n) { date ^= (sec()^n)<<sec_off; }
    inline int sec() { return (date>>sec_off)&((1<<sec_len)-1); }
    inline void setmin(int n) { date ^= (min()^n)<<min_off; }
    inline int min() { return (date>>min_off)&((1<<min_len)-1); }
    inline void seth(int n) { date ^= (h()^n)<<h_off; }
    inline int h() { return (date>>h_off)&((1<<h_len)-1); }
    inline void setd(int n) { date ^= (d()^n)<<d_off; }
    inline int d() { return (date>>d_off)&((1<<d_len)-1); }
    inline void setm(int n) { date ^= (m()^n)<<m_off; }
    inline int m() { return (date>>m_off)&((1<<m_len)-1); }
    inline void sety(int n) { date ^= (y()^(n-2014))<<y_off; }
    inline int y() { return ((date>>y_off)&((1<<y_len)-1))+2014; }
};

struct BuyInfo {
    static const int sec_off=0;
    static const int sec_len=6;
    static const int min_off=sec_len;
    static const int min_len=6;
    static const int h_off=min_off+min_len;
    static const int h_len=5;
    static const int d_off=h_off+h_len;
    static const int d_len=5;
    static const int m_off=d_off+d_len;
    static const int m_len=4;
    static const int y_off=m_off+m_len;
    static const int y_len=1;
    unsigned int date;
    unsigned int item_id;
    unsigned int price;
    unsigned int quantity;
    BuyInfo() {
        //year=month=day=hour=minute=second=item_id=category=-1;
        date = item_id = price = quantity = -1;
    }
    BuyInfo(char *text) {
        // YYYY-MM-DDThh:mm:ss.SSS 
        int _y, _m, _d, _h, _min, _s;
        static char s[BUF_SIZE];
        static char s2[BUF_SIZE];
        char *tmps, *date, *item_s, *price_s, *quan_s;
        tmps = strtok(text, ",");
        date = strtok(NULL, ",");
        item_s = strtok(NULL, ",");
        price_s = strtok(NULL, ",");
        quan_s = strtok(NULL, "\0");
        sscanf(item_s, "%u", &item_id);
        sscanf(price_s, "%u", &price);
        sscanf(quan_s, "%u", &quantity);
        sscanf(date, "%d-%d-%dT%d:%d:%d.%*dZ", &_y, &_m, &_d, &_h, &_min, &_s);
        date = 0;
        setsec(_s);
        setmin(_min);
        seth(_h);
        setd(_d);
        setm(_m);
        sety(_y);
    }
    void print() {
        printf("%u\n", item_id);
    }
    inline void setsec(int n) { date ^= (sec()^n)<<sec_off; }
    inline int sec() { return (date>>sec_off)&((1<<sec_len)-1); }
    inline void setmin(int n) { date ^= (min()^n)<<min_off; }
    inline int min() { return (date>>min_off)&((1<<min_len)-1); }
    inline void seth(int n) { date ^= (h()^n)<<h_off; }
    inline int h() { return (date>>h_off)&((1<<h_len)-1); }
    inline void setd(int n) { date ^= (d()^n)<<d_off; }
    inline int d() { return (date>>d_off)&((1<<d_len)-1); }
    inline void setm(int n) { date ^= (m()^n)<<m_off; }
    inline int m() { return (date>>m_off)&((1<<m_len)-1); }
    inline void sety(int n) { date ^= (y()^(n-2014))<<y_off; }
    inline int y() { return ((date>>y_off)&((1<<y_len)-1))+2014; }
};

class Session {
    int session_id;
    int num_click;
    int info_type;
    ClickInfo *click_infos;
    BuyInfo *buy_infos;
    
public:
    static const int TEXT = 0;
    static const int BINARY = 1;
    static const int CLICK = 0;
    static const int BUY = 1;
    Session() : session_id(0), num_click(0), click_infos(NULL), buy_infos(NULL), info_type(CLICK) {
    }
    Session(int _info_type) {
        *this = Session();
        this->info_type = _info_type;
    }
    Session(FILE *f, int type, int _info_type) {
        *this = Session();
        info_type = _info_type;
        if (type==TEXT) {
            read_text(f);
        } else if (type==BINARY) {
            read_binary(f);
        }
    }
    int read_text(FILE *f) {
        static char s[BUF_SIZE];
        static ClickInfo ci_buf[BUF_SIZE];
        static BuyInfo bi_buf[BUF_SIZE];
        fpos_t fpos;
        int _sid, _item, _cate;
        char *s_res;
        session_id = num_click = 0;
        while (!feof(f)) {
            fgetpos(f, &fpos);
            s_res = fgets(s, BUF_SIZE, f);
            if (s_res==NULL || strlen(s)<3) {
                break;
            }
            sscanf(s, "%d", &_sid);
            if (session_id==0) {
                session_id = _sid;
            }
            if (session_id!=_sid) {
                fsetpos(f, &fpos);
                break;
            }
            if (info_type==CLICK)
                ci_buf[num_click++] = ClickInfo(s);
            if (info_type==BUY)
                bi_buf[num_click++] = BuyInfo(s);
        } 
        if (num_click && info_type==CLICK){
            click_infos = new ClickInfo[num_click];
            for ( int i=0; i<num_click; i++ )
                click_infos[i] = ci_buf[i];
        }
        if (num_click && info_type==BUY){
            buy_infos = new BuyInfo[num_click];
            for ( int i=0; i<num_click; i++ )
                buy_infos[i] = bi_buf[i];
        }
        return 0;
    }
    int write_binary(FILE *f) {
        fwrite(&session_id, sizeof(session_id), 1, f);
        fwrite(&num_click, sizeof(num_click), 1, f);
        if (num_click && info_type==CLICK) {
            fwrite(click_infos, sizeof(ClickInfo), num_click, f);
            return sizeof(session_id)+sizeof(num_click)+num_click*sizeof(ClickInfo);
        }
        if (num_click && info_type==BUY) {
            fwrite(buy_infos, sizeof(BuyInfo), num_click, f);
            return sizeof(session_id)+sizeof(num_click)+num_click*sizeof(BuyInfo);
        }
        return sizeof(session_id)+sizeof(num_click);
    }
    Session read_binary(FILE *f) {
        del();
        fread(&session_id, sizeof(session_id), 1, f);
        fread(&num_click, sizeof(num_click), 1, f);
        if (info_type==CLICK) {
            click_infos = new ClickInfo[num_click];
            fread(click_infos, sizeof(ClickInfo), num_click, f);
        } else if (info_type==BUY) {
            buy_infos = new BuyInfo[num_click];
            fread(buy_infos, sizeof(BuyInfo), num_click, f);
        }
        return *this;
    }
    void del() {
        if (click_infos!=NULL)
            delete [] click_infos;
        if (buy_infos!=NULL)
            delete [] buy_infos;
        click_infos = NULL;
        buy_infos = NULL;
        *this = Session();
    }
    int remove_items(bool (*func)(const ClickInfo)) {
       int nw = 0;
       for (int i=0; i<num_click; i++) {
           if (!func(click_infos[i])) {
               std::swap(click_infos[nw], click_infos[i]);
               nw++;
           }
       }
       num_click = nw;
    }
    int id() const { return session_id; }
    int len() const { return num_click; }
    ClickInfo click(int i) { return click_infos[i]; }
    BuyInfo buy(int i) { return buy_infos[i]; }
    bool operator==(const Session b) { return this->id()==b.id(); }
    bool operator!=(const Session b) { return !(*this==b); }
    bool empty() const { return num_click==0; }
    void print() { printf("%d %d\n", session_id, num_click); }
};


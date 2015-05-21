// Code by duck

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include "Session.cpp"

//using namespace std;

const int BUT_SIZE = 1000;

class SessionReader{
    FILE *f;
    Session nw_session;
    char s[BUF_SIZE];
    int info_type;
public:
    SessionReader() : f(NULL), info_type(0) {}
    SessionReader(const char *f_name, const char *info_type_s) {
        f = fopen(f_name, "r");
        if (strcmp(info_type_s, "click")==0) {
            info_type=Session::CLICK;
        } else if (strcmp(info_type_s, "buy")==0) {
            info_type=Session::BUY;
        } 
    }
    bool data_available() {
        return f!=NULL;
    }
    Session read_next_session() {
        if (!data_available())
            return Session();
        return Session(f, Session::TEXT, info_type);
    }
    void close() { fclose(f); f=NULL; }
    
};

int main(int argc, char **argv) {
    if (argc!=4) {
        puts("Usage:");
        puts("\ttextdata_compressor text_data_name type out_data_name");
        puts("\t\ttype = [click|buy]");
        return 0;
    }
    SessionReader sr;
    Session sn;
    int nw_byte;
    sr = SessionReader(argv[1], argv[2]);
    FILE *out = fopen(argv[3], "wb");
    while (sn=sr.read_next_session(), !sn.empty()) {
        nw_byte += sn.write_binary(out);
        sn.del();
    }
    sn.write_binary(out);
    puts("write ok");
	return 0;
}


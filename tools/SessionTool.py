import struct

SEC_OFF=0;
SEC_LEN=6;
MIN_OFF=SEC_LEN;
MIN_LEN=6;
H_OFF=MIN_OFF+MIN_LEN;
H_LEN=5;
D_OFF=H_OFF+H_LEN;
D_LEN=5;
M_OFF=D_OFF+D_LEN;
M_LEN=4;
Y_OFF=M_OFF+M_LEN;
Y_LEN=1;
CATE_OFF=Y_OFF+Y_LEN;
CATE_LEN=4;

class ClickInfo:
    def __init__(self):
        self.date_cate = -1
        self.item_id = -1
    def __init__(self, date_cate, item_id):
        self.date_cate = date_cate
        self.item_id = item_id

    def setsec(self, n):
        self.date_cate ^= (self.sec()^n)<<SEC_OFF
    def sec(self):
        return (self.date_cate>>SEC_OFF)&((1<<SEC_LEN)-1)
    def setmin(self, n):
        self.date_cate ^= (self.min()^n)<<MIN_OFF
    def min(self):
        return (self.date_cate>>MIN_OFF)&((1<<MIN_LEN)-1)
    def seth(self, n):
        self.date_cate ^= (self.h()^n)<<H_OFF
    def h(self):
        return (self.date_cate>>H_OFF)&((1<<H_LEN)-1)
    def setd(self, n):
        self.date_cate ^= (self.d()^n)<<D_OFF
    def d(self):
        return (self.date_cate>>D_OFF)&((1<<D_LEN)-1)
    def setm(self, n):
        self.date_cate ^= (self.m()^n)<<M_OFF
    def m(self):
        return (self.date_cate>>M_OFF)&((1<<M_LEN)-1)
    def sety(self, n):
        self.date_cate ^= (self.y()^(n-2014))<<Y_OFF
    def y(self):
        return ((self.date_cate>>Y_OFF)&((1<<Y_LEN)-1))+2014
    def setcate(self, n):
        self.date_cate ^= (self.cate()^n)<<CATE_OFF
    def cate(self):
        return (self.date_cate>>CATE_OFF)&((1<<CATE_LEN)-1)

class BuyInfo:
    def __init__(self):
        self.date_cate = -1
        self.item_id = -1
        self.price = -1
        self.quantity = -1
    def __init__(self, date_cate, item_id, price, quantity):
        self.date_cate = date_cate
        self.item_id = item_id
        self.price = price
        self.quantity = quantity

    def setsec(self, n):
        self.date_cate ^= (self.sec()^n)<<SEC_OFF
    def sec(self):
        return (self.date_cate>>SEC_OFF)&((1<<SEC_LEN)-1)
    def setmin(self, n):
        self.date_cate ^= (self.min()^n)<<MIN_OFF
    def min(self):
        return (self.date_cate>>MIN_OFF)&((1<<MIN_LEN)-1)
    def seth(self, n):
        self.date_cate ^= (self.h()^n)<<H_OFF
    def h(self):
        return (self.date_cate>>H_OFF)&((1<<H_LEN)-1)
    def setd(self, n):
        self.date_cate ^= (self.d()^n)<<D_OFF
    def d(self):
        return (self.date_cate>>D_OFF)&((1<<D_LEN)-1)
    def setm(self, n):
        self.date_cate ^= (self.m()^n)<<M_OFF
    def m(self):
        return (self.date_cate>>M_OFF)&((1<<M_LEN)-1)
    def sety(self, n):
        self.date_cate ^= (self.y()^(n-2014))<<Y_OFF
    def y(self):
        return ((self.date_cate>>Y_OFF)&((1<<Y_LEN)-1))+2014
    def setcate(self, n):
        self.date_cate ^= (self.cate()^n)<<CATE_OFF
    def cate(self):
        return (self.date_cate>>CATE_OFF)&((1<<CATE_LEN)-1)

class Session:
    """ 
        use
            s=Session("buy") or s=Session("click")
        and here comes an example
        
            with open("buys.dat") as f:
                s = Session("buy")
                while s.read_binary(f).session_id!=0:
                    print "Session id:" + str(s.session_id) + "     number of buys:" + str(s.num_click)
                    s = Session("buy")
    """
    def __init__(self, info_type):
        self.session_id = -1
        self.num_click = -1
        self.click_info = []
        self.buy_info = []
        self.info_type = info_type
    def UPI(self, b):
        return struct.unpack("<L", b)[0]
    def read_binary(self, f):
        self.click_info = []
        self.buy_info = []
        self.session_id = self.UPI(f.read(4))
        self.num_click = self.UPI(f.read(4))
        if self.info_type=="click":
            for i in xrange(self.num_click):
                date_cate = self.UPI(f.read(4))
                item_id = self.UPI(f.read(4))
                self.click_info.append(ClickInfo(date_cate, item_id))
        elif self.info_type=="buy":
            for i in xrange(self.num_click):
                date_cate = self.UPI(f.read(4))
                item_id = self.UPI(f.read(4))
                price = self.UPI(f.read(4))
                quan = self.UPI(f.read(4))
                self.buy_info.append(ClickInfo(date_cate, item_id))
        return self
    

if __name__=="__main__":
    pass

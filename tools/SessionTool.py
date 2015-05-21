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
        self.date = -1
        self.cate = -1
        self.item_id = -1

    def __init__(self, date, cate, item_id):
        self.date = date
        self.cate = cate
        self.item_id = item_id

    def setsec(self, n):
        self.date ^= (self.sec()^n)<<SEC_OFF
    def sec(self):
        return (self.date>>SEC_OFF)&((1<<SEC_LEN)-1)
    def setmin(self, n):
        self.date ^= (self.min()^n)<<MIN_OFF
    def min(self):
        return (self.date>>MIN_OFF)&((1<<MIN_LEN)-1)
    def seth(self, n):
        self.date ^= (self.h()^n)<<H_OFF
    def h(self):
        return (self.date>>H_OFF)&((1<<H_LEN)-1)
    def setd(self, n):
        self.date ^= (self.d()^n)<<D_OFF
    def d(self):
        return (self.date>>D_OFF)&((1<<D_LEN)-1)
    def setm(self, n):
        self.date ^= (self.m()^n)<<M_OFF
    def m(self):
        return (self.date>>M_OFF)&((1<<M_LEN)-1)
    def sety(self, n):
        self.date ^= (self.y()^(n-2014))<<Y_OFF
    def y(self):
        return ((self.date>>Y_OFF)&((1<<Y_LEN)-1))+2014

class BuyInfo:
    def __init__(self):
        self.date = -1
        self.item_id = -1
        self.price = -1
        self.quantity = -1
    def __init__(self, date, item_id, price, quantity):
        self.date = date
        self.item_id = item_id
        self.price = price
        self.quantity = quantity

    def setsec(self, n):
        self.date ^= (self.sec()^n)<<SEC_OFF
    def sec(self):
        return (self.date>>SEC_OFF)&((1<<SEC_LEN)-1)
    def setmin(self, n):
        self.date ^= (self.min()^n)<<MIN_OFF
    def min(self):
        return (self.date>>MIN_OFF)&((1<<MIN_LEN)-1)
    def seth(self, n):
        self.date ^= (self.h()^n)<<H_OFF
    def h(self):
        return (self.date>>H_OFF)&((1<<H_LEN)-1)
    def setd(self, n):
        self.date ^= (self.d()^n)<<D_OFF
    def d(self):
        return (self.date>>D_OFF)&((1<<D_LEN)-1)
    def setm(self, n):
        self.date ^= (self.m()^n)<<M_OFF
    def m(self):
        return (self.date>>M_OFF)&((1<<M_LEN)-1)
    def sety(self, n):
        self.date ^= (self.y()^(n-2014))<<Y_OFF
    def y(self):
        return ((self.date>>Y_OFF)&((1<<Y_LEN)-1))+2014
    def setcate(self, n):
        self.date ^= (self.cate()^n)<<CATE_OFF
    def cate(self):
        return (self.date>>CATE_OFF)&((1<<CATE_LEN)-1)

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
    def PI(self, n):
        return struct.pack("<L", n)
    def read_binary(self, f):
        self.click_info = []
        self.buy_info = []
        self.session_id = self.UPI(f.read(4))
        self.num_click = self.UPI(f.read(4))
        if self.info_type=="click":
            for i in xrange(self.num_click):
                date = self.UPI(f.read(4))
                cate = self.UPI(f.read(4))
                item_id = self.UPI(f.read(4))
                self.click_info.append(ClickInfo(date, cate, item_id))
        elif self.info_type=="buy":
            for i in xrange(self.num_click):
                date = self.UPI(f.read(4))
                item_id = self.UPI(f.read(4))
                price = self.UPI(f.read(4))
                quan = self.UPI(f.read(4))
                self.buy_info.append(BuyInfo(date, item_id, price, quan))
        return self
    def write_binary(self, f):
        f.write(PI(self.session_id))
        f.write(PI(self.num_click))
        if self.info_type=="click":
            for ci in self.click_info:
                f.write(PI(ci.date))
                f.write(PI(ci.cate))
                f.write(PI(ci.item_id))
        elif self.info_type=="buy":
            for bi in self.buy_info:
                f.write(PI(bi.date))
                f.write(PI(bi.item_id))
                f.write(PI(bi.price))
                f.write(PI(bi.quan))
        return self
    def make_end(self):
        self.click_info = None
        self.buy_info = None
        self.session_id = 0
        self.num_click = 0


    

if __name__=="__main__":
    pass

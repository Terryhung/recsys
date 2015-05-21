from SessionTool import ClickInfo 
from SessionTool import BuyInfo 
from SessionTool import Session 
import data_tool
import sys

"""
    for predict buy or not.
    NOT for predicting the "buy set"
"""

def write(y, se, f):
    s = str(y)+" "
    nw = 1
    se.click_info.sort(key=lambda x:x.item_id)
    for item in se.click_info:
        s += str(36*item.item_id +    item.m()) + ":1 "
        s += str(36*item.item_id + 12+item.h()) + ":1 "
        break
    print >>f, s[:-1]
    

def main():
    if len(sys.argv)!=4:
        print "python ./tools/make_liblinear_bits.py input_click input_buys out_name"
        print "    you should use this in 'recsys' folder but not ./tools"
        exit()
    s_buy = []
    print "initializing..."
    item_id_map = data_tool.get_reduced_id_mapping("./item_id_table.txt")
    brand_map = data_tool.get_reduced_id_mapping("./brand_table.txt")
    print "Start to read buy data."
    with open(sys.argv[2], "r") as f:
        s = Session("buy")
        while s.read_binary(f).session_id!=0:
            s_buy.append(s)
            s = Session("buy")
    data_tool.session_reduce_id_brand(s_buy, item_id_map, brand_map)
    print "Read buy data ok."
    s_buy.sort(key=lambda x:x.session_id)
    s_buy.append(Session("buy"))
    print "Sort buy data ok."
    print "Start to write to "+sys.argv[3]
    nw_buy = 0
    i = 0
    with open(sys.argv[1], "r") as f, open(sys.argv[3], "w") as out:
        s = Session("click")
        while s.read_binary(f).session_id!=0:
            data_tool.session_reduce_id_brand(s, item_id_map, brand_map)
            if s.session_id==s_buy[nw_buy]:
                write(1, s, out)
                nw_buy += 1
            else:
                write(0, s, out)
            i += 1
            if i%100000==0:
                print str(i) + " data ok."
                print "    now session_id="+s.session_id
            s = Session("click")
    

if __name__=="__main__":
    main()

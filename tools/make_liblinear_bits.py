from SessionTool import ClickInfo 
from SessionTool import BuyInfo 
from SessionTool import Session 
import data_tool
import sys

"""
    for predict buy or not.
    NOT for predicting the "buy set"
"""

def item_feature_maker_month_hour(item):
    s = str(36*item.item_id +    item.m()) + ":1 "
    s += str(36*item.item_id + 12+item.h()) + ":1 "
    return s

def item_feature_maker_month_cate(item):
    s  = str(27*item.item_id +    item.m()) + ":1 "
    if item.cate>=14:
        s += str(27*item.item_id + 12+14) + ":1 "
    else:
        s += str(27*item.item_id + 12+item.cate) + ":1 "
    return s

def item_feature_maker_cate(item):
    if item.cate>=14:
        s = str(15*item.item_id + 14) + ":1 "
    else:
        s = str(15*item.item_id + item.cate) + ":1 "
    return s

def item_feature_maker_spec_offer(item):
    if item.cate==13:
        s = str(2*item.item_id + 1) + ":1 "
    else:
        s = str(2*item.item_id + 0) + ":1 "
    return s

def write(y, se, f, item_feature_maker):
    s = str(y)+" "
    data_tool.session_sort_info_by_item_id(se)
    lastitem = None
    for item in se.info:
        if lastitem!=None:
            if item.item_id==lastitem.item_id:
                continue
        lastitem = item
        s += item_feature_maker(item)
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
    brand_map[4294967295] = 13
    print "Start to read buy data."
    buy_id = {}
    with open(sys.argv[2], "r") as f:
        s = Session("buy")
        while s.read_binary(f).session_id!=0:
            buy_id[s.session_id] = 1
            s = Session("buy")
    print "Read buy data ok."
    print "Start to write to "+sys.argv[3]
    nw_buy = 0
    i = 0
    item_feature_maker = item_feature_maker_cate
    with open(sys.argv[1], "r") as f, open(sys.argv[3], "w") as out:
        s = Session("click")
        while s.read_binary(f).session_id!=0:
            data_tool.session_reduce_id_brand(s, item_id_map, brand_map)
            if buy_id.get(s.session_id)!=None:
                write(1, s, out, item_feature_maker)
            else:
                write(0, s, out, item_feature_maker)
            i += 1
            if i%100000==0:
                print str(i) + " data ok."
                print "    now session_id="+str(s.session_id)
            s = Session("click")
    print "Done"
    

if __name__=="__main__":
    main()

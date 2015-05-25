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

def item_feature_maker_spec_offer(item):
    if item.cate==13:
        s = str(2*item.item_id + 1) + ":1 "
    else:
        s = str(2*item.item_id + 0) + ":1 "
    return s

# ^^^^^^^ above are old version. can't work.

def item_feature_maker_numbeclick(item, se_info):
    nb = se_info['item_be_click'][item.item_id]
    if nb<=2:
        return ([0], 2)
    else:
        return ([1], 2)

def item_feature_maker_cate(item, se_info):
    if item.cate>=14:
        return ([14], 15)
    else:
        return ([item.cate], 15)

def item_feature_maker_padding_2(item, se_info):
    return ([], 2)


def preprocessor_dict(se):
    res_dict = {}
    cnt = 1
    res_dict['item_be_click'] = {}
    se.info.append(ClickInfo())
    for i in xrange(len(se.info)-1):
        if se.info[i].item_id!=se.info[i+1].item_id:
            res_dict['item_be_click'][se.info[i].item_id] = cnt
            cnt = 1
        else:
            cnt += 1
    se.info = se.info[:-1]
    return res_dict

def session_feature_maker_numclick(se):
    res = []
    for i in range(0, 5):
        if 2**(2*i-2)<se.num_click and se.num_click<2**(2*i):
            res.append(i)
    return (res, 5)

def get_feat_string(feat_list, nw_feat_cnt, total_feat_cnt=0, item_id=0):
    s = ""
    for f in feat_list:
        s += str(total_feat_cnt*item_id+nw_feat_cnt+f) + ":1 "
    return s

def get_data_feature_maker(preprocessor, session_feature_maker, item_feature_makers):
    if not type(item_feature_makers) is list:
        ifm_list = [item_feature_makers]
    else:
        ifm_list = item_feature_makers
    def data_feature_maker(y, se):
        def calc_total_feat_cnt():
            item = se.info[0]
            total_feat_cnt = 0
            for ifm in ifm_list:
                (feat_list, res_feat_cnt) = ifm(item, se_info)
                total_feat_cnt += res_feat_cnt
            return total_feat_cnt
        data_tool.session_sort_info_by_item_id(se)
        se_info = preprocessor(se)
        s = str(y) + " "
        feat_cnt = 1
        (feat_list, res_feat_cnt) = session_feature_maker(se)
        s += get_feat_string(feat_list, feat_cnt)
        feat_cnt += res_feat_cnt
        total_feat_cnt = calc_total_feat_cnt()
        lastitem = ClickInfo()
        for item in se.info:
            if item.item_id==lastitem.item_id:
                continue
            else:
                lastitem = item
            for ifm in ifm_list:
                (feat_list, res_feat_cnt) = ifm(item, se_info)
                s += get_feat_string(feat_list, feat_cnt, total_feat_cnt, item.item_id)
                feat_cnt += res_feat_cnt
        return s[:-1]
    return data_feature_maker

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
    data_feature_maker = get_data_feature_maker(
                                                preprocessor_dict, 
                                                session_feature_maker_numclick, 
                                                [item_feature_maker_numbeclick, item_feature_maker_cate])
    with open(sys.argv[1], "r") as f, open(sys.argv[3], "w") as out:
        s = Session("click")
        while s.read_binary(f).session_id!=0:
            data_tool.session_reduce_id_brand(s, item_id_map, brand_map)
            if buy_id.get(s.session_id)!=None:
                y = 1
            else:
                y = 0
            print >>out, data_feature_maker(y, s)
            i += 1
            if i%100000==0:
                print str(i) + " data ok."
                print "    now session_id="+str(s.session_id)
            s = Session("click")
    print "Done"
    

if __name__=="__main__":
    main()

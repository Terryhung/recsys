import SessionTool


def get_reduced_id_mapping(txt_name):
    res_dict = {}
    with open(txt_name, "r") as f:
        for s in f.readlines():
            sp = s.split(":")
            res_dict[int(sp[1])] = int(sp[0])
    return res_dict


def session_reduce_id_brand(sessions, item_id_map, brand_map):
    def one_session_reduce_id_brand(s):
        if se.info_type=="click":
            for ci in se.click_info:
                if ci.cate>=14:
                    ci.cate = brand_map[ci.cate]+14
                ci.item_id = item_id_map[ci.item_id]
        elif se.info_type=="buy":
            for bi in se.buy_info:
                bi.item_id = item_id_map[bi.item_id]
    if type(sessions) is list:
        for se in sessions:
            one_session_reduce_id_brand(se)
    elif type(sessions) is SessionTool.Session:
        one_session_reduce_id_brand(sessions)
    else:
        print ""
        raise AssertionError("Should be Session/list of Session")
            


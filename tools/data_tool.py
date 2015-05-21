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
        if s.info_type=="click":
            for ci in s.click_info:
                if ci.cate>=14:
                    ci.cate = brand_map[ci.cate]+14
                ci.item_id = item_id_map[ci.item_id]
        elif s.info_type=="buy":
            for bi in se.buy_info:
                bi.item_id = item_id_map[bi.item_id]
    if type(sessions) is list and isinstance(sessions[0], SessionTool.Session):
        for se in sessions:
            one_session_reduce_id_brand(se)
    elif isinstance(sessions, SessionTool.Session):
        one_session_reduce_id_brand(sessions)
    else:
        raise AssertionError("Should be Session/list of Session : "+str(type(sessions[0])))

def session_sort_info_by_item_id(sessions):
    if sessions.info_type=='click':
        sessions.click_info.sort(key=lambda x:x.item_id)
    elif sessions.info_type=='buy':
        sessions.buy_info.sort(key=lambda x:x.item_id)



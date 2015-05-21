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
        for i in s.info:
            if s.info_type=="click":
                if i.cate>=14:
                    i.cate = brand_map[i.cate]+14
            i.item_id = item_id_map[i.item_id]
    if type(sessions) is list and isinstance(sessions[0], SessionTool.Session):
        for se in sessions:
            one_session_reduce_id_brand(se)
    elif isinstance(sessions, SessionTool.Session):
        one_session_reduce_id_brand(sessions)
    else:
        raise AssertionError("Should be Session/list of Session : "+str(type(sessions[0])))

def session_sort_info_by_item_id(sessions):
    sessions.info.sort(key=lambda x:x.item_id)



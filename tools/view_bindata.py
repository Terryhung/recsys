from SessionTool import ClickInfo
from SessionTool import BuyInfo
from SessionTool import Session 
import sys

if len(sys.argv)!=3:
    print "Usage:"
    print "\tpython tools/view_bindata bindata_name num_read"
    exit(0)

with open(sys.argv[1], "r") as f:
    se = Session('click')
    i = 0
    n = int(sys.argv[2])
    while se.read_binary(f).session_id!=0:
        print se.session_id
        for item in se.info:
            print "    " + str(item.item_id)
        i += 1
        if i>=n:
            break


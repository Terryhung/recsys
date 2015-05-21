from SessionTool import ClickInfo 
from SessionTool import BuyInfo 
from SessionTool import Session 
import sys
if __name__=="__main__":
    if len(sys.argv)!=2:
        print "python test.py click_dat"
        exit()
    with open(sys.argv[1]) as f:
        s = Session("buy")
        while s.read_binary(f).session_id!=0:
            print "Session id:" + str(s.session_id) + "     number of buys:" + str(s.num_click)

    

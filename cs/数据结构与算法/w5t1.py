import math
import time

def sysPerm(n,k):
    start = time.perf_counter() 
    res = math.perm(n,k)
    end = time.perf_counter() 
    print ('time(ns) : %s'%((end-start)*1000000))
    return res
    
if __name__=='__main__':
    print('res : %s\n'%sysPerm(5,2))
    print('res : %s\n'%sysPerm(20,7))
    print('res : %s\n'%(sysPerm(100,11)))
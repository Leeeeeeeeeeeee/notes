#!/user/bin/env python
#!-*-coding:utf-8 -*-
#!@Time     :2018/9/27 2018/9/27
#!@Author   :Lee
#!@File     :.py

from functools import reduce

def str2float(s):
    def findDot(s0):
        count = 0
        for i in s0[-1:]:
            if i == '.':
                break
            else:
                count = count + 1

    def trans(c):
        if c == '.':
            return
        else:
            d = {'1': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9}
            c = d.get(c)

    def add(x, y):
        return x * 10 + y

    n = findDot(s)
    num = reduce(add, (map(trans, s))
    return num / (10 ** n)

print('str2float(\'123.456\') =', str2float('123.456'))
if abs(str2float('123.456') - 123.456) < 0.00001:
    print('测试成功!')
else:
    print('测试失败!')
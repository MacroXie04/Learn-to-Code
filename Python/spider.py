# -*- codeing = utf-8 -*-
# @Time : 6/28/23 1:13 PM
# @Author : Hongzhe Xie
# @File : spider.py
# @Software : PyCharm

import sys
import os
import re
import xlwt
import urllib.request,urllib.error
from bs4 import BeautifulSoup
import sqlite3

def main():
    baseurl = "https://movie.douban.com/chart"
    askUrl("https://www.topuniversities.com/university-rankings/world-university-rankings/2024?&countries=ca")
    askUrl("https://marshallsociety.com/essay-competition/")


def getData():
    datalist = []
    return datalist


def askUrl(url):
    head = {
        "User-Agent" : "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/114.0.0.0 Safari/537.36"
    }
    request = urllib.request.Request(url,headers=head)
    html = ""
    try:
        response = urllib.request.urlopen(request)
        html = response.read().decode("utf-8")
        print(html)
    except urllib.error.URLError as error:
        if hasattr(error,"code"):
            print(error.code)
        if hasattr(error,"reason"):
            print(error.reason)
    return html

try:
    if __name__ == "__main__":
        # askUrl("https://www.baidu.com/")
        # askUrl("http://yutian.hongzhe.site")
        # askUrl("https://530t04f125.yicp.fun/")
        # askUrl("https://shanglischool.com/meizhoucaipu/")
        # askUrl("https://www.mps.gov.cn/")
        # askUrl("http://yutian.hongzhe.site")
        # askUrl("https://xianyu.chinaxiaokang.com/xianyuzhanshi/longnan/fengcai/2022/0331/4276892.html")
        askUrl("http://guba.eastmoney.com/list,002031,1,f.html")
        askUrl("http://www.people.com.cn/")
except Exception as error_type:
    print(f"{error_type}")

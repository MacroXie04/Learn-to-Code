# -*- codeing = utf-8 -*-
# @Time : 7/22/23 11:25 PM
# @Author : Hongzhe Xie
# @File : web.py
# @Software : PyCharm

from flask import Flask
from flask import render_template
app = Flask(__name__)

# 网站地址和函数之间的链接
@app.route('/show/info')
def index():
    return render_template('index.html')



if __name__ == '__main__':
    app.run()
## Python爬虫学习笔记（五）——XPath的使用

### 介绍
XPath，全称XML Path Language，即XML路径语言，用来搜寻XML文档，也同样适用于HTML文档的搜索。所以，在做爬虫的时候，就可以使用XPath来做相应的信息抽取。python中相应的库为lxml库，需要自行安装

### 正文

XPath主要是有大量的方法，故我主要用代码的形式来记录。
**XPath常用规则**

| 表达式   | 描述                     |
| -------- | ------------------------ |
| nodename |                          |
| /        | 选取此节点的所有子节点   |
| //       | 从当前节点选取直接子节点 |
| .        | 选取当前节点             |
| ..       | 选取当前节点的父节点     |
| @        | 选取属性                 |

**常用功能**
```
from lxml import etree

text = '''
<div>
<ul>
<li class="item-0"><a href="link1.html">first item</a></li>
<li class="item-1"><a href="link2.html">second item</a></li>
<li class="item-inactive"><a href="link3.html">thirst item</a></li>
<li class="item-1"><a href="link4.html">fourth item</a></li>
<li class="item-0"><a href="link5.html">fifth item</a></li>
</ul>
</div>
'''
# 直接读取
html = etree.HTML(text)
# 读取文件
html = etree.parse('./test.html', etree.HTMLParser())

# 选取所有节点
result = html.xpath('//*')
# 选取所有li节点 
result = html.xpath('//li')
# 选取li节点的所有直接a子节点
# 这里需要注意/和//的区别。前者是直接子节点，换句话说，直接子节点的子节点不是我的直接子节点；后者则是全部子节点
result = html.xpath('//li/a')
# 属性匹配
#选取class属性为item-0的li节点
result = html.xpath('//li[@class=''item-0'']')
# 属性获取
# 获取li节点下所有a节点的href属性
result = html.xpath('//li/a/@href')
# 属性多值匹配
# 如果属性有多个值，就需要用contain()函数
result = html.xpath('//li[contain(@class, "li")]/a/text()')
# 多属性匹配
# 如果有多个属性，可以用运算符，例如and
result = html.xpath('//li[contain(@class, "li") and @name="item"]/a/text()')
# 选取父节点
# 选取href属性为link4.html的a节点，获取其父节点，然后再获取其class属性
## 方法一
result = html.xpath('//a[@href="link4.html"/../@class')
## 方法二
result = html.xpath('//a[@href="link4.html"/parent::*/@class')
# 文本获取
## 错误示范，li后面还有一个a节点，所需要的是a节点的内容
result = html.xpath('//li[@class="item-0"]/text()')
## 正确代码
result = html.xpath('//li[@class="item-0"]/a/text()')
# 按序选择
## 选取第一个li节点
result =html.xpath('//li[1]/a/text()')
## 选取最后一个li节点
result =html.xpath('//li[last()]/a/text()')
## 选取位置小于3的li节点
result =html.xpath('//li[postion()<3]/a/text()')
## 选取倒数第三个li节点
result =html.xpath('//li[last()-2]/a/text()')
# 节点轴选择
## ancestor轴，获取所有祖先节点
result = html.xpath('//li[1]/ancetor::*')
## 加上限定条件的ancestor轴
result = html.xpath('//li[1]/ancetor::div')
## attribute轴，获取所有属性值
result = html.xpath('//li[1]/attribute::*')
## child轴，获取所有直接子节点，加上限定条件
result = html.xpath('//li[1]/child::a[@href="link1.html"]')
## descenda轴，可以获取所有子孙节点，加上限定条件为span节点，只获取span节点
result = html.xpath('//li[1]/descendant::span')
## following轴，获取当前节点之后的所有节点，加上索引表示第几个后序节点
result = html.xpath('//li[1]/following::*[2]')
## following-sibling轴，获取当前节点之后所有同级节点
result = html.xpath('//li[1]/following-sibling::*')
```

### 总结
XPath有十分强大的功能，而且提供了十分丰富的内容，难度固然不高，但是大量的内容需要熟练的使用才能掌握。但我个人其实有些疑问，似乎有很多方法只是实现了相同的一个功能，还不了解其中有什么区别。
XPath的用法可以查看：[http://www.w3school.com.cn/xpath/index.asp](http://www.w3school.com.cn/xpath/index.asp)
lxml库的用法可以查看：[http://lxml.de/](http://lxml.de/)
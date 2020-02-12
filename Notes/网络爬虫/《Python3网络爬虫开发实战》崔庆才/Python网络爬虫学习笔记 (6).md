## Python爬虫学习笔记（六）——BeautifulSoup和pyquery的使用

### 介绍
BeautifulSoup和pyquery都是用来解析html的库，与昨天学的XPath有很多相似之处，因此就将这两个库放在一起学习

### BeautifulSoup库

**基本用法**

```
from bs4 import BeautifulSoup

html = #略
# 初始化BeautifulSoup，第二个参数表示解释器为lxml
soup = BeautifulSoup(html, 'lxml')
# prettify()方法可以标准化html的缩进格式
print(soup.prettify())
# 
```

**节点选择器**

直接调用节点的名称就可以选择节点元素，例如soup.div就是选择第一个div节点
经过选择器选择后，选择结果都是bs4.element.Tag类型，这是这个库里一个重要的数据结构
Tag类型同样可以继续调用节点进行下一步的选择，例如soup.div.ul，也就是说可以嵌套选择，选择后的结果依然是Tag类型

关于Tag类，有几个常用的属性介绍一下
```
# 节点的文本内容
soup.div.string
# 节点的名称
soup.div.name
# 节点的属性
soup.div.attrs
```
其中string和name都是str类型，而attrs是dict类型，因为节点可能会有多个属性。
属性的类型也不一定都是str类型，有的返回结果是字符串组成的列表，例如class属性，一个节点元素可能有多个class。

此外，再介绍一下如何选中关联节点。
```
# 子节点，返回结果是列表形式，包含节点和文本
soup.p.contents
# 子节点，返回结果是生成器，需要遍历输出
soup.p.children
# 子孙节点，返回结果是生成器，需要遍历输出
soup.p.descendants
# 父节点
soup.p.parent
# 祖先节点
soup.p.parents
# 兄弟节点
## 后一个兄弟节点
soup.p.next_sibling
## 后面的所有兄弟节点
soup.p.next_siblings
## 前一个兄弟节点
soup.p.previous_sibling
## 前面的所有兄弟节点
soup.p.previous_siblings
```
这些关联节点返回不全是Tag类型，但是有相同的属性，所以可以用相同的方式查询属性

**方法选择器**

* find_all()
这个方法的API如下：find_all(name, attrs, recursive, text, **kwargs)
第一个属性是节点名，返回结果是列表类型，其元素是Tag类型
第二个是属性，返回结果是列表类型，其元素是Tag类型
第三个是文本，传入类型可以是字符串，也可以是正则表达式对象，返回结果是列表类型，其元素是str类型
* find()
返回单个元素，其余类似find_all()方法
* find_parents()和find_parent()
* find_next_siblings()和find_next_sibling()
* find_previous_siblings()和find_previous_sibling()

### pyquery库
关于BeautifulSoup，其实还有CSS选择器部分没介绍，但是pyquery的CSS选择器更加强大，因此就直接介绍pyquery吧

**初始化**

类似于bs，初始化pyquery的时候，也需要传入HTML来初始化一个PyQuery对象。它的初始化方式有多种，可以直接传入字符串，可以传入URL，可以传入HTML文件等
```
from pyquery import PyQuery as pq

doc = pq(html)
doc = pq(url='https://cuiqingcai.com')
doc = pq(filename='deme.html')
```

**查找节点**

```
# 选取class为list的节点
items = doc('.list')
# 子节点
lis = items.children()
# class为active的子节点
lis = items.children('.active')
# 传入CSS选择器，选取为li的子孙节点
lis = items.find('li')
# 父节点
lis = items.parent()
# 祖先节点，如果需要筛选，也可以传入CSS选择器
container = items.parents()
# 兄弟节点
lis = ltems.siblings()
```

**遍历**

pyquery的选择结果可能是多个节点，类型都是PyQuery类型，所以需要遍历来获取。这时候需要调用item()方法
```
lis = doc('li').item()
for li in lis:
    print(li)
```

**获取信息**

类似于bs，这里用attrs()来获取属性，用text()来获取文本
但如果想获取HTML文本，需要调用html()方法

**节点操作**

pyquery提供了一系列方法来对节点进行动态修改，这里就介绍一些常用的方法
```
li = doc('item-0.active')
# 删除class属性
li.removeClass('active')
# 添加class属性
li.addClass('active')
# 改变属性
li.attr('name', 'link')
# 改变文本内容
li.text(str)
# 改变html
li.html(html)
# 移除节点
li.remove()
```

**伪类选择器**

```
# 第一个li节点
li = doc('li:first-hild')
# 最后一个li节点
li = doc('li:last-child')
# 第二个li节点
li = doc('li:nth-child(2)')
# 第三个li之后的li节点
li = doc('li:gt(2)')
# 偶数位置的li节点
li = doc('li:nth-child(2n)')
# 包含second文本的li节点
li = doc('li:contains(second)')
```

### 总结

关于HTML解析库的内容，基本上就全部介绍完了，通过这些内容，基本可以解决HTML的解析了。
接下来打算跳过书本的第五章，直接学习ajax的有关内容，因为接下来打算做一个和淘宝有关的项目，需要了解动态加载的内容。
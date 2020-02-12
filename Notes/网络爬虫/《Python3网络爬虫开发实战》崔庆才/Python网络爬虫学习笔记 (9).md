## Python爬虫学习笔记（九）——Selenium的使用

### 介绍
之前介绍了Ajax的分析和爬取方式，但是也不能解决全部问题。
比如[中国青年网](http://news.youth.cn/gn/)的分页部分使用JS生成的，并非原始HTML代码，[ECharts](https://echarts.baidu.com/demo.html#bar-negative)中的图形都是经过JS计算之后生成的，[淘宝](https://www.taobao.com/)的Ajax接口有很多加密参数。这些网站很难直接分析Ajax来抓取。为了解决这些问题，最直接的方式就是模拟浏览器运行，这样就可以做到在浏览器中看到是什么样，抓取的源码就是什么样。
今天就介绍一下Selenium的使用

### 正文

```
from selenium import webdriver

# 初始化
browser = webdriver.Chrome()
'''
browser = webdriver.Firefox()
browser = webdriver.Edge()
browser = webdriver.PhantomJS()
browser = webdriver.Safari()
'''
# 访问页面
browser.get('https://www.taobao.com')
# 输出源代码
print(browser.page_source)
# 查找单个节点,返回WebElement类型
input = browser.find_element(By.ID, 'q')
input = browser.find_element_by_id('q')
# 查找全部节点,返回list，每个元素都是WebElement类型
lis = browser.find_elements(By.CSS_SELECTOR, '.service-bd li')
lis = browser.find_elements_by_css_selector('.service-bd li')
# 节点交互
## 输入文字及清除文字
input.send_keys('iPhone')
inpur.clear()
input.send_keys('iPad')
## 点击按钮
button = browser.find_element_by_class_name('btn-search')
button.click()
# 动作链
## 例如鼠标拖拽、键盘按键等
browser.get('http://www.runoob.com/try/try.php?filename=jqueryul-api-droppable')
browser.switch_to.frame('iframeResult')
source = browser.find_element_by_css_selector('#draggable')
target = browser.find_element_by_css_selector('#droppable')
actions = ActionChains(browser)
actions.drag_and_drop(source, target)
actions.perform()
# 执行JavaScript
## 例如下拉进度条
browser.get('https://www.zhihu.com/explore')
browser.execute_script('window.scrollTo(0, document.body.scrollHeight)')
browser.execute_script('alert("To Bottom")')
# 获取节点信息
## 获取节点属性
logo = browser.find_element_by_id('zh-top-link-logo')
print(logo.get_attribute('class'))
## 获取文本值
input = browser.find_element_by_class_name('zu-top-add-question')
print(input.text)
## 获取id、位置、标签名和大小
print(input.id)
print(input.location)
print(input.tag_name)
print(input.size)
# 切换Frame
# 延时等待
## 隐式等待
browser.implicitly_wait(10)
## 显式等待
# 前进和后退
# 选项卡管理
# 异常处理
# 关闭浏览器
browser.close()
```

### 总结

看这章的时候，就明显感觉到自己前端知识基础不够扎实了，CSS选择器啥的不是很会，选节点基本是看书的，所以打算暂停，去补一下知识了。然后明天就正式上课了，weekdays的时候就没什么时间学额外的内容了，所以周末再更吧。顺便趁着这几天补一下前端知识。
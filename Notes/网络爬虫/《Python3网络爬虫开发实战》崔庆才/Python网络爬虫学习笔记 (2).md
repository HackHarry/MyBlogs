## Python爬虫学习笔记（二）——requests库的使用

### 准备工作
requests库不是python自带的库，可以用pip安装。在使用时导入requests即可。

### 基本用法
#### GET请求
```
r = requests.get(url)
print(r.text)
```
其中，网页返回的内容是json格式的字符串类型，所以可以直接调用json()方法得到字典格式的内容
` print(r.json()) `
此外，如果需要附加额外的信息，可以用params这个参数，示例如下：
```
data = {
    'name': 'germey'
    'age': 22
}
url = 'http://httpbin.org/get'
r = requests.get(url, params=data)
print(r.text)
```
这样子，请求的链接就被自动构造成了'http://httpbin.org/get?age=22&name=germey'
浏览器头也是可以用headers这个参数来实现，代码如下：
` r = requests.get(url, headers = headers) `

#### POST请求
实现POST请求类似于GET请求，示例如下：
```
data = {'name': 'germey', 'age': '22'}
r = requests.post(url, data = data)
print(r.text)
```

#### 响应
发送请求之后，得到的自然是响应。常用的获取响应信息的方法和属性有下面几个：
```
r = requests.get(url)
print(r.status_code)
print(r.headers)
print(r.cookies)
print(r.history)
```

### 高级用法
#### Cookies
获取Cookies
```
r = requests.get(url)
print(r.cookies)
```
如果需要使用Cookies的话，只需要将Cookies设置到Headers里面，然后发送请求即可，十分简单

#### 会话维持
在requests中，如果直接用get()或post()等方法，相当于打开了不同的会话；如果要维持相同的会话，需要用Session对象，示例如下：
```
s = requests.Session()
s.get(url)
```

#### 代理设置
```
proxies = {
    "http": url_http,
    "https": url_https,
}
requests.get(url, proxies = proxies)
```

#### SSL证书验证
requests会检查SSL证书，可以使用verify参数来控制是否检查证书，默认为开启。何时需要关掉呢？举个例子。
例如访问12306官网时，会出现证书验证错误的结果，因为12306的证书没有被官方CA机构信任，所以会提示错误SSLError，代码如下：
```
r = requests.get('http://www.12306.cn', verify=False)
print(r.status_code)
```

#### 超时设置
` r = requests.get(url, timeout=1) `

#### 身份认证
` r = requests.get(url, auth=(username, password)) `

### 总结
requests库比urllib库简便了许多，不过还有些内容我没有完全理解，例如Prepared Request，这些都需要日后的不断练习。
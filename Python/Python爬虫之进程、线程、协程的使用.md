### Python爬虫之进程、线程、协程的使用

上次为了爬取想看的电影，写了个视频网站爬虫。今天上完了这学期最后一节课，又不想复习，就继续完善爬虫代码了。上次说到，因为爬取数量比较小，直接单线程爬取，所以今天来尝试写一下更高效地爬虫。

#### 环境设置

因为这是学习测试，为了对比不同写法的爬虫的优劣，需要营造出服务器请求响应很慢的状况，因此我用python的flask库搭建了一个简单的本地服务器，通过sleep方法来拖延响应时间。代码如下：

```python
from flask import Flask
import time

app = Flask(__name__)

@app.route("/")
def index():
    # 等待3秒后返回hello
    time.sleep(3)
    return "hello"

if __name__ == '__main__':
    app.run(threaded = True, debug = True)
```

运行这个文件就能在`127.0.0.1:5000`开启本地服务器了。

#### 普通爬虫

普通爬虫没有利用多进程、多线程或是协程技术，顺序执行所有请求，当遇到阻塞或是请求等待时，需要排队等待。代码如下：

```python
import time
import requests

url = "http://127.0.0.1:5000/"
total = 5

def spider_requests(_):
    requests.get(url)

def single_process():
    print("single process: ", end = "")
    start = time.time()
    for i in range(total):
        spider_requests(i)
    print("{}s".format(time.time()-start))
    print("----------------------------")
    
if __name__ == '__main__':
    single_process()
```

运行结果：

```cmd
single process: 15.034725666046143s
```

可以看到，普通爬虫发起5次请求花费了15秒的时间。

#### 多进程爬虫

如今的计算机基本都已经不是单核CPU了，因此可以利用多进程来实现爬虫的并行操作。

```python
import time
import requests
import multiprocessing

url = "http://127.0.0.1:5000/"
total = 5

def spider_requests(_):
    requests.get(url)

def multi_process():
    print("multi process: ", end = "")
    start = time.time()
    # 我的电脑是四核CPU，因此进程池选择4
    pool = multiprocessing.Pool(4)
    pool.map(spider_requests, range(total))
    print("{}s".format(time.time()-start))
    print("----------------------------")
    
if __name__ == '__main__':
    multi_process()
```

运行结果：

```cmd
multi process: 7.122582197189331s
```

比起普通的爬虫，多进程爬虫快了一倍。事实上，多进程爬虫爬取速度与CPU核心数有着很大的关系。我们总共请求5次，开了4个进程，因此有一个进程需要执行两次，总共6秒，多出来的1秒是进程调度花费的时间。可以看到，多进程中进程调度会花费不少时间。

#### 多线程爬虫

线程是Windows系统下调度和执行的基本单位，同一进程中两个线程的切换不会引起进程的切换，因此理论上比起多进程爬虫，多线程爬虫应当效率更高。

```python
import time
import requests
import threading

url = "http://127.0.0.1:5000/"
total = 5

def spider_requests(_):
    requests.get(url)
    
def multi_thread():
    print("multi threading: ", end = "")
    start = time.time()
    for i in range(total):
        t = threading.Thread(target=spider_requests, args=(i,))
        t.start()
        t.join()
    print("{}s".format(time.time()-start))
    print("----------------------------")

if __name__ == '__main__':
    multi_thread()
```

运行结果：

```cmd
multi threading: 15.041304111480713s
```

我们发现，多线程爬虫依然执行了15秒，并没有想象中的那么快速，这是为什么呢？

> 实际上，这是python的机制引起的。 因为Python的线程虽然是真正的线程，但解释器执行代码时，有一个GIL锁：Global Interpreter Lock，任何Python线程执行前，必须先获得GIL锁，然后，每执行100条字节码，解释器就自动释放GIL锁，让别的线程有机会执行。这个GIL全局锁实际上把所有线程的执行代码都给上了锁，所以，多线程在Python中只能交替执行，即使100个线程跑在100核CPU上，也只能用到1个核。 

也就是说，python的多线程实际上只是一种并发实现，而非并行。虽然能让程序看上去不是单一条线在跑，但实际上依然是单路执行的，只是一直在切换罢了。

#### 协程爬虫

> 协程又称微线程、纤程，是一种用户态的轻量级线程

协程有两个库，一个是gevent库，这是通过第三方来greenlet实现协程 。另外，从Python 3.4版本开始，python加入了自带的协程库——asyncio库。我们来对比使用一下这两种实现。

##### gevent库

```python
from gevent import monkey
monkey.patch_all()

import time
import requests
import gevent

url = "http://127.0.0.1:5000/"
total = 5

def spider_requests(_):
    requests.get(url)

def gevent_coroutine():
    print("gevent coroutine ", end = "")
    start = time.time()
    job_list = [gevent.spawn(spider_requests, _) for _ in range(total)]
    gevent.joinall(job_list)
    print("{}s".format(time.time()-start))
    print("----------------------------")

if __name__ == '__main__':
    gevent_coroutine()
```

运行结果：

```cmd
gevent coroutine 3.0617427825927734s
```

##### asyncio库

asyncio库是异步处理的，因此不能使用requests库来发起请求，因为requests无法挂起，不能进行异步操作。所以我们使用支持异步操作的aiohttp库来发起请求。

不过需要注意的是，python在3.4版本之后对aiohttp和asyncio库进行很多修改，不同版本的python可能写法也不一定相同，我运行的python版本是3.7.4。其中`asyncio.run()`方法就是python 3.7+的新特性，在此之前应当使用loop来操作。

代码如下：

```python
import time
import asyncio
import aiohttp

url = "http://127.0.0.1:5000/"
total = 5

async def spider_aiohttp():
    async with aiohttp.ClientSession() as session:
        await session.get(url)

async def coroutine_run():
    tasks = []
    for _ in range(total):
        tasks.append(asyncio.create_task(spider_aiohttp()))
    await asyncio.wait(tasks)

def asyncio_coroutine():
    print("asyncio coroutine ", end = "")
    start = time.time()
    asyncio.run(coroutine_run())
    print("{}s".format(time.time()-start))
    print("----------------------------")

if __name__ == '__main__':
    gevent_coroutine()
```

运行结果：

```cmd
asyncio coroutine 3.0285747051239014s
```

我们可以看到，以上两种实现方式的运行时间都大约在3秒钟，比起其他方式非常快了。

gevent库实现起来比较方便，但是是调用第三方库，会对python的一些基本库修改。目前我遇到的问题是使用了gevent库后无法开启多进程，网络上也少有资料。

asyncio库是python的内建库，写起来更pythonic，可操作性更高。不过使用起来不是非常方便，特别是需要将原来的普通爬虫修改为协程爬虫时，需要做大量改动。此外，当开启协程过多，会出现aiohttp未关闭的警告，但不会影响程序执行，我也不知道是哪里出的问题。

在知乎上看到网友对这两者的评价，我觉得很贴切：gevent像是自动挡的汽车，asyncio像是手动挡的汽车。

#### 比较

total = 5

```
single process: 15.034725666046143s
multi process: 7.122582197189331s
multi threading: 15.041304111480713s
gevent coroutine 3.0617427825927734s
asyncio coroutine 3.0285747051239014s
```

total = 100

```
single process: 300.7399170398712s
multi process: 85.22105407714844s
multi threading: 300.70550775527954s
gevent coroutine 3.3077826499938965s
asyncio coroutine 3.238480806350708s
```

可以看到，当请求次数越来越多时，协程的优势越来越明显，也可以看到，gevent实现的协程会比asyncio稍稍慢一点。

#### 电影爬虫代码修改

因为我本来是基于requests库写的，如果要用asyncio实现协程就很麻烦了，因此我基于gevent修改了代码，并补上了一些异常处理。

```python
from gevent import monkey
monkey.patch_all()

import requests
import time
import os
import gevent

base_url = ""
url_list = []

def download(url):
    global url_list
    headers = {
            'User-Agent': 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/55.0.2883.87 Safari/537.36',
            'Accept-Encoding': 'gzip, deflate, sdch',
            'Accept-Language': 'zh-CN,z;q=0.8'
        }
    filename = './videos/' + url[-7:]
    if os.path.exists(filename) == False:
        with open(filename, "wb") as fp: 
            start =  start = time.time()
            i = 0
            while i < 5:
                try:
                    response = requests.get(url, headers=headers, timeout = 10)
                    break
                except requests.exceptions.RequestException as e:
                    print("{}: {}".format(url[-7:], e))
                    i += 1
                    time.sleep(i/2)
            if i >= 5:
                print("{} failed!".format(url[-7:]))
            else:
                fp.write(response.content)
                url_list.remove(url)
                print("{} has finished! URL remains: {}".format(url[-7:], len(url_list)))
    else:
        url_list.remove(url)

if __name__ == "__main__":
    base_url = input("url:")
    base_url = base_url[:-7]
    num = int(input("max:"))
    url_list = [base_url + str(i).zfill(4) + ".ts" for i in range(0, num+1)]
    start = time.time()
    while len(url_list) > 0:
        job_list = [gevent.spawn(download, url) for url in url_list]
        gevent.joinall(job_list)
    print("it works {}s".format(time.time()-start))
```


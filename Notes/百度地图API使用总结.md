# 一

最近，我在做一个纽约地区自行车可视化的项目，其中需要用到地图操作。起初，我尝试用D3.js库绘制地图，但因为资料有点少、坑有点多，摸索了几天后最后放弃了，改用一些地图的API。

因为是在国内，备选项基本上就是阿里系的高德地图和百度系的百度地图，两者我都去了解了一下。粗略体验下，高德地图API的使用更加方便，而且官方文档十分详细，可以堪比新手教程了，而百度地图的文档过于简洁了，有些方法都没讲所有参数的作用。但因为高德地图没有国外的地图数据，因此只能用百度地图了。

### 调用

首先，需要申请服务密钥，这步很简单，需要注意的是应用类型，百度地图API改版之后区分了服务端和浏览器端。由于我需要的是JavaScript调用，因此申请的是浏览器端。除此之外，还有微信小程序、安卓端和iOS端。
然后是在代码中调用API了。
首先需要在里创建一个容器，我需要让地图充满整个页面。

```html
<style type="text/css">  
    html{height:100%}    
    body{height:100%;margin:0px;padding:0px}    
    #container{height:100%}    
</style>
```

然后是script调用百度地图API

```html
<script type="text/javascript" src="http://api.map.baidu.com/api?v=3.0&ak=密钥"></script>
```

接下来是在body中创建一个div标签用于显示地图

```javascript
var map = new BMap.Map("container"); 
//创建地图实例
var point = new BMap.Point(116.404, 39.915); 
//创建点坐标
map.centerAndZoom(point, 15); 
//初始化地图，设置地图中心点以及缩放等级
map.enableScrollWheelZoom(true);
//开启鼠标滚轮缩放
```

### 坐标转换

百度的坐标转换文档是真的简陋，就给了三个例子，连说明都没有。我先给出百度文档中的相关代码，然后解释一下代码的意义。

```javascript
translateCallback = function (data) {
    if(data.status === 0) {
        var marker = new BMap.Marker(data.points[0]);
        bm.addOverlay(marker);
        var label = new BMap.Label("转换后的百度坐标（正确）",{offset:new BMap.Size(20,-10)});
        marker.setLabel(label); //添加百度label
        bm.setCenter(data.points[0]);
    }
}

setTimeout(function() {
    var convertor = new BMap.Convertor();
    var pointArr = [];
    pointArr.push(ggPoint);
    convertor.translate(pointArr, 1, 5, translateCallback)
}, 1000);
```

首先是translateCallback函数，这个函数是一个回调函数，用于执行转换后的操作。至于为什么这么写，我对JavaScript不熟悉，只能按照百度的写法来了。data是转换后的Object，目前看到有两个参数，一个是status，表示转换状态，一个是points，表示转换后的点坐标。
然后是setTimeout函数，这是一个延时函数，不需要考虑太多，其中1000的单位是ms。我们来关注convertor.tanslate()方法，其中convertor是BMap命名空间下的Convertor类的对象，第一个参数pointArr顾名思义就是存储坐标点的Object，或者理解为数组，最后一个参数translateCallback就是回调函数。中间的两个参数没有说明具体含义，我个人猜测是表示不同的坐标系转换，将编号为1的坐标系转换为编号为5的坐标系。
**需要注意**的点有两个：

1. pointArr数组元素的类型是BMap.Point，我就是因为没有注意这个问题，而导致回调函数根本没有被执行。而如果传入的类型错误，它不会报错，而只是给个警告。
2. 坐标转换接口的调用似乎是有上限的，根据测试，一次最多调用10个点，因此如果有大量点需要转换，我想到两个方法。一个是分组转换，还有一个是事先预处理，提前将点转换为百度坐标。

### 标注

然后是向地图添加标注的操作，标注是BMap下的Marker类，添加方法是addOverlay()。

```javascript
var marker = new BMap.Marker(point);
// 创建标注    
map.addOverlay(marker);
// 将标注添加到地图中
map.removeOverlay(marker);
// 移除标注
map.clearOverlays();
// 清除所有标注
```

我们常用的操作有，更改标注的偏移量、更换图标、监听标注、拖拽标注等。以下是官方文档的代码。

##### 修改标注属性

```javascript
function addMarker(point, index){  // 创建图标对象   
    var myIcon = new BMap.Icon("markers.png", new BMap.Size(23, 25), {    
        // 指定定位位置。   
        // 当标注显示在地图上时，其所指向的地理位置距离图标左上    
        // 角各偏移10像素和25像素。您可以看到在本例中该位置即是   
        // 图标中央下端的尖角位置。    
        anchor: new BMap.Size(10, 25),    
        // 设置图片偏移。   
        // 当您需要从一幅较大的图片中截取某部分作为标注图标时，您   
        // 需要指定大图的偏移位置，此做法与css sprites技术类似。    
        imageOffset: new BMap.Size(0, 0 - index * 25)   // 设置图片偏移    
    });      
    // 创建标注对象并添加到地图   
    var marker = new BMap.Marker(point, {icon: myIcon});    
    map.addOverlay(marker);    
}
```

此外，Marker也有setIcon()方法来设置标注图标，但是官方文档只说明了有这么个方法，并没有给出说明。以下我自己摸索的写法，去掉了外面的function，这样方便用在需要清除部分标注的场景。不过需要注意的是，大部分浏览器会限制Javascript加载本地文件，因此需要搭建服务器后才能加载本地文件。

```javascript
var myIcon = new BMap.Icon("bicycle.png", new BMap.Size(24, 24), {
    anchor: new BMap.Size(10, 25),
    imageOffset: new BMap.Size(0, 0)  
});
var marker = new BMap.Marker(data.points[j], {icon: myIcon})
map.addOverlay(marker);
```

##### 监听标注

```
marker.addEventListener("click", function(){    
    alert("您点击了标注");    
});  
```

##### 拖拽标注

```
marker.enableDragging();    
marker.addEventListener("dragend", function(e){    
    alert("当前位置：" + e.point.lng + ", " + e.point.lat);    
})   
```

---

以上就是我到目前为止用到的百度地图API的操作。



# 二

这次，我做的工作主要有两个，一是用Python对坐标进行预处理，二是在两个点之间绘制折线来表示路径。其中Python的预处理工作有两个，一个是计算坐标，另一个是转换坐标。

首先讲讲为什么要用Python而不是直接用JavaScript。

我所需要做的事情是绘制每分钟自行车的位置，并将其与出发点连线。考虑到数据量比较大，实时计算位置会很慢，因此我打算预先计算好每分钟所有自行车的位置。由于每辆自行车需要和出发点连线，因此还需要存下出发点的坐标，而多辆自行车可能有同一个出发点，因此我用一个数组专门存出发点坐标，然后每辆自行车存下对应出发点数组的下标。

这个思路应该是没有问题的，但当我实际操作时候就发现问题了。先回顾一下JavaScript坐标转换的代码。

```javascript
translateCallback = function (data) {
    if(data.status === 0) {
        var marker = new BMap.Marker(data.points[0]);
        bm.addOverlay(marker);
        var label = new BMap.Label("转换后的百度坐标（正确）",{offset:new BMap.Size(20,-10)});
        marker.setLabel(label); //添加百度label
        bm.setCenter(data.points[0]);
    }
}

setTimeout(function() {
    var convertor = new BMap.Convertor();
    var pointArr = [];
    pointArr.push(ggPoint);
    convertor.translate(pointArr, 1, 5, translateCallback)
}, 1000);
```

实际操作中发现，传入的pointArr和返回函数中的data.points很难一一对应上。此外，JavaScript中这两个函数似乎是异步的，并非是setTimeout执行一次，translateCallback就执行一次，因此就算在外围定义全局变量也难以实现对应关系。于是，我就考虑用Python对坐标进行预处理。

### Python调用百度地图API

Python调用API是通过http/https形式发起检索请求，获取返回json或xml格式的检索数据，这里需要有一点点爬虫的知识。

说起来有一个有趣的事情，上次我对JavaScript中转换坐标函数的参数1和5的解释，在这里的文档里有详细的介绍，的确是表示不同类型的坐标，总共有8种。

因为这种调用方式是WebAPI，官方文档没有给出具体语言的具体代码，以下是我自己写的代码。

```python
import requests
import time

def convertor(coords):
    url = 'http://api.map.baidu.com/geoconv/v1/?'
    payload = {
        'coords': '{}, {}'.format(coords[0], coords[1]),
        'from': 1,
        'to': 5,
        'ak': '密钥'
    }
    while True:
        response = requests.get(url=url, params=payload)
        time.sleep(0.01)
        if response.json()['status'] == 0:
            return response.json()['result'][0]
```

关于请求参数、返回结果参数和状态码，官方文档有详细的介绍，我就偷个懒吧。

### 绘制折线

折线在地图上绘制为一系列直线段。可以自定义这些线段的颜色、粗细和透明度。颜色可以是十六进制数字形式（比如：#ff0000）或者是颜色关键字（比如：red）。

以下代码段会在两点之间创建6像素宽的蓝色折线：

```javascript
var polyline = new BMap.Polyline([
		station[station_id],
		point_xy
	],
	{strokeColor:"blue", strokeWeight:6, strokeOpacity:0.5}
);
map.addOverlay(polyline);
```

---

虽然这次更新讲起来，好像没什么内容，但我在纠结数据该怎么存的时候花了很长时间，而因为数据量比较大，跑Python数据就跑了半天。最开始时候，我是打算一次跑完数据再写入文件里，但是都是跑到一半就失败了，我以为是接口调用太频繁，就一直修改sleep的值，结果发现似乎是数据太大，存在一个变量里存不下了。

总而言之，数据处理这块还是有很多坑的，也有我经验不足、没能事先想好的原因在里面，还是花了不少时间。
# 什么是ANR，如何避免

ANR是指应用程序未响应，安卓系统对于一些事件需要在一定的时间范围内完成，如果超过预定时间仍未能得到有效响应或者响应时间过长，都会造成ANR。

出现的原因有三种：

（1）KeyDispatchTimeout（5 seconds）主要类型按键或触摸事件在特定时间内无响应

（2）BroadcastTimeout（10 seconds）BoradcastReceiver在特定的时间内无法处理

（3）ServiceTimeout（20 seconds）小概率类型Service在特定的时间内无法处理完成

3：避免ANR最核心的一点就是在主线程减少耗时操作。通常需要从那个以下几个方案下手：

（1）使用子线程处理耗时IO操作

（2）降低子线程优先级，使用Thread或者HandlerThread时，调用Process.setThreadPriority（Process.THREAD_PRIORITY_BACKGROUND）设置优先级，否则仍然会降低程序响应，因为默认Thread的优先级和主线程相同

（3）使用Handler处理子线程结果，而不是使用Thread.wait()或者Thread.sleep()来阻塞主线程

（4）Activity的onCreate和onResume回调中尽量避免耗时的代码

（5）BroadcastReceiver中onReceiver代码也要尽量减少耗时操作，建议使用intentService处理。intentService是一个异步的，会自动停止的服务，很好解决了传统的Service中处理完耗时操作忘记停止并销毁Service的问题

# ContentProvider实现原理

# 介绍Binder机制

# 匿名共享内存，使用场景

# 如何自定义View，如果要实现一个转盘圆形的View，需要重写View中的哪些方法？(onLayout,onMeasure,onDraw)

# Android事件分发机制

## 1. 基础认知

1.1 事件分发的”事件“是指什么？

**答：点击事件（`Touch`事件）**。具体介绍如下：

![image-20220414164743405](E:\Libraries\notes\se\android\Android_files\image-20220414164743405.png)

此处需要特别说明：事件列，即指从手指接触屏幕至手指离开屏幕这个过程产生的一系列事件。一般情况下，事件列都是以DOWN事件开始、UP事件结束，中间有无数的MOVE事件。

![image-20220414164759290](E:\Libraries\notes\se\android\Android_files\image-20220414164759290.png)

### 1.2 事件分发的本质

**答：将点击事件（MotionEvent）传递到某个具体的`View` & 处理的整个过程**

> 即 事件传递的过程 = 分发过程。

### 1.3 事件在哪些对象之间进行传递？

**答：Activity、ViewGroup、View**。`Android`的`UI`界面由`Activity`、`ViewGroup`、`View` 及其派生类组成

![image-20220414164819052](E:\Libraries\notes\se\android\Android_files\image-20220414164819052.png)

![image-20220414164840825](E:\Libraries\notes\se\android\Android_files\image-20220414164840825.png)

### 1.4 事件分发的顺序

即 事件传递的顺序：`Activity` -> `ViewGroup` -> `View`

> 即：1个点击事件发生后，事件先传到`Activity`、再传到`ViewGroup`、最终再传到 `View`

### 1.5 事件分发过程由哪些方法协作完成？

**答：dispatchTouchEvent() 、onInterceptTouchEvent()和onTouchEvent()**

![image-20220414164940418](E:\Libraries\notes\se\android\Android_files\image-20220414164940418.png)

### 1.6 总结

![image-20220414165007656](E:\Libraries\notes\se\android\Android_files\image-20220414165007656.png)

## 2. 事件分发机制流程详细分析

主要包括：`Activity`事件分发机制、`ViewGroup`事件分发机制、`View`事件分发机制

### 流程1：Activity的事件分发机制

Android事件分发机制首先会将点击事件传递到Activity中，具体是执行dispatchTouchEvent()进行事件分.

```JAVA
/**
  * 源码分析：Activity.dispatchTouchEvent（）
  */ 
  public boolean dispatchTouchEvent(MotionEvent ev) {

    // 仅贴出核心代码

    // ->>分析1
    if (getWindow().superDispatchTouchEvent(ev)) {

        return true;
        // 若getWindow().superDispatchTouchEvent(ev)的返回true
        // 则Activity.dispatchTouchEvent（）就返回true，则方法结束。即 ：该点击事件停止往下传递 & 事件传递过程结束
        // 否则：继续往下调用Activity.onTouchEvent

    }
    // ->>分析3
    return onTouchEvent(ev);
  }

/**
  * 分析1：getWindow().superDispatchTouchEvent(ev)
  * 说明：
  *     a. getWindow() = 获取Window类的对象
  *     b. Window类是抽象类，其唯一实现类 = PhoneWindow类
  *     c. Window类的superDispatchTouchEvent() = 1个抽象方法，由子类PhoneWindow类实现
  */
  @Override
  public boolean superDispatchTouchEvent(MotionEvent event) {

      return mDecor.superDispatchTouchEvent(event);
      // mDecor = 顶层View（DecorView）的实例对象
      // ->> 分析2
  }

/**
  * 分析2：mDecor.superDispatchTouchEvent(event)
  * 定义：属于顶层View（DecorView）
  * 说明：
  *     a. DecorView类是PhoneWindow类的一个内部类
  *     b. DecorView继承自FrameLayout，是所有界面的父类
  *     c. FrameLayout是ViewGroup的子类，故DecorView的间接父类 = ViewGroup
  */
  public boolean superDispatchTouchEvent(MotionEvent event) {

      return super.dispatchTouchEvent(event);
      // 调用父类的方法 = ViewGroup的dispatchTouchEvent()
      // 即将事件传递到ViewGroup去处理，详细请看后续章节分析的ViewGroup的事件分发机制

  }
  // 回到最初的分析2入口处

/**
  * 分析3：Activity.onTouchEvent()
  * 调用场景：当一个点击事件未被Activity下任何一个View接收/处理时，就会调用该方法
  */
  public boolean onTouchEvent(MotionEvent event) {

        // ->> 分析5
        if (mWindow.shouldCloseOnTouch(this, event)) {
            finish();
            return true;
        }
        
        return false;
        // 即 只有在点击事件在Window边界外才会返回true，一般情况都返回false，分析完毕
    }

/**
  * 分析4：mWindow.shouldCloseOnTouch(this, event)
  * 作用：主要是对于处理边界外点击事件的判断：是否是DOWN事件，event的坐标是否在边界内等
  */
  public boolean shouldCloseOnTouch(Context context, MotionEvent event) {

  if (mCloseOnTouchOutside && event.getAction() == MotionEvent.ACTION_DOWN
          && isOutOfBounds(context, event) && peekDecorView() != null) {

        // 返回true：说明事件在边界外，即 消费事件
        return true;
    }

    // 返回false：在边界内，即未消费（默认）
    return false;
  } 
```

当一个点击事件发生时，从`Activity`的事件分发开始（`Activity.dispatchTouchEvent()`），流程总结如下：

![image-20220414165237533](E:\Libraries\notes\se\android\Android_files\image-20220414165237533.png)

![image-20220414165423739](E:\Libraries\notes\se\android\Android_files\image-20220414165423739.png)

没看完

# Socket和LocalSocket

# HttpClient和URLConnection的区别

区别

1、HttpURLConnection是java的标准类，没有做封装，用起来比较原始

2、HttpClient是开源框架，封装了访问HTTP的请求头、参数、内容体、响应等；HttpURLConnection中的输入输出流操作，在这个接口中被统一封装成了HttpPost（HttpGet）和HttpResponse。这样，减少了操作的繁琐性。

下面分别给出HttpURLConnection和HttpClient实现GET、POST请求示例，作为学习。

（1）HttpURLConnection实现GET

```java
package com.jingchenyong.test;
 
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
 
public class Test_HttpURLConnection_GET
{
    public static void main(String[] args) throws Exception
    {
        String urlString="http://15.6.46.35:8080/platform/index.html";
        URL url=new URL(urlString);
        HttpURLConnection conn = (HttpURLConnection)url.openConnection();
        conn.setRequestProperty("Accept-Charset", "UTF-8");
        conn.setRequestProperty("connection", "keep-Alive");
        conn.setRequestMethod("GET");
        conn.connect();
        
        int code=conn.getResponseCode();
        System.out.println(code);
        //把流转为字符串方式一
        //String  result=IOUtils.toString(conn.getInputStream(),"UTF-8");
        //把流转为字符串方式二
        BufferedReader br=new BufferedReader(new InputStreamReader(conn.getInputStream(), "UTF-8"));
        String result="";
        String tmp="";
        while((tmp=br.readLine())!=null){
            result=result+tmp;
        }
        System.out.println(result);
        //关闭流和连接    
    }   
}
```

HttpURLConnection实现POST

```java
package com.jingchenyong.test;
 
import java.io.BufferedOutputStream;
import java.net.HttpURLConnection;
import java.net.URL;
 
import org.apache.commons.io.IOUtils;
import org.apache.commons.lang.StringUtils;
 
import com.alibaba.fastjson.JSON;
import com.alibaba.fastjson.JSONObject;
 
public class Test_HttpURLConnection_POST
{
    
    public static void main(String[] args)
        throws Exception
    {
        //设置连接
        String urlString = "http://15.6.46.37:9200//henry/henry/_search";
        URL url = new URL(urlString);
        HttpURLConnection conn = (HttpURLConnection)url.openConnection();
        conn.setRequestProperty("Accept-Charset", "UTF-8");
        conn.setRequestProperty("connection", "keep-Alive");
        conn.setRequestMethod("POST");
        conn.setDoInput(true);
        conn.setDoOutput(true);
        conn.connect();
        String jsonstring = getJOSNString();
        if (StringUtils.isNotBlank(jsonstring))
        {
            /**
             * post提交方式一
             */
           /* OutputStream os = conn.getOutputStream();
            BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(os));
            writer.write(jsonstring);
            writer.flush();
            writer.close();*/
            BufferedOutputStream out = new BufferedOutputStream(conn.getOutputStream());
            out.write(jsonstring.getBytes());
            out.flush();
            out.close();
            //流转字符串的另一种方式见GET方式
            String  result=IOUtils.toString(conn.getInputStream(),"UTF-8");
            System.out.println(result);
            //注意关闭流和连接，这里省略
        }
    }
    
    public static String getJOSNString()
    {
        JSONObject jsonobject = new JSONObject();
        JSONObject jsonobject1 = new JSONObject();
        JSONObject jsonobject2 = new JSONObject();
        jsonobject2.put("name", "jingchenyong");
        jsonobject1.put("match", jsonobject2);
        jsonobject.put("query", jsonobject1);
        String jsonstring = JSON.toJSONString(jsonobject);
        return jsonstring;
    }
}
```

HttpClient实现GET

```java
package com.jingchenyong.test;
 
import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.Map;
import java.util.Map.Entry;
 
import org.apache.commons.collections.MapUtils;
import org.apache.http.client.config.RequestConfig;
import org.apache.http.client.methods.CloseableHttpResponse;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.utils.URIBuilder;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.impl.client.HttpClients;
 
public class Test_HttpClient_GET
{
    
    public static void main(String[] args) throws Exception
    {
        String url="http://15.6.46.35:8080/platform/index.html";
        URIBuilder builder = new URIBuilder(url);
        CloseableHttpClient httpClient = HttpClients.createDefault();
        Map<String,Object> map=getMap();
        if(MapUtils.isNotEmpty(map)){
            for(Entry<String,Object> entry:map.entrySet()){
                builder.addParameter(entry.getKey(), String.valueOf(entry.getValue()));
            }
            url=builder.build().toString();
        }
        HttpGet get=new HttpGet(url);
        // 增加超时设置
        RequestConfig requestConfig = RequestConfig.custom().setConnectTimeout(1000).build();
        get.setConfig(requestConfig);
        
        //发送GET请求
        CloseableHttpResponse response=httpClient.execute(get);
        //获取状态码
        System.out.println(response.getStatusLine().getStatusCode());
        //把结果流转为字符串方式一
        /*
        String result=IOUtils.toString(response.getEntity().getContent());
        System.out.println(result);
        */
        //把结果流转为字符串方式二
        StringBuilder reMsgBuider = new StringBuilder();
        InputStream in = response.getEntity().getContent();
        BufferedReader reader = new BufferedReader(new InputStreamReader(in, "UTF-8"));
        String msg = null;
        // 读取返回消息体
        while ((msg = reader.readLine()) != null) {
            reMsgBuider.append(msg);
        }
        String result = reMsgBuider.toString();
        System.out.println(result);
        //关闭流和连接
        
    }
    public static Map<String,Object> getMap(){
        Map<String,Object> map=new HashMap<String,Object>();
        //map.put("name", "jingchenyong");
        //map.put("age", 26);
        return map;
    }
}
```

HttpClient实现POST

```java
package com.jingchenyong.test;
 
import org.apache.commons.io.IOUtils;
import org.apache.http.client.config.RequestConfig;
import org.apache.http.client.methods.CloseableHttpResponse;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.StringEntity;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.impl.client.HttpClients;
import org.apache.http.util.EntityUtils;
 
import com.alibaba.fastjson.JSON;
import com.alibaba.fastjson.JSONObject;
 
public class Test_HttpClient_POST
{
    
    public static void main(String[] args) throws Exception{
        String jsonstring=getJOSNString();
        RequestConfig config = RequestConfig.custom().setSocketTimeout(30000).setConnectTimeout(30000).build();
        CloseableHttpClient client = HttpClients.custom().setDefaultRequestConfig(config).build();
        HttpPost post = new HttpPost("http://15.6.46.37:9200//henry/henry/_search");
        //填充post体
        post.setEntity(new StringEntity(jsonstring,"UTF-8"));
        CloseableHttpResponse response = client.execute(post);
        System.out.println("状态码为："+response.getStatusLine().getStatusCode());
        //方式一
        //System.out.println("获取的结果为(获取方式一)："+IOUtils.toString(response.getEntity().getContent()));
        //方式二 见GET
        //方式三
        System.out.println("获取的结果为(获取方式二)："+EntityUtils.toString(response.getEntity(), "UTF-8"));
    }
    
    public static String getJOSNString()
    {
        JSONObject jsonobject = new JSONObject();
        JSONObject jsonobject1 = new JSONObject();
        JSONObject jsonobject2 = new JSONObject();
        jsonobject2.put("name", "jingchenyong");
        jsonobject1.put("match", jsonobject2);
        jsonobject.put("query", jsonobject1);
        String jsonstring = JSON.toJSONString(jsonobject);
        return jsonstring;
    }
}
```

性能方面：
HttpURLConnection的访问速度比HttpClient要快。

# Parcelable和Serializable区别

Parcelable和Serializable都可以实现序列化，使对象可以变为二进制流在内存中传输数据。在Android中，只要实现二者之一就可以使用Intent和Binder来传递数据。实现了Parcelable接囗的类依赖于Parcel这个类来实现数据传递，它并不是一个一般化用途的序列化机制，主要用于IPC机制下的高性能传输。

#### 差别

1. 来源上

Parcelable是Android提供的序列化接口，Serializable是Java提供的序列化接口。因此Parcelable只能在Android中使用，而Serializable可以在任何使用Java语言的地方使用。

1. 使用上

Parcelable使用起来比较麻烦，序列化过程需要实现Parcelable的`writeToParcel(Parcel dest, int f1ags)`方法和`describeContents()`方法。其中`describeContents()`方法直接返回0就可以了。为了反序列化，还需要提供一个非空的名为`CREATOR`的静态字段，该字段类型是实现了Parcelable.Creator接口的类，一般用一个匿名内部类实现就可以了。现在也有一些插件可以方便地实现Parcelable接口。

Serializable的使用就比较简单，直接实现Serializable接口即可，该接口没有任何方法。序列化机制依赖于一个long型的`serialVersionUID`，如果没有显式的指定，在序列化运行时会基于该类的结构自动计算出一个值。如果类的结构发生变化就会导致自动计算出的`serialVersionUID`不同。这就会导致一个问题，序列化之后类如果新增了一个字段，反序列过程就会失败。一般会报**InvalidClassException**这样的异常。
而如果显式的指定了`serialversionUID`，只要类的结构不发生重大变化，如字段类型发生变化等，仅仅添加或者删除字段等都可以反序列化成功。
注意：如果要把对象持久化到存储设备或者通过网络传输到其它设备，最好使用Serializable。

1. 效率上

Serializable的序列化和反序列化都需要使用到IO操作；而Parcelable不需要IO操作，Parcelable的效率要高于Serializable，Android中推荐使用Parcelable。

### 自定义一个类让其实现Parcelable，大致流程是什么?

自定义一个类让其实现Parcelable接口，大致流程是先实现该接口的`writeToParcel(Parcel dest, int flags)`和`describeContents()`方法。然后添加一个Parcelable.Creator类型的名字为`CREATOR`的非空字段。例如：

```
public class Person implements Parcelable {
    private String name;
    private int age;
    
    //...
    
    @Override
    public int describeContents() {
        return 0;
    }
    
    @Override
    public void writeToParcel(Parcel dest, int flags) {
        dest.writeString(name); // 写出name
        dest.writeInt(age); // 写出age
    }
    
    public static final Parcelable.Creator<Person> CREATOR = new Parcelable.
            Creator<Person>() {
            
        @Override
        public Person createFromParcel(Parcel source) {
            Person person = new Person();
            person.name = source.readString(); // 读取name
            person.age = source.readInt(); // 读取age
            return person;
        }
        
        @Override
        public Person[] newArray(int size) {
            return new Person[size];
        }
    };
}
```

该类中的字段类型除了基本类型和String及它们对应的数组，如果有其它自定义的类型，也需要实现Parcelable或者Serializable接口。

# Android里跨进程传递数据的几种方案。

1.Bundle，在安卓中不同的应用运行在不同的进程中。通过Intent启动其他应用的组件Activity、Service、Receiver时，可以将数据存储在Bundle中，然后设置在Intent中。

2.系统文件，如SP。

3.ContentProvidert提供数据分享的接口：ContentResolver

4.跨进程Messenger

6.AIDL

# TextView怎么改变局部颜色

SpannableString、HTML

# Android中Handler声明非静态对象会发出警告，为什么，非得是静态的？(Memory Leak)

# 广播注册后不解除注册会有什么问题？(内存泄露)

# 属性动画(Property Animation)和补间动画(Tween Animation)的区别，为什么在3.0之后引入属性动画([官方解释：调用简单](http://android-developers.blogspot.com/2011/05/introducing-viewpropertyanimator.html))

# Android里的LRU算法原理

# BrocastReceive里面可不可以执行耗时操作?

# Service onBindService 和startService 启动的区别
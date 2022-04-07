gradle 入门指南 https://www.jianshu.com/p/4fbf352ffc56

# Groovy基础

gradle使用Groovy作为基本语言

## 数据类型

Groovy是弱化类型语言，但是实现上还是强类型相关，如果类型不对，还是会报错。Groovy 中的基本数据类型有

- byte -这是用来表示字节值。例如2。

- short -这是用来表示一个短整型。例如10。

- int -这是用来表示整数。例如1234。

- long -这是用来表示一个长整型。例如10000090。

- float -这是用来表示32位浮点数。例如12.34。

- double -这是用来表示64位浮点数，这些数字是有时可能需要的更长的十进制数表示。例如12.3456565。

- char -这定义了单个字符文字。例如“A”。

- Boolean -这表示一个布尔值，可以是true或false。

- String -这些是以字符串的形式表示的文本。例如，“Hello World”的。

```groovy
int a = 4;
float b = 1.0;
double c = 2.1;
byte  te = 4;
char ch = 'c';
String str = "abcd";
```

## 变量和方法的声明

在 Groovy 中通过 def 关键字进行变量和方法的声明。

```groovy
def a = 1
def b = 1.0
def str = "Hello World"

def output() {
    print 'Hello World'
}
```

Groovy 类似脚本，所以有很多都可以省略：

- 语句后的分号;可以省略
- 变量的类型可以省略
- 方法返回值 return 语句可以省略

方法的声明：

Groovy 也是一门 JVM 语言，所以在语法上与 Java 有很多相通的地方，这样在方法的声明时候格式也比较随意，所以作为 Android 程序员，我们可以选择靠拢 Java 语法格式的风格。

```groovy
def methodName() {
    print("HelloWorld")
}

def int sum2Number(a, b) {
    return a + b
}

def sum(a, b) {
    return a+b
}

int add(a ,b) {
    return a + b
}
```

## 循环

Groovy 中循环控制语句与 Java 中的类似，有以下三种：

- for 语句
- while 语句
- for-in 语句

```groovy
for(int i = 0 ;i < 9; i++) {
    println(i)
}

int i = 0
while(i++ < 9) {
    println(i)
}

for(int j in 1..9) {
    println(j)
}
```

同样，针对循环也有循环控制语句：

break：break语句用于结束循环和switch语句内的控制流。

continue：结束本次循环，进行下次循环，仅限于while和for循环。

```groovy
for(int i = 0 ;i < 9; i++) {
    println(i)
    continue
}

for(int j in 1..9) {
    println(j)
    break
}
```

## 条件判断语句

Groovy 中的条件判断语句与 Java 中的类似，有：

- if
- if...else
- if...else if...else
- switch

例子就不演示了，语法跟 Java 相同。

在上面的 Groovy 基础介绍中，形式上跟 Java 语言非常相似，没有太大的变化，针对 Java 、Android 程序员来说应该非常容易上手。

## List列表

基本语法：List 列表使用[ ] 进行声明，并通过索引进行区分。

```groovy
def listEmpty = []    //空列表
def list = [1,2,3,4,5] //整数值列表
def listInt = [1,[2,3],4,5] //列表嵌套列表
def listString = ["andoter","note"] //字符串列表
def listNone = ["andoter",1,4]  //异构对象列表
```

列表中的方法：

- boolean add(E e)
- void add(int index, E element)
- boolean addAll(Collection<? extends E> c)
- void clear()
- boolean contains(Object o)
- Iterator<E> iterator()
- Object[] toArray()
- int lastIndexOf(Object o)
- E set(int index, E element)

这些方法都跟 Java 中的类似，打开对应的类型查看后，发现通过 def 声明的列表竟然是 java.util.List 下面的。

```groovy
def listEmpty = []    //空列表
def list = [1,2,3,4,5] //整数值列表
def listInt = [1,[2,3],4,5] //列表嵌套列表
def listString = ["andoter","note"] //字符串列表
def listNone = ["andoter",1,4]  //异构对象列表

listEmpty.add(1)
listEmpty << 6
println(listEmpty.size())
list.clear()
println(listInt.contains([2,3]))
println(listString.lastIndexOf("note"))
println(listNone.indexOf(1))
```

> 需要注意，在 groovyjarjarantlr.collections.List 包下同样存在 List，所以使用的时候需要注意。

关于列表 List 的遍历，我们可以参照 Java 中的 Iterator 接口去遍历，或者使用 Groovy 系统提供的 each 方法进行遍历。在 Groovy 中提供 DefaultGroovyMethods 类，该类定义很多快捷使用方法：

- abs：取绝对值计算
- addAll(Collection)
- each：遍历
- eachWithIndex：带 index 的遍历
- grep：符合条件的element会被提取出来，形成一个list
- every：所有的element都满足条件才返回true，否则返回false
- any：只要存在一个满足条件的element就返回true，否则返回false
- join：用指定的字符连接collection中的element
- sort：根据指定条件进行排序
- find：查找collection中满足条件的‘第一个’element
- findAll：查找collection中满足条件的‘所有’element

很多使用的方法，可参照源码查看。

```groovy
def listString = ["andoter","note"]

listString.each {
    println(it)
}

listString.each {
    value -> println(value)
}
```

## Map 映射

Map集合中的元素由键值访问。 Map中使用的键可以是任何类。当我们插入到Map集合中时，需要两个值：键和值。

```groovy
def mapEmpty = [ : ]
def mapString = ["name":"andoter","email" : "andoter0504@gmail.com"]
def mapInt = ["name" : 123, "age" : 26]
```

映射中的方法：

- void clear()
- boolean containsValue(Object value)
- Map.Entry<K, V> eldest()
- Set<Map.Entry<K,V>> entrySet()
- void forEach(BiConsumer<? super K, ? super V> action)
- V get(Object key)
- Set<K> keySet()
- Collection<V> values()

总体上方法与 Java 中的 Map 相同。

```groovy
def mapEmpty = [ : ]
def mapString = ["name":"andoter", "email" : "andoter0504@gmail.com"]
def mapInt = ["name" : 123, "age" : 26]

mapEmpty.put("name","andoter")
mapEmpty.values()
mapString.get("name")
mapInt.containsValue("123")
mapString.each {key, value ->
    if(key == null || key.length() == 0) {
        println("Null Object")
    }

    if(key.equals("name")){
        println(key + "=" + value)
    }else{
        println(key + ":" + value)
    }
}
```

## IO操作

Java 提供了 java.io.* 一系列方法用于文件的操作，这些方法在 Groovy 中也适用。Groovy 针对 Java 提供的方法做了增强处理，更方便使用。

```groovy
def file = new File("/Users/dengshiwei/WorkProject/GradlePlugin/groovydemo/src/main/groovy/TestGroovy.groovy")
if (file.exists()) {
   file.eachLine {
       line ->
           println(line)
   }
} else {
    print("File not exist")
}
```

这里简单的示例下，更多的内容请参照官方 API 接口。

## 闭包

闭包作为 Groovy 中非常重要的特性，它使得 Groovy 语言更加灵活，在 Gradle 项目构建中，更是在 DSL 中大量被使用，所以掌握闭包的使用对掌握 Android 项目构建有非常重要的作用。

### 闭包的定义

作者：Ant_way
链接：https://www.jianshu.com/p/4fbf352ffc56
来源：简书
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

作者：Ant_way
链接：https://www.jianshu.com/p/4fbf352ffc56
来源：简书
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

作者：Ant_way
链接：https://www.jianshu.com/p/4fbf352ffc56
来源：简书
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

作者：Ant_way
链接：https://www.jianshu.com/p/4fbf352ffc56
来源：简书
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

作者：Ant_way
链接：https://www.jianshu.com/p/4fbf352ffc56
来源：简书
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

作者：Ant_way
链接：https://www.jianshu.com/p/4fbf352ffc56
来源：简书
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

**属性**

- minSdkVersion：最小API level
- compileSdkVersion：编译的SDK版本
- targetSdkVersion：目标版本
- dependencies：依赖配置，依赖的库

**几个重要的配置文件**

1. 项目的build.gradle

```gradle
dependencies {
	classpath 'com.android.tools.build:gradle:3.0.1'
}
```

2. gradle-wrapper.properties(在项目\gradlelwrapperl)

```java
distributionUrl=https\://services.gradle.org/distributions/gradle-4.1-allzip
```

3. module中的build.gradle文件
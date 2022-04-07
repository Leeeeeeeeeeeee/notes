# windows程序内部运行原理

## Windows API

操作系统所能够完成的每一个特殊功能通常都有一个函数与其对应，也就是说，操作系统把它所能够完成的功能以函数的形式提供给应用程序使用，应用程序对这些函数的调用就叫做系统调用，这些函数的集合就是Windows应用程序编程接口(Application Programming Interface)，简称Windows API。

位置：Windows/System32/Kernel32.dll、 USER32.dll、GDI32.dll

使用：C和Windows SDK开发包( API函数是用纯C写的，都在windows.h中有声明)

## MFC

MFC英文全称为Microsoft Foundation Classes (微软基础类库)，是把Windows API进行封装的类库，它是一个类的集合，通过覆盖Windows API，提供了一个面向对象的编程方式。
MFC使Windows程序员能够利用C++面象对象的特性进行编程。

## Windows编程模型

![image-20220301084146831](windows_files\image-20220301084146831.png)

应用程序开始执行后，系统都会为该程序创建一个消息队列，这个消息队列用来存放该程序创建的窗口的消息(消息通常与窗口相关)。

例如，当我们按下鼠标左键的时候，将会产生消息，系统会将这个消息放到窗口所属的应用程序的消息队列中，等待应用程序的处理。产生的消息都会依次放到消息队列中，而应用程序则通过一个消息循环不断地从消息队列中取出消息，并进行响应。

如用户在某个程序活动时按了一下键盘，操作系统马上能够感知到这一事件，并且能够知道用户按下的是哪一个键，操作系统并不决定对这一事件如何作出反应，而是将这一事件转交给应用程序，由应用程序决定如何对这一事件作出反应。对事件作出反应的过程就是消息响应，各种消息响应放在一起组成了窗口过程。

## 消息

操作系统是怎样将感知到的事件传递给应用程序的呢？这是通过消息机制(Message)来实现的。操作系统将每个事件都包装成一个称为消息的结构体MSG来传递给应用程序，参看MSDN。

MSG结构定义如下： 

```c++
typedef struct tagMSG {       
    	HWND   hwnd;      
    	UINT   message;
    	WPARAM wParam;
    	LPARAM lParam;
    	DWORD  time;
    	POINT  pt;
} MSG; 
```

## 句柄

操作系统要管理和操作各种各样的资源，都是通过句柄来找到对应的资源。按资源的类型，又可将句柄细分成图标句柄(HICON)，光标句柄(HCURSOR)，窗口句柄(HWND)，应用程序实例句柄(HINSTANCE)等等各种类型的句柄。

操作系统给每一个窗口指定的一个唯一的标识号即窗口句柄。 

API中对数据的宏定义

```c++
int x, y;
x = 30;	
y = 30;		
//x和y既可以用来表示坐标点，也可以用来表示宽度和高度，还可以用来表示身高和体重。

typedef int WIDTH
typedef int HEIGHT
WIDTH x;
HEIGHT y;
//我们从变量的类型上就可以知道x和y是用来表示宽度和高度。

```

## 编写Windows应用程序的要素

![image-20220301084620601](windows_files\image-20220301084620601.png)

```java
char str[255];
sprintf (str, "%s"，lpCmdLine);
//参数1：父窗口，默认为桌面
//参数2：显示的内容
//参数3：窗口标题
//参数4：窗口布局
//返回值：整型数，告诉程序用户按了哪个按钮
MessageBox (NULL, str,"命令行",O);
sprintf(str,"%d", nCmdShow) ;
MessageBox (NULL,str,"窗口状态", 0);
```

## 代码

```c++
#include <windows.h>
#include <stdio.h>

//声明窗口过程函数
LRESULT CALLBACK MyWndProc(
	HWND hwnd,//handle to window
    UINT uMsg,//message identifier
	WPARAM wParam,//first message parameter
    LPARAM lParam,// second message parameter
)
    
//1 入口函数
int WINAPI WinMain(
	HINSTANCE hInstance,//应用程序的实例句柄
	HINSTANCE hPrevInstance,//老版本需要，传入空
	LPSTR lpCmdLine,//命令行
	int nCmdShow,// 窗口显示时的状态
)
{
	//2 创建窗口
	//2.1 设计一个窗口类
    WNDCLASS MyWnd;
	MyWnd.cbClsExtra = NULL;//窗口类附加内存，用不到，设置为空就好
    MyWnd.cbWndExtra = NULL;//窗口附加内存，用不到，设置为空就好
	MyWnd.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//背景颜色，getStockObject还可以获得画刷、画笔、字体、调色板，句柄类型不一样，c语言特性需要对这些资源进行强转
    MyWnd.hCursor = LoadCursor (NULL，IDC_ARROW);//鼠标形状
    MyWnd.hIcon = LoadIcon (NULL，IDI_APPLICATION );//窗口图标，LoadIcon的第一个参数为空代表图标资源由操作系统提供，不为空时只能传入hInstance，代表图标自己绘制
    MyWnd.hInstance = hISnstance;//应用程序实例句柄
    MyWnd.lpfnWndProc = MyWndProc;//指向窗口过程函数的指针
    MyWnd.lpszClassName = "Hello";//窗口型号名称
    MyWnd.lpszMenuName = NULL;//窗口没有菜单
	MyWnd.style = CS_HREDRAW | cS_VREDRAW;//样式，当水平尺寸或垂直尺寸变化时，窗口要重新绘制
    
    //2.2 对设计好的窗口类进行注册
	RegisterClass(&MyWnd) ;
	
    //2.3 创建窗口
    HWND hWnd;//定义了一个句柄，不代表窗口已经生成
	hWnd = CreateWindow("Hello","Windows编程", 
                        WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX,
                        //~WS_MAXIMIZEBOX代表去掉最大化按钮
                        0,0,800,600,
                        //CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT
                        //代表不指定具体的位置和尺寸，使用默认的，操作系统会根据分辨率、窗口布局等显示窗口
                        NULL,NULL,hInstance,
                        "欢迎来到Windows编程!"
                        //CREATE消息携带的信息，打开窗口前显示
                       );
/**
	//API函数，创建窗口，调用时会发送消息W_CREATE
	HWND CreateWindow(
		LPCTSTR lpClassName,//已注册的窗口类名称
		LPCTSTR ipWindowName,//窗口标题栏中显示的文本
		DWORD dwStyle,//窗口类样式，代表共同都拥有的样式
		int x,//水平坐标,坐标原点是屏幕的左上角
		int y,//垂直坐标
		int nWidth,//宽度
		int nHeight,//高度
		HWND hWndParent,//父窗口句柄,桌面是操作系统原始的父窗口
		HMENU hMenu,//菜单句柄
		HINSTANCE hInstance,//应用程序实例句柄
		LPVOID lpParam//用于多文档程序的附加参数,单文档为NULL
	);
**/
    
/**
	//消息结构体
**/
    //2.4 显示及其更新窗口
    ShowWindow (hWnd,SW_SHOW);
    UpdateWindow (hWnd) ;
	//如果有无效区，则马上发送WM_PAINT到窗口处理过程，
	//不进消息队列进行排队等待，立即刷新窗口，否则，什么都不做。
    
    //3.消息循环
    //如果没有消息循环，窗口会一闪而过
	MSG msg;
    while (GetMessage (&msg, NULL,0,0))//从消息队列中获取消息,拿到QUIT消息则返回0，当程序异常时返回-1
    {
		TranslateMessage (&msg);//消息解释
        /**
        	TranslateMessage函数用于将虚拟键消息转换为字符消息。当我们敲击键盘上的某个字符键时，系统将产生WM_KEYDOWN和WM_KEYUP消息。这两个消息的附加参数(wParam和lParam）包含的是虚拟键代码和扫描码等信息，而我们在程序中往往需要得到某个字符的ASCII码，TranslateMessage这个函数就可以将WM_KEYDOWN和WM_KEYUP消息的组合转换为一条WM_CHAR消息，该消息的WParam附加参数包含了字符的ASCII码），并将转换后的新消息投递到调用线程的消息队列中。注意，Translate函数并不会修改原有的信息，他只是产生新的消息并投递到消息队列中。
        **/
		DispatchMessage (&msg) ;//将消息发送到“窗口过程”
    }
	return 0;

/**
	BOOL GetMessage(
		LPMSG lpMsg,              // 消息结构体指针，返回消息信息 
		HWND hWnd,               // 窗口句柄 ，通常设为NULL
		UINT wMsgFilterMin,   // 消息过滤最小值 
		UINT wMsgFilterMax   // 消息过滤最大值 
     ); 
	//GetMessage从线程的消息队列中取出消息，取出的消息保存在事先定义好的消息的结构体对象中。

**/
    //4.“窗口过程函数”(编写消息响应代码)

    
typedef struct _WNDCLASS { 
   UINT    	style;//窗口类样式
   WNDPROC	lpfnWndProc;//窗口过程函数指针
   int      cbClsExtra;//窗口类附加内存字节数，通常为0
   int      cbWndExtra;//窗口附加内存字节数，通常为0
   HANDLE 	hInstance;//应用程序实例句柄
   HICON   	hIcon;//标题栏图标
   HCURSOR 	hCursor;//光标
   HBRUSH  	hbrBackground;//窗口背景颜色
   LPCTSTR 	lpszMenuName;//菜单资源名称
   LPCTSTR 	lpszClassName;//窗口类名称
} WNDCLASS; 

WNDCLASS MyWnd;
MyWnd.cbClsExtra = NULL;
MyWnd.cbWnd Extra = NULL;
MyWnd.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
MyWnd.hCursor = LoadCursor (NULL, IDC_ARROW);
MyWnd.hIcon = LoadIcon (NULL,IDI_QUESTION);
MyWnd.hInstance = hInstance;
MyWnd.lpfnWndProc = MyWndProc;
MyWnd.lpszClassName = "He1lo";
MyWnd.lpszMenuName = NULL;
MyWnd.style = CS_HREDRAW | CS_VREDRAW;
    


```

![image-20220322083341565](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20220322083341565.png)

/[2.3创建窗口HWND hWnd;
hWnd = CreateWindow("Hello","Windows编程"， WS_OVERLAPPEDWINDOW，
cw_USEDEFAULT,Cw_USEDEFAULT,Cw_USEDEFAULT,CW_U0,0,800,600,
NULL,NULL, hInstance,"欢迎来到Windows编程!");
//2.4 显示及其更新窗口
ShowWindow (hWnd，sw_SHOW) ;UpdateWindow (hWnd) ;
如果有无效区，则马上发送WM PAINT到窗口处理过程，
//不进消息队列进行排队等待，立即刷新窗口，否则，什么都不做。//3.消息循环
MSG msg;
while (GetMessage (&msg, NULL,0,0))//从消息队列中获取消息
TranslateMessage (&msg) ; //消息解释

窗口过程函数

```c
LRESULT CALLBACK MyWndProc (
    HWND hwnd,//handle to window
	UINT uMsg，//message identifier
    WPARAM wParam,//first message parameter
	LPARAM lParam//second message parameter
}

switch (uMsg){
    case WM_CREATE:
		//查看CreateWindow函数的最后一个参数
		MessageBox(hwnd,(char*) (((LPCREATESTRUCT)1Param)->lpCreateParams),"启动窗口",0);
		return 0;//返回值不能是-1，否则CreateWindow函数返回0
	case WM_CLOSE:
		if (IDYES == MessageBox (hwnd,"真的要退出吗?","退出"，MB_YI)
			DestroyWindow (hwnd);
		break;
    case WM_DESTROY:
		PostQuitMessage(0);
        break;
    case WM_CHAR:
		char str[255];
		sprintf (str,"char is %d", wParam);
        MessageBox (hwnd,str,"按键响应",0);。
        break;
    case WM_LBUTTONDOWN:
        HDC hDC;
        hDC = GetDC(hwnd);
        TextOut(hDC,255,100,"Hello World!",strlen("Hello World!"));
        ReleaseDC(hwnd,hDC);
        break;
	case WM_PAINT://窗口无效-->重绘-->窗口重新变成有效状态
        HDC hpaintDC;
        PAINTSTRUCT ps;
        hpaintDC = BeginPaint(hwnd,&ps);//不能用getDC
        TextOut(hpaintDC,255,150,"Hello World!",strlen("Hello World"));//文本输出，应该在beginpaint下面
        EndPaint(hwnd,&ps);
    case WM_RBUTTONDOWN:
        sendMessage(hwnd,WM_SETTEXT,0,(LPARAM)"right button down");//改变当前窗口的标题
        sendMessage(FindWindow("CalcFrame",NULL),WM_SETTEXT,0,(LPARAM)"right button down");//改变其他窗口的标题，CalcFrame是系统计算器的窗口类名称
        break;
    default:
		return DefwindowProc(hwnd, uMsg, wParam，lParam);
}
return 0;
            
/**
大多数消息是由操作系统产生和发送，此外我们也可以人为调用SendMessage和PostMessage函数来自行发送消息。
SendMessage将消息直接发送给窗口，并调用该窗口过程进行处理。在窗口过程对消息处理完毕后,该函数才返回。
PostMessage函数将消息放入与创建窗口的线程相关联的消息队列后立即返回。
**/

```

![image-20220322083548298](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20220322083548298.png)

![image-20220322083231374](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20220322083231374.png)

![image-20220322082846223](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20220322082846223.png)

step3 创建窗口

step4 显示及更新窗口

![image-20220322082948969](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20220322082948969.png)

![image-20220329090210390](E:\Libraries\notes\se\windows\windows_files\image-20220329090210390.png)

![image-20220329090258210](E:\Libraries\notes\se\windows\windows_files\image-20220329090258210.png)

![image-20220329091457096](E:\Libraries\notes\se\windows\windows_files\image-20220329091457096.png)
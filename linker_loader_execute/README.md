# 你所不知道的C語言：動態連結器篇 (linker)

# How to get malloc and free times.
#    LD_PRELOAD

1.define MALLOC(x) do { if (malloc(x)) malloc_count++; }
http://loda.hala01.com/2011/11/%E8%AB%87linux-kernel%E5%B7%A8%E9%9B%86-do-while0-%E7%9A%84%E6%92%B0%E5%AF%AB%E6%96%B9%E5%BC%8F/
.do while(0){};
	避免goto 的使用
	dangling else

2.interpositioning
	即可得知每次 malloc() 呼叫對應的參數，甚至可以統計記憶體配置，完全不需要變更原始程式碼
可能的應用是遊戲破解, 執行時期追蹤,
	 sandboxing()
		遊戲動態預測memory還夠不夠用
		偷換亂數的function 讓你玩遊戲必贏
			Unrandomize (暫時不「亂」的亂數)
			https://rafalcieslak.wordpress.com/2013/04/02/dynamic-linker-tricks-using-ld_preload-to-cheat-inject-features-and-investigate-programs/

     software fault isolation (SFI)
		chrome OS : 學術上名子

	 profiling

 	 TCMalloc
		或者效能最佳化的函式庫
	    google: Thread-chaching malloc
		ex:tcmalloc mysql: 只要用LD_PRELOAD  一行code都不用改

3.透過設定 LD_PRELOAD 環境變數，glibc 的 dynamic linker (ld-linux.so) 會在載入和重定位 (relocation) libc.so 之前，載入我們撰寫的 /tmp/libmcount.so 動態連結函式庫，如此一來，我們實做的 malloc 就會在 libc.so 提供的 malloc 函式之前被載入。當然，我們還是需要「真正的」 malloc，否則無法發揮作用，所以透過 dlsym 去從 libc.so 載入 malloc 程式碼，這裡 RTLD_NEXT 參數告知動態連結器，我們想從下一個載入的動態函式庫載入 malloc 的程式碼位址
	libc.so :實做printf malloc..等等真正的地方

	Reference:
	https://github.com/shihyu/Linux_Programming/tree/master/example/%E7%94%A8LD_PRELOAD%E6%9B%BF%E6%8F%9B%E5%8B%95%E6%85%8B%E9%80%A3%E7%B5%90%E7%9A%84%E5%87%BD%E5%BC%8F%E5%BA%AB
	http://jayconrod.com/posts/23/tutorial-function-interposition-in-linux
	http://samanbarghi.com/blog/2014/09/05/how-to-wrap-a-system-call-libc-function-in-linux/

C 語言是設計來開發OS , OS要懂 你才會懂C語言

# No such file or directory" 可能跟你猜想的不一樣
# => 其實是linux kernel program loader 給的  不是linker
在動態連結的環境中，ELF interpreter 其實就是 dynamic linker!
	https://github.com/imay/imay.github.io/blob/master/_posts/2014-11-02-linker-loader.md

	怎樣把同toolchain 又一樣的glibc 換到不同平台 不可以跑？
		Ans: 偷換掉 xxxx
	[zhaochun ~]$gcc -Wl,--dynamic-linker=xxxx main.c
	[zhaochun ~]$readelf -l a.out

linux 核心的程式碼 fs/binfmt_elf.c
Line 723

    if (elf_ppnt->p_type == PT_INTERP) {
    /* This is the program interpreter used for
     * shared libraries - for now assume that this
     * is an a.out format binary
     */
    ...
		// here elf_interpreter 34:25s Jserv
        elf_interpreter = kmalloc(elf_ppnt->p_filesz, GFP_KERNEL);
        if (!elf_interpreter) goto out_free_ph;
        retval = kernel_read(bprm->file, elf_ppnt->p_offset,
                             elf_interpreter, elf_ppnt->p_filesz);

	Reference:
	http://www.cs.stevens.edu/~jschauma/810/elf.html
	https://maskray.me/blog/2015-03-26-elf-hacks
	http://mgalgs.github.io/2013/05/10/hacking-your-ELF-for-fun-and-profit.html
	延伸閱讀:
    	《Binary Hacks》
    	Executable and Linkable Format (非常詳盡)
    	ELF Hacks
    	Hacking Your ELF For Fun And Profit

# ELF formate
1.GOT : Global offset table
2.PLT : Procedure linkage table

# Review compiler
    From Source to Binary: How A Compiler Works: GNU Toolchain
    Compiler可以砍掉沒人使用的 static global variable 來節省空間，但是不能砍掉沒人使用的 non-static global variable，因為無法確定別的 Compilation Unit 會不會用到此變數
    這是為何建議 local function 要宣告成 static 的用意！


   沒有pre processor 之前 最早的c用 cat 把全部的.c 黏成一大沱在編譯
   早期的 C 語言編譯器沒有 preprocessor，在 1973 年之後，引入 preprocessor，啟發自 BCPL 和 PL/I 程式語言的 file inclusion 機制 [ source ]，對模組化設計有更好的支援。
	=>  Compilation Unit
	=>  每個c 檔案 都是獨立的邏輯單元
	=>  在一個 compilation unit 內的宣告和定義，決定了函式與資料物件的有效範圍 (scope)。

    Compilation units

    The most common way of building C projects is to decompose every source file into an object file then link all the objects together at the end. This procedure works great for incremental development, but it is suboptimal for performance and optimization. Your compiler can't detect potential optimizations across file boundaries this way.
	因為有不同scope 反而無法最佳化了
	ex:1+2+3+..100=5050
	C1(1+..50) C2(51+..100) c1 c2 indepandant

	=> LTO : Link Time Optimization
		https://gcc.gnu.org/wiki/LinkTimeOptimizationFAQ

		ex: compiler 把沒call到的function  移掉
			避免被最佳化

			__attribute__ ((used))
			void foo(v) int v; {__builtin_longjmp(jb, v);}

# Modern C
    Modern C : Air bus 用的compiler 有bug 飛機墜機
    來自法國 INRIA (國家資訊暨自動化研究院) 的大作，必讀！ The top compiler
	http://icube-icps.unistra.fr/img_auth.php/d/db/ModernC.pdf

	CompCert 是 INRIA 旗下針對高度安全和可靠性需求研發、支援 "formal verification" 的 C 語言編譯器

	C 必讀書
	1. K&R 
	2. C99 SPEC
	3. 實做面 ex: Modern C(INRIA)

	File scope static const objects may be replicated in all compilation units that use them # 1:09
	英語中 replicate 有「複製」或「重複」的意思，這意思是說，一旦物件宣告為 static const，那麼編譯器就可以施加更多樣的最佳化策略。

    extern listElem const singleton;
	https://nlhsueh.gitbooks.io/oose/content/manuscript/DPSingleton.html

	Motivation 動機

       有時候我們在系統中只想要一個實體，唯一的一個。例如說我們只需要一個視窗管理員，只需要一個 RadioPlayer(要不然聲音就打架了)，只需要一個產品的工廠物件（請參考 Abstract factory）。我們希望該唯一的物件很容易的被讀取到；並且確定不會有其他的物件被產生出來。

	 [Rule 4.22.2.2 ] File scope static const objects cannot be used inside inline functions with external linkage. Another way is to declare them

    extern listElem const singleton;


and to define them in one of the compilation units:
    listElem const singleton = { 0 };

This second method has the big disadvantage that the value of the object is not available in the other units that include the declaration. Therefore we may miss some opportunities for the compiler to optimize our code.

考慮以下程式碼:
	// compiler time 已經轉成static const (vlaue
    inline listElem *listElem_init(listElem *el) {
        if (el) *el = singleton;
        return el;
    }

	consider 以下
		extern const static 排列組合......Reasearch compiler 反應你對C的了解	

# C99 static inline
# 程式碼可以放header file內 不會symbol conflict
	[ 22.5. Functions. ] (Page 174)
inline declared functions have difficulties with other symbols that have no or internal linkage. Such functions that are not static at the same time can’t access to static file scope variable, even if they are const qualified. Our proposal simplifies things with that respect.

     A function declaration of storage class register is equivalent to a declaration as static inline with the additional property that its address can’t be taken.

    All functions that are static inline have access to register objects that are visible at their point of definition.

    All functions declared inline have access to register constants that are visible at their point of definition.

# symbol visibility
# 	用extern 就可以call 非static function 
	    預設情況下，所有「不是 static」的函式都可會開放給其他 compilation unit 去存取，這樣的行為我們稱為 "export" 
		一個 symbol 一旦 export，就可能遇到前述的 interpositioning，這很可能會導致非預期的行為。解決方法是，妥善地設定 symbol visibility。

	gcc 和 clang 都支援 visibility 屬性和 -fvisibility 編譯命令，以便對每個 object file 來進行全域設定：

    default : 不修改 visibility
    hidden : 對 visibility 的影響與 static 這個 qualifier 相同。此 symbol 不會被放入 dynamic symbol table，其他動態連結函式庫或執行檔看不到此 symbol


	example
		in chewing API 它只露出給人call的API (T)
		但是其他像是malloc memcpy strlen 等等都是 (U:undefined)

    if (__GNUC__ > 3) && (defined(__ELF__) || defined(__PIC__))
    #    define CHEWING_API __attribute__((__visibility__("default")))
    #    define CHEWING_PRIVATE __attribute__((__visibility__("hidden")))
    #else
    #    define CHEWING_API
    #    define CHEWING_PRIVATE
    #endif

[ source ]

可透過編譯器參數來指定全域的 visibility，一旦設定為 hidden，則所有沒有特別指定 symbol 會被認定為 local，僅有修飾 __attribute__ ((visibility ("default"))

延伸閱讀:

    Linker and Libraries Guide
    Why symbol visibility is good

# WEAK SYMBOl
考慮以下程式碼: (sym.c)
    static int local(void) { }
    int global(void) { }
    int  __attribute__((weak)) weak(void) { }

# dynamic linking
	PLT : program lookup table
		    local 這邊 找不到 才會靠GOT找
			跳板

	GOT : global offset table 
			global
			真正的位址

VMware作者 強大
	1.computer science from the bottom up
	https://www.bottomupcs.com/

	2.ch9 dynamic linking
	https://www.bottomupcs.com/chapter08.xhtml

# analysis linker
readelf --dynamic /bin/ls | grep --color PLTGOT
ldd /bin/ls
readelf -a /bin/ls | grep Shared

# Ch9 The dynamic linker
https://www.bottomupcs.com/dynamic_linker.xhtml

relocation
Table 9.1. Relocation Example
https://myao0730.blogspot.tw/2015/09/csapplinking.html


PIC: Position independence code
https://zh.wikipedia.org/wiki/%E5%9C%B0%E5%9D%80%E6%97%A0%E5%85%B3%E4%BB%A3%E7%A0%81

# jserv 寫的dynamic loader
https://github.com/jserv/min-dl

# GOT: Global offset table
https://www.bottomupcs.com/global_offset_tables.xhtml
1.big advantage of a shared library with virtual memory
2.The dynamic linker will find the most convenient place in virtual memory for each library required and place it there. 
  MMU 讓好多virtual memeory shared libraries 對應到同一個phy mem shared libraries

3.If we have a look at the readelf output we can see that the .got section starts 0x10570 bytes past where library was loaded into memory. Thus if the library were to be loaded into memory at address 0x6000000000000000 the .got would be at 0x6000000000010570, and register r1 would always point to this address.

# PLT: The procedure lookup table
0.lld 有看到link 很多so 我不們不會把so內全部的symbol都搬進去 太花時間
1.lazying binding
2.很像cache 本地端有symbol就不用查 有用到 且不存在 再去查
3.libfoo.so.1 libfooso.2 ....elf會標版本 要去link那一個版本
		https://www.bottomupcs.com/libraries_and_the_linker.xhtml
4.dll hell
5.深入淺出hello world ( Jserv
	https://github.com/tinyclub/open-c-book
6.C語言編程透視
	http://blog.linux.org.tw/~jserv/archives/002125.html

7.DOCKER
	applying virtual virtualization on ELf binararies ....

# malloc profile
	https://gitlab.com/o9000/malloc-profile

# GDB
	ptrace
	rr rr.project.org 

# Q&A
ASLR : Address space layout

兩process用同一個shared libraries VA會一樣嘛？ 同時不同組 VA對應到相同PA

ANS:ASLR  開 => VA會不一樣 => 避免被攻擊 
          關 => VA一樣

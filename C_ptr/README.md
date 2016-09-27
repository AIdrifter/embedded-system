# 你所不知道的C語言
https://www.youtube.com/watch?v=VpyaxUdSd_s
https://embedded2015.hackpad.com/C-s0rlzR8wVtm

1. 面試愛考
http://stackoverflow.com/questions/8208021/how-to-increment-a-pointer-address-and-pointers-value/8208106#8208106

2. typedef of reduce ....
    (*(void(*)())0)();

3. godbolt : 直接在網頁上看到 gcc 生成的程式碼

4. signal prototype
    void **(*d) (int &, char **(*)(char *, char **));

    signal 系統呼叫的宣告方式也很經典:

    How to read this prototype? ( stack overflow

5. Go 語言也有指標
  Ken Thompson
  語言帶過去給 Go 語言，連同美妙的 struct

	struct 要搭配 pointer

6. C89 <=> C99


7. "Programming in C: if it doesn't work, just add a star. Or multiple stars. Or ampersands."
   use * **  &&

8. C99 spec : committee Draft(free) 2007 i (N1256 version)
其實幾乎都是最終版了
http://port70.net/~nsz/c/c11/n1570.html

Contents 要認真看（目錄
 a. google will ignore symbols
 5.2.1 character stes
 5.2.3 signals and interrupts
 6.2.1 scopes of identifiers
 6.4.5 string literals
	experssions
	declaration

 P163 前認真看


7.26.12 : wchar


object > pointer
object != object-oriented

Microsoft 不支援C99


    [3.14] object

    region of data storage in the execution environment, the contents of which can represent values

	int) 7 != (float) 7.0

	[6.2.4] Storage durations of objects

    An object has a storage duration that determines its lifetime. There are three storage durations: static, automatic, and allocated.

    ==> 注意生命週期 (lifetime) 的概念，中文講「初始化」時，感覺像是「盤古開天」，很容易令人誤解。其實 initialize 的英文意義很狹隘: "to set (variables, counters, switches, etc.) to their starting values at the beginning of a program or subprogram."

         The lifetime of an object is the portion of program execution during which storage is guaranteed to be reserved for it. An object exists, has a constant address and retains its last-stored value throughout its lifetime. If an object is referred to outside of its lifetime, the behavior is undefined.

    ==> 在 object 的生命週期以內，其存在就意味著有對應的常數記憶體位址。注意，C 語言永遠只有 call-by-value

   # 指標本質是scalar type
     scalar type" 這個術語，日後我們看到 `++`, `--`, `+=`, `-=` 等操作，都是對 scalar (純量)i

        *(int32_t * const) (0x67a9) = 0xaa6; # hijackinf function pointer?

		* deference of
		& address of
		= assign


10. void真的萬能？ void*  可與 function pointer 互轉?
	6.3.2.3:8

	A pointer to a function of one type may be converted to a pointer to a function of another type and back again; the result shall compare equal to the original pointer. If a converted pointer is used to call a function whose type is not compatible with the pointed-to type, the behavior is undefined.


C language is popular via unixi from bell lab
MS-dos 後來也改用c
C 流行了以後 規格書都還沒定好!!
C 設標準 是為了讓各家廠商可以開發unix
ASCII IEEE754

c89 以前是沒有void的
    `void *` 的設計，導致開發者必須透過 explict (顯式) 或強制轉型，才能存取最終的 object，否則就會丟出編譯器的錯誤訊息，從而避免危險的指標操作

    我們無法直接對 `void *` 做數值操作

    void* p = ...;

    void *p2 = p + 1; /* what exactly is the size of void? */

# aligment
    /* may receive wrong value if ptr is not 2-byte aligned */

    uint16_t value = *(uint16_t*)ptr;/* portable way of reading a little-endian value */

    uint16_t value = *(uint8_t*)ptr | ((*(uint8_t*)(ptr+1))<<8);

# pointer
pointer to pointer # 沒有雙指標 只有指標的指標
C 只有 call by value
指標的指標的指標 <=> Motif
                 another KDE

# forward declaration
1.declaration != define
	define:有明確指出數值,空集合也算

struct oltk             : declare (imcomplete type) pointer to imcomplete type
struct oltk {};         : define
struct oltk { int x};   : define
define a 5              : define

2.希望有宣告 不要有定義：forward declaration

struct oltk 和 struct oltk_button 沒有具體的定義 (definition)
或實做 (implementation)，僅有宣告 (declaration)

struct 不要放 header file
pointer to imcomplete type
=>本質上不可以deference 但是可以取出他的type

軟體界面 (interface) 揭露於 oltk.h，不管 struct oltk 內容怎麼修改，已公開的函式如 `oltk_button_add` 都是透過 pointer 存取給定的位址，而不用顧慮具體 struct oltk 的實做，如此一來，不僅可以隱藏實做細節，還能兼顧二進位的相容性 (binary compatibility)。

# GDB
只用 printf() 觀察的話，永遠只看到你設定的框架 (format string) 以內的資料，
但很容易就忽略資料是否合法、範圍是否正確，以及是否看對地方

也可以動態用memcpy喔
gdb) p memcpy(calendar, b, sizeof(b[0]))

# Pointer vs Array
	# declaration
    extern, 如 `extern char x[];` => 不能變更為 pointer 的形式
    definition/statement, 如 `char x[10]` => 不能變更為 pointer 的形式
    parameter of function, 如 `func(char x[])` => 可變更為 pointer 的形式 => `func(char *x)`

	# expression
	兩者等價 範例 pointer_vs_array.c

	=> C 語言沒有真正array,array 只是一種expression

    在 The C Programming Language 第 2 版，Page 99 寫道:
    As formal parameters in a function definition,
    Page 100 則寫
    char s[]; and char *s are equivalent.
    這就是悲劇的由來，人們往往忘了前一頁
    `x[i]` 總是被編譯器改寫為 `*(x + i)` <== in expression

	int x[3][5]; <=> only express
	x[i]`, which is equivalent to `(*((x)+(i)))`

	array subscripting 在**編譯時期**只能作以下兩件事:
    得知 size
    	Obtain a pointer to element 0
    前兩者以外的操作，都透過 pointer
    	array subscripting => syntax sugar

# function pointer
	C99 [ 6.3.2.1 ] A function 'designator' is an expression that has function type
	int main() { return (********puts)("Hello"); }

	由於 `puts` 的 function prototype 是 `int puts(const char *s)`，
	因此 每次經過 `*` operator 運算後得到的結果是仍然是 `int`。
	所以，`*` 的數目不會影響結果。最後 return 的值是根據 s 的長度加上 '\n'。
	而這個例子 return 給 `main` 的值是 6

# 重新探討「字串」
wchar vs char
utf8
string iterals
    C 語言規格中定義了 string literals 會被分配於 "static storage" 當中 
	(C99 [6.4.5])，並說明如果程式嘗試修改 string literals 的內容，將會造成未定義行為
    以 gcc 的 ELF target 來說，將 string literals 分配在 read-only data section 中 (當然包含了 `\0`結尾)



    C語言提供了一些 syntax sugar 來初始化陣列，
	這使得 `char *p = ”hello world”` 和 `char p[] = “hello world”` 
	寫法相似，但底層的行為卻大相逕庭

    值得注意的是，陣列的寫法依據 C99 規範，string literals 是必須放在 "static storage" 中，而  `char p[]` 的語意則表示要把資料分配在 stack 內，所以這會造成編譯器 (gcc) 隱性地 (implicitly) 產生額外的程式碼，使得 C 程式在執行時期可把 string literals 從 static storage 複製到 stack 中。雖然字串本身並非存放於 stack 內，但 `char p[]` 卻是分配在 stack內，這也造成 `return p` 是"未定義行為"
		1. printf 也會call strlen
		2. strlen undefine
		2. 每種printf在不同lib實做 都不一樣

# Toward
	Linus Torvalds 親自教你 C 語言
	https://twlinuxkernelhackers.hackpad.com/LinusC-5jnXZm9VdCm
	不是你不懂kernel 是你它馬的不懂C語言
    #define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

	linux kernel 用了很多gcc的行為 
	但是根據C99 是undefined behavior

# Insecure coding in C
    slideshare  by Olve Maudal
    許多危險、未定義的 C 語言程式碼
    MISRA C
    "Guidelines for the use of the C language in critical systems"

    依據 C99 規格 6.3.2.3
    nothing requires the NULL pointer to have the numeric value of zero;
    這點導致實做上的歧異NULL 不一定就是0唷
	https://www.ptt.cc/bbs/C_and_CPP/M.1461840781.A.192.html

	C99 offset macro : Jserv blog 

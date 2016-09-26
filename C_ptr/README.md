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

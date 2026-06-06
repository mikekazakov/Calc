typedef short i16;
typedef unsigned short u16;
typedef int i32;
typedef unsigned int u32;
typedef long i64;
typedef unsigned long u64;

// POSIX
extern void * dlopen(const char * path, i32 mode);
extern void * dlsym(void * handle, const char * symbol);
extern void abort();

// Objective-C runtime
typedef struct objc_selector *SEL;
typedef struct objc_class *Class;
struct objc_object { Class isa; };
typedef struct objc_object *id;

static Class (*objc_getClass)(const char *name);
static id (*objc_msgSend)(id self, SEL op, ...);
static SEL (*sel_registerName)(const char *str);
static Class NSString;
static void *ObjCRuntime;
static void *FoundationFramework;

#define MSG_IMPL_0(ret,obj,sel)       ((ret (*)(id, SEL))objc_msgSend)(obj, sel)
#define MSG_IMPL_1(ret,obj,sel,a)     ((ret (*)(id, SEL, __typeof__(a)))objc_msgSend)(obj, sel, (a))
#define MSG_IMPL_2(ret,obj,sel,a,b)   ((ret (*)(id, SEL, __typeof__(a), __typeof__(b)))objc_msgSend)(obj, sel, (a), (b))
#define MSG_IMPL_3(ret,obj,sel,a,b,c) ((ret (*)(id, SEL, __typeof__(a), __typeof__(b), __typeof__(c)))objc_msgSend)(obj, sel, (a), (b), (c))
#define MSG_IMPL_N(_3, _2, _1, NAME, ...)  NAME
#define MSG(ret, obj, sel, ...) MSG_IMPL_N(__VA_ARGS__ __VA_OPT__(,) MSG_IMPL_3, MSG_IMPL_2, MSG_IMPL_1, MSG_IMPL_0)(ret, obj, sel __VA_OPT__(,) __VA_ARGS__)

#define CLASS_MSG_IMPL_0(ret,class,sel)       ((ret (*)(Class, SEL))objc_msgSend)(class, sel)
#define CLASS_MSG_IMPL_1(ret,class,sel,a)     ((ret (*)(Class, SEL, __typeof__(a)))objc_msgSend)(class, sel, (a))
#define CLASS_MSG_IMPL_2(ret,class,sel,a,b)   ((ret (*)(Class, SEL, __typeof__(a), __typeof__(b)))objc_msgSend)(class, sel, (a), (b))
#define CLASS_MSG_IMPL_3(ret,class,sel,a,b,c) ((ret (*)(Class, SEL, __typeof__(a), __typeof__(b), __typeof__(c)))objc_msgSend)(class, sel, (a), (b), (c))
#define CLASS_MSG_IMPL_N(_3, _2, _1, NAME, ...)  NAME
#define CLASS_MSG(ret, class, sel, ...) CLASS_MSG_IMPL_N(__VA_ARGS__ __VA_OPT__(,) CLASS_MSG_IMPL_3, CLASS_MSG_IMPL_2, CLASS_MSG_IMPL_1, CLASS_MSG_IMPL_0)(ret, class, sel __VA_OPT__(,) __VA_ARGS__)

// Selectors
static SEL $length;
static SEL $string;
static SEL $stringWithCharacters$length$;
static SEL $stringWithUTF8String$;

static void * LoadLibraryOrDie(const char * path) {
    void * handle = dlopen(path, 2);
    if (handle == 0)
        abort();
    return handle;
}

static void * LoadSymbolorDie(void *handle, const char * symbol) {
    void * ret = dlsym(handle, symbol);
    if (ret == 0)
        abort();
    return ret;
}

static void LoadLibraries()
{
    ObjCRuntime = LoadLibraryOrDie("/usr/lib/libobjc.A.dylib");
    FoundationFramework = LoadLibraryOrDie("/System/Library/Frameworks/Foundation.framework/Foundation");
    objc_getClass = LoadSymbolorDie(ObjCRuntime, "objc_getClass");
    objc_msgSend = LoadSymbolorDie(ObjCRuntime, "objc_msgSend");
    sel_registerName = LoadSymbolorDie(ObjCRuntime, "sel_registerName");
    NSString = objc_getClass("NSString");
}

static void RegisterSelectors() {
    $string = sel_registerName("string");
    $stringWithUTF8String$ = sel_registerName("stringWithUTF8String:");
    $stringWithCharacters$length$ = sel_registerName("stringWithCharacters:length:");
    $length = sel_registerName("length");
}

int main() {
    LoadLibraries();
    RegisterSelectors();

    const u16 *str_test = (u16*)u"Test";
    id str = CLASS_MSG(id, NSString, $stringWithCharacters$length$, str_test, (u64)4);
    u64 len = MSG(u64, str, $length);
    return len;
}

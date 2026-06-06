typedef short i16;
typedef unsigned short u16;
typedef int i32;
typedef unsigned int u32;
typedef long i64;
typedef unsigned long u64;
typedef float f32;
typedef double f64;

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
static Class NSApplication;
static Class NSString;
static Class NSWindow;
static void *ObjCRuntime;
static void *FoundationFramework;
static void *AppKitFramework;

#define MSG_IMPL_0(r,obj,sel)         ((r(*)(id,SEL))objc_msgSend)(obj, sel)
#define MSG_IMPL_1(r,obj,sel,a)       ((r(*)(id,SEL,__typeof__(a)))objc_msgSend)(obj,sel, (a))
#define MSG_IMPL_2(r,obj,sel,a,b)     ((r(*)(id,SEL,__typeof__(a),__typeof__(b)))objc_msgSend)(obj,sel,(a),(b))
#define MSG_IMPL_3(r,obj,sel,a,b,c)   ((r(*)(id,SEL,__typeof__(a),__typeof__(b),__typeof__(c)))objc_msgSend)(obj,sel,(a),(b),(c))
#define MSG_IMPL_4(r,obj,sel,a,b,c,d) ((r(*)(id,SEL,__typeof__(a),__typeof__(b),__typeof__(c),__typeof__(d)))objc_msgSend)(obj,sel,(a),(b),(c),(d))
#define MSG_IMPL_N(_4, _3, _2, _1, NAME, ...)  NAME
#define MSG(ret, obj, sel, ...) MSG_IMPL_N(__VA_ARGS__ __VA_OPT__(,) MSG_IMPL_4, MSG_IMPL_3, MSG_IMPL_2, MSG_IMPL_1, MSG_IMPL_0)(ret, obj, sel __VA_OPT__(,) __VA_ARGS__)

#define CLASS_MSG_IMPL_0(r,cls,sel)         ((r(*)(Class,SEL))objc_msgSend)(cls,sel)
#define CLASS_MSG_IMPL_1(r,cls,sel,a)       ((r(*)(Class,SEL,__typeof__(a)))objc_msgSend)(cls,sel,(a))
#define CLASS_MSG_IMPL_2(r,cls,sel,a,b)     ((r(*)(Class,SEL,__typeof__(a),__typeof__(b)))objc_msgSend)(cls,sel,(a),(b))
#define CLASS_MSG_IMPL_3(r,cls,sel,a,b,c)   ((r(*)(Class,SEL,__typeof__(a),__typeof__(b),__typeof__(c)))objc_msgSend)(cls,sel,(a),(b),(c))
#define CLASS_MSG_IMPL_4(r,cls,sel,a,b,c,d) ((r(*)(Class,SEL,__typeof__(a),__typeof__(b),__typeof__(c),__typeof__(d)))objc_msgSend)(cls,sel,(a),(b),(c),(d))
#define CLASS_MSG_IMPL_N(_4, _3, _2, _1, NAME, ...)  NAME
#define CLASS_MSG(ret, class, sel, ...) CLASS_MSG_IMPL_N(__VA_ARGS__ __VA_OPT__(,) CLASS_MSG_IMPL_4, CLASS_MSG_IMPL_3, CLASS_MSG_IMPL_2, CLASS_MSG_IMPL_1, CLASS_MSG_IMPL_0)(ret, class, sel __VA_OPT__(,) __VA_ARGS__)

// Types
struct CGPoint {
    f64 x;
    f64 y;
};
typedef struct CGPoint CGPoint;
typedef CGPoint NSPoint;

struct CGSize {
    f64 width;
    f64 height;
};
typedef struct CGSize CGSize;
typedef CGSize NSSize;

struct CGRect {
    CGPoint origin;
    CGSize size;
};
typedef struct CGRect CGRect;
typedef CGRect NSRect;

// Selectors
static SEL $alloc;
static SEL $initWithContentRect$styleMask$backing$defer$;
static SEL $length;
static SEL $makeKeyAndOrderFront$;
static SEL $release;
static SEL $retain;
static SEL $run;
static SEL $setTitle$;
static SEL $sharedApplication;
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
    AppKitFramework = LoadLibraryOrDie("/System/Library/Frameworks/AppKit.framework/AppKit");
    objc_getClass = LoadSymbolorDie(ObjCRuntime, "objc_getClass");
    objc_msgSend = LoadSymbolorDie(ObjCRuntime, "objc_msgSend");
    sel_registerName = LoadSymbolorDie(ObjCRuntime, "sel_registerName");
    NSApplication = objc_getClass("NSApplication");
    NSString = objc_getClass("NSString");
    NSWindow = objc_getClass("NSWindow");
}

static void RegisterSelectors() {
    $alloc = sel_registerName("alloc");
    $initWithContentRect$styleMask$backing$defer$ = sel_registerName("initWithContentRect:styleMask:backing:defer:");
    $length = sel_registerName("length");
    $makeKeyAndOrderFront$ = sel_registerName("makeKeyAndOrderFront:");
    $release = sel_registerName("release");
    $retain = sel_registerName("retain");
    $run = sel_registerName("run");
    $setTitle$ = sel_registerName("setTitle:");
    $sharedApplication = sel_registerName("sharedApplication");
    $string = sel_registerName("string");
    $stringWithCharacters$length$ = sel_registerName("stringWithCharacters:length:");
    $stringWithUTF8String$ = sel_registerName("stringWithUTF8String:");
}

int main() {
    LoadLibraries();
    RegisterSelectors();

    const u16 *str_test = (u16*)u"Hello, world!";
    id str = CLASS_MSG(id, NSString, $stringWithCharacters$length$, str_test, (u64)13);

    id sharedApplication = CLASS_MSG(id, NSApplication, $sharedApplication);
    id window = CLASS_MSG(id, NSWindow, $alloc);
    NSRect rc = {.origin = {.x = 200, .y = 200}, .size = { .width = 200, .height = 200 }};
    window = MSG(id, window, $initWithContentRect$styleMask$backing$defer$, rc, (u64)0b1111, (u64)2, false );
    MSG(void, window, $setTitle$, str );
    MSG(void, window, $makeKeyAndOrderFront$, (id)0 );

    MSG(void, sharedApplication, $run);
}

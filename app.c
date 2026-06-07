typedef signed char i8;
typedef unsigned char u8;
typedef short i16;
typedef unsigned short u16;
typedef int i32;
typedef unsigned int u32;
typedef long i64;
typedef unsigned long u64;
typedef float f32;
typedef double f64;
typedef enum: u8 {false=0, true=1} bool;

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

// Imported Objective C classes
static Class NSAppearance;
static Class NSApplication;
static Class NSAutoreleasePool;
static Class NSMenu;
static Class NSMenuItem;
static Class NSString;
static Class NSWindow;

// Objective C selectors
static SEL $addItem$;
static SEL $alloc;
static SEL $appearanceNamed$;
static SEL $initWithContentRect$styleMask$backing$defer$;
static SEL $initWithTitle$action$keyEquivalent$;
static SEL $length;
static SEL $makeKeyAndOrderFront$;
static SEL $new;
static SEL $release;
static SEL $retain;
static SEL $run;
static SEL $setActivationPolicy$;
static SEL $setAppearance$;
static SEL $setMainMenu$;
static SEL $setSubmenu$;
static SEL $setTitle$;
static SEL $sharedApplication;
static SEL $string;
static SEL $stringWithCharacters$length$;
static SEL $stringWithUTF8String$;
static SEL $terminate$;

// Program state
static id g_App; // NSApplication
static id g_MainMenu; // NSMenu
static id g_Window; // NSWindow

static void retain(id obj) {
    MSG(void, obj, $retain);
}

static void release(id obj) {
    MSG(void, obj, $release);
}

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
    NSAppearance = objc_getClass("NSAppearance");
    NSApplication = objc_getClass("NSApplication");
    NSAutoreleasePool = objc_getClass("NSAutoreleasePool");
    NSMenu = objc_getClass("NSMenu");
    NSMenuItem = objc_getClass("NSMenuItem");
    NSString = objc_getClass("NSString");
    NSWindow = objc_getClass("NSWindow");
}

static void RegisterSelectors() {
    $addItem$ = sel_registerName("addItem:");
    $alloc = sel_registerName("alloc");
    $appearanceNamed$ = sel_registerName("appearanceNamed:");
    $initWithContentRect$styleMask$backing$defer$ = sel_registerName("initWithContentRect:styleMask:backing:defer:");
    $initWithTitle$action$keyEquivalent$ = sel_registerName("initWithTitle:action:keyEquivalent:");
    $length = sel_registerName("length");
    $makeKeyAndOrderFront$ = sel_registerName("makeKeyAndOrderFront:");
    $new = sel_registerName("new");
    $release = sel_registerName("release");
    $retain = sel_registerName("retain");
    $run = sel_registerName("run");
    $setActivationPolicy$ = sel_registerName("setActivationPolicy:");
    $setAppearance$ = sel_registerName("setAppearance:");
    $setMainMenu$ = sel_registerName("setMainMenu:");
    $setSubmenu$ = sel_registerName("setSubmenu:");
    $setTitle$ = sel_registerName("setTitle:");
    $sharedApplication = sel_registerName("sharedApplication");
    $string = sel_registerName("string");
    $stringWithCharacters$length$ = sel_registerName("stringWithCharacters:length:");
    $stringWithUTF8String$ = sel_registerName("stringWithUTF8String:");
    $terminate$ = sel_registerName("terminate:");
}

static void InitializeApplication() {
    CLASS_MSG(id, NSAutoreleasePool, $new);
    g_App = CLASS_MSG(id, NSApplication, $sharedApplication);
    MSG(bool, g_App, $setActivationPolicy$, (i64)0);
}

static void InitializeMainMenu() {
    g_MainMenu = CLASS_MSG(id, NSMenu, $new);

    id app_menu_item = CLASS_MSG(id, NSMenuItem, $new);
    MSG(void, g_MainMenu, $addItem$, app_menu_item);

    id app_menu = CLASS_MSG(id, NSMenu, $new);
    {
        id app_menu_quit_title = CLASS_MSG(id, NSString, $stringWithUTF8String$, "Quit Calc");
        id app_menu_quit_key_equivalent = CLASS_MSG(id, NSString, $stringWithUTF8String$, "q");
        id app_menu_quit = CLASS_MSG(id, NSMenuItem, $alloc);
        app_menu_quit = MSG(id, app_menu_quit, $initWithTitle$action$keyEquivalent$, app_menu_quit_title, $terminate$, app_menu_quit_key_equivalent);
        MSG(void, app_menu, $addItem$, app_menu_quit);
        release(app_menu_quit);
        release(app_menu_quit_key_equivalent);
        release(app_menu_quit_title);
    }

    MSG(void, app_menu_item, $setSubmenu$, app_menu);

    MSG(void, g_App, $setMainMenu$, g_MainMenu);
    release(app_menu);
    release(app_menu_item);
}

static void InitializeWindow() {
    const u16 *str_test = (u16*)u"Hello, world!";
    id str = CLASS_MSG(id, NSString, $stringWithCharacters$length$, str_test, (u64)13);

    g_Window = CLASS_MSG(id, NSWindow, $alloc);
    NSRect rc = {.origin = {.x = 200, .y = 200}, .size = { .width = 200, .height = 200 }};
    g_Window = MSG(id, g_Window, $initWithContentRect$styleMask$backing$defer$, rc, (u64)0b1111, (u64)2, false);
    MSG(void, g_Window, $setTitle$, str);

    {
        // Switch to Dark Aqua appearance
        id dark_aqua_name = CLASS_MSG(id, NSString, $stringWithUTF8String$, "NSAppearanceNameDarkAqua");
        id dark_aqua_appearance = CLASS_MSG(id, NSAppearance, $appearanceNamed$, dark_aqua_name);
        MSG(void, g_Window, $setAppearance$, dark_aqua_appearance);
        release(dark_aqua_appearance);
        release(dark_aqua_name);
    }

    MSG(void, g_Window, $makeKeyAndOrderFront$, (id)0);
}

int main() {
    LoadLibraries();
    RegisterSelectors();
    InitializeApplication();
    InitializeMainMenu();
    InitializeWindow();
    MSG(void, g_App, $run);
}

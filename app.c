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

// POSIX
extern void * dlopen(const char * path, i32 mode);
extern void * dlsym(void * handle, const char * symbol);
extern void abort();
extern int printf( const char* restrict format, ... );

// Objective-C runtime
typedef struct objc_selector *SEL;
typedef struct objc_class *Class;
typedef void (*IMP)(void /* id, SEL, ... */ );
struct objc_object { Class isa; };
typedef struct objc_object *id;

static bool (*class_addMethod)(Class cls, SEL name, IMP  imp, const char *types);
static void *(*objc_autoreleasePoolPush)();
static void (*objc_autoreleasePoolPop)(void *ctxt);
static Class (*objc_getClass)(const char *name);
static Class (*objc_allocateClassPair)(Class superclass, const char *name, u64 extraBytes);
static void (*objc_registerClassPair)(Class cls);
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
static Class NSButton;
static Class NSMenu;
static Class NSMenuItem;
static Class NSObject;
static Class NSString;
static Class NSWindow;

// Objective C selectors
static SEL $addItem$;
static SEL $alloc;
static SEL $appearanceNamed$;
static SEL $applicationDidFinishLaunching$;
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
static SEL $setDelegate$;
static SEL $setMainMenu$;
static SEL $setSubmenu$;
static SEL $setTitle$;
static SEL $setTitlebarAppearsTransparent$;
static SEL $sharedApplication;
static SEL $string;
static SEL $stringWithCharacters$length$;
static SEL $stringWithUTF8String$;
static SEL $terminate$;
static SEL $activateIgnoringOtherApps$;
static SEL $buttonWithTitle$target$action$;
static SEL $buttonWithTitle$image$target$action$;
static SEL $onButtonEqClicked$;
static SEL $addSubview$;
static SEL $contentView;

// Program state
static id g_App; // NSApplication
static id g_AppDelegate; // AppDelegate
static id g_MainMenu; // NSMenu
static id g_Window; // NSWindow
static id g_ButtonEq; // NSButton

// Forward declarations
static void retain(id obj);
static void release(id obj);
static void *LoadLibraryOrDie(const char * path);
static void *LoadSymbolorDie(void *handle, const char * symbol);
static void LoadLibraries();
static void RegisterSelectors();
static void onApplicationDidFinishLaunching(id self, SEL cmd, id notification);
static void InitializeAppDelegate();
static void InitializeApplication();
static void InitializeMainMenu();
static void InitializeWindow();

static void retain(id obj) {
    MSG(void, obj, $retain);
}

static void release(id obj) {
    MSG(void, obj, $release);
}

static void *LoadLibraryOrDie(const char * path) {
    void * handle = dlopen(path, 2);
    if (handle == 0)
        abort();
    return handle;
}

static void *LoadSymbolorDie(void *handle, const char * symbol) {
    void *ret = dlsym(handle, symbol);
    if (ret == 0)
        abort();
    return ret;
}

static void LoadLibraries()
{
    ObjCRuntime = LoadLibraryOrDie("/usr/lib/libobjc.A.dylib");
    FoundationFramework = LoadLibraryOrDie("/System/Library/Frameworks/Foundation.framework/Foundation");
    AppKitFramework = LoadLibraryOrDie("/System/Library/Frameworks/AppKit.framework/AppKit");
    objc_autoreleasePoolPush = LoadSymbolorDie(ObjCRuntime, "objc_autoreleasePoolPush");
    objc_autoreleasePoolPop = LoadSymbolorDie(ObjCRuntime, "objc_autoreleasePoolPop");
    objc_getClass = LoadSymbolorDie(ObjCRuntime, "objc_getClass");
    objc_allocateClassPair = LoadSymbolorDie(ObjCRuntime, "objc_allocateClassPair");
    class_addMethod = LoadSymbolorDie(ObjCRuntime, "class_addMethod");
    objc_msgSend = LoadSymbolorDie(ObjCRuntime, "objc_msgSend");
    objc_registerClassPair = LoadSymbolorDie(ObjCRuntime, "objc_registerClassPair");
    sel_registerName = LoadSymbolorDie(ObjCRuntime, "sel_registerName");
    NSAppearance = objc_getClass("NSAppearance");
    NSApplication = objc_getClass("NSApplication");
    NSAutoreleasePool = objc_getClass("NSAutoreleasePool");
    NSButton = objc_getClass("NSButton");
    NSMenu = objc_getClass("NSMenu");
    NSMenuItem = objc_getClass("NSMenuItem");
    NSObject = objc_getClass("NSObject");
    NSString = objc_getClass("NSString");
    NSWindow = objc_getClass("NSWindow");
}

static void RegisterSelectors() {
    $addItem$ = sel_registerName("addItem:");
    $alloc = sel_registerName("alloc");
    $appearanceNamed$ = sel_registerName("appearanceNamed:");
    $applicationDidFinishLaunching$ = sel_registerName("applicationDidFinishLaunching:");
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
    $setDelegate$ = sel_registerName("setDelegate:");
    $setMainMenu$ = sel_registerName("setMainMenu:");
    $setSubmenu$ = sel_registerName("setSubmenu:");
    $setTitle$ = sel_registerName("setTitle:");
    $setTitlebarAppearsTransparent$ = sel_registerName("setTitlebarAppearsTransparent:");
    $sharedApplication = sel_registerName("sharedApplication");
    $string = sel_registerName("string");
    $stringWithCharacters$length$ = sel_registerName("stringWithCharacters:length:");
    $stringWithUTF8String$ = sel_registerName("stringWithUTF8String:");
    $terminate$ = sel_registerName("terminate:");
    $activateIgnoringOtherApps$ = sel_registerName("activateIgnoringOtherApps:");
    $buttonWithTitle$target$action$ = sel_registerName("buttonWithTitle:target:action:");
    $buttonWithTitle$image$target$action$ = sel_registerName("buttonWithTitle:image:target:action:");
    $onButtonEqClicked$ = sel_registerName("onButtonEqClicked:");
    $addSubview$ = sel_registerName("addSubview:");
    $contentView = sel_registerName("contentView");
}

static void onApplicationDidFinishLaunching(id self, SEL cmd, id notification) {
    InitializeWindow();
    MSG(void, g_App, $activateIgnoringOtherApps$, true);
}

static void onButtonEqClicked(id self, SEL cmd, id sender) {
    printf("onButtonEqClicked\n");
}

static void InitializeAppDelegate() {
    Class class = objc_allocateClassPair(NSObject, "AppDelegate", 0);
    class_addMethod(class, $applicationDidFinishLaunching$, (IMP)onApplicationDidFinishLaunching,"v@:@");
    class_addMethod(class, $onButtonEqClicked$, (IMP)onButtonEqClicked,"v@:@");
    objc_registerClassPair(class);
    g_AppDelegate = CLASS_MSG(id, class, $new);
}

static void InitializeApplication() {
    g_App = CLASS_MSG(id, NSApplication, $sharedApplication);
    MSG(void, g_App, $setDelegate$, g_AppDelegate);
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
    }

    MSG(void, app_menu_item, $setSubmenu$, app_menu);

    MSG(void, g_App, $setMainMenu$, g_MainMenu);
    release(app_menu);
    release(app_menu_item);
}

static void InitializeWindow() {
    g_Window = CLASS_MSG(id, NSWindow, $alloc);
    NSRect rc = {.origin = {.x = 200, .y = 200}, .size = { .width = 200, .height = 200 }};
    u64 windows_flags = (1 << 15) | (1 << 2) | (1 << 1) | (1 << 0);
    g_Window = MSG(id, g_Window, $initWithContentRect$styleMask$backing$defer$, rc, windows_flags, (u64)2, false);
    MSG(void, g_Window, $setTitlebarAppearsTransparent$, true);

    {
        // Switch to Dark Aqua appearance
        id dark_aqua_name = CLASS_MSG(id, NSString, $stringWithUTF8String$, "NSAppearanceNameDarkAqua");
        id dark_aqua_appearance = CLASS_MSG(id, NSAppearance, $appearanceNamed$, dark_aqua_name);
        MSG(void, g_Window, $setAppearance$, dark_aqua_appearance);
    }

    id content_view = MSG(id, g_Window, $contentView);

    id str = CLASS_MSG(id, NSString, $stringWithUTF8String$, "=");
    g_ButtonEq = CLASS_MSG(id, NSButton, $buttonWithTitle$target$action$, str, g_AppDelegate, $onButtonEqClicked$);

    MSG(void, content_view, $addSubview$, g_ButtonEq);

    MSG(void, g_Window, $makeKeyAndOrderFront$, (id)0);
}

int main() {
    LoadLibraries();
    RegisterSelectors();
    void *autorelease_pool = objc_autoreleasePoolPush();
    InitializeAppDelegate();
    InitializeApplication();
    InitializeMainMenu();
    MSG(void, g_App, $run);
    objc_autoreleasePoolPop(autorelease_pool);
}

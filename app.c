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
extern void* dlopen(const char* path, i32 mode);
extern void* dlsym(void* handle, const char* symbol);
extern void abort();
extern int printf(const char* restrict format, ...);

// Objective-C runtime
typedef struct objc_selector* SEL;
typedef struct objc_class* Class;
typedef void (*IMP)(void /* id, SEL, ... */);
struct objc_object {
  Class isa;
};
typedef struct objc_object* id;

static bool (*class_addMethod)(Class cls, SEL name, IMP imp, const char* types);
static void* (*objc_autoreleasePoolPush)();
static void (*objc_autoreleasePoolPop)(void* ctxt);
static Class (*objc_getClass)(const char* name);
static Class (*objc_allocateClassPair)(Class superclass, const char* name, u64 extraBytes);
static void (*objc_registerClassPair)(Class cls);
static id (*objc_msgSend)(id self, SEL op, ...);
static SEL (*sel_registerName)(const char* str);

static void* ObjCRuntime;
static void* FoundationFramework;
static void* AppKitFramework;

#define MSG_IMPL_0(r, obj, sel) ((r (*)(id, SEL))objc_msgSend)(obj, sel)
#define MSG_IMPL_1(r, obj, sel, a) ((r (*)(id, SEL, __typeof__(a)))objc_msgSend)(obj, sel, (a))
#define MSG_IMPL_2(r, obj, sel, a, b) ((r (*)(id, SEL, __typeof__(a), __typeof__(b)))objc_msgSend)(obj, sel, (a), (b))
#define MSG_IMPL_3(r, obj, sel, a, b, c) ((r (*)(id, SEL, __typeof__(a), __typeof__(b), __typeof__(c)))objc_msgSend)(obj, sel, (a), (b), (c))
#define MSG_IMPL_4(r, obj, sel, a, b, c, d) ((r (*)(id, SEL, __typeof__(a), __typeof__(b), __typeof__(c), __typeof__(d)))objc_msgSend)(obj, sel, (a), (b), (c), (d))
#define MSG_IMPL_N(_4, _3, _2, _1, NAME, ...) NAME
#define MSG(ret, obj, sel, ...) MSG_IMPL_N(__VA_ARGS__ __VA_OPT__(, ) MSG_IMPL_4, MSG_IMPL_3, MSG_IMPL_2, MSG_IMPL_1, MSG_IMPL_0)(ret, obj, sel __VA_OPT__(, ) __VA_ARGS__)

#define CLASS_MSG_IMPL_0(r, cls, sel) ((r (*)(Class, SEL))objc_msgSend)(cls, sel)
#define CLASS_MSG_IMPL_1(r, cls, sel, a) ((r (*)(Class, SEL, __typeof__(a)))objc_msgSend)(cls, sel, (a))
#define CLASS_MSG_IMPL_2(r, cls, sel, a, b) ((r (*)(Class, SEL, __typeof__(a), __typeof__(b)))objc_msgSend)(cls, sel, (a), (b))
#define CLASS_MSG_IMPL_3(r, cls, sel, a, b, c) ((r (*)(Class, SEL, __typeof__(a), __typeof__(b), __typeof__(c)))objc_msgSend)(cls, sel, (a), (b), (c))
#define CLASS_MSG_IMPL_4(r, cls, sel, a, b, c, d) ((r (*)(Class, SEL, __typeof__(a), __typeof__(b), __typeof__(c), __typeof__(d)))objc_msgSend)(cls, sel, (a), (b), (c), (d))
#define CLASS_MSG_IMPL_N(_4, _3, _2, _1, NAME, ...) NAME
#define CLASS_MSG(ret, class, sel, ...) \
  CLASS_MSG_IMPL_N(__VA_ARGS__ __VA_OPT__(, ) CLASS_MSG_IMPL_4, CLASS_MSG_IMPL_3, CLASS_MSG_IMPL_2, CLASS_MSG_IMPL_1, CLASS_MSG_IMPL_0)(ret, class, sel __VA_OPT__(, ) __VA_ARGS__)

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
static Class NSGlassEffectContainerView;
static Class NSGlassEffectView;
static Class NSMenu;
static Class NSMenuItem;
static Class NSObject;
static Class NSString;
static Class NSView;
static Class NSWindow;

// Objective C selectors
static SEL $activateIgnoringOtherApps$;
static SEL $addItem$;
static SEL $addSubview$;
static SEL $alloc;
static SEL $anchorWithOffsetToAnchor$;
static SEL $appearanceNamed$;
static SEL $applicationDidFinishLaunching$;
static SEL $bottomAnchor;
static SEL $buttonWithTitle$image$target$action$;
static SEL $buttonWithTitle$target$action$;
static SEL $centerXAnchor;
static SEL $centerYAnchor;
static SEL $constraintEqualToAnchor$;
static SEL $constraintEqualToConstant$;
static SEL $contentView;
static SEL $heightAnchor;
static SEL $initWithContentRect$styleMask$backing$defer$;
static SEL $initWithTitle$action$keyEquivalent$;
static SEL $leadingAnchor;
static SEL $length;
static SEL $makeKeyAndOrderFront$;
static SEL $new;
static SEL $onButtonDotClicked$;
static SEL $onButtonEqClicked$;
static SEL $onButtonPlusMinusClicked$;
static SEL $onButtonZeroClicked$;
static SEL $release;
static SEL $retain;
static SEL $run;
static SEL $setActivationPolicy$;
static SEL $setActive$;
static SEL $setAppearance$;
static SEL $setBezelStyle$;
static SEL $setContentView$;
static SEL $setCornerRadius$;
static SEL $setDelegate$;
static SEL $setMainMenu$;
static SEL $setRefusesFirstResponder$;
static SEL $setSubmenu$;
static SEL $setTitle$;
static SEL $setTitlebarAppearsTransparent$;
static SEL $setTranslatesAutoresizingMaskIntoConstraints$;
static SEL $sharedApplication;
static SEL $string;
static SEL $stringWithCharacters$length$;
static SEL $stringWithUTF8String$;
static SEL $terminate$;
static SEL $topAnchor;
static SEL $trailingAnchor;
static SEL $widthAnchor;

// Program state
static id g_App;              // NSApplication
static id g_AppDelegate;      // AppDelegate
static id g_MainMenu;         // NSMenu
static id g_Window;           // NSWindow
static id g_ButtonPlusMinus;  // NSButton
static id g_ButtonZero;       // NSButton
static id g_ButtonDot;        // NSButton
static id g_ButtonEq;         // NSButton

// Forward declarations
static void retain(id obj);
static void release(id obj);
static void* LoadLibraryOrDie(const char* path);
static void* LoadSymbolorDie(void* handle, const char* symbol);
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

static void* LoadLibraryOrDie(const char* path) {
  void* handle = dlopen(path, 2);
  if (handle == 0)
    abort();
  return handle;
}

static void* LoadSymbolorDie(void* handle, const char* symbol) {
  void* ret = dlsym(handle, symbol);
  if (ret == 0)
    abort();
  return ret;
}

static void LoadLibraries() {
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
#define LOAD_CLASS(cls) cls = objc_getClass(#cls);
  LOAD_CLASS(NSAppearance);
  LOAD_CLASS(NSApplication);
  LOAD_CLASS(NSAutoreleasePool);
  LOAD_CLASS(NSButton);
  LOAD_CLASS(NSGlassEffectContainerView);
  LOAD_CLASS(NSGlassEffectView);
  LOAD_CLASS(NSMenu);
  LOAD_CLASS(NSMenuItem);
  LOAD_CLASS(NSObject);
  LOAD_CLASS(NSString);
  LOAD_CLASS(NSView);
  LOAD_CLASS(NSWindow);
#undef LOAD_CLASS
}

static void RegisterSelectors() {
#define REGISTER(selector)                                               \
  {                                                                      \
    char buf[sizeof(#selector) - 1], *dst = buf, *src = (#selector) + 1; \
    while ((*dst++ = *src++))                                            \
      if (dst[-1] == '$')                                                \
        dst[-1] = ':';                                                   \
    (selector) = sel_registerName(buf);                                  \
  }
  REGISTER($activateIgnoringOtherApps$);
  REGISTER($addItem$);
  REGISTER($addSubview$);
  REGISTER($alloc);
  REGISTER($anchorWithOffsetToAnchor$);
  REGISTER($appearanceNamed$);
  REGISTER($applicationDidFinishLaunching$);
  REGISTER($bottomAnchor);
  REGISTER($buttonWithTitle$image$target$action$);
  REGISTER($buttonWithTitle$target$action$);
  REGISTER($centerXAnchor);
  REGISTER($centerYAnchor);
  REGISTER($constraintEqualToAnchor$);
  REGISTER($constraintEqualToConstant$);
  REGISTER($contentView);
  REGISTER($heightAnchor);
  REGISTER($initWithContentRect$styleMask$backing$defer$);
  REGISTER($initWithTitle$action$keyEquivalent$);
  REGISTER($leadingAnchor);
  REGISTER($length);
  REGISTER($makeKeyAndOrderFront$);
  REGISTER($new);
  REGISTER($onButtonDotClicked$);
  REGISTER($onButtonEqClicked$);
  REGISTER($onButtonPlusMinusClicked$);
  REGISTER($onButtonZeroClicked$);
  REGISTER($release);
  REGISTER($retain);
  REGISTER($run);
  REGISTER($setActivationPolicy$);
  REGISTER($setActive$);
  REGISTER($setAppearance$);
  REGISTER($setBezelStyle$);
  REGISTER($setContentView$);
  REGISTER($setCornerRadius$);
  REGISTER($setDelegate$);
  REGISTER($setMainMenu$);
  REGISTER($setRefusesFirstResponder$);
  REGISTER($setSubmenu$);
  REGISTER($setTitle$);
  REGISTER($setTitlebarAppearsTransparent$);
  REGISTER($setTranslatesAutoresizingMaskIntoConstraints$);
  REGISTER($sharedApplication);
  REGISTER($string);
  REGISTER($stringWithCharacters$length$);
  REGISTER($stringWithUTF8String$);
  REGISTER($terminate$);
  REGISTER($topAnchor);
  REGISTER($trailingAnchor);
  REGISTER($widthAnchor);
#undef REGISTER
}

static void onApplicationDidFinishLaunching(id self, SEL cmd, id notification) {
  InitializeWindow();
  MSG(void, g_App, $activateIgnoringOtherApps$, true);
}

static void onButtonPlusMinusClicked(id self, SEL cmd, id sender) {
  printf("onButtonPlusMinusClicked\n");
}

static void onButtonZeroClicked(id self, SEL cmd, id sender) {
  printf("onButtonZeroClicked\n");
}

static void onButtonDotClicked(id self, SEL cmd, id sender) {
  printf("onButtonDotClicked\n");
}

static void onButtonEqClicked(id self, SEL cmd, id sender) {
  printf("onButtonEqClicked\n");
}

static void InitializeAppDelegate() {
  Class class = objc_allocateClassPair(NSObject, "AppDelegate", 0);
  class_addMethod(class, $applicationDidFinishLaunching$, (IMP)onApplicationDidFinishLaunching, "v@:@");
  class_addMethod(class, $onButtonEqClicked$, (IMP)onButtonEqClicked, "v@:@");
  class_addMethod(class, $onButtonPlusMinusClicked$, (IMP)onButtonPlusMinusClicked, "v@:@");
  class_addMethod(class, $onButtonZeroClicked$, (IMP)onButtonZeroClicked, "v@:@");
  class_addMethod(class, $onButtonDotClicked$, (IMP)onButtonDotClicked, "v@:@");
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

static void AddButton(id* button_target, id* button_glass_target, id parent_view, const char* text, SEL action) {
  id glass_effect_view = CLASS_MSG(id, NSGlassEffectView, $new);
  MSG(void, glass_effect_view, $setTranslatesAutoresizingMaskIntoConstraints$, false);
  MSG(void, glass_effect_view, $setCornerRadius$, 25.);

  MSG(void, parent_view, $addSubview$, glass_effect_view);

  id str = CLASS_MSG(id, NSString, $stringWithUTF8String$, text);
  id button = CLASS_MSG(id, NSButton, $buttonWithTitle$target$action$, str, g_AppDelegate, action);
  MSG(void, button, $setTranslatesAutoresizingMaskIntoConstraints$, false);
  MSG(void, button, $setBezelStyle$, (u64)7);
  MSG(void, button, $setRefusesFirstResponder$, true);
  MSG(void, glass_effect_view, $setContentView$, button);

  MSG(void, MSG(id, MSG(id, glass_effect_view, $widthAnchor), $constraintEqualToConstant$, 48.), $setActive$, true);
  MSG(void, MSG(id, MSG(id, glass_effect_view, $heightAnchor), $constraintEqualToConstant$, 48.), $setActive$, true);

  *button_target = button;
  *button_glass_target = glass_effect_view;
}

static void InitializeWindow() {
  g_Window = CLASS_MSG(id, NSWindow, $alloc);
  NSRect rc = {.origin = {.x = 200, .y = 200}, .size = {.width = 300, .height = 400}};
  u64 windows_flags = (1 << 15) | (1 << 2) | (1 << 1) | (1 << 0);
  g_Window = MSG(id, g_Window, $initWithContentRect$styleMask$backing$defer$, rc, windows_flags, (u64)2, false);
  MSG(void, g_Window, $setTitlebarAppearsTransparent$, true);

  {
    // Switch to Dark Aqua appearance
    id dark_aqua_name = CLASS_MSG(id, NSString, $stringWithUTF8String$, "NSAppearanceNameDarkAqua");
    id dark_aqua_appearance = CLASS_MSG(id, NSAppearance, $appearanceNamed$, dark_aqua_name);
    MSG(void, g_Window, $setAppearance$, dark_aqua_appearance);
  }

  id glass_container_view = CLASS_MSG(id, NSGlassEffectContainerView, $new);
  MSG(void, g_Window, $setContentView$, glass_container_view);

  id cv = CLASS_MSG(id, NSView, $new);
  MSG(void, cv, $setTranslatesAutoresizingMaskIntoConstraints$, false);

  MSG(void, glass_container_view, $setContentView$, cv);

  id cv_lead_anch = MSG(id, cv, $leadingAnchor);
  id cv_trail_anch = MSG(id, cv, $trailingAnchor);
  id cv_bott_anch = MSG(id, cv, $bottomAnchor);

  id plus_minus_gl = nullptr;
  AddButton(&g_ButtonPlusMinus, &plus_minus_gl, cv, "+-", $onButtonPlusMinusClicked$);

  id zero_gl = nullptr;
  AddButton(&g_ButtonZero, &zero_gl, cv, "0", $onButtonZeroClicked$);

  id dot_gl = nullptr;
  AddButton(&g_ButtonDot, &dot_gl, cv, ".", $onButtonDotClicked$);

  id eq_gl = nullptr;
  AddButton(&g_ButtonEq, &eq_gl, cv, "=", $onButtonEqClicked$);
  MSG(void, MSG(id, MSG(id, cv_lead_anch, $anchorWithOffsetToAnchor$, MSG(id, plus_minus_gl, $leadingAnchor)), $constraintEqualToConstant$, 20.), $setActive$, true);
  MSG(void, MSG(id, MSG(id, MSG(id, plus_minus_gl, $bottomAnchor), $anchorWithOffsetToAnchor$, cv_bott_anch), $constraintEqualToConstant$, 20.), $setActive$, true);
  MSG(void, MSG(id, MSG(id, MSG(id, plus_minus_gl, $trailingAnchor), $anchorWithOffsetToAnchor$, MSG(id, zero_gl, $leadingAnchor)), $constraintEqualToConstant$, 6.), $setActive$, true);
  MSG(void, MSG(id, MSG(id, zero_gl, $centerYAnchor), $constraintEqualToAnchor$, MSG(id, plus_minus_gl, $centerYAnchor)), $setActive$, true);
  MSG(void, MSG(id, MSG(id, MSG(id, zero_gl, $trailingAnchor), $anchorWithOffsetToAnchor$, MSG(id, dot_gl, $leadingAnchor)), $constraintEqualToConstant$, 6.), $setActive$, true);
  MSG(void, MSG(id, MSG(id, dot_gl, $centerYAnchor), $constraintEqualToAnchor$, MSG(id, plus_minus_gl, $centerYAnchor)), $setActive$, true);
  MSG(void, MSG(id, MSG(id, MSG(id, dot_gl, $trailingAnchor), $anchorWithOffsetToAnchor$, MSG(id, eq_gl, $leadingAnchor)), $constraintEqualToConstant$, 6.), $setActive$, true);
  MSG(void, MSG(id, MSG(id, eq_gl, $centerYAnchor), $constraintEqualToAnchor$, MSG(id, plus_minus_gl, $centerYAnchor)), $setActive$, true);

  MSG(void, g_Window, $makeKeyAndOrderFront$, (id)0);

  MSG(void, glass_container_view, $release);
  MSG(void, cv, $release);
}

int main() {
  LoadLibraries();
  RegisterSelectors();
  void* autorelease_pool = objc_autoreleasePoolPush();
  InitializeAppDelegate();
  InitializeApplication();
  InitializeMainMenu();
  MSG(void, g_App, $run);
  objc_autoreleasePoolPop(autorelease_pool);
}

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
struct objc_super {
  id receiver;
  Class super_class;
};
static bool (*class_addMethod)(Class cls, SEL name, IMP imp, const char* types);
static void* (*objc_autoreleasePoolPush)();
static void (*objc_autoreleasePoolPop)(void* ctxt);
static Class (*objc_getClass)(const char* name);
static Class (*objc_allocateClassPair)(Class superclass, const char* name, u64 extraBytes);
static void (*objc_registerClassPair)(Class cls);
static void (*objc_msgSend)(void /*id self, SEL op, ...*/);
static void (*objc_msgSendSuper)(void /*struct objc_super *super, SEL op, ...*/);
static SEL (*sel_registerName)(const char* str);

// AppKit
static void (*NSBeep)();

static void* ObjCRuntime;
static void* FoundationFramework;
static void* AppKitFramework;

#define MSG_IMPL_0(r, obj, sel) ((r(*)(id, SEL))objc_msgSend)(obj, sel)
#define MSG_IMPL_1(r, obj, sel, a) ((r(*)(id, SEL, typeof(a)))objc_msgSend)(obj, sel, (a))
#define MSG_IMPL_2(r, obj, sel, a, b) ((r(*)(id, SEL, typeof(a), typeof(b)))objc_msgSend)(obj, sel, (a), (b))
#define MSG_IMPL_3(r, obj, sel, a, b, c) ((r(*)(id, SEL, typeof(a), typeof(b), typeof(c)))objc_msgSend)(obj, sel, (a), (b), (c))
#define MSG_IMPL_4(r, obj, sel, a, b, c, d) ((r(*)(id, SEL, typeof(a), typeof(b), typeof(c), typeof(d)))objc_msgSend)(obj, sel, (a), (b), (c), (d))
#define MSG_IMPL_N(_4, _3, _2, _1, NAME, ...) NAME
#define MSG(ret, obj, sel, ...) MSG_IMPL_N(__VA_ARGS__ __VA_OPT__(, ) MSG_IMPL_4, MSG_IMPL_3, MSG_IMPL_2, MSG_IMPL_1, MSG_IMPL_0)(ret, obj, sel __VA_OPT__(, ) __VA_ARGS__)

#define CLASS_MSG_IMPL_0(r, cls, sel) ((r(*)(Class, SEL))objc_msgSend)(cls, sel)
#define CLASS_MSG_IMPL_1(r, cls, sel, a) ((r(*)(Class, SEL, typeof(a)))objc_msgSend)(cls, sel, (a))
#define CLASS_MSG_IMPL_2(r, cls, sel, a, b) ((r(*)(Class, SEL, typeof(a), typeof(b)))objc_msgSend)(cls, sel, (a), (b))
#define CLASS_MSG_IMPL_3(r, cls, sel, a, b, c) ((r(*)(Class, SEL, typeof(a), typeof(b), typeof(c)))objc_msgSend)(cls, sel, (a), (b), (c))
#define CLASS_MSG_IMPL_4(r, cls, sel, a, b, c, d) ((r(*)(Class, SEL, typeof(a), typeof(b), typeof(c), typeof(d)))objc_msgSend)(cls, sel, (a), (b), (c), (d))
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
static Class NSTextField;
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
static SEL $onButtonClearClicked$;
static SEL $onButtonDeleteClicked$;
static SEL $onButtonDivideClicked$;
static SEL $onButtonDotClicked$;
static SEL $onButtonEightClicked$;
static SEL $onButtonEqClicked$;
static SEL $onButtonFiveClicked$;
static SEL $onButtonFourClicked$;
static SEL $onButtonMinusClicked$;
static SEL $onButtonMultiplyClicked$;
static SEL $onButtonNineClicked$;
static SEL $onButtonOneClicked$;
static SEL $onButtonPercentClicked$;
static SEL $onButtonPlusClicked$;
static SEL $onButtonPlusMinusClicked$;
static SEL $onButtonSevenClicked$;
static SEL $onButtonSixClicked$;
static SEL $onButtonThreeClicked$;
static SEL $onButtonTwoClicked$;
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
static SEL $initWithFormat$;
static SEL $stringWithFormat$;
static SEL $setStringValue$;
static SEL $keyDown$;
static SEL $keyCode;
static SEL $performClick$;

// Number
static constexpr u64 NUMBER_BASE = 1000;
static constexpr u64 NUMBER_MAX = 14;
struct Number {
  u16 limbs[NUMBER_MAX];  // 1000-based digits
  u8 len;                 // len
  u8 scale;               // scale of number, i.e. x 10^(-scale)
  u8 sign;                // 0 = positive
  // NAN is encoded as scale=255
};

// Calculator
static constexpr u64 MAX_TOKENS = 64;
enum TokenType {
  TOK_NUM  // holds a number
};
struct Token {
  enum TokenType type;
  // f64 number;
  struct Number number;
};
struct Calculator {
  struct Token toks[MAX_TOKENS];
  u64 toks_num;
};
enum CalcCommand {
  CMD_0,
  CMD_1,
  CMD_2,
  CMD_3,
  CMD_4,
  CMD_5,
  CMD_6,
  CMD_7,
  CMD_8,
  CMD_9,
  CMD_DELETE,
};

// Program state
static id g_App;              // NSApplication
static id g_AppDelegate;      // AppDelegate
static id g_MainMenu;         // NSMenu
static id g_Window;           // NSWindow
static Class g_WindowClass;   // AppWindow
static id g_ButtonDelete;     // NSButton
static id g_ButtonClear;      // NSButton
static id g_ButtonPercent;    // NSButton
static id g_ButtonDivide;     // NSButton
static id g_ButtonSeven;      // NSButton
static id g_ButtonEight;      // NSButton
static id g_ButtonNine;       // NSButton
static id g_ButtonMultiply;   // NSButton
static id g_ButtonFour;       // NSButton
static id g_ButtonFive;       // NSButton
static id g_ButtonSix;        // NSButton
static id g_ButtonMinus;      // NSButton
static id g_ButtonOne;        // NSButton
static id g_ButtonTwo;        // NSButton
static id g_ButtonThree;      // NSButton
static id g_ButtonPlus;       // NSButton
static id g_ButtonPlusMinus;  // NSButton
static id g_ButtonZero;       // NSButton
static id g_ButtonDot;        // NSButton
static id g_ButtonEq;         // NSButton
static id g_TextCurrent;      // NSTextField
static struct Calculator g_CurrentState;

// Forward declarations

// Initialization
static void retain(id obj);
static void release(id obj);
static void* LoadLibraryOrDie(const char* path);
static void* LoadSymbolorDie(void* handle, const char* symbol);
static void LoadLibraries();
static void RegisterSelectors();

// GUI functions
static void onApplicationDidFinishLaunching(id self, SEL cmd, id notification);
static void onWindowKeyDown(id self, SEL cmd, id event);
static void InitializeAppDelegate();
static void InitializeApplication();
static void InitializeMainMenu();
static void InitializeWindow();

// Calculator functions
static void CalcInit(struct Calculator* calc);
static id CalcVisualize(struct Calculator* calc);
static bool CalcProcess(struct Calculator* calc, enum CalcCommand cmd);

// Number functions
static struct Number NumberFromU64(u64 number);
static struct Number NumberNAN();
static struct Number NumberByAppendingDigit(struct Number number, u8 digit);
static struct Number NumberByRemovingRightmostDigit(struct Number number);
static id NumberToNSString(struct Number number);
static bool NumberIsNAN(struct Number number);
static bool NumberIsZero(struct Number number);

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
  objc_msgSendSuper = LoadSymbolorDie(ObjCRuntime, "objc_msgSendSuper");
  objc_registerClassPair = LoadSymbolorDie(ObjCRuntime, "objc_registerClassPair");
  sel_registerName = LoadSymbolorDie(ObjCRuntime, "sel_registerName");
  NSBeep = LoadSymbolorDie(AppKitFramework, "NSBeep");
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
  LOAD_CLASS(NSTextField);
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
  REGISTER($onButtonClearClicked$);
  REGISTER($onButtonDeleteClicked$);
  REGISTER($onButtonDivideClicked$);
  REGISTER($onButtonDotClicked$);
  REGISTER($onButtonEightClicked$);
  REGISTER($onButtonEqClicked$);
  REGISTER($onButtonFiveClicked$);
  REGISTER($onButtonFourClicked$);
  REGISTER($onButtonMinusClicked$);
  REGISTER($onButtonMultiplyClicked$);
  REGISTER($onButtonNineClicked$);
  REGISTER($onButtonOneClicked$);
  REGISTER($onButtonPercentClicked$);
  REGISTER($onButtonPlusClicked$);
  REGISTER($onButtonPlusMinusClicked$);
  REGISTER($onButtonSevenClicked$);
  REGISTER($onButtonSixClicked$);
  REGISTER($onButtonThreeClicked$);
  REGISTER($onButtonTwoClicked$);
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
  REGISTER($initWithFormat$);
  REGISTER($stringWithFormat$);
  REGISTER($setStringValue$);
  REGISTER($keyDown$);
  REGISTER($keyCode);
  REGISTER($performClick$);
#undef REGISTER
}

static void onApplicationDidFinishLaunching(id self, SEL cmd, id notification) {
  InitializeWindow();
  MSG(void, g_App, $activateIgnoringOtherApps$, true);
}

static void onWindowKeyDown(id self, SEL cmd, id event) {
  switch (MSG(u16, event, $keyCode)) {
    case 0x1D:
    case 0x52:
      return MSG(void, g_ButtonZero, $performClick$, (id)0);
    case 0x12:
    case 0x53:
      return MSG(void, g_ButtonOne, $performClick$, (id)0);
    case 0x13:
    case 0x54:
      return MSG(void, g_ButtonTwo, $performClick$, (id)0);
    case 0x14:
    case 0x55:
      return MSG(void, g_ButtonThree, $performClick$, (id)0);
    case 0x15:
    case 0x56:
      return MSG(void, g_ButtonFour, $performClick$, (id)0);
    case 0x17:
    case 0x57:
      return MSG(void, g_ButtonFive, $performClick$, (id)0);
    case 0x16:
    case 0x58:
      return MSG(void, g_ButtonSix, $performClick$, (id)0);
    case 0x1A:
    case 0x59:
      return MSG(void, g_ButtonSeven, $performClick$, (id)0);
    case 0x1C:
    case 0x5B:
      return MSG(void, g_ButtonEight, $performClick$, (id)0);
    case 0x19:
    case 0x5C:
      return MSG(void, g_ButtonNine, $performClick$, (id)0);
    case 0x33:
      return MSG(void, g_ButtonDelete, $performClick$, (id)0);
    default:
      struct objc_super super = {.receiver = self, .super_class = NSWindow};
      ((void (*)(struct objc_super*, SEL, id))objc_msgSendSuper)(&super, $keyDown$, event);
  }
}

static void feedCmdAndUpdate(enum CalcCommand cmd) {
  if (CalcProcess(&g_CurrentState, cmd)) {
    MSG(void, g_TextCurrent, $setStringValue$, CalcVisualize(&g_CurrentState));
  } else {
    NSBeep();
  }
}

static void onButtonDeleteClicked(id self, SEL cmd, id sender) {
  feedCmdAndUpdate(CMD_DELETE);
}

static void onButtonClearClicked(id self, SEL cmd, id sender) {
  printf("onButtonClearClicked\n");
}

static void onButtonPercentClicked(id self, SEL cmd, id sender) {
  printf("onButtonPercentClicked\n");
}

static void onButtonDivideClicked(id self, SEL cmd, id sender) {
  printf("onButtonDivideClicked\n");
}

static void onButtonSevenClicked(id self, SEL cmd, id sender) {
  feedCmdAndUpdate(CMD_7);
}

static void onButtonEightClicked(id self, SEL cmd, id sender) {
  feedCmdAndUpdate(CMD_8);
}

static void onButtonNineClicked(id self, SEL cmd, id sender) {
  feedCmdAndUpdate(CMD_9);
}

static void onButtonMultiplyClicked(id self, SEL cmd, id sender) {
  printf("onButtonMultiplyClicked\n");
}

static void onButtonFourClicked(id self, SEL cmd, id sender) {
  feedCmdAndUpdate(CMD_4);
}

static void onButtonFiveClicked(id self, SEL cmd, id sender) {
  feedCmdAndUpdate(CMD_5);
}

static void onButtonSixClicked(id self, SEL cmd, id sender) {
  feedCmdAndUpdate(CMD_6);
}

static void onButtonMinusClicked(id self, SEL cmd, id sender) {
  printf("onButtonMinusClicked\n");
}

static void onButtonOneClicked(id self, SEL cmd, id sender) {
  feedCmdAndUpdate(CMD_1);
}

static void onButtonTwoClicked(id self, SEL cmd, id sender) {
  feedCmdAndUpdate(CMD_2);
}

static void onButtonThreeClicked(id self, SEL cmd, id sender) {
  feedCmdAndUpdate(CMD_3);
}

static void onButtonPlusClicked(id self, SEL cmd, id sender) {
  printf("onButtonPlusClicked\n");
}

static void onButtonPlusMinusClicked(id self, SEL cmd, id sender) {
  printf("onButtonPlusMinusClicked\n");
}

static void onButtonZeroClicked(id self, SEL cmd, id sender) {
  feedCmdAndUpdate(CMD_0);
}

static void onButtonDotClicked(id self, SEL cmd, id sender) {
  printf("onButtonDotClicked\n");
}

static void onButtonEqClicked(id self, SEL cmd, id sender) {
  printf("onButtonEqClicked\n");
}

static void InitializeAppDelegate() {
  g_WindowClass = objc_allocateClassPair(NSWindow, "AppWindow", 0);
  class_addMethod(g_WindowClass, $keyDown$, (IMP)onWindowKeyDown, "v@:@");
  objc_registerClassPair(g_WindowClass);

  Class appdel = objc_allocateClassPair(NSObject, "AppDelegate", 0);
  class_addMethod(appdel, $applicationDidFinishLaunching$, (IMP)onApplicationDidFinishLaunching, "v@:@");
  class_addMethod(appdel, $onButtonDeleteClicked$, (IMP)onButtonDeleteClicked, "v@:@");
  class_addMethod(appdel, $onButtonClearClicked$, (IMP)onButtonClearClicked, "v@:@");
  class_addMethod(appdel, $onButtonPercentClicked$, (IMP)onButtonPercentClicked, "v@:@");
  class_addMethod(appdel, $onButtonDivideClicked$, (IMP)onButtonDivideClicked, "v@:@");
  class_addMethod(appdel, $onButtonSevenClicked$, (IMP)onButtonSevenClicked, "v@:@");
  class_addMethod(appdel, $onButtonEightClicked$, (IMP)onButtonEightClicked, "v@:@");
  class_addMethod(appdel, $onButtonNineClicked$, (IMP)onButtonNineClicked, "v@:@");
  class_addMethod(appdel, $onButtonMultiplyClicked$, (IMP)onButtonMultiplyClicked, "v@:@");
  class_addMethod(appdel, $onButtonFourClicked$, (IMP)onButtonFourClicked, "v@:@");
  class_addMethod(appdel, $onButtonFiveClicked$, (IMP)onButtonFiveClicked, "v@:@");
  class_addMethod(appdel, $onButtonSixClicked$, (IMP)onButtonSixClicked, "v@:@");
  class_addMethod(appdel, $onButtonMinusClicked$, (IMP)onButtonMinusClicked, "v@:@");
  class_addMethod(appdel, $onButtonOneClicked$, (IMP)onButtonOneClicked, "v@:@");
  class_addMethod(appdel, $onButtonTwoClicked$, (IMP)onButtonTwoClicked, "v@:@");
  class_addMethod(appdel, $onButtonThreeClicked$, (IMP)onButtonThreeClicked, "v@:@");
  class_addMethod(appdel, $onButtonPlusClicked$, (IMP)onButtonPlusClicked, "v@:@");
  class_addMethod(appdel, $onButtonEqClicked$, (IMP)onButtonEqClicked, "v@:@");
  class_addMethod(appdel, $onButtonPlusMinusClicked$, (IMP)onButtonPlusMinusClicked, "v@:@");
  class_addMethod(appdel, $onButtonZeroClicked$, (IMP)onButtonZeroClicked, "v@:@");
  class_addMethod(appdel, $onButtonDotClicked$, (IMP)onButtonDotClicked, "v@:@");
  objc_registerClassPair(appdel);
  g_AppDelegate = CLASS_MSG(id, appdel, $new);
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
  g_Window = CLASS_MSG(id, g_WindowClass, $alloc);
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

  id delete_gl = nullptr;
  AddButton(&g_ButtonDelete, &delete_gl, cv, "<", $onButtonDeleteClicked$);

  id clear_gl = nullptr;
  AddButton(&g_ButtonClear, &clear_gl, cv, "C", $onButtonClearClicked$);

  id percent_gl = nullptr;
  AddButton(&g_ButtonPercent, &percent_gl, cv, "%", $onButtonPercentClicked$);

  id divide_gl = nullptr;
  AddButton(&g_ButtonDivide, &divide_gl, cv, "/", $onButtonDivideClicked$);

  id seven_gl = nullptr;
  AddButton(&g_ButtonSeven, &seven_gl, cv, "7", $onButtonSevenClicked$);

  id eight_gl = nullptr;
  AddButton(&g_ButtonEight, &eight_gl, cv, "8", $onButtonEightClicked$);

  id nine_gl = nullptr;
  AddButton(&g_ButtonNine, &nine_gl, cv, "9", $onButtonNineClicked$);

  id multiply_gl = nullptr;
  AddButton(&g_ButtonMultiply, &multiply_gl, cv, "x", $onButtonMultiplyClicked$);

  id four_gl = nullptr;
  AddButton(&g_ButtonFour, &four_gl, cv, "4", $onButtonFourClicked$);

  id five_gl = nullptr;
  AddButton(&g_ButtonFive, &five_gl, cv, "5", $onButtonFiveClicked$);

  id six_gl = nullptr;
  AddButton(&g_ButtonSix, &six_gl, cv, "6", $onButtonSixClicked$);

  id minus_gl = nullptr;
  AddButton(&g_ButtonMinus, &minus_gl, cv, "-", $onButtonMinusClicked$);

  id one_gl = nullptr;
  AddButton(&g_ButtonOne, &one_gl, cv, "1", $onButtonOneClicked$);

  id two_gl = nullptr;
  AddButton(&g_ButtonTwo, &two_gl, cv, "2", $onButtonTwoClicked$);

  id three_gl = nullptr;
  AddButton(&g_ButtonThree, &three_gl, cv, "3", $onButtonThreeClicked$);

  id plus_gl = nullptr;
  AddButton(&g_ButtonPlus, &plus_gl, cv, "+", $onButtonPlusClicked$);

  id plus_minus_gl = nullptr;
  AddButton(&g_ButtonPlusMinus, &plus_minus_gl, cv, "+-", $onButtonPlusMinusClicked$);

  id zero_gl = nullptr;
  AddButton(&g_ButtonZero, &zero_gl, cv, "0", $onButtonZeroClicked$);

  id dot_gl = nullptr;
  AddButton(&g_ButtonDot, &dot_gl, cv, ".", $onButtonDotClicked$);

  id eq_gl = nullptr;
  AddButton(&g_ButtonEq, &eq_gl, cv, "=", $onButtonEqClicked$);

  g_TextCurrent = CLASS_MSG(id, NSTextField, $new);
  MSG(void, g_TextCurrent, $setTranslatesAutoresizingMaskIntoConstraints$, false);
  MSG(void, g_TextCurrent, $setRefusesFirstResponder$, true);
  MSG(void, cv, $addSubview$, g_TextCurrent);

  MSG(void, g_TextCurrent, $setStringValue$, CalcVisualize(&g_CurrentState));

  MSG(void, MSG(id, MSG(id, MSG(id, g_TextCurrent, $bottomAnchor), $anchorWithOffsetToAnchor$, MSG(id, delete_gl, $topAnchor)), $constraintEqualToConstant$, 6.), $setActive$, true);
  MSG(void, MSG(id, MSG(id, cv_lead_anch, $anchorWithOffsetToAnchor$, MSG(id, g_TextCurrent, $leadingAnchor)), $constraintEqualToConstant$, 20.), $setActive$, true);
  MSG(void, MSG(id, MSG(id, MSG(id, g_TextCurrent, $trailingAnchor), $anchorWithOffsetToAnchor$, cv_trail_anch), $constraintEqualToConstant$, 20.), $setActive$, true);
  MSG(void, MSG(id, MSG(id, delete_gl, $centerXAnchor), $constraintEqualToAnchor$, MSG(id, plus_minus_gl, $centerXAnchor)), $setActive$, true);
  MSG(void, MSG(id, MSG(id, MSG(id, delete_gl, $bottomAnchor), $anchorWithOffsetToAnchor$, MSG(id, seven_gl, $topAnchor)), $constraintEqualToConstant$, 6.), $setActive$, true);
  MSG(void, MSG(id, MSG(id, MSG(id, delete_gl, $trailingAnchor), $anchorWithOffsetToAnchor$, MSG(id, clear_gl, $leadingAnchor)), $constraintEqualToConstant$, 6.), $setActive$, true);
  MSG(void, MSG(id, MSG(id, clear_gl, $centerYAnchor), $constraintEqualToAnchor$, MSG(id, delete_gl, $centerYAnchor)), $setActive$, true);
  MSG(void, MSG(id, MSG(id, MSG(id, clear_gl, $trailingAnchor), $anchorWithOffsetToAnchor$, MSG(id, percent_gl, $leadingAnchor)), $constraintEqualToConstant$, 6.), $setActive$, true);
  MSG(void, MSG(id, MSG(id, percent_gl, $centerYAnchor), $constraintEqualToAnchor$, MSG(id, delete_gl, $centerYAnchor)), $setActive$, true);
  MSG(void, MSG(id, MSG(id, MSG(id, percent_gl, $trailingAnchor), $anchorWithOffsetToAnchor$, MSG(id, divide_gl, $leadingAnchor)), $constraintEqualToConstant$, 6.), $setActive$, true);
  MSG(void, MSG(id, MSG(id, divide_gl, $centerYAnchor), $constraintEqualToAnchor$, MSG(id, delete_gl, $centerYAnchor)), $setActive$, true);
  MSG(void, MSG(id, MSG(id, seven_gl, $centerXAnchor), $constraintEqualToAnchor$, MSG(id, plus_minus_gl, $centerXAnchor)), $setActive$, true);
  MSG(void, MSG(id, MSG(id, MSG(id, seven_gl, $bottomAnchor), $anchorWithOffsetToAnchor$, MSG(id, four_gl, $topAnchor)), $constraintEqualToConstant$, 6.), $setActive$, true);
  MSG(void, MSG(id, MSG(id, MSG(id, seven_gl, $trailingAnchor), $anchorWithOffsetToAnchor$, MSG(id, eight_gl, $leadingAnchor)), $constraintEqualToConstant$, 6.), $setActive$, true);
  MSG(void, MSG(id, MSG(id, eight_gl, $centerYAnchor), $constraintEqualToAnchor$, MSG(id, seven_gl, $centerYAnchor)), $setActive$, true);
  MSG(void, MSG(id, MSG(id, MSG(id, eight_gl, $trailingAnchor), $anchorWithOffsetToAnchor$, MSG(id, nine_gl, $leadingAnchor)), $constraintEqualToConstant$, 6.), $setActive$, true);
  MSG(void, MSG(id, MSG(id, nine_gl, $centerYAnchor), $constraintEqualToAnchor$, MSG(id, seven_gl, $centerYAnchor)), $setActive$, true);
  MSG(void, MSG(id, MSG(id, MSG(id, nine_gl, $trailingAnchor), $anchorWithOffsetToAnchor$, MSG(id, multiply_gl, $leadingAnchor)), $constraintEqualToConstant$, 6.), $setActive$, true);
  MSG(void, MSG(id, MSG(id, multiply_gl, $centerYAnchor), $constraintEqualToAnchor$, MSG(id, seven_gl, $centerYAnchor)), $setActive$, true);
  MSG(void, MSG(id, MSG(id, four_gl, $centerXAnchor), $constraintEqualToAnchor$, MSG(id, plus_minus_gl, $centerXAnchor)), $setActive$, true);
  MSG(void, MSG(id, MSG(id, MSG(id, four_gl, $bottomAnchor), $anchorWithOffsetToAnchor$, MSG(id, one_gl, $topAnchor)), $constraintEqualToConstant$, 6.), $setActive$, true);
  MSG(void, MSG(id, MSG(id, MSG(id, four_gl, $trailingAnchor), $anchorWithOffsetToAnchor$, MSG(id, five_gl, $leadingAnchor)), $constraintEqualToConstant$, 6.), $setActive$, true);
  MSG(void, MSG(id, MSG(id, five_gl, $centerYAnchor), $constraintEqualToAnchor$, MSG(id, four_gl, $centerYAnchor)), $setActive$, true);
  MSG(void, MSG(id, MSG(id, MSG(id, five_gl, $trailingAnchor), $anchorWithOffsetToAnchor$, MSG(id, six_gl, $leadingAnchor)), $constraintEqualToConstant$, 6.), $setActive$, true);
  MSG(void, MSG(id, MSG(id, six_gl, $centerYAnchor), $constraintEqualToAnchor$, MSG(id, four_gl, $centerYAnchor)), $setActive$, true);
  MSG(void, MSG(id, MSG(id, MSG(id, six_gl, $trailingAnchor), $anchorWithOffsetToAnchor$, MSG(id, minus_gl, $leadingAnchor)), $constraintEqualToConstant$, 6.), $setActive$, true);
  MSG(void, MSG(id, MSG(id, minus_gl, $centerYAnchor), $constraintEqualToAnchor$, MSG(id, four_gl, $centerYAnchor)), $setActive$, true);
  MSG(void, MSG(id, MSG(id, one_gl, $centerXAnchor), $constraintEqualToAnchor$, MSG(id, plus_minus_gl, $centerXAnchor)), $setActive$, true);
  MSG(void, MSG(id, MSG(id, MSG(id, one_gl, $bottomAnchor), $anchorWithOffsetToAnchor$, MSG(id, plus_minus_gl, $topAnchor)), $constraintEqualToConstant$, 6.), $setActive$, true);
  MSG(void, MSG(id, MSG(id, MSG(id, one_gl, $trailingAnchor), $anchorWithOffsetToAnchor$, MSG(id, two_gl, $leadingAnchor)), $constraintEqualToConstant$, 6.), $setActive$, true);
  MSG(void, MSG(id, MSG(id, two_gl, $centerYAnchor), $constraintEqualToAnchor$, MSG(id, one_gl, $centerYAnchor)), $setActive$, true);
  MSG(void, MSG(id, MSG(id, MSG(id, two_gl, $trailingAnchor), $anchorWithOffsetToAnchor$, MSG(id, three_gl, $leadingAnchor)), $constraintEqualToConstant$, 6.), $setActive$, true);
  MSG(void, MSG(id, MSG(id, three_gl, $centerYAnchor), $constraintEqualToAnchor$, MSG(id, one_gl, $centerYAnchor)), $setActive$, true);
  MSG(void, MSG(id, MSG(id, MSG(id, three_gl, $trailingAnchor), $anchorWithOffsetToAnchor$, MSG(id, plus_gl, $leadingAnchor)), $constraintEqualToConstant$, 6.), $setActive$, true);
  MSG(void, MSG(id, MSG(id, plus_gl, $centerYAnchor), $constraintEqualToAnchor$, MSG(id, one_gl, $centerYAnchor)), $setActive$, true);
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

static void CalcInit(struct Calculator* calc) {
  calc->toks[0].type = TOK_NUM;
  calc->toks[0].number = NumberFromU64(42);
  calc->toks_num = 1;
}

static id CalcVisualize(struct Calculator* calc) {
  id str = NumberToNSString(calc->toks[0].number);
  return str;
}

static bool CalcProcess(struct Calculator* calc, enum CalcCommand cmd) {
  switch (cmd) {
    case CMD_0:
    case CMD_1:
    case CMD_2:
    case CMD_3:
    case CMD_4:
    case CMD_5:
    case CMD_6:
    case CMD_7:
    case CMD_8:
    case CMD_9: {
      // TODO: check if the top is actually a number
      struct Number new = NumberByAppendingDigit(calc->toks[calc->toks_num - 1].number, (u8)cmd);
      if (NumberIsNAN(new))
        return false;
      calc->toks[calc->toks_num - 1].number = new;
      return true;
    }
    case CMD_DELETE: {
      // TODO: check if the top is actually a number
      struct Number new = NumberByRemovingRightmostDigit(calc->toks[calc->toks_num - 1].number);
      if (NumberIsNAN(new))
        return false;
      calc->toks[calc->toks_num - 1].number = new;
      return true;
    }
    default:;
  }
  return false;
}

static struct Number NumberFromU64(u64 number) {
  struct Number r = {0};
  if (number == 0) {
    r.len = 1;
    return r;
  }
  while (number != 0) {
    r.limbs[r.len++] = number % NUMBER_BASE;
    number = number / NUMBER_BASE;
  }
  return r;
}

static struct Number NumberNAN() {
  struct Number nan = {0};
  nan.len = 1;
  nan.scale = 255;
  return nan;
}

static id NumberToNSString(struct Number number) {
  if (NumberIsNAN(number)) {
    return CLASS_MSG(id, NSString, $stringWithUTF8String$, "NaN");
  }

  // First grab the digits into a temporary buffer
  char digits[64] = {0};
  u8 len = number.len;
  if (len == 0)
    len = 1;
  u32 dp = 0;
  u16 top = number.limbs[len - 1];
  if (top >= 100) {
    digits[dp++] = (char)('0' + (top / 100));
    digits[dp++] = (char)('0' + ((top / 10) % 10));
    digits[dp++] = (char)('0' + (top % 10));
  } else if (top >= 10) {
    digits[dp++] = (char)('0' + (top / 10));
    digits[dp++] = (char)('0' + (top % 10));
  } else {
    digits[dp++] = (char)('0' + top);
  }

  for (i32 i = (i32)len - 2; i >= 0; --i) {
    u16 limb = number.limbs[i];
    digits[dp++] = (char)('0' + (limb / 100));
    digits[dp++] = (char)('0' + ((limb / 10) % 10));
    digits[dp++] = (char)('0' + (limb % 10));
  }

  // Now format the string
  char out[128] = {0};
  u32 op = 0;
  if (number.sign)
    out[op++] = '-';

  if (number.scale == 0) {
    for (u32 i = 0; i < dp; ++i)
      out[op++] = digits[i];
  } else if (number.scale >= dp) {
    out[op++] = '0';
    out[op++] = '.';
    for (u32 i = 0; i < (u32)number.scale - dp; ++i)
      out[op++] = '0';
    for (u32 i = 0; i < dp; ++i)
      out[op++] = digits[i];
  } else {
    u32 int_len = dp - number.scale;
    for (u32 i = 0; i < int_len; ++i)
      out[op++] = digits[i];
    out[op++] = '.';
    for (u32 i = int_len; i < dp; ++i)
      out[op++] = digits[i];
  }

  out[op] = 0;
  return CLASS_MSG(id, NSString, $stringWithUTF8String$, out);
}

static bool NumberIsNAN(struct Number number) {
  return number.scale == 255;
}

static bool NumberIsZero(struct Number number) {
  if (NumberIsNAN(number))
    return false;
  for (u32 i = 0; i < number.len; ++i)
    if (number.limbs[i] != 0)
      return false;
  return true;
}

static struct Number NumberByAppendingDigit(struct Number number, u8 digit) {
  if (digit > 9 || NumberIsNAN(number))
    return NumberNAN();
  if (NumberIsZero(number) && number.scale == 0)
    return NumberFromU64(digit);

  struct Number out = number;
  if (out.len == 0)
    out.len = 1;

  // Append a decimal digit at the right by computing mantissa = mantissa * 10 + digit.
  u32 carry = digit;
  for (u32 i = 0; i < out.len; ++i) {
    u32 v = (u32)out.limbs[i] * 10 + carry;
    out.limbs[i] = (u16)(v % NUMBER_BASE);
    carry = v / NUMBER_BASE;
  }

  if (carry != 0) {
    if (out.len >= NUMBER_MAX)
      return NumberNAN();
    out.limbs[out.len++] = (u16)(carry % NUMBER_BASE);
  }

  if (out.scale != 0) {
    if (out.scale >= 254)
      return NumberNAN();
    out.scale += 1;
  }

  return out;
}

static struct Number NumberByRemovingRightmostDigit(struct Number number) {
  if (NumberIsNAN(number))
    return number;

  u32 len = number.len ? number.len : 1;

  u32 borrow = 0;
  for (i32 i = (i32)len - 1; i >= 0; --i) {
    u32 v = (u32)number.limbs[i] + borrow * NUMBER_BASE;
    number.limbs[i] = (u16)(v / 10);
    borrow = v % 10;
  }

  while (len > 1 && number.limbs[len - 1] == 0)
    len--;

  number.len = (u8)len;

  if (number.scale > 0) {
    number.scale -= 1;
  }

  return number;
}

int main() {
  LoadLibraries();
  RegisterSelectors();
  void* autorelease_pool = objc_autoreleasePoolPush();
  CalcInit(&g_CurrentState);
  InitializeAppDelegate();
  InitializeApplication();
  InitializeMainMenu();
  MSG(void, g_App, $run);
  objc_autoreleasePoolPop(autorelease_pool);
}

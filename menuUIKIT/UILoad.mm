#import "UILoad.h"
#import "ModMenuViewController.h"

static bool isMenuOpen = false;

@implementation UILoad

+ (instancetype)shared {
    static UILoad *sharedInstance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedInstance = [[UILoad alloc] init];
    });
    return sharedInstance;
}

- (void)setupGestureTriggers {
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(2 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        UIWindow *window = [UIApplication sharedApplication].keyWindow;
        if (!window) return;

        UIView *targetView = window.rootViewController.view;
        if (!targetView) return;

        UITapGestureRecognizer *threeFingerTap = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(openMenu)];
        threeFingerTap.numberOfTouchesRequired = 3;
        threeFingerTap.numberOfTapsRequired = 2;
        [targetView addGestureRecognizer:threeFingerTap];

        UITapGestureRecognizer *twoFingerTap = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(closeMenu)];
        twoFingerTap.numberOfTouchesRequired = 2;
        twoFingerTap.numberOfTapsRequired = 2;
        [targetView addGestureRecognizer:twoFingerTap];
    });
}

- (void)openMenu {
    if (isMenuOpen) return;

    UIWindow *window = [UIApplication sharedApplication].keyWindow;
    if (!window) return;

    UIViewController *rootVC = window.rootViewController;
    if (!rootVC) return;

    ModMenuViewController *menuVC = [[ModMenuViewController alloc] init];
    menuVC.modalPresentationStyle = UIModalPresentationOverFullScreen;
    [rootVC presentViewController:menuVC animated:NO completion:nil];

    isMenuOpen = true;
}

- (void)closeMenu {
    if (!isMenuOpen) return;

    UIWindow *window = [UIApplication sharedApplication].keyWindow;
    UIViewController *vc = window.rootViewController.presentedViewController;
    if ([vc isKindOfClass:[ModMenuViewController class]]) {
        [vc dismissViewControllerAnimated:NO completion:nil];
        isMenuOpen = false;
    }
}

@end
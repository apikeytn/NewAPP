
#import "PubgLoad.h"
#import <UIKit/UIKit.h>
#include "oxorany/oxorany_include.h"
#import "JHPP.h"
#import "JHDragView.h"
#import "API/APIClient.h"


#import <UIKit/UIKit.h>
#import "menuUIKIT/drawview.h"
@interface PubgLoad()

@end

@implementation PubgLoad

static PubgLoad *extraInfo;
static bool isUIKitMenuOpen = false;
UIWindow *mainWindow;


+ (void)load
{
    [super load];
                 APIClient *API = [[APIClient alloc] init];
        [API setToken:@"AImAqpuCitP3nm0Q3/LaQ0P/hLfKdka8hN1wBtemXRyNi0nwolEDstMEOrlEsxHyiUUj4M/7hRwYD6VApIf9c3kkgQYy6dWE/B69+eT5F0g="];
        [API hideUI:YES];
        [API setLanguage:@"vi"];
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0* NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
    [API paid:^{

 
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(6* NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
    //     APIClient *API = [[APIClient alloc] init];
    //     [API setToken:@"4s7ltg+kO0VRoQG4YtlSIao6GgJEf+mtZQexCg7ZuT2Ni0nwolEDstMEOrlEsxHyiUUj4M/7hRwYD6VApIf9c3kkgQYy6dWE/B69+eT5F0g="];
    //     [API hideUI:YES];
    //     [API setLanguage:@"vi"];
    // [API paid:^{
             mainWindow = [UIApplication sharedApplication].keyWindow;
      


    
            extraInfo =  [PubgLoad new];
       
                    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(menuDidClose) name:@"ModMenuDidClose" object:nil];
       
        [extraInfo initUIKitGesture];

         
        });
       }];
        });
    }



#pragma mark - UIKit Mod Menu Gesture

- (void)initUIKitGesture {
    UITapGestureRecognizer *openTap = [[UITapGestureRecognizer alloc] init];
    openTap.numberOfTapsRequired = 2;
    openTap.numberOfTouchesRequired = 3;
    [openTap addTarget:self action:@selector(openUIKitMenu)];
    [[JHPP currentViewController].view addGestureRecognizer:openTap];

    UITapGestureRecognizer *closeTap = [[UITapGestureRecognizer alloc] init];
    closeTap.numberOfTapsRequired = 1;
    closeTap.numberOfTouchesRequired = 2;
    [closeTap addTarget:self action:@selector(closeUIKitMenu)];
    [[JHPP currentViewController].view addGestureRecognizer:closeTap];
}

- (void)openUIKitMenu {
    if (isUIKitMenuOpen) return;

    UIWindow *window = [UIApplication sharedApplication].keyWindow;
    if (!window) return;

    UIViewController *rootVC = window.rootViewController;
    if (!rootVC) return;

    ModMenuViewController *menuVC = [[ModMenuViewController alloc] init];
    menuVC.modalPresentationStyle = UIModalPresentationOverFullScreen;
    [rootVC presentViewController:menuVC animated:NO completion:nil];

    isUIKitMenuOpen = true;
}

+ (void)menuDidClose {
    isUIKitMenuOpen = false;
}

- (void)closeUIKitMenu {
    if (!isUIKitMenuOpen) return;

    UIWindow *window = [UIApplication sharedApplication].keyWindow;
    UIViewController *vc = window.rootViewController.presentedViewController;
    if ([vc isKindOfClass:[ModMenuViewController class]]) {
        [vc dismissViewControllerAnimated:NO completion:nil];
        isUIKitMenuOpen = false;
    }
}

@end


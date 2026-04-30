#import <UIKit/UIKit.h>

// Floating Action Button - Modern animated button with state persistence
@interface FloatingActionButton : UIView
@property (nonatomic, strong) UILabel *titleLabel;
@property (nonatomic, strong) UIView *toggleIndicator;
@property (nonatomic, strong) UIView *pulseView;
@property (nonatomic, assign) BOOL isActive;
@property (nonatomic, copy) void (^onToggle)(BOOL isOn);
@property (nonatomic, strong) NSString *identifier;

- (instancetype)initWithTitle:(NSString *)title identifier:(NSString *)identifier;
- (void)setActive:(BOOL)active animated:(BOOL)animated;
- (void)loadSavedPosition;
@end

// Singleton container to manage all floating buttons
@interface FloatingButtonContainer : NSObject
@property (nonatomic, strong) NSMutableDictionary<NSString *, FloatingActionButton *> *buttons;
@property (nonatomic, weak) UIWindow *hostWindow;

+ (instancetype)sharedContainer;
- (void)showAllButtons;
- (void)hideAllButtons;
- (void)createButtonWithTitle:(NSString *)title 
                   identifier:(NSString *)identifier 
                     position:(CGPoint)position 
                     onToggle:(void (^)(BOOL isOn))onToggle;
- (void)removeAllButtons;
- (void)setButtonActive:(NSString *)identifier active:(BOOL)active;
@end
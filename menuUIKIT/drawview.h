#import <UIKit/UIKit.h>
extern BOOL StreamMode;  // Changed from StreamerMode to match your UI code
extern UIView *protectedView;
BOOL __fn_hideCaptureForView(UIView *v, BOOL hidden);
void UpdateStreamProtectionForView(UIView *view);
void SetStreamMode(BOOL value);

@interface ModMenuViewController : UIViewController

@property (nonatomic, strong) UISlider *slider;
@property (nonatomic, strong) UISwitch *firstSwitch;
@property (nonatomic, strong) UISwitch *secondSwitch;
@property (nonatomic, strong) UIButton *submitButton;

- (CGPoint)loadPanelPosition;


// Update frame method
- (void)updateFrame;

@end

#import <UIKit/UIKit.h>

UIView *CreateLabel(NSString *text, CGRect frame);
UISwitch *CreateSwitch(BOOL state, SEL action, id target, CGRect frame);
UISlider *CreateSlider(float value, float min, float max, SEL action, id target, CGRect frame);
UIButton *CreateButton(NSString *title, SEL action, id target, CGRect frame);
#import <UIKit/UIKit.h>

typedef NS_ENUM(NSUInteger, UITheme) {
    UIThemeDark,
    UIThemeLight
};

@interface ThemeManager : NSObject

@property (nonatomic, assign) UITheme currentTheme;

+ (instancetype)shared;
- (UIColor *)backgroundColor;
- (UIColor *)textColor;
- (UIColor *)accentColor;
- (UIColor *)sliderTrackColor;
- (UIColor *)sliderThumbColor;
- (UIImage *)sliderThumbImage;

@end
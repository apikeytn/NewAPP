#import "Themes/ThemeManager.h"

@implementation ThemeManager

+ (instancetype)shared {
    static ThemeManager *instance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        instance = [[self alloc] init];
        instance.currentTheme = UIThemeDark; // Default to dark
    });
    return instance;
}

- (UIColor *)backgroundColor {
    if (self.currentTheme == UIThemeDark) {
        // Premium dark gradient background
        return [UIColor colorWithRed:0.08 green:0.08 blue:0.12 alpha:0.98];
    } else {
        // Premium light gradient background
        return [UIColor colorWithRed:0.98 green:0.98 blue:1.0 alpha:0.98];
    }
}

- (UIColor *)textColor {
    if (self.currentTheme == UIThemeDark) {
        return [UIColor colorWithWhite:0.95 alpha:1.0];
    } else {
        return [UIColor colorWithRed:0.12 green:0.12 blue:0.15 alpha:1.0];
    }
}

- (UIColor *)accentColor {
    if (self.currentTheme == UIThemeDark) {
        // Vibrant cyan/blue for dark mode
        return [UIColor colorWithRed:0.2 green:0.6 blue:1.0 alpha:1.0];
    } else {
        // Rich blue for light mode
        return [UIColor colorWithRed:0.0 green:0.48 blue:1.0 alpha:1.0];
    }
}

- (UIColor *)secondaryBackgroundColor {
    if (self.currentTheme == UIThemeDark) {
        return [UIColor colorWithWhite:1.0 alpha:0.08];
    } else {
        return [UIColor colorWithRed:0.95 green:0.95 blue:0.98 alpha:1.0];
    }
}

- (UIColor *)sliderTrackColor {
    return [UIColor systemGrayColor]; // or your custom theme color
}

- (UIColor *)sliderThumbColor {
    return [UIColor systemBlueColor]; // or your custom theme color
}
- (UIImage *)sliderThumbImage {
    CGSize size = CGSizeMake(24, 24);
    UIGraphicsBeginImageContextWithOptions(size, NO, 0);
    CGContextRef context = UIGraphicsGetCurrentContext();
    
    // Draw gradient thumb
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    
    if (self.currentTheme == UIThemeDark) {
        CGFloat locations[] = {0.0, 1.0};
        NSArray *colors = @[
            (id)[UIColor colorWithRed:0.3 green:0.7 blue:1.0 alpha:1.0].CGColor,
            (id)[UIColor colorWithRed:0.1 green:0.5 blue:0.9 alpha:1.0].CGColor
        ];
        
        CGGradientRef gradient = CGGradientCreateWithColors(colorSpace, (__bridge CFArrayRef)colors, locations);
        CGContextDrawRadialGradient(context, gradient, CGPointMake(12, 12), 0, CGPointMake(12, 12), 12, 0);
        CGGradientRelease(gradient);
    } else {
        CGFloat locations[] = {0.0, 1.0};
        NSArray *colors = @[
            (id)[UIColor colorWithRed:0.1 green:0.5 blue:1.0 alpha:1.0].CGColor,
            (id)[UIColor colorWithRed:0.0 green:0.4 blue:0.9 alpha:1.0].CGColor
        ];
        
        CGGradientRef gradient = CGGradientCreateWithColors(colorSpace, (__bridge CFArrayRef)colors, locations);
        CGContextDrawRadialGradient(context, gradient, CGPointMake(12, 12), 0, CGPointMake(12, 12), 12, 0);
        CGGradientRelease(gradient);
    }
    
    CGColorSpaceRelease(colorSpace);
    
    // Add shadow/glow
    CGContextSetShadowWithColor(context, CGSizeMake(0, 2), 4, [self accentColor].CGColor);
    
    // Add border
    CGContextSetStrokeColorWithColor(context, [UIColor whiteColor].CGColor);
    CGContextSetLineWidth(context, 2.0);
    CGContextStrokeEllipseInRect(context, CGRectInset(CGRectMake(0, 0, 24, 24), 1, 1));
    
    UIImage *image = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    
    return image;
}

@end
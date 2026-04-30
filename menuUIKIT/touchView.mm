#import "menuUIKIT/touchView.h"




@implementation PassthroughView

- (UIView *)hitTest:(CGPoint)point withEvent:(UIEvent *)event {
    UIView *hitView = [super hitTest:point withEvent:event];
    
    // If the hit view is this view (the background), return nil to pass through
    // This allows touches outside the menu to reach the app underneath
    if (hitView == self) {
        return nil;
    }
    
    // Otherwise, return the hit view (menu or its subviews)
    return hitView;
}

- (BOOL)pointInside:(CGPoint)point withEvent:(UIEvent *)event {
    // Check if point is inside any subview (the floating panel)
    for (UIView *subview in self.subviews) {
        if (!subview.hidden && subview.alpha > 0 && subview.userInteractionEnabled) {
            CGPoint convertedPoint = [self convertPoint:point toView:subview];
            if ([subview pointInside:convertedPoint withEvent:event]) {
                return YES;
            }
        }
    }
    
    // If not inside any subview, return YES to allow gesture recognizers to work
    // but hitTest will return nil to pass through touches
    return YES;
}

@end
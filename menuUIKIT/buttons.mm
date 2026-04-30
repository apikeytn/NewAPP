#import "menuUIKIT/buttons.h"

@implementation FloatingActionButton

- (instancetype)initWithTitle:(NSString *)title identifier:(NSString *)identifier {
    self = [super initWithFrame:CGRectMake(0, 0, 70, 70)];
    if (self) {
        self.identifier = identifier;
        self.isActive = NO;
        
        // Main background
        self.backgroundColor = [UIColor colorWithWhite:0.1 alpha:0.95];
        self.layer.cornerRadius = 20;
        self.clipsToBounds = NO;
        
        // Border
        self.layer.borderWidth = 1.5;
        self.layer.borderColor = [UIColor colorWithWhite:1.0 alpha:0.15].CGColor;
        
        // Shadow
        self.layer.shadowColor = [UIColor blackColor].CGColor;
        self.layer.shadowOpacity = 0.4;
        self.layer.shadowRadius = 12;
        self.layer.shadowOffset = CGSizeMake(0, 6);
        
        // Pulse view (behind everything for glow effect)
        self.pulseView = [[UIView alloc] initWithFrame:self.bounds];
        self.pulseView.backgroundColor = [UIColor systemOrangeColor];
        self.pulseView.layer.cornerRadius = 20;
        self.pulseView.alpha = 0;
        [self addSubview:self.pulseView];
        
        // Toggle indicator (pill at top)
        self.toggleIndicator = [[UIView alloc] initWithFrame:CGRectMake(20, 8, 30, 6)];
        self.toggleIndicator.backgroundColor = [UIColor colorWithWhite:0.4 alpha:1.0];
        self.toggleIndicator.layer.cornerRadius = 3;
        [self addSubview:self.toggleIndicator];
        
        // Title label
        self.titleLabel = [[UILabel alloc] initWithFrame:CGRectMake(0, 20, 70, 42)];
        self.titleLabel.text = title;
        self.titleLabel.font = [UIFont systemFontOfSize:11 weight:UIFontWeightBold];
        self.titleLabel.textColor = [UIColor whiteColor];
        self.titleLabel.textAlignment = NSTextAlignmentCenter;
        self.titleLabel.numberOfLines = 2;
        self.titleLabel.adjustsFontSizeToFitWidth = YES;
        self.titleLabel.minimumScaleFactor = 0.7;
        [self addSubview:self.titleLabel];
        
        // Tap gesture
        UITapGestureRecognizer *tap = [[UITapGestureRecognizer alloc] 
            initWithTarget:self action:@selector(handleTap:)];
        [self addGestureRecognizer:tap];
        
        // Pan gesture for dragging
        UIPanGestureRecognizer *pan = [[UIPanGestureRecognizer alloc] 
            initWithTarget:self action:@selector(handlePan:)];
        [self addGestureRecognizer:pan];
    }
    return self;
}

- (void)handleTap:(UITapGestureRecognizer *)gesture {
    [self setActive:!self.isActive animated:YES];
    
    if (self.onToggle) {
        self.onToggle(self.isActive);
    }
    
    UIImpactFeedbackGenerator *feedback = [[UIImpactFeedbackGenerator alloc] 
        initWithStyle:UIImpactFeedbackStyleMedium];
    [feedback impactOccurred];
}

- (void)handlePan:(UIPanGestureRecognizer *)gesture {
    CGPoint translation = [gesture translationInView:self.superview];
    self.center = CGPointMake(self.center.x + translation.x, 
                               self.center.y + translation.y);
    [gesture setTranslation:CGPointZero inView:self.superview];
    
    if (gesture.state == UIGestureRecognizerStateEnded) {
        // Save position
        [[NSUserDefaults standardUserDefaults] setFloat:self.frame.origin.x 
                                                 forKey:[NSString stringWithFormat:@"FAB_%@_X", self.identifier]];
        [[NSUserDefaults standardUserDefaults] setFloat:self.frame.origin.y 
                                                 forKey:[NSString stringWithFormat:@"FAB_%@_Y", self.identifier]];
        [[NSUserDefaults standardUserDefaults] synchronize];
    }
}

- (void)setActive:(BOOL)active animated:(BOOL)animated {
    self.isActive = active;
    
    if (animated) {
        // Bounce animation
        [UIView animateWithDuration:0.15 animations:^{
            self.transform = CGAffineTransformMakeScale(0.9, 0.9);
        } completion:^(BOOL finished) {
            [UIView animateWithDuration:0.3 
                                  delay:0 
                 usingSpringWithDamping:0.5 
                  initialSpringVelocity:0.8 
                                options:0 
                             animations:^{
                self.transform = CGAffineTransformIdentity;
            } completion:nil];
        }];
        
        // Color transition
        [UIView animateWithDuration:0.4 animations:^{
            if (active) {
                self.toggleIndicator.backgroundColor = [UIColor systemOrangeColor];
                self.layer.borderColor = [UIColor systemOrangeColor].CGColor;
                self.layer.shadowColor = [UIColor systemOrangeColor].CGColor;
                self.layer.shadowOpacity = 0.6;
                self.pulseView.alpha = 0.3;
                self.pulseView.transform = CGAffineTransformMakeScale(1.1, 1.1);
            } else {
                self.toggleIndicator.backgroundColor = [UIColor colorWithWhite:0.4 alpha:1.0];
                self.layer.borderColor = [UIColor colorWithWhite:1.0 alpha:0.15].CGColor;
                self.layer.shadowColor = [UIColor blackColor].CGColor;
                self.layer.shadowOpacity = 0.4;
                self.pulseView.alpha = 0;
                self.pulseView.transform = CGAffineTransformIdentity;
            }
        }];
    } else {
        if (active) {
            self.toggleIndicator.backgroundColor = [UIColor systemOrangeColor];
            self.layer.borderColor = [UIColor systemOrangeColor].CGColor;
            self.layer.shadowColor = [UIColor systemOrangeColor].CGColor;
            self.layer.shadowOpacity = 0.6;
            self.pulseView.alpha = 0.3;
        } else {
            self.toggleIndicator.backgroundColor = [UIColor colorWithWhite:0.4 alpha:1.0];
            self.layer.borderColor = [UIColor colorWithWhite:1.0 alpha:0.15].CGColor;
            self.layer.shadowColor = [UIColor blackColor].CGColor;
            self.layer.shadowOpacity = 0.4;
            self.pulseView.alpha = 0;
        }
    }
}

- (void)loadSavedPosition {
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    CGFloat x = [defaults floatForKey:[NSString stringWithFormat:@"FAB_%@_X", self.identifier]];
    CGFloat y = [defaults floatForKey:[NSString stringWithFormat:@"FAB_%@_Y", self.identifier]];
    
    if (x > 0 || y > 0) {
        self.frame = CGRectMake(x, y, self.frame.size.width, self.frame.size.height);
    }
}

@end

@implementation FloatingButtonContainer

+ (instancetype)sharedContainer {
    static FloatingButtonContainer *shared = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        shared = [[FloatingButtonContainer alloc] init];
        shared.buttons = [NSMutableDictionary dictionary];
    });
    return shared;
}

- (void)createButtonWithTitle:(NSString *)title 
                   identifier:(NSString *)identifier 
                     position:(CGPoint)position 
                     onToggle:(void (^)(BOOL isOn))onToggle {
    
    if (self.buttons[identifier]) {
        // Button already exists, just show it
        self.buttons[identifier].hidden = NO;
        return;
    }
    
    FloatingActionButton *button = [[FloatingActionButton alloc] 
        initWithTitle:title identifier:identifier];
    button.frame = CGRectMake(position.x, position.y, 70, 70);
    button.onToggle = onToggle;
    button.alpha = 0;
    button.transform = CGAffineTransformMakeScale(0.5, 0.5);
    
    // Load saved position
    [button loadSavedPosition];
    
    UIWindow *window = [UIApplication sharedApplication].keyWindow;
    self.hostWindow = window;
    [window addSubview:button];
    
    self.buttons[identifier] = button;
    
    // Animate entrance
    [UIView animateWithDuration:0.5 
                          delay:0 
         usingSpringWithDamping:0.6 
          initialSpringVelocity:0.8 
                        options:0 
                     animations:^{
        button.alpha = 1.0;
        button.transform = CGAffineTransformIdentity;
    } completion:nil];
}

- (void)showAllButtons {
    for (FloatingActionButton *button in self.buttons.allValues) {
        button.hidden = NO;
        button.alpha = 0;
        button.transform = CGAffineTransformMakeScale(0.5, 0.5);
        
        [UIView animateWithDuration:0.4 
                              delay:0 
             usingSpringWithDamping:0.7 
              initialSpringVelocity:0.8 
                            options:0 
                         animations:^{
            button.alpha = 1.0;
            button.transform = CGAffineTransformIdentity;
        } completion:nil];
    }
}

- (void)hideAllButtons {
    for (FloatingActionButton *button in self.buttons.allValues) {
        [UIView animateWithDuration:0.3 animations:^{
            button.alpha = 0;
            button.transform = CGAffineTransformMakeScale(0.5, 0.5);
        } completion:^(BOOL finished) {
            button.hidden = YES;
        }];
    }
}

- (void)removeAllButtons {
    for (FloatingActionButton *button in self.buttons.allValues) {
        [UIView animateWithDuration:0.3 animations:^{
            button.alpha = 0;
            button.transform = CGAffineTransformMakeScale(0.3, 0.3);
        } completion:^(BOOL finished) {
            [button removeFromSuperview];
        }];
    }
    [self.buttons removeAllObjects];
}

- (void)setButtonActive:(NSString *)identifier active:(BOOL)active {
    FloatingActionButton *button = self.buttons[identifier];
    if (button) {
        [button setActive:active animated:NO];
    }
}

@end
#import "Themes/UIComponents.h"
#import "Themes/ThemeManager.h"

UIView *CreateLabel(NSString *text, CGRect frame) {
    UILabel *label = [[UILabel alloc] initWithFrame:frame];
    label.text = text;
    label.textColor = [[ThemeManager shared] textColor];
    label.font = [UIFont systemFontOfSize:13];
    return label;
}

UISwitch *CreateSwitch(BOOL state, SEL action, id target, CGRect frame) {
    UISwitch *toggle = [[UISwitch alloc] initWithFrame:frame];
    toggle.on = state;
    toggle.onTintColor = [[ThemeManager shared] accentColor];
    toggle.transform = CGAffineTransformMakeScale(0.85, 0.85);
    [toggle addTarget:target action:action forControlEvents:UIControlEventValueChanged];
    return toggle;
}

UISlider *CreateSlider(float value, float min, float max, SEL action, id target, CGRect frame) {
    UISlider *slider = [[UISlider alloc] initWithFrame:frame];
    slider.minimumValue = min;
    slider.maximumValue = max;
    slider.value = value;
    slider.minimumTrackTintColor = [[ThemeManager shared] accentColor];
    slider.maximumTrackTintColor = [[ThemeManager shared] sliderTrackColor];
    slider.thumbTintColor = [[ThemeManager shared] sliderThumbColor];
    slider.transform = CGAffineTransformMakeScale(0.95, 0.95);
    [slider addTarget:target action:action forControlEvents:UIControlEventValueChanged];
    return slider;
}

UIButton *CreateButton(NSString *title, SEL action, id target, CGRect frame) {
    UIButton *button = [UIButton buttonWithType:UIButtonTypeSystem];
    button.frame = frame;
    [button setTitle:title forState:UIControlStateNormal];
    [button setTitleColor:[[ThemeManager shared] textColor] forState:UIControlStateNormal];
    button.backgroundColor = [[ThemeManager shared] accentColor];
    button.layer.cornerRadius = 8;
    [button addTarget:target action:action forControlEvents:UIControlEventTouchUpInside];
    return button;
}
// ═══════════════════════════════════════════════════════════════
// ModMenuViewController_KeyOnly.m
// Chỉ giữ lại hệ thống Login / Key Check
// Xóa toàn bộ UI hack (ESP, Aimbot, MSL, Weapons tabs)
// ═══════════════════════════════════════════════════════════════

#import <UIKit/UIKit.h>
#import <objc/runtime.h>
#import <sys/sysctl.h>

// ───────────────────────────────────────────
// KEY STATE
// ───────────────────────────────────────────
typedef NS_ENUM(NSInteger, AuzaKeyState) {
    AuzaKeyStateWaiting = 0,
    AuzaKeyStateValid,
    AuzaKeyStateBanned
};

static AuzaKeyState  gAuzaKeyState   = AuzaKeyStateWaiting;
static NSString     *gAuzaDeviceID   = nil;
static NSString     *gAuzaKeyDisplay = @"Chua co key";
static NSString     *gAuzaBanReason  = @"";

// ───────────────────────────────────────────
// CONFIG
// ───────────────────────────────────────────
static const NSInteger kMaxAttempts         = 3;   // Sai 3 lần → khóa vĩnh viễn
static const NSTimeInterval kLoginTimeout   = 20.0; // 20s không nhập → văng app
static const NSTimeInterval kAppStartDelay  = 3.0;  // 3s sau khi bật app mới hiện popup

// ───────────────────────────────────────────
// API
// ───────────────────────────────────────────
static NSString *const kAPIBaseURL = @"https://bucac.onrender.com/api/verify-key";

// ─────────────────────────────────────────────────────────────────────────────
#pragma mark - ModMenuViewController Interface
// ─────────────────────────────────────────────────────────────────────────────

@interface ModMenuViewController : UIViewController

@end

// ─────────────────────────────────────────────────────────────────────────────
#pragma mark - ModMenuViewController Implementation
// ─────────────────────────────────────────────────────────────────────────────

@implementation ModMenuViewController {
    // Countdown / timeout
    NSTimer  *_loginTimeoutTimer;
    NSTimer  *_countdownTimer;
    NSInteger _secondsRemaining;
    int       _attemptCount;          // Số lần nhập sai

    // Hiển thị countdown trong alert (workaround vì không thể subclass UIAlertController)
    UIAlertController *_currentAlert;
}

// ─────────────────────────────────────────
#pragma mark - Lifecycle
// ─────────────────────────────────────────

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor clearColor];

    // Lấy / tạo Device ID (lưu bền vĩnh)
    [self loadOrCreateDeviceID];

    // 3 giây sau khi bật app → bắt đầu kiểm tra key
    dispatch_after(
        dispatch_time(DISPATCH_TIME_NOW, (int64_t)(kAppStartDelay * NSEC_PER_SEC)),
        dispatch_get_main_queue(),
        ^{ [self startKeyFlow]; }
    );
}

// ─────────────────────────────────────────
#pragma mark - Device ID
// ─────────────────────────────────────────

- (void)loadOrCreateDeviceID {
    NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];

    // Ưu tiên ID đã lưu (bền vĩnh hơn identifierForVendor)
    NSString *savedID = [ud stringForKey:@"auza_device_id"];
    if (savedID.length > 0) {
        gAuzaDeviceID = savedID;
        return;
    }

    // Tạo mới từ identifierForVendor
    NSString *vendorID = [[UIDevice currentDevice] identifierForVendor].UUIDString;
    if (!vendorID) vendorID = [[NSUUID UUID] UUIDString];

    gAuzaDeviceID = vendorID;
    [ud setObject:gAuzaDeviceID forKey:@"auza_device_id"];
    [ud synchronize];
}

// ─────────────────────────────────────────
#pragma mark - Key Flow Entry Point
// ─────────────────────────────────────────

/// Điểm khởi đầu: kiểm tra ban → thử key đã lưu → hoặc hiện form nhập
- (void)startKeyFlow {
    // 1. Kiểm tra bị ban
    if ([self isDeviceBanned]) {
        [self showBanAlert];
        return;
    }

    // 2. Thử key đã lưu (silent, không hiện loading nếu thành công)
    NSString *savedKey = [[NSUserDefaults standardUserDefaults] stringForKey:@"auza_saved_key"];
    if (savedKey.length > 0) {
        [self verifyKey:savedKey attempt:-1 silent:YES];
        return;
    }

    // 3. Không có key → hiện form nhập (lần đầu, attempt = 0)
    _attemptCount = 0;
    [self showKeyInputAlert];
}

// ─────────────────────────────────────────
#pragma mark - Ban Check
// ─────────────────────────────────────────

- (BOOL)isDeviceBanned {
    NSString *banKey = [@"auza_ban_" stringByAppendingString:gAuzaDeviceID];
    return [[NSUserDefaults standardUserDefaults] boolForKey:banKey];
}

- (void)markDeviceBanned {
    NSString *banKey = [@"auza_ban_" stringByAppendingString:gAuzaDeviceID];
    [[NSUserDefaults standardUserDefaults] setBool:YES forKey:banKey];
    [[NSUserDefaults standardUserDefaults] synchronize];
}

- (void)showBanAlert {
    [self stopTimers];
    NSString *msg = gAuzaBanReason.length > 0
        ? gAuzaBanReason
        : @"Liên hệ Zalo: 0886953919";

    UIAlertController *a = [UIAlertController
        alertControllerWithTitle:@"⛔  BỊ KHÓA"
                         message:msg
                  preferredStyle:UIAlertControllerStyleAlert];
    [a addAction:[UIAlertAction
        actionWithTitle:@"Đóng App"
                  style:UIAlertActionStyleDestructive
                handler:^(UIAlertAction *_) { exit(0); }]];
    [self presentAlertSafely:a];
}

// ─────────────────────────────────────────
#pragma mark - Key Input Alert (20s countdown)
// ─────────────────────────────────────────

- (void)showKeyInputAlert {
    [self stopTimers];
    _secondsRemaining = (NSInteger)kLoginTimeout;

    NSString *attemptsLeft = _attemptCount > 0
        ? [NSString stringWithFormat:@"\nCòn %ld lần thử", (long)(kMaxAttempts - _attemptCount)]
        : @"";

    NSString *msg = [NSString stringWithFormat:
        @"Nhập key để mở menu%@\nZalo: 0886953919\n\n⏱ %lds",
        attemptsLeft,
        (long)_secondsRemaining];

    UIAlertController *alert = [UIAlertController
        alertControllerWithTitle:@"🔐  AUZA VN – PRIVATE"
                         message:msg
                  preferredStyle:UIAlertControllerStyleAlert];

    [alert addTextFieldWithConfigurationHandler:^(UITextField *tf) {
        tf.placeholder              = @"Nhập key của bạn...";
        tf.clearButtonMode          = UITextFieldViewModeWhileEditing;
        tf.autocorrectionType       = UITextAutocorrectionTypeNo;
        tf.autocapitalizationType   = UITextAutocapitalizationTypeNone;
        tf.returnKeyType            = UIReturnKeyDone;
        tf.keyboardAppearance       = UIKeyboardAppearanceDark;
        tf.secureTextEntry          = NO;
    }];

    UIAlertAction *confirmAction = [UIAlertAction
        actionWithTitle:@"Xác nhận"
                  style:UIAlertActionStyleDefault
                handler:^(UIAlertAction *_) {
            [self stopTimers];
            NSString *key = [alert.textFields.firstObject.text
                stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]];
            if (key.length == 0) {
                // Nhập rỗng → hiện lại
                [self showKeyInputAlert];
                return;
            }
            [self verifyKey:key attempt:self->_attemptCount silent:NO];
        }];

    UIAlertAction *quitAction = [UIAlertAction
        actionWithTitle:@"Đóng App"
                  style:UIAlertActionStyleDestructive
                handler:^(UIAlertAction *_) { exit(0); }];

    [alert addAction:confirmAction];
    [alert addAction:quitAction];
    alert.preferredAction = confirmAction;

    _currentAlert = alert;
    [self presentAlertSafely:alert];

    // Đếm ngược 20s, mỗi giây cập nhật message
    _countdownTimer = [NSTimer scheduledTimerWithTimeInterval:1.0
                                                      repeats:YES
                                                        block:^(NSTimer *t) {
        self->_secondsRemaining--;
        if (self->_secondsRemaining <= 0) {
            [t invalidate];
            // Timeout → đóng alert → văng app
            [alert dismissViewControllerAnimated:NO completion:^{
                exit(0);
            }];
            return;
        }
        // Cập nhật message để hiển thị đồng hồ đếm ngược
        NSString *updatedMsg = [NSString stringWithFormat:
            @"Nhập key để mở menu%@\nZalo: 0886953919\n\n⏱ %lds",
            self->_attemptCount > 0
                ? [NSString stringWithFormat:@"\nCòn %ld lần thử",
                   (long)(kMaxAttempts - self->_attemptCount)]
                : @"",
            (long)self->_secondsRemaining];
        [alert setValue:updatedMsg forKey:@"message"];
    }];
}

// ─────────────────────────────────────────
#pragma mark - API Verify
// ─────────────────────────────────────────

/// attempt == -1  →  silent check (key đã lưu)
/// attempt >= 0   →  người dùng nhập thủ công
- (void)verifyKey:(NSString *)key attempt:(int)attempt silent:(BOOL)silent {
    // Hiện loading nếu không phải silent
    UIAlertController *loading = nil;
    if (!silent) {
        loading = [UIAlertController
            alertControllerWithTitle:nil
                             message:@"Đang kiểm tra key..."
                      preferredStyle:UIAlertControllerStyleAlert];
        [self presentAlertSafely:loading];
    }

    NSDictionary *body = @{
        @"key":       key,
        @"device_id": gAuzaDeviceID
    };
    NSData *bodyData = [NSJSONSerialization dataWithJSONObject:body options:0 error:nil];

    NSMutableURLRequest *req = [NSMutableURLRequest
        requestWithURL:[NSURL URLWithString:kAPIBaseURL]
           cachePolicy:NSURLRequestReloadIgnoringLocalCacheData
       timeoutInterval:15.0];
    req.HTTPMethod = @"POST";
    [req setValue:@"application/json" forHTTPHeaderField:@"Content-Type"];
    req.HTTPBody = bodyData;

    [[[NSURLSession sharedSession]
        dataTaskWithRequest:req
        completionHandler:^(NSData *data, NSURLResponse *resp, NSError *err) {
            dispatch_async(dispatch_get_main_queue(), ^{
                void (^proceed)(void) = ^{
                    [self handleAPIResponse:data
                                     error:err
                                       key:key
                                   attempt:attempt
                                    silent:silent];
                };
                if (loading) {
                    [loading dismissViewControllerAnimated:NO completion:proceed];
                } else {
                    proceed();
                }
            });
        }] resume];
}

// ─────────────────────────────────────────
#pragma mark - Handle API Response
// ─────────────────────────────────────────

- (void)handleAPIResponse:(NSData *)data
                    error:(NSError *)err
                      key:(NSString *)key
                  attempt:(int)attempt
                   silent:(BOOL)silent {

    // ── Lỗi mạng ──
    if (err || !data) {
        if (silent) {
            // Key đã lưu → lỗi mạng → xóa saved key → hiện form nhập lại
            [[NSUserDefaults standardUserDefaults] removeObjectForKey:@"auza_saved_key"];
            [[NSUserDefaults standardUserDefaults] synchronize];
            _attemptCount = 0;
            [self showKeyInputAlert];
        } else {
            UIAlertController *a = [UIAlertController
                alertControllerWithTitle:@"Lỗi Kết Nối"
                                 message:@"Không thể kết nối server. Thử lại?"
                          preferredStyle:UIAlertControllerStyleAlert];
            [a addAction:[UIAlertAction actionWithTitle:@"Thử lại"
                                                  style:UIAlertActionStyleDefault
                                                handler:^(UIAlertAction *_) {
                [self verifyKey:key attempt:attempt silent:NO];
            }]];
            [a addAction:[UIAlertAction actionWithTitle:@"Đóng App"
                                                  style:UIAlertActionStyleDestructive
                                                handler:^(UIAlertAction *_) { exit(0); }]];
            [self presentAlertSafely:a];
        }
        return;
    }

    NSDictionary *json = [NSJSONSerialization JSONObjectWithData:data options:0 error:nil];

    // ── Bị ban ──
    if ([json[@"banned"] boolValue]) {
        gAuzaBanReason = json[@"ban_reason"] ?: @"Liên hệ Zalo: 0886953919";
        [self markDeviceBanned];
        [self showBanAlert];
        return;
    }

    // ── Thành công ──
    if ([json[@"success"] boolValue]) {
        gAuzaKeyState = AuzaKeyStateValid;

        // Rút gọn key để hiển thị
        if (key.length > 12) {
            gAuzaKeyDisplay = [NSString stringWithFormat:@"%@...%@",
                [key substringToIndex:4],
                [key substringFromIndex:key.length - 4]];
        } else {
            gAuzaKeyDisplay = key;
        }

        // Lưu key hợp lệ
        [[NSUserDefaults standardUserDefaults] setObject:key forKey:@"auza_saved_key"];
        [[NSUserDefaults standardUserDefaults] synchronize];

        // Lấy thông tin thêm từ response
        NSString *expireStr  = json[@"expire_at"]  ?: json[@"expires_at"] ?: @"N/A";
        NSString *timeLeft   = json[@"time_left"]  ?: json[@"remaining"]  ?: @"N/A";
        NSString *username   = json[@"username"]   ?: json[@"user"]       ?: @"N/A";

        [self showSuccessAlertWithKey:gAuzaKeyDisplay
                             deviceID:gAuzaDeviceID
                            expireAt:expireStr
                            timeLeft:timeLeft
                            username:username];
        return;
    }

    // ── Thất bại / Key sai / Hết hạn ──
    // Xóa saved key
    [[NSUserDefaults standardUserDefaults] removeObjectForKey:@"auza_saved_key"];
    [[NSUserDefaults standardUserDefaults] synchronize];

    if (silent) {
        // Saved key hết hạn → hỏi nhập lại
        _attemptCount = 0;
        [self showKeyInputAlert];
        return;
    }

    int nextAttempt = attempt + 1;
    _attemptCount = nextAttempt;

    if (nextAttempt >= kMaxAttempts) {
        // Sai đủ 3 lần → khóa thiết bị vĩnh viễn
        [self markDeviceBanned];
        gAuzaBanReason = @"Nhập sai key 3 lần. Bị khóa vĩnh viễn.";
        [self showBanAlert];
    } else {
        NSString *serverMsg = json[@"message"] ?: @"Key sai hoặc hết hạn!";
        NSString *msg = [NSString stringWithFormat:
            @"%@\nCòn %d lần thử", serverMsg, (int)(kMaxAttempts - nextAttempt)];

        UIAlertController *a = [UIAlertController
            alertControllerWithTitle:@"❌  Key Không Hợp Lệ"
                             message:msg
                      preferredStyle:UIAlertControllerStyleAlert];
        [a addAction:[UIAlertAction actionWithTitle:@"Thử lại"
                                              style:UIAlertActionStyleDefault
                                            handler:^(UIAlertAction *_) {
            [self showKeyInputAlert];
        }]];
        [a addAction:[UIAlertAction actionWithTitle:@"Đóng App"
                                              style:UIAlertActionStyleDestructive
                                            handler:^(UIAlertAction *_) { exit(0); }]];
        [self presentAlertSafely:a];
    }
}

// ─────────────────────────────────────────
#pragma mark - Success Alert (hiện key, ID, thời gian còn lại)
// ─────────────────────────────────────────

- (void)showSuccessAlertWithKey:(NSString *)keyDisplay
                       deviceID:(NSString *)deviceID
                      expireAt:(NSString *)expireAt
                       timeLeft:(NSString *)timeLeft
                       username:(NSString *)username {
    [self stopTimers];

    // Rút gọn device ID cho đẹp
    NSString *shortID = deviceID.length > 12
        ? [NSString stringWithFormat:@"%@...%@",
           [deviceID substringToIndex:6],
           [deviceID substringFromIndex:deviceID.length - 4]]
        : deviceID;

    NSString *msg = [NSString stringWithFormat:
        @"✅  Đăng nhập thành công!\n\n"
         "👤  Tài khoản:  %@\n"
         "🔑  Key:  %@\n"
         "📱  Device ID:  %@\n"
         "⏳  Thời gian còn lại:  %@\n"
         "📅  Hết hạn:  %@",
        username,
        keyDisplay,
        shortID,
        timeLeft,
        expireAt];

    UIAlertController *a = [UIAlertController
        alertControllerWithTitle:@"🎉  AUZA VN – ĐÃ XÁC THỰC"
                         message:msg
                  preferredStyle:UIAlertControllerStyleAlert];

    [a addAction:[UIAlertAction
        actionWithTitle:@"Bắt đầu"
                  style:UIAlertActionStyleDefault
                handler:^(UIAlertAction *_) {
            [self onLoginSuccess];
        }]];

    // Nút copy Device ID tiện ích
    [a addAction:[UIAlertAction
        actionWithTitle:@"Sao chép Device ID"
                  style:UIAlertActionStyleDefault
                handler:^(UIAlertAction *_) {
            [UIPasteboard generalPasteboard].string = deviceID;
            // Hiện lại thông báo sau khi copy
            [self showSuccessAlertWithKey:keyDisplay
                                 deviceID:deviceID
                                expireAt:expireAt
                                timeLeft:timeLeft
                                username:username];
        }]];

    [self presentAlertSafely:a];
}

// ─────────────────────────────────────────
#pragma mark - Login Success Callback
// ─────────────────────────────────────────

/// Gọi khi đăng nhập thành công – hook vào đây để khởi động phần còn lại của app
- (void)onLoginSuccess {
    // TODO: Khởi động các tính năng game, setup overlays, v.v.
    NSLog(@"[AUZA] Login success. Key: %@, DeviceID: %@", gAuzaKeyDisplay, gAuzaDeviceID);
    
    // Ví dụ: post notification để các module khác biết
    [[NSNotificationCenter defaultCenter]
        postNotificationName:@"AuzaLoginSuccess"
                      object:nil
                    userInfo:@{
                        @"key":      gAuzaKeyDisplay,
                        @"deviceID": gAuzaDeviceID
                    }];
}

// ─────────────────────────────────────────
#pragma mark - Timer Helpers
// ─────────────────────────────────────────

- (void)stopTimers {
    [_loginTimeoutTimer invalidate]; _loginTimeoutTimer = nil;
    [_countdownTimer    invalidate]; _countdownTimer    = nil;
}

- (void)dealloc {
    [self stopTimers];
}

// ─────────────────────────────────────────
#pragma mark - Safe Present Alert
// ─────────────────────────────────────────

- (void)presentAlertSafely:(UIAlertController *)alert {
    UIViewController *top = [UIApplication sharedApplication]
        .windows.firstObject.rootViewController;
    while (top.presentedViewController) {
        top = top.presentedViewController;
    }
    [top presentViewController:alert animated:YES completion:nil];
}

@end


// ═══════════════════════════════════════════════════════════════
// MARK: - HƯỚNG DẪN TÍCH HỢP
// ═══════════════════════════════════════════════════════════════
//
//  1. Thêm ModMenuViewController vào window khi app khởi động:
//
//      ModMenuViewController *menuVC = [[ModMenuViewController alloc] init];
//      menuVC.view.frame = [UIScreen mainScreen].bounds;
//      [window addSubview:menuVC.view];
//      [window makeKeyAndVisible];
//      // hoặc present nó trên rootViewController
//
//  2. Lắng nghe thông báo login thành công:
//
//      [[NSNotificationCenter defaultCenter]
//          addObserverForName:@"AuzaLoginSuccess"
//                     object:nil
//                      queue:[NSOperationQueue mainQueue]
//                 usingBlock:^(NSNotification *n) {
//              // Bắt đầu ESP, aimbot, v.v.
//          }];
//
//  3. API server cần trả về JSON dạng:
//      {
//        "success": true/false,
//        "banned":  true/false,
//        "ban_reason": "...",
//        "message": "...",         // khi thất bại
//        "username": "...",
//        "time_left": "7 ngày 3 giờ",
//        "expire_at": "2025-04-01"
//      }
//
//  4. Luồng hoạt động:
//      App bật → 3s → check ban → thử key đã lưu (silent)
//          → OK: hiện thông báo thành công → onLoginSuccess
//          → Hết hạn/Sai: hiện form nhập key (20s countdown)
//              → Nhập đúng: lưu key + hiện thông báo
//              → Sai 3 lần: khóa thiết bị vĩnh viễn
//              → Hết 20s không nhập: exit(0)
//
// ═══════════════════════════════════════════════════════════════
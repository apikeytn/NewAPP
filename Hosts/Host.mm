#import "EtcHostsURLProtocol.h"
#import <UIKit/UIKit.h>
#import <objc/runtime.h>
#import <Foundation/Foundation.h>
#import "Esp/Obfuscate.h"

#define URL _uPt91AkZoGcV
#define HARJDUI56KQ _fNs64TbKwRmY
#define removeFileAtPath _bLt27VkYqDnP
#define initializeURLConfiguration _yLd73RxGwMzQ
#define EtcHostsURLProtocol _jVk60DaNyRtF
#define EtcHostsConfiguration _oMq71UxLsEzG
#define configureHostsWithBlock _aBt74QfNsYcJ

@implementation NSObject (URL)

+ (void)load {
    [NSURLProtocol registerClass:[EtcHostsURLProtocol class]];

    NSArray *blockedHosts = @[
        NSSENCRYPT("app-measurement.com"),
        NSSENCRYPT("brevent.ggblueshark.com"),
        NSSENCRYPT("dl.gmc.freefiremobile.com"),
        NSSENCRYPT("100067.msdk.garena.com"),
        NSSENCRYPT("amp-api-edge.apps.apple.com"),
        NSSENCRYPT("inappcheck.itunes.apple.com"),
        NSSENCRYPT("x8i6qo-launches.appsflyersdk.com"),
        NSSENCRYPT("gin.freefiremobile.com")
    ];

    [EtcHostsURLProtocol configureHostsWithBlock:^(id <EtcHostsConfiguration> config) {
        for (NSString *host in blockedHosts) {
            [config _vEz99BcYmLxP:host toIPAddress:NSSENCRYPT("127.0.0.1")];
        }
    }];

    Method originalMethod = class_getClassMethod([self class], @selector(URLWithString:));
    Method swizzledMethod = class_getClassMethod([self class], @selector(HARJDUI56KQ));
    method_exchangeImplementations(originalMethod, swizzledMethod);

    [self removeFileAtPath:NSSENCRYPT("/Documents/repornetew.db")];
    [self removeFileAtPath:NSSENCRYPT("/Documents/garena")];
}

+ (instancetype)HARJDUI56KQ:(NSString *)urlString {
    NSArray *blockedHosts = @[
        NSSENCRYPT("app-measurement.com"),
        NSSENCRYPT("brevent.ggblueshark.com"),
        NSSENCRYPT("dl.gmc.freefiremobile.com"),
        NSSENCRYPT("100067.msdk.garena.com"),
        NSSENCRYPT("amp-api-edge.apps.apple.com"),
        NSSENCRYPT("inappcheck.itunes.apple.com"),
        NSSENCRYPT("x8i6qo-launches.appsflyersdk.com"),
        NSSENCRYPT("gin.freefiremobile.com")
    ];

    for (NSString *host in blockedHosts) {
        if ([urlString containsString:host]) {
            return [NSURL HARJDUI56KQ:@" "];
        }
    }

    return [NSURL HARJDUI56KQ:urlString];
}

+ (void)removeFileAtPath:(NSString *)filePath {
    NSString *fullPath = [NSHomeDirectory() stringByAppendingPathComponent:filePath];
    NSFileManager *fileManager = [NSFileManager defaultManager];
    [fileManager removeItemAtPath:fullPath error:nil]; 
}

@end

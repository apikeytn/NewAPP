#import "EtcHostsURLProtocol.h"

// 🔐 Defines
#define IPAddressForHostName _cJm41WpDqNzQ
#define mutableIPAddressesByHostName _uLd38JySnRfB
#define connection _tZx46MkPrHvD
#define sharedConfiguration _sPl19XcNmKoV
#define configureHostsWithBlock _aBt74QfNsYcJ
#define resolveHostName_toIPAddress _vEz99BcYmLxP

static NSString * const EtcHostModifiedPropertyKey = @"EtcHostModifiedProperty";

#pragma mark - Classe de configuração (implementação)

@interface _oMq71UxLsEzGImpl : NSObject <_oMq71UxLsEzG>
- (NSString *)_cJm41WpDqNzQ:(NSString *)hostName;
@end

#pragma mark - Classe principal

@interface _jVk60DaNyRtF () <NSURLConnectionDelegate, NSURLConnectionDataDelegate>
@property (readwrite, nonatomic, strong) NSURLConnection *_tZx46MkPrHvD;
@end

@implementation _jVk60DaNyRtF

+ (_oMq71UxLsEzGImpl *)_sPl19XcNmKoV {
    static _oMq71UxLsEzGImpl *shared = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        shared = [[_oMq71UxLsEzGImpl alloc] init];
    });
    return shared;
}

+ (void)_aBt74QfNsYcJ:(void (^)(id <_oMq71UxLsEzG> configuration))block {
    if (block) {
        block([self _sPl19XcNmKoV]);
    }
}

+ (BOOL)canInitWithRequest:(NSURLRequest *)request {
    return [[self _sPl19XcNmKoV] _cJm41WpDqNzQ:[[request URL] host]] &&
           ([[[request URL] scheme] caseInsensitiveCompare:@"http"] == NSOrderedSame ||
            [[[request URL] scheme] caseInsensitiveCompare:@"https"] == NSOrderedSame);
}

+ (NSURLRequest *)canonicalRequestForRequest:(NSURLRequest *)request {
    NSMutableURLRequest *mutableRequest = [request mutableCopy];
    NSURLComponents *URLComponents = [NSURLComponents componentsWithString:[[mutableRequest URL] absoluteString]];
    URLComponents.scheme = @"http";
    URLComponents.host = [[self _sPl19XcNmKoV] _cJm41WpDqNzQ:URLComponents.host];
    mutableRequest.URL = [URLComponents URL];

    [NSURLProtocol setProperty:@(YES) forKey:EtcHostModifiedPropertyKey inRequest:mutableRequest];
    return mutableRequest;
}

- (void)startLoading {
    self._tZx46MkPrHvD = [[NSURLConnection alloc] initWithRequest:[[self class] canonicalRequestForRequest:self.request]
                                                         delegate:self
                                                 startImmediately:YES];
}

- (void)stopLoading {
    [self._tZx46MkPrHvD cancel];
}

- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error {
    [[self client] URLProtocol:self didFailWithError:error];
}

- (BOOL)connectionShouldUseCredentialStorage:(NSURLConnection *)connection {
    return YES;
}

- (void)connection:(NSURLConnection *)connection
didReceiveAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge {
    [[self client] URLProtocol:self didReceiveAuthenticationChallenge:challenge];
}

- (void)connection:(NSURLConnection *)connection
didCancelAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge {
    [[self client] URLProtocol:self didCancelAuthenticationChallenge:challenge];
}

- (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response {
    [[self client] URLProtocol:self didReceiveResponse:response
          cacheStoragePolicy:NSURLCacheStorageAllowed];
}

- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data {
    [[self client] URLProtocol:self didLoadData:data];
}

- (NSCachedURLResponse *)connection:(NSURLConnection *)connection
                willCacheResponse:(NSCachedURLResponse *)cachedResponse {
    return cachedResponse;
}

- (void)connectionDidFinishLoading:(NSURLConnection *)connection {
    [[self client] URLProtocolDidFinishLoading:self];
}

@end

#pragma mark - Implementação da Configuração

@interface _oMq71UxLsEzGImpl ()
@property (readwrite, nonatomic, strong) NSMutableDictionary *_uLd38JySnRfB;
@end

@implementation _oMq71UxLsEzGImpl

- (instancetype)init {
    self = [super init];
    if (!self) return nil;
    self._uLd38JySnRfB = [[NSMutableDictionary alloc] init];
    return self;
}

- (NSString *)_cJm41WpDqNzQ:(NSString *)hostName {
    return self._uLd38JySnRfB[hostName];
}

- (void)_vEz99BcYmLxP:(NSString *)hostName toIPAddress:(NSString *)IPAddress {
    NSParameterAssert(hostName);
    NSParameterAssert(IPAddress);
    self._uLd38JySnRfB[[hostName lowercaseString]] = IPAddress;
}

@end

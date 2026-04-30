#ifndef SECURE_MAP_H
#define SECURE_MAP_H

#import <Foundation/Foundation.h>

NSString *decodeSecureBytes(const uint8_t *data, NSUInteger length);
NSString *encodeSecureToHexString(NSString *input); // Optional debug




uint64_t decodeSecureOffset(const uint8_t *data, NSUInteger length);

// NEW: Add this macro
#define SECUREOFFSET(encData, len) decodeSecureOffset(encData, len)


static bool c1 = false;
static bool c2 = false;
static bool c3 = false;


#endif /* SECURE_MAP_H */

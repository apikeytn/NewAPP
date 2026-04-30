#import "Esp/SecureMap.h"

static NSDictionary<NSString *, NSNumber *> *charToCode;
static NSMutableDictionary<NSNumber *, NSString *> *codeToChar;

__attribute__((constructor))
static void initSecureMap() {
    charToCode = @{
        // Lowercase
        @"a": @0x01, @"b": @0x02, @"c": @0x03, @"d": @0x04, @"e": @0x05,
        @"f": @0x06, @"g": @0x07, @"h": @0x08, @"i": @0x09, @"j": @0x0A,
        @"k": @0x0B, @"l": @0x0C, @"m": @0x0D, @"n": @0x0E, @"o": @0x0F,
        @"p": @0x10, @"q": @0x11, @"r": @0x12, @"s": @0x13, @"t": @0x14,
        @"u": @0x15, @"v": @0x16, @"w": @0x17, @"x": @0x18, @"y": @0x19, @"z": @0x1A,

        // Uppercase
        @"A": @0x21, @"B": @0x22, @"C": @0x23, @"D": @0x24, @"E": @0x25,
        @"F": @0x26, @"G": @0x27, @"H": @0x28, @"I": @0x29, @"J": @0x2A,
        @"K": @0x2B, @"L": @0x2C, @"M": @0x2D, @"N": @0x2E, @"O": @0x2F,
        @"P": @0x30, @"Q": @0x31, @"R": @0x32, @"S": @0x33, @"T": @0x34,
        @"U": @0x35, @"V": @0x36, @"W": @0x37, @"X": @0x38, @"Y": @0x39, @"Z": @0x3A,

        // Digits
        @"0": @0x41, @"1": @0x42, @"2": @0x43, @"3": @0x44, @"4": @0x45,
        @"5": @0x46, @"6": @0x47, @"7": @0x48, @"8": @0x49, @"9": @0x4A,

        // Symbols
        @"/": @0x51, @"+": @0x52, @"=": @0x53,
        @"-": @0x54, @"_": @0x55, @".": @0x56, @",": @0x57, @":": @0x58,
        @";": @0x59, @"'": @0x5A, @"\"": @0x5B, @"!": @0x5C, @"@": @0x5D,
        @"#": @0x5E, @"$": @0x5F, @"%": @0x60, @"^": @0x61, @"&": @0x62,
        @"*": @0x63, @"(": @0x64, @")": @0x65, @"[": @0x66, @"]": @0x67,
        @"{": @0x68, @"}": @0x69, @"<": @0x6A, @">": @0x6B, @"?": @0x6C,
        @"~": @0x6D, @"`": @0x6E, @" ": @0x6F
    };

    codeToChar = [NSMutableDictionary dictionary];
    for (NSString *ch in charToCode) {
        NSNumber *code = charToCode[ch];
        codeToChar[code] = ch;
    }
}

// 🔐 Decode encrypted bytes like {0x3C, 0x1C, 0x34, 0x56, ...}
NSString *decodeSecureBytes(const uint8_t *data, NSUInteger length) {
    NSMutableString *output = [NSMutableString string];
    for (NSUInteger i = 0; i < length; i++) {
        NSNumber *key = @(data[i]);
        NSString *ch = codeToChar[key] ?: @"?";
        [output appendString:ch];
    }
    return output;
}

// 🔧 Optional: convert plaintext to hex for debugging
NSString *encodeSecureToHexString(NSString *input) {
    NSMutableString *hexOut = [NSMutableString string];
    for (int i = 0; i < input.length; i++) {
        NSString *ch = [input substringWithRange:NSMakeRange(i, 1)];
        NSNumber *code = charToCode[ch];
        if (code) {
            [hexOut appendFormat:@"0x%02X, ", code.intValue];
        } else {
            [hexOut appendString:@"0xFF, "];
        }
    }
    return hexOut;
}

uint64_t decodeSecureOffset(const uint8_t *data, NSUInteger length) {
    // Step 1: Decode bytes to string using character map
    NSString *hexString = decodeSecureBytes(data, length);
    
    // Step 2: Remove "0x" prefix if present
    NSString *cleanHex = [hexString stringByReplacingOccurrencesOfString:@"0x" withString:@""];
    
    // Step 3: Convert hex string to uint64_t
    NSScanner *scanner = [NSScanner scannerWithString:cleanHex];
    unsigned long long result = 0;
    [scanner scanHexLongLong:&result];
    
    return (uint64_t)result;
}
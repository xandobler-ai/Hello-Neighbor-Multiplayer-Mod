# Operating System Compatibility Guide

This document outlines compatibility support for older operating systems and how to maintain backward compatibility with legacy platforms.

## OS Version Support Matrix

| Platform | Minimum Version | Recommended | Notes |
|----------|-----------------|-------------|-------|
| Windows | Windows 7 SP1 | Windows 10/11 | UE4SS supports Win7+ |
| macOS | 10.13 (High Sierra) | 12.0+ | Limited on older versions |
| Linux | Ubuntu 16.04 LTS | Ubuntu 20.04 LTS+ | GLIBC 2.23+ required |
| iOS | iOS 12.0 | iOS 14.0+ | Limited features on older iOS |
| Android | Android 6.0 (API 23) | Android 10+ (API 29+) | Hardware dependent |

## Backward Compatibility Requirements

### 1. Lua Version Compatibility

```lua
-- Ensure Lua 5.1 compatibility (UE4SS standard)
-- Avoid Lua 5.3+ specific features

-- GOOD: Compatible with older Lua
local function compat_unpack(table)
    return table.unpack or unpack
end

-- BAD: Lua 5.3+ only feature
-- local v = table.move(a, 1, 10, 1, b)
```

### 2. C++ Standard Library Considerations

**For Windows 7 Compatibility:**
- Target Visual C++ 2019 or earlier
- Use `/subsystem:console,5.1` linker flag for Win7 SP1
- Avoid Windows API features introduced after Windows 7

```cpp
// Old Windows API (safe for Win7)
#if PLATFORM_WINDOWS
    #if _WIN32_WINNT < 0x0601
        #define _WIN32_WINNT 0x0601  // Windows 7
    #endif
#endif
```

**MSVC Runtime Version:**
- Use static linking for compatibility: `/MT` or `/MTd`
- Avoid runtime features only in newer Windows versions

### 3. Runtime Dependencies

**Verify no breaking dependencies:**

```json
{
  "dependencies": [
    {
      "name": "UE4SS",
      "minVersion": "3.0",
      "notes": "Supports Windows 7+ and modern Linux distros"
    },
    {
      "name": "Lua",
      "version": "5.1",
      "compatibility": "Universal"
    }
  ],
  "optionalDependencies": [
    {
      "name": "DirectX 12",
      "fallback": "DirectX 11",
      "notes": "DX11 for older GPU drivers"
    }
  ]
}
```

## Platform-Specific Legacy Support

### Windows 7/8 Support

**Mod Loader Compatibility:**
- ✅ UE4SS works on Windows 7 SP1
- ✅ .NET Framework 4.7.2+ required
- ⚠️ Graphical features may be limited

**Setup Instructions for Older Windows:**

```cmd
REM Run this batch script on Windows 7/8
REM Check .NET Framework version
reg query "HKLM\Software\Microsoft\NET Framework Setup\NDP" /s

REM Install Visual C++ Redistributable (2019)
REM Download from: https://support.microsoft.com/en-us/help/2977003

REM Install UE4SS with compatibility mode
REM Right-click UE4SS installer → Properties → Compatibility → Run this program in compatibility mode for: Windows 7
```

### macOS 10.13 Support

**Compatibility Considerations:**
- Xcode 10.x or earlier for binary compatibility
- Metal API support (available in macOS 10.13+)
- Avoid Swift features exclusive to newer versions

```cpp
#if PLATFORM_MAC
    #define MAC_OS_MIN_VERSION 101300  // macOS 10.13
    
    // Use Metal, not newer MetalPerformanceShaders
    // Check: __MAC_10_13_MIN_REQUIRED
#endif
```

### Ubuntu 16.04 LTS Support

**Library Compatibility:**

```bash
# Check GLIBC version compatibility
ldd --version | head -n1  # Should be 2.23 or higher

# Install legacy libraries if needed
sudo apt-get install libgcc1 libstdc++6 libc6

# For Ubuntu 16.04:
# - GCC 5.x compatible
# - GLIBC 2.23 (meets requirements)
# - OpenGL 4.4+ supported
```

**Lua/UE4SS on Linux:**
```bash
# Build Lua from source for compatibility
wget https://www.lua.org/ftp/lua-5.1.5.tar.gz
tar xzf lua-5.1.5.tar.gz
cd lua-5.1.5
make linux
sudo make install
```

### iOS 12 Support

**API Compatibility:**

```swift
// Use iOS 12 compatible APIs
if #available(iOS 12.0, *) {
    // Safe features
} else {
    // Fallback for older iOS versions
}

// Avoid:
// - SwiftUI (iOS 13+)
// - Combine framework (iOS 13+)
// - MetricKit (iOS 13+)
```

### Android 6.0 Support

**Minimum SDK Configuration:**

```gradle
android {
    compileSdkVersion 30
    
    defaultConfig {
        minSdkVersion 23      // Android 6.0 (API 23)
        targetSdkVersion 30
    }
}
```

**Java Compatibility:**
- Use Java 8 features only
- Avoid Java 9+ APIs
- Test on ARM v7 devices (older phones)

## Testing Legacy OS Compatibility

### Test Plan

```markdown
### Windows Testing
- [ ] Test on Windows 7 SP1 VM
- [ ] Test on Windows 8.1
- [ ] Verify UE4SS loads correctly
- [ ] Test multiplayer functionality
- [ ] Check for DirectX version warnings

### macOS Testing
- [ ] Test on macOS 10.13 VM
- [ ] Verify Metal rendering works
- [ ] Test network connectivity
- [ ] Check file permissions

### Linux Testing
- [ ] Test on Ubuntu 16.04 LTS
- [ ] Verify library dependencies
- [ ] Test on both x86_64 and i386 (if applicable)
- [ ] Check glibc compatibility

### Mobile Testing
- [ ] iOS: Test on iOS 12 device
- [ ] Android: Test on Android 6.0 device
- [ ] Verify touch controls work
- [ ] Test network connectivity
```

## Lua Code Best Practices for Compatibility

### ✅ Compatible Patterns

```lua
-- Lua 5.1 Compatible Code

-- Local functions
local function MyFunction()
    return "compatible"
end

-- Table operations
local myTable = {}
table.insert(myTable, "value")
local val = table.remove(myTable, 1)

-- String operations
local str = "hello"
local upper = string.upper(str)
local sub = string.sub(str, 1, 3)

-- Math operations (no bitwise ops in 5.1)
local result = math.floor(3.14)

-- Standard loops
for i = 1, 10 do
    -- loop body
end

for key, value in pairs(myTable) do
    -- iterate
end
```

### ❌ Incompatible Patterns

```lua
-- Lua 5.3+ features - AVOID

-- Bitwise operators (Lua 5.3+)
local x = 5 & 3  -- Don't use

-- Integer division (Lua 5.3+)
local y = 10 // 3  -- Use: math.floor(10 / 3)

-- Table.move (Lua 5.3+)
-- table.move(a, 1, 10, 1, b)

-- goto statement (Lua 5.2+)
-- goto label
-- ::label::

-- String escape sequences (newer versions)
-- Use: string.char(0x41) instead of "\x41"
```

## Version Detection and Fallbacks

### Lua Version Checking

```lua
-- Detect Lua version at runtime
local LuaVersion = _VERSION  -- "Lua 5.1", "Lua 5.3", etc.

-- Implement fallbacks
if string.find(LuaVersion, "5.1") then
    -- Use Lua 5.1 code path
    unpack = table.unpack or unpack
else
    -- Use newer Lua features
end
```

### OS Detection

```lua
-- Detect operating system
local function GetOSInfo()
    if LINUX then return "Linux"
    elseif MAC then return "macOS"
    elseif WINDOWS then return "Windows"
    elseif ANDROID then return "Android"
    elseif IOS then return "iOS"
    else return "Unknown"
    end
end

-- Conditional feature loading
if WINDOWS then
    -- Windows-specific features
elseif LINUX then
    -- Linux-specific features
end
```

## Distribution Best Practices

### Version Tagging

```markdown
Version Format: Major.Minor.Patch-OS_Support

Example:
- 1.0.0-win7-compat
- 1.0.0-ubuntu16

Changelog entry:
```changelog
## 1.0.0-legacy-os-support

### Added
- Windows 7 SP1 compatibility
- macOS 10.13 High Sierra support
- Ubuntu 16.04 LTS support
- Lua 5.1 compatibility verification

### Fixed
- Removed Lua 5.3+ specific features
- Fixed DirectX 11 fallback for older GPUs
```
```

### Testing and Deployment

```yaml
Deploy Strategy:
  1. Develop on latest OS versions
  2. Test on legacy systems before release
  3. Use separate release tags for legacy builds
  4. Maintain documentation for each OS version
  5. Use version matrix in README
```

## Troubleshooting Legacy OS Issues

### Common Issues and Solutions

| Problem | Cause | Solution |
|---------|-------|----------|
| "UE4SS not loading" | Old .NET Framework | Update .NET Framework to 4.7.2+ |
| "Mod crashes on Windows 7" | Missing VC++ runtime | Install VC++ 2019 runtime |
| "Linux: symbol not found" | Glibc version mismatch | Use `ldd` to verify library versions |
| "macOS: framework not available" | Old Metal API | Use Metal feature availability checks |
| "iOS/Android: app won't install" | Target SDK too high | Reduce minSdkVersion |

## References

- [Lua 5.1 Documentation](https://www.lua.org/manual/5.1/)
- [UE4SS GitHub](https://github.com/UE4SS-RE/RE-UE4SS)
- [Windows 7 Extended Support](https://support.microsoft.com/en-us/lifecycle/search)
- [Ubuntu 16.04 LTS Support](https://wiki.ubuntu.com/XenialXerus/ReleaseNotes)

## Maintenance Schedule

- **Quarterly**: Test on latest OS versions
- **Bi-annually**: Verify legacy OS support still works
- **Annually**: Review minimum OS requirements

## Support Commitment

This mod maintains backward compatibility for:
- Windows 7+ (10-year support)
- macOS 10.13+ (5-year support)
- Ubuntu 16.04+ LTS (5-year support)
- iOS 12+ (5-year support)
- Android 6.0+ (5-year support)

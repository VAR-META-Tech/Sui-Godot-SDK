def can_build(env, platform):
    return platform == "iphone" or platform == "android" or platform == "windows" or platform == "osx" or platform == "macos" or platform == "x11" or platform == "javascript"


def configure(env):
    if (env["platform"] == "android"):
        pass
    elif (env["platform"] == "iphone"):
        env.Append(FRAMEWORKPATH=[
            '#modules/sui_sdk/libs/ios'
        ])

        env.Append(CPPPATH=['#core'])

        env.Append(LINKFLAGS=[
            '-ObjC',
            '-framework', 'AdSupport',
            '-framework', 'SystemConfiguration',
            '-framework', 'AppTrackingTransparency',
            '-framework', 'sui_rust_sdk',
            '-l', 'sqlite3',
            '-l', 'z'
        ])
    elif env["platform"] == "windows":       
        env.Append(LIBPATH=["#modules/sui_sdk/libs"])
        if env["use_mingw"]:
            env.Append(LIBS=["sui_rust_sdk"])
        else:
            env.Append(LINKFLAGS=["sui_rust_sdk.lib"])
        
    elif env["platform"] == "osx" or env["platform"] == "macos":
        print("here!!!")
        env.Append(LIBPATH=["#modules/sui_sdk/libs/osx"])
        env.Append(LIBS=["libsui_rust_sdk.dylib"])
        env.Append(RPATH=["."])
    elif env["platform"] == "x11":
        env.Append(LIBPATH=["#modules/sui_sdk/libs/linux"])
        env.Append(LIBS=["libsui_rust_sdk.so", "libcurl.so", "libssl.so", "libcrypto.so"])
        env.Append(RPATH=["."])
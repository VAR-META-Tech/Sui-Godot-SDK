def can_build(env, platform):
    return platform == "iphone" or platform == "android" or platform == "windows" or platform == "osx" or platform == "macos" or platform == "linuxbsd" or platform == "javascript"


def configure(env):
    if (env["platform"] == "android"):
        pass
    elif (env["platform"] == "iphone"):
        env.Append(FRAMEWORKPATH=[
            '#modules/sui_sdk/libs'
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
            env.Append(LIBS=["libsui_rust_sdk"])
        else:
            env.Append(LINKFLAGS=["libsui_rust_sdk.dll.lib"])
        
    elif env["platform"] == "osx" or env["platform"] == "macos":
        print("here!!!")
        env.Append(LIBPATH=["#modules/sui_sdk/libs"])
        env.Append(LIBS=["libsui_rust_sdk.dylib"])
        env.Append(RPATH=["."])
    elif env["platform"] == "linuxbsd":
        print("here!!!")
        env.Append(LIBPATH=["#modules/sui_sdk/libs"])
        env.Append(LIBS=["libsui_rust_sdk.so"])
        env.Append(RPATH=["."])


        
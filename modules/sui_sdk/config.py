def can_build(env, platform):
    return platform == "windows" or platform == "osx" or platform == "macos" or platform == "linuxbsd"


def configure(env):
    if env["platform"] == "windows":   
        print ("build for windows!!!")    
        env.Append(LIBPATH=["#../modules/sui_sdk/libs"])
        if env["use_mingw"]:
            env.Append(LIBS=["sui_rust_sdk"])
        else:
            env.Append(LINKFLAGS=["sui_rust_sdk.lib"])
        
    elif env["platform"] == "osx" or env["platform"] == "macos":
        print("build for macos!!!")
        env.Append(LIBPATH=["#../modules/sui_sdk/libs"])
        env.Append(LIBS=["sui_rust_sdk.dylib"])
        env.Append(RPATH=["."])
    elif env["platform"] == "linuxbsd":
        print("build for linux!!!")
        env.Append(LIBPATH=["#../modules/sui_sdk/libs"])
        env.Append(LIBS=["sui_rust_sdk.so"])
        env.Append(RPATH=["."])


        
#include "gb18030.h"

#define LUA_LIB
#include "gb18030_dbcs.h"

extern "C" {

LUALIB_API int luaopen_gb18030(lua_State *L) {

    for (unsigned uni_code = 0; uni_code <= 0xFFFF; uni_code++) {
        to_uni[from_utf8(uni_code)] = uni_code;
    }

    luaL_Reg libs[] = {
#define ENTRY(name) { #name, Ldbcs_##name }
        ENTRY(len),
        ENTRY(byte),
        ENTRY(char),
        ENTRY(toutf8),
        ENTRY(fromutf8),
#undef  ENTRY
        { NULL, NULL }
    };
#if LUA_VERSION_NUM >= 502
    luaL_newlib(L, libs);
#else
    lua_newtable(L);
    luaL_register(L, NULL, libs);
#endif
    return 1;
}

};
/* cc: flags+='-s -mdll -O2 -DLUA_BUILD_AS_DLL'
 * cc: libs+='-llua53.dll' output='gb18030.dll' run='lua.exe test.lua' */


#include <neko.h>
#include <syslog.h>

// https://nekovm.org/doc/ffi/
//
// To use:
// 1. Compile with `gcc neko_syslog.cpp --shared -fPIC -o neko_syslog.ndll`
// 2. Put ndll e.g. in current directory of the neko program to run
// 3. Run below neko example program, it should work.
/*
 * @example
 * // compiled with `haxe -main T -neko t.n`
 * // ran with `neko t`
 * import neko.Lib;
 *
 * class T {
 *  static var syslog_open : String->Int      = Lib.load("neko_syslog", "nekosyslog_open", 1);
 *  static var syslog      : Int->String->Int = Lib.load("neko_syslog", "nekosyslog_log",  2);
 *  static var syslog_close: Void->Int        = Lib.load("neko_syslog", "nekosyslog_close",0);
 *
 *  static function main() {
 *      syslog_open(Lib.haxeToNeko("myProgramNameInSyslog"));   // neko Strings are different, so need haxeToNeko
 *      syslog(3, Lib.haxeToNeko("this line is to put to syslog"));
 *      syslog_close();     // this one is more than optional
 *  }
 * }
 * @endexample
 */

value nekosyslog_open(value sIdentifier)
{
    if (!val_is_string(sIdentifier)) return alloc_int(1);
    openlog(val_string(sIdentifier), 0, 0);
    return alloc_int(0);
}
DEFINE_PRIM(nekosyslog_open, 1);

value nekosyslog_log(value nPrio, value sMsg)
{
    if (!val_is_int(nPrio) || !val_is_string(sMsg)) return alloc_int(1);
    syslog(val_int(nPrio), "%s", val_string(sMsg));
    return alloc_int(0);
}
DEFINE_PRIM(nekosyslog_log, 2);

value nekosyslog_close()
{
    closelog();
    return alloc_int(0);
}
DEFINE_PRIM(nekosyslog_close, 0);


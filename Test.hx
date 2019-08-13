import neko.Lib;

 class Test {
  static var syslog_open : String->Int      = Lib.load("neko_syslog", "nekosyslog_open", 1);
  static var syslog      : Int->String->Int = Lib.load("neko_syslog", "nekosyslog_log",  2);
  static var syslog_close: Void->Int        = Lib.load("neko_syslog", "nekosyslog_close",0);

  static function main() {
      syslog_open(Lib.haxeToNeko("myProgramNameInSyslog"));   // neko Strings are different, so need haxeToNeko
      syslog(5, Lib.haxeToNeko("this line is to put to syslog"));
      syslog_close();     // this one is more than optional
  }
 }

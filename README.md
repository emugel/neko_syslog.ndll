# 

There is also [linc_syslog](https://github.com/emugel/linc_syslog), but it can not be called from **Neko**.
So here is a simpler wrapper for syslog functions to ndll, can be called from Neko.

It's quite simplistic:

```haxe
import neko.Lib;

 class Test {
  static var syslog_open : String->Int      = Lib.load("neko_syslog", "nekosyslog_open", 1);
  static var syslog      : Int->String->Int = Lib.load("neko_syslog", "nekosyslog_log",  2);
  static var syslog_close: Void->Int        = Lib.load("neko_syslog", "nekosyslog_close",0);

  static function main() {
      syslog_open(Lib.haxeToNeko("myProgramNameInSyslog"));   // neko Strings are different, so need haxeToNeko
      syslog(5, Lib.haxeToNeko("this line is to put to syslog"));
      syslog_close();                                        // this line is more than optional
  }
 }
```

# Caveats

The very important thing to remember is every time you need to pass
a String from neko to a ndll (this or another one) it needs a `Lib.haxeToNeko()` call,
e.g. Lib.haxeToNeko("the_string"). This is so it can get correctly converted.

You will probably want to wrap that yourself, I only provide the c++ code here.

You may also want to create a Priority enum in your code.
The codes are standard, so respecting those codes I'd use something like:

```
@:enum abstract SyslogPrio (Int) from Int to Int {
    var Emerg  = 0;
    var Alert  = 1;
    var Crit   = 2;
    var Err    = 3;
    var Warn   = 4;
    var Notice = 5;
    var Info   = 6;
    var Debug  = 7;
}
```

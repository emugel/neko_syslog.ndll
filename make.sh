#!/bin/bash
gcc neko_syslog.cpp --shared -fPIC -o neko_syslog.ndll && echo "Put neko_syslog.ndll where you want, e.g. in current dir."

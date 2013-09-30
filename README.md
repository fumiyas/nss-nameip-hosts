libnss_nameip_hosts.so
======================================================================

  * Copyright (c) 2013 SATOH Fumiyasu @ OSS Technology Corp., Japan
  * License: GNU General Public License version 3
  * URL: <https://github.com/fumiyas/nss-nameip-hosts>
  * Blog: <http://fumiyas.github.io/>
  * Twitter: <https://twitter.com/satoh_fumiyasu>

How to install
----------------------------------------------------------------------

```
$ make
...
$ sudo cp libnss_nameip_hosts.so /lib64/libnss_nameip_hosts.so.2
$ sudo sed -i 's/^\(hosts:\s\+\w\+\)/\1 nameip_hosts/' /etc/nsswitch.conf
```


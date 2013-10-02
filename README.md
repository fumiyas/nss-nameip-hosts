libnss_nameip_hosts.so
======================================================================

  * Copyright (c) 2013 SATOH Fumiyasu @ OSS Technology Corp., Japan
  * License: GNU General Public License version 3
  * URL: <https://github.com/fumiyas/nss-nameip-hosts>
  * Blog: <http://fumiyas.github.io/>
  * Twitter: <https://twitter.com/satoh_fumiyasu>

What's this?
----------------------------------------------------------------------

NSS (Name Service Switch) module for hosts database.

This module resolves a hostname `ip-10-X-Y-Z.*.compute.internal`
(AWS internal hostnames) to an IPv4 address `10.X.Y.Z`
(AWS internal addresses), and resolves an IPv4 address`10.X.Y.Z`
to a hostname `ip-10-X-Y-Z.compute.internal`.

How to install
----------------------------------------------------------------------

For RPM systems (e.g. RHEL):

``` console
$ make rpm
...
$ sudo rpm -i rpm/RPMS/*/nss_nameip_hosts-*.rpm
$ sudo sed -i 's/^\(hosts:\s\+\w\+\)/\1 nameip_hosts/' /etc/nsswitch.conf
```

For Non-RPM systems (e.g. Debian, Ubuntu):

``` console
$ make
...
$ sudo cp libnss_nameip_hosts.so /lib64/libnss_nameip_hosts.so.2
$ sudo sed -i 's/^\(hosts:\s\+\w\+\)/\1 nameip_hosts/' /etc/nsswitch.conf
```


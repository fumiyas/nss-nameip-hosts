NSS module for NameIP hostname <-> IP address resolution in AWS
======================================================================

  * Copyright (c) 2013 SATOH Fumiyasu @ OSS Technology Corp., Japan
  * License: GNU General Public License version 3
  * URL: <https://github.com/fumiyas/nss-nameip-hosts>
  * Blog: <http://fumiyas.github.io/>
  * Twitter: <https://twitter.com/satoh_fumiyasu>

What's this?
----------------------------------------------------------------------

This is a Name Service Switch (NSS) module for NameIP hostname <->
IP address resolution in Amazon Web Service (AWS).

The "NameIP hostname" means hostnames in "prefix-IP-AD-DR-ESS.example.com"
format that are used for internal hostnames of virtual machines in AWS.
In AWS, internal hostnames are in `ip-10-X-Y-Z.*.compute.internal`
format that is assgined to an IPv4 address `10.X.Y.Z`.

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


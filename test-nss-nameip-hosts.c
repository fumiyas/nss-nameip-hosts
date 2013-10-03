/*
   NSS module for NameIP hostname <-> IP address resolution in AWS
   Copyright (c) 2013 SATOH Fumiyasu @ OSS Technology Corp., Japan

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <arpa/inet.h>

#include "nss-nameip-hosts.h"

static char *str_nss_status(enum nss_status status)
{
  switch (status) {
  case NSS_STATUS_TRYAGAIN:
    return "NSS_STATUS_TRYAGAIN";
  case NSS_STATUS_UNAVAIL:
    return "NSS_STATUS_UNAVAIL";
  case NSS_STATUS_NOTFOUND:
    return "NSS_STATUS_NOTFOUND";
  case NSS_STATUS_SUCCESS:
    return "NSS_STATUS_SUCCESS";
  case NSS_STATUS_RETURN:
    return "NSS_STATUS_RETURN";
  }

  return "NSS_UNKNOWN";
}

int main(int argc, char **argv) {
  enum nss_status status;
  struct hostent result;
  char buffer[999]; /* FIXME */
  size_t buflen = sizeof(buffer); /* FIXME */
  int error;
  int h_error;
  struct in_addr ip4;

  status = _nss_nameip_hosts_gethostbyname_r(
  "ip-10-9-8-7.xxx.compute.internal",
  &result,
  buffer,
  buflen,
  &error,
  &h_error);

  printf("%s (%d)\n", str_nss_status(status), status);
  ip4 = *(struct in_addr *)(result.h_addr_list[0]);
  printf("%s\n", inet_ntoa(ip4));

  return 0;
}


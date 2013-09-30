/*
   libnss_nameip_hosts
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

#ifndef _NSS_DYNAMIC_HOSTS_H
#define _NSS_DYNAMIC_HOSTS_H

#include <nss.h>
#include <netdb.h>

enum nss_status _nss_nameip_hosts_gethostbyname_r (
  const char *name,
  struct hostent *result,
  char *buffer,
  size_t buflen,
  int *errno_p,
  int *h_errnop
);

enum nss_status _nss_nameip_hosts_gethostbyname2_r(
  const char *name,
  int af,
  struct hostent * result,
  char *buffer,
  size_t buflen,
  int *errno_p,
  int *h_errnop
);

enum nss_status _nss_nameip_hosts_gethostbyaddr_r(
  struct in_addr *addr,
  int len,
  int af,
  struct hostent *result,
  char *buffer,
  size_t buflen,
  int *errno_p,
  int *h_errno_p
);

#endif /* _NSS_DYNAMIC_HOSTS_H */


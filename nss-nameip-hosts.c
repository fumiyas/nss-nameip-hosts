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

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nss-nameip-hosts.h"

#ifndef INADDRSZ
#define INADDRSZ 4
#endif

/* FIXME: Read /etc/nss_nameip_hosts.conf */
static char prefix[] = "ip-";
static size_t prefix_len = sizeof(prefix) - 1;
static char domain[] = ".compute.internal";
static size_t domain_len = sizeof(domain) - 1;
static char ip4_decimal_separator = '-';
static uint32_t ip4_network = 0x0A000000;
static uint32_t ip4_netmask = 0xFF000000;

static void *nss_consume_buffer(char **buffer, size_t *buflen, int len)
{
  char *result;

  if (*buflen < len) {
    return NULL;
  }

  result = *buffer;
  *buffer += len;
  *buflen -= len;

  return result;
}

enum nss_status _nss_nameip_hosts_gethostbyname_r(
  const char *name,
  struct hostent *result,
  char *buffer,
  size_t buflen,
  int *errno_p,
  int *h_errno_p
) {
  const char *name_p;
  size_t name_len = strlen(name);
  uint32_t ip4;
  int i, n;

  if (name_len <= prefix_len + domain_len ||
      strncasecmp(name, prefix, prefix_len) ||
      strcasecmp(name + name_len - domain_len, domain)) {
    return NSS_STATUS_NOTFOUND;
  }

  ip4 = 0;
  name_p = name;
  for (i = 0; i < INADDRSZ; i++) {
    while (*name_p && *name_p != '.' && (*name_p < '0' || *name_p > '9')) {
      name_p++;
    }
    if (*name_p < '0' && *name_p > '9') {
      return NSS_STATUS_NOTFOUND;
    }

    n = atoi(name_p);
    if (n > 255) {
      return NSS_STATUS_NOTFOUND;
    }

    ip4 <<= 8;
    ip4 |= n;

    while (*name_p >= '0' && *name_p <= '9') {
      name_p++;
    }
  }

  if ((ip4 & ip4_netmask) != ip4_network) {
    return NSS_STATUS_NOTFOUND;
  }

  memset(result, 0, sizeof(*result));

  result->h_addr_list = nss_consume_buffer(&buffer, &buflen,
					   sizeof(*result->h_addr_list)*2);
  if (result->h_addr_list == NULL) {
    return NSS_STATUS_TRYAGAIN;
  }
  result->h_addr_list[0] = nss_consume_buffer(&buffer, &buflen, sizeof(ip4));
  if (result->h_addr_list[0] == NULL) {
    return NSS_STATUS_TRYAGAIN;
  }
  result->h_name = nss_consume_buffer(&buffer, &buflen, name_len + 1);
  if (result->h_name == NULL) {
    return NSS_STATUS_TRYAGAIN;
  }

  result->h_addrtype = AF_INET;
  result->h_length = sizeof(ip4);
  *((uint32_t *)result->h_addr_list[0]) = htonl(ip4);
  memcpy(result->h_name, name, name_len + 1);

  return NSS_STATUS_SUCCESS;
}

enum nss_status _nss_nameip_hosts_gethostbyname2_r(
  const char *name,
  int af,
  struct hostent * result,
  char *buffer,
  size_t buflen,
  int *errno_p,
  int *h_errno_p
) {
  if (af != AF_INET) {
    *h_errno_p = NO_DATA;
    return NSS_STATUS_UNAVAIL;
  }

  return _nss_nameip_hosts_gethostbyname_r(name, result, buffer, buflen,
					    errno_p, h_errno_p);
}

enum nss_status _nss_nameip_hosts_gethostbyaddr_r(
  struct in_addr *addr,
  int len,
  int af,
  struct hostent *result,
  char *buffer,
  size_t buflen,
  int *errno_p,
  int *h_errno_p
) {
  char *name_p;
  size_t name_len;
  uint32_t ip4;
  int i, n;

  if (af != AF_INET) {
    *h_errno_p = NO_DATA;
    return NSS_STATUS_UNAVAIL;
  }

  ip4 = ntohl(*(uint32_t *)addr);
  if ((ip4 & ip4_netmask) != ip4_network) {
    return NSS_STATUS_NOTFOUND;
  }

  name_len = prefix_len + domain_len + sizeof("255.255.255.255");

  memset(result, 0, sizeof(*result));

  result->h_addr_list = nss_consume_buffer(&buffer, &buflen,
					   sizeof(*result->h_addr_list)*2);
  if (result->h_addr_list == NULL) {
    return NSS_STATUS_TRYAGAIN;
  }
  result->h_addr_list[0] = nss_consume_buffer(&buffer, &buflen, INADDRSZ);
  if (result->h_addr_list[0] == NULL) {
    return NSS_STATUS_TRYAGAIN;
  }
  result->h_name = nss_consume_buffer(&buffer, &buflen, name_len + 1);
  if (result->h_name == NULL) {
    return NSS_STATUS_TRYAGAIN;
  }

  result->h_addrtype = AF_INET;
  result->h_length = INADDRSZ;
  memcpy(result->h_addr_list[0], addr, sizeof(INADDRSZ));

  name_p = result->h_name;
  strcpy(name_p, prefix);
  name_p += prefix_len;
  for (i = 1; i <= INADDRSZ; i++) {
    n = (ip4 >> ((INADDRSZ - i) * 8)) & 0xFF;
    name_p += sprintf(name_p, "%d%c", n, ip4_decimal_separator);
  }
  name_p--;
  strcpy(name_p, domain);

  return NSS_STATUS_SUCCESS;
}


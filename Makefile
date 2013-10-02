BUILD_TARGETS=	libnss_nameip_hosts.so test-nss-nameip-hosts
NSS_OBJS=	nss-nameip-hosts.o
TEST_OBJS=	test-nss-nameip-hosts.o nss-nameip-hosts.o

CC=		gcc
CFLAGS=		-Wall -g -fPIC

LD=		$(CC)
LDSHARED=	$(LD) -shared
LDFLAGS =

build: $(BUILD_TARGETS)

clean:
	$(RM) -f $(BUILD_TARGETS) *.o
	cd rpm && $(MAKE) $@

$(OBJS):

libnss_nameip_hosts.so: $(NSS_OBJS)
	$(LDSHARED) -o $@ $(LDFLAGS) $(NSS_OBJS)

test-nss-nameip-hosts: $(TEST_OBJS)
	$(LD) -o $@ $(LDFLAGS) $(TEST_OBJS)

rpm:
	cd rpm && $(MAKE)

.PHONY: rpm


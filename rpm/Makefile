RPMBUILD=	rpmbuild
RPMBUILD_X=	HOME="$(PWD)" $(RPMBUILD)

RPM_FILES=	.rpmmacros .rpmdb
RPM_DIRS=	SPECS SOURCES BUILD RPMS SRPMS

default: rpm

clean:
	rm -rf $(RPM_FILES) $(RPM_DIRS)

.rpmmacros: Makefile
	rm -f $@.tmp
	echo "%_topdir $(PWD)" >>$@.tmp
	echo "%_builddir $(PWD)/BUILD" >>$@.tmp
	echo "%_buildrootdir %{_builddir}" >>$@.tmp
	echo "%_tmppath %{_builddir}" >>$@.tmp
	echo "%in_source $(PWD)/.." >>$@.tmp
	mv $@.tmp $@

rpm_dirs:
	mkdir -p $(RPM_DIRS)

rpm: .rpmmacros rpm_dirs
	$(RPMBUILD_X) -bb nss_nameip_hosts.spec


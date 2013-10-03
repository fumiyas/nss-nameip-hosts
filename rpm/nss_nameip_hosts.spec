%define libc_ver %((rpm -q --qf '%%{version}' glibc 2>/dev/null || echo 2) |tail -n1)

Summary: NSS module for NameIP hostname <-> IP address resolution in AWS
Name: nss_nameip_hosts
Version: 0.0.1
Release: 1%{?dist}
URL: https://GitHub.com/fumiyas/nss-nameip-hosts
License: GPLv3
Group: System Environment/Base
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)

%if 0%{!?in_source:1}
Source0: nss-nameip-hosts-%{version}.tar.gz
%endif

%description
This is a Name Service Switch (NSS) module for NameIP hostname <->
IP address resolution in Amazon Web Service (AWS).

The "NameIP hostname" means hostnames in "prefix-IP-AD-DR-ESS.example.com"
format that are used for internal hostnames of virtual machines in AWS.
In AWS, internal hostnames are in "ip-10-X-Y-Z.*.compute.internal"
format that is assgined to an IPv4 address "10.X.Y.Z".

%prep
%if 0%{?in_source:1}
mkdir -p "%{_builddir}/%{name}-%{version}"
pushd "%{in_source}"
cp -rpL $(ls |grep -v '^rpm$') \
  "%{_builddir}/%{name}-%{version}/"
popd
%setup -q -T -D
%else
%setup -q
%endif

%build
make

%install
rm -rf %{buildroot}

libc_ver="%{libc_ver}"
libc_ver_major="${libc_ver%%%%.*}"

mkdir -p -m 0755 %{buildroot}/%{_lib}
install -p -m 0755 libnss_nameip_hosts.so \
  %{buildroot}/%{_lib}/libnss_nameip_hosts-$libc_ver.so
ln -s libnss_nameip_hosts-%{libc_ver}.so \
  %{buildroot}/%{_lib}/libnss_nameip_hosts.so.$libc_ver_major

%clean
rm -rf %{buildroot}

%files
%defattr(-,root,root)
%doc README.md COPYING
/%{_lib}/libnss_nameip_hosts-*.so
/%{_lib}/libnss_nameip_hosts.so.*

%changelog
* Wed Oct  2 2013 SATOH Fumiyasu <fumiyas at OSSTech Co., Japan> 0.0.1-1
- Initial release


hostaliases.so
==============

`hostaliases.so` is a little dynamic library that enhance the posix functions used to get address from hostname.

It adds the possibility to define string aliases to network address.

Currently instruments:

- getaddrinfo
- gethostbyname
- gethostbyname2
- gethostbyname_r
- gethostbyname2_r

Usage
------------

```
export HOSTALIASES=~/.hosts
echo "g www.google.com" >> ~/.hosts
LD_PRELOAD=/usr/lib/hostaliases.so curl g # This would redirect you to www.google.com
```

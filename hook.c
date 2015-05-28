#include "utils.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define __USE_GNU
#include <dlfcn.h>

/*
 *	Overrides real gethostbyname
 * */
struct hostent *gethostbyname(const char *name)
{
    // Load real gethostbyname function
    static struct hostent *(*gethostbyname_real) (const char *) = NULL;
    if (!gethostbyname_real)
	gethostbyname_real = dlsym(RTLD_NEXT, "gethostbyname");

    // Call real gethostbyname with resolved alias from HOSTALIASES variable
    const char *alias = resolveAlias(name);
    struct hostent *ret = gethostbyname_real(alias ? alias : name);
    return ret;
}

/*
 * Overrides real gethostbyname2
 * */
struct hostent *gethostbyname2(const char *name, int af)
{
    // Load real gethostbyname2 function
    static struct hostent *(*gethostbyname2_real) (const char *, int) =
	NULL;
    if (!gethostbyname2_real)
	gethostbyname2_real = dlsym(RTLD_NEXT, "gethostbyname2");

    // Call real gethostbyname2 with resolved alias from HOSTALIASES variable
    const char *alias = resolveAlias(name);
    struct hostent *ret = gethostbyname2_real(alias ? alias : name, af);
    return ret;
}

/*
 * Overrides real gethostbyaddr_r
 */

int
gethostbyname_r(const char *name,
		struct hostent *ret, char *buf, size_t buflen,
		struct hostent **result, int *h_errnop)
{
    // Load real gethostbyname_r function
    static int (*gethostbyname_r_real) (const char *,
					struct hostent *, char *, size_t,
					struct hostent **, int *) = NULL;
    if (!gethostbyname_r_real)
	gethostbyname_r_real = dlsym(RTLD_NEXT, "gethostbyname_r");

    // Call real gethostbyname_r with resolved alias from HOSTALIASES variable
    const char *alias = resolveAlias(name);
    int mret =
	gethostbyname_r_real(alias ? alias : name, ret, buf, buflen,
			     result,
			     h_errnop);
    return mret;
}

/*
 * Overrides real gethostbyaddr2_r
 */
int
gethostbyname2_r(const char *name, int af,
		 struct hostent *ret, char *buf, size_t buflen,
		 struct hostent **result, int *h_errnop)
{
    // Load real gethostbyname2_r function
    static int (*gethostbyname2_r_real) (const char *, int af,
					 struct hostent *, char *, size_t,
					 struct hostent **, int *) = NULL;
    if (!gethostbyname2_r_real)
	gethostbyname2_r_real = dlsym(RTLD_NEXT, "gethostbyname2_r");

    // Call real gethostbyname2_r with resolved alias from HOSTALIASES variable
    const char *alias = resolveAlias(name);
    int mret =
	gethostbyname2_r_real(alias ? alias : name, af, ret, buf, buflen,
			      result,
			      h_errnop);
    return mret;
}


/*
 * Overrides real getaddrinfo
 * */
int
getaddrinfo(const char *node, const char *service,
	    const struct addrinfo *hints, struct addrinfo **res)
{
    // Load real getaddrinfo function
    static int (*getaddrinfo_real) (const char *, const char *,
				    const struct addrinfo *,
				    struct addrinfo **) = NULL;
    if (!getaddrinfo_real)
	getaddrinfo_real = dlsym(RTLD_NEXT, "getaddrinfo");

    // Call real getaddrinfo with resolved alias from HOSTALIASES variable
    const char *alias = resolveAlias(node);
    int ret = getaddrinfo_real(alias ? alias : node, service, hints, res);
    return ret;
}

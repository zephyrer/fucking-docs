int inet_pton(int family, const char *strptr, void *addrptr)
{
	if (family == AF_INET) {
		struct in_addr in_val;
		
		/* converts a a dots-and-numbers format string 
		 * to a network address in a struct in_addr */
		if (!inet_aton(strptr, &in_val)) {	
			memcpy(addrptr, &in_val, sizeof(struct in_addr));
			return (1);
		}
		return (0);
	}
	errno = EAFNOSUPPORT;
	return (-1);
}
int i;
struct ifaddrs *ifap, *ifa;


    getifaddrs(&ifap);
    char *net_mask = NULL; 
    int buffer_size = 200;
    char *ifa_addr = NULL;

    for (ifa = ifap; ifa; ifa = ifa->ifa_next)
    {
        struct sockaddr_in *ifan = (struct sockaddr_in *) ifa->ifa_netmask; //interface netmask
        struct sockaddr_in *ifaa_in = (struct sockaddr_in*)ifa->ifa_addr; //interface address

        //same as above with the exception that it is for ipv6
        struct sockaddr_in6 *ifan6 = (struct sockaddr_in6 *) ifa->ifa_netmask;
        struct sockaddr_in6 *ifaa_in6 = (struct sockaddr_in6*)ifa->ifa_addr;
        char *prevNet_mask = net_mask;
        net_mask = (char*)calloc(buffer_size, sizeof(char*));
        ifa_addr = (char*)calloc(buffer_size, sizeof(char*));

        inet_ntop(ifa->ifa_addr->sa_family,ifa->ifa_addr->sa_family == AF_INET?(void*)&ifan->sin_addr : (void*)&ifan6->sin6_addr, net_mask, buffer_size);
        inet_ntop(ifa->ifa_addr->sa_family, ifa->ifa_addr->sa_family == AF_INET?(void*)&ifaa_in->sin_addr: (void*)&ifaa_in6->sin6_addr ,ifa_addr , buffer_size);
        printf("Interface: %s\tNetMask: %s", ifa->ifa_name, net_mask);

        //space evenly
        int num_spaces = strlen(net_mask) - 40;
        if(num_spaces < 0) num_spaces *= -1;
        for(i = 0; i <num_spaces;i++) printf(" ");

        printf("Address: %s\n",ifa_addr);
    }

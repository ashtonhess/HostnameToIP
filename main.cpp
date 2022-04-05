#include <iostream>
using namespace std;
#include <stdlib.h>
#include <stdio.h>

#include <string>
#include<vector>
#include <algorithm>
#include <cstring>

#include <sys/socket.h>
#include <netinet/in.h>//sockaddr_in
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#define SERVER_PORT 11328


int sock=0;
//string addy="127.0.0.1";//setting addy to the local loopback IP addy
//string addy="192.168.15.118";
string addy="35.129.56.107";
//string addy="cuppong.hessdevelopments.com";   //THIS SHOULD WORK...
const char *addyChar=addy.c_str();
struct sockaddr_in sockAddy;

int hostname_to_ip(char *hostname , char *ip);

int main(int argc, char*argv[]) {

    //int result;
    string hostnameString="cuppong.hessdevelopments.com";
    char *hostname= const_cast<char *>(hostnameString.c_str());
    char ip[100];
    hostname_to_ip(hostname, ip);
    cout<<"hostname: "<<hostname<<endl<<"ip: "<<ip<<endl;

    return 0;

}
int hostname_to_ip(char *hostname , char *ip)
{
    //int sockfd;
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_in *h;
    int rv;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; // use AF_INET6 to force IPv6
    hints.ai_socktype = SOCK_STREAM;

    if ( (rv = getaddrinfo( hostname , "http" , &hints , &servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and connect to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next)
    {
        //cout<<"for loop"<<endl;
        h = (struct sockaddr_in *) p->ai_addr;
        strcpy(ip , inet_ntoa( h->sin_addr ) );
    }

    freeaddrinfo(servinfo); // all done with this structure
    return 0;
}
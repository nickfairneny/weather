#include <stdio.h>
#include <libsocket/libinetsocket.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    // Connect to http://aerisweather.com
    int fd = create_inet_stream_socket("api.aerisapi.com", "80", LIBSOCKET_IPv4, 0);
    if (fd == -1)
    {
        printf("Can't connect to service");
        exit(1);
    }
    
    char request[100];
    printf("Enter zip code: ");
    scanf("%s", request);
    
    // Open the socket number (fd) as a FILE
    FILE *f = fdopen(fd, "rb+");
    if (!f)
    {
        printf("Can't open file\n");
        exit(1);
        
    }
    
    // Send GET request to web server
    fprintf(f, "GET /observations/%s?client_id=wQhXMMnxoRV4HNKoRLZrL&client_secret=rUOW0GEyf5bT9JhUzro2WQAuUpj3A7nFHgVCRGEK HTTP/1.0\n", request);
    fprintf(f, "Host: api.aerisapi.com\n");
    fprintf(f, "\n");
    
    char line[1000];
   
    while (fgets(line, 1000, f) != NULL)
    {
        char * start = strstr(line, "<p>");
        if (start == NULL)
            continue;   // Not interested in lines that don't have <p>
        char * end = strstr(line, "<\\/p>");
        *end = '\0';
        
        printf("%s", start+3);
    }
    
    fclose(f);
}
#include <stdio.h>
#include <libsocket/libinetsocket.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

int main(int argc, char *argv[])
{
    // Connect to http://aerisweather.com
    int fd = create_inet_stream_socket("api.aerisapi.com", "80", LIBSOCKET_IPv4, 0);
    if (fd == -1)
    {
        printf("Can't connect to service");
        exit(1);
    }
    
    char *request = argv[1];

    // Open the socket number (fd) as a FILE
    FILE *f = fdopen(fd, "rb+");
    if (!f)
    {
        printf("Can't open file\n");
        exit(1);
        
    }
    
    // Send GET request to web server
    fprintf(f, "GET /observations/%s?client_id=zQruYC9BuiOUMIQdmrNHR&client_secret=5ccOm2fWy9EUsKuUKps1STxD7MtLFLOYrMLYo7Ip HTTP/1.0\n", request);
    fprintf(f, "Host: api.aerisapi.com\n");
    fprintf(f, "\n");
    
    char line[20000];
    char *location;
    char *windspeedstart;
    char *windspeed;
    char *winddirection;
    char *humidity;
    char *temperature;
    char *state;
    char *city;
    char *datetime;
    char *rawtime;
    
    while (fgets(line, 20000, f) != NULL)
    {
        
         //wind direction
        if (strstr(line, "windDir")!=NULL) 
        { 
            winddirection = (strstr(line, "windDir") + 27); 
             
        }
    
        if (strstr(line, "windGustKTS")!= NULL)
        {
            *(strstr(line, "windGustKTS" ) - 3) = '\0';
        }
        
        //windspeed
        if (strstr(line, "windMPH")!=NULL) 
        { 
            windspeedstart = (strstr(line, "windMPH") + 9); 
   
        }
    
        if (strstr(line, "windSpeedKTS")!= NULL)
        {
            *(strstr(line, "windSpeedKTS" ) - 2) = '\0';
        }
        
        //humidity
        if (strstr(line, "humidity")!=NULL) 
        { 
            humidity = (strstr(line, "humidity") + 10); 
            
        }
    
        if (strstr(line, "pressureMB")!= NULL)
        {
            *(strstr(line, "pressureMB" ) - 2) = '\0';
        }
        
        //temperature
        if (strstr(line, "tempF")!=NULL) 
        { 
           temperature = (strstr(line, "tempF") + 7); 
            
        }
    
        if (strstr(line, "dewpointC")!= NULL)
        {
            *(strstr(line, "dewpointC" ) - 2) = '\0';
        }
        
        //date and time
        if (strstr(line, "obDateTime")!=NULL) 
        { 
           datetime = (strstr(line, "obDateTime") + 13); 
            
        }
        
        if (strstr(line, "dateTimeISO")!= NULL)
        {
            *(strstr(line, "dateTimeISO" ) - 32) = '\0';
        }
        
        //raw time
        if (strstr(line, "obTimestamp")!=NULL) 
        { 
           rawtime = (strstr(line, "obTimestamp") + 13); 
            
        }
        
        if (strstr(line, "obDateTime")!= NULL)
        {
            *(strstr(line, "obDateTime" ) - 2) = '\0';
        }
        
        //state
        if (strstr(line, "state")!=NULL) 
        { 
           state = (strstr(line, "state") + 8); 
            
        }
    
        if (strstr(line, "country")!= NULL)
        {
            *(strstr(line, "country" ) - 3) = '\0';
        }
        
        //city
        if (strstr(line, "name")!=NULL) 
        { 
           city = (strstr(line, "name") + 7); 
            
        }
    
        if (strstr(line, "state")!= NULL)
        {
            *(strstr(line, "state" ) - 3) = '\0';
        }
       
    }
    
    time_t t;
    t = (time_t) atoll(rawtime);
    struct tm *info;
    info = localtime( &t );
    
    //printf("time test: %s", asctime(info));
    
    
     /*
    char st1 = state[0];
    char st2 = state[1];
    printf("%c%c\n", toupper(st1), toupper(st2));
    
    printf("WINDSPEED: %s\n", windspeedstart);
    printf("WIND DIRECTION: %s\n", winddirection);
    printf("HUMIDITY: %s %%\n", humidity);
    printf("TEMPERATURE: %s F\n", temperature);
    printf("STATE: %s\n", state);
    printf("CITY: %s\n", city);
    printf("DATE/TIME: %s\n", datetime);
    printf("RAW TIME: %s\n", rawtime);
    */
    
    fclose(f);
}    
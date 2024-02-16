from socket import *
#類似using namespace 的效果，引入多函式庫時要謹慎使用，避免不同庫裡有相同函式

serverPort=12345    
serverSocket = socket(AF_INET, SOCK_STREAM)

serverSocket.bind(('', serverPort)) #socket綁定地址及port,空為自定義
serverSocket.listen(5) #backlog
print ('socket port is ', serverPort)

while True:

	print ('Ready to connect!')

	connectionSocket, addr =serverSocket.accept() #

	try:

		message =connectionSocket.recv(2048) #有list不夠大或者沒收到的問題

		filename = message.split()[1] #從接收到的訊息用以空格做分割，取欄位1也就是檔案名稱
		
		f = open(filename[1:]) #前面有一個/捨去後全拿，可以得檔案並打開

		outputdata =f.read() #讀取檔案完整內容
		print (outputdata) #確認讀取有無正確
		
		connectionSocket.send('\nHTTP/1.1 200 OK\n\n'.encode())   #200 OK為HTTP狀態碼，表正常，與下列幾行編織成一個html

		for i in range(0, len(outputdata)):
			connectionSocket.send(outputdata[i].encode())
            
		connectionSocket.send("\r\n".encode())    #CRLF
		connectionSocket.close()

	except IOError:
		connectionSocket.send("\nHTTP/1.1 404 Not Found\n\n".encode())    #與200 OK相反，404為錯誤碼
		
		connectionSocket.close()


#pragma once


#define DEFAULT_PORT "12345" 
#define DEFAULT_BUFFER_LENGTH	512
struct message_buffer_info {
	int type;//1 post mp4, 2 send mp4 file , 3 remote get file,
	long offset;
	long length;
};

struct content_buffer {
	char *buffer;
};

enum {
	postvideo = 1001,
	sendfile = 1002,//2
	getfile = 1003,//3
	byebye = 1004,//4
	seekfile = 1005//4
};
class TCP_Client {
public:
	TCP_Client(char* servername);
	bool Start(); 

	// Free the resouces
	void Stop();

	// Send message to server
	bool Send(char* szMsg);
	// Send message to server
	bool Send(char* szMsg, long size);
	// Receive message from server
	int Recv(char *msgRecv);
	int Recv(char *msgRecv, int size);
	int Select();
	SOCKET getSocket();
private:
	char* szServerName;
	SOCKET ConnectSocket;
};


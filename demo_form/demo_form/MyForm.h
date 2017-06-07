#pragma once
#include <Shlobj.h>
#include <Commdlg.h>
#include <iostream>
#include <fstream>
#include <xstring>
#include <string>
#include <msclr\marshal_cppstd.h>
#include "tcp_client.h"
#include <windows.h>
#include <shellapi.h>
#include "MyForm_progress.h"

#pragma comment(lib,"Comdlg32.lib")
#pragma comment(lib,"shell32.lib")
#pragma comment(lib,"user32.lib")
#using <System.dll> 
#using <System.Windows.Forms.dll> 
#using <System.Drawing.dll>

namespace demo_form {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;

	using namespace std;
	

	std::string fileName = "";
	std::string remoteIp ="127.0.0.1";
	TCP_Client  tcp_client_conn("127.0.0.1");

	
	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();

			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  push;

	private: System::Windows::Forms::TextBox^  IP_remote;
	protected:




	private: System::Windows::Forms::TextBox^  sendfilename;

	private: Thread^ pushThread;
	private: Thread^ pushProgressThread;
	private: MyFormProgress^ pushProgress;
	private: System::Windows::Forms::Timer^ time;
	private: int position;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;

	private: System::Windows::Forms::Button^  select;

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->push = (gcnew System::Windows::Forms::Button());
			this->IP_remote = (gcnew System::Windows::Forms::TextBox());
			this->sendfilename = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->select = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// push
			// 
			this->push->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->push->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->push->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->push->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->push->Location = System::Drawing::Point(259, 171);
			this->push->Name = L"push";
			this->push->Size = System::Drawing::Size(90, 47);
			this->push->TabIndex = 0;
			this->push->Text = L"Play";
			this->push->UseVisualStyleBackColor = false;
			this->push->Click += gcnew System::EventHandler(this, &MyForm::push_Click);
			// 
			// IP_remote
			// 
			this->IP_remote->Location = System::Drawing::Point(131, 54);
			this->IP_remote->Name = L"IP_remote";
			this->IP_remote->Size = System::Drawing::Size(260, 26);
			this->IP_remote->TabIndex = 2;
			this->IP_remote->Text = L"10.250.52.66";
			this->IP_remote->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox1_TextChanged);
			// 
			// sendfilename
			// 
			this->sendfilename->Location = System::Drawing::Point(131, 114);
			this->sendfilename->Name = L"sendfilename";
			this->sendfilename->Size = System::Drawing::Size(260, 26);
			this->sendfilename->TabIndex = 4;
			this->sendfilename->Text = L"Open a local file...";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(34, 60);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(91, 20);
			this->label1->TabIndex = 6;
			this->label1->Text = L"IP Address:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(41, 117);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(84, 20);
			this->label2->TabIndex = 7;
			this->label2->Text = L"File Name:";
			this->label2->Click += gcnew System::EventHandler(this, &MyForm::label2_Click);
			// 
			// select
			// 
			this->select->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->select->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->select->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->select->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->select->Location = System::Drawing::Point(131, 171);
			this->select->Name = L"select";
			this->select->Size = System::Drawing::Size(87, 46);
			this->select->TabIndex = 9;
			this->select->Text = L"Open";
			this->select->UseVisualStyleBackColor = false;
			this->select->Click += gcnew System::EventHandler(this, &MyForm::select_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->ClientSize = System::Drawing::Size(461, 282);
			this->Controls->Add(this->select);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->sendfilename);
			this->Controls->Add(this->IP_remote);
			this->Controls->Add(this->push);
			this->Name = L"MyForm";
			this->Text = L"Play Video File Demo";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		private:System::Void InitializeProgressBar(){
			
				this->pushProgressThread =
				gcnew Thread(gcnew ThreadStart(this, &MyForm::IncreaseProgressBar));

			this->pushProgressThread->Start();


		}
		private:System::Void DestroyeProgressBarForCancel() {

			//this->pushProgress->Hide();

			this->pushProgressThread->Interrupt();


		}
	private:System::Void IncreaseProgressBar() {
		this->pushProgress = gcnew MyFormProgress();
		//pushProgress->setProgress(0);
		this->pushProgress->ShowDialog();
		this->pushProgress->BringToFront();

		//pushProgress->setProgress(position);
	}
		// This method is executed on the worker thread and makes  
		// an safe call on the TextBox control.  
		private: System::Void real_push()
		{
			msclr::interop::marshal_context context;
			remoteIp = context.marshal_as<std::string>(this->IP_remote->Text);

			tcp_client_conn = TCP_Client(((char *)remoteIp.c_str()));
			bool ret = false;
			int retry = 10;
			do
			{
				ret = tcp_client_conn.Start();
				if (!ret)
				{
					retry--;
					if (retry == 0)
						return;
					Sleep(200);
				}
			} while (!ret);
			message_buffer_info messageCmd;
			content_buffer sendBuffer;
			//sendBuffer.buffer = NULL;

			int cmdLength = sizeof(struct message_buffer_info);

			message_buffer_info revCmd;
			std::fstream myfile(fileName, std::ios::in | std::ios::binary | std::ios::ate);
			std::streampos end = myfile.tellg();
			myfile.seekg(0, std::ios::beg);
			std::streampos start = myfile.tellg();
			long fileLength = (long)(end - start);
			long fileRemaining = fileLength;
			long fileSendingMaxL = 14600;
			long fileSendingL = fileSendingMaxL;
			long requestFileLength = 0;
			long fileOffset = 0;

			messageCmd.type = htonl(postvideo);// cmd
			messageCmd.offset = 0;
			messageCmd.length = htonl(fileLength);


			char *cmdBuf = new char[cmdLength];
			//cout << "cmdLength = " << cmdLength;
			::memcpy(cmdBuf, &messageCmd, cmdLength);

			if (ret)
			{
				ret = tcp_client_conn.Send(cmdBuf, cmdLength);//send post video request
				if (ret == false)
				{
					delete cmdBuf;
					return;
				}
			}

			char *recvBuf = new char[cmdLength];
			
			InitializeProgressBar();

			while (ret && stopPush == false) {
				int result = tcp_client_conn.Select();
				if (result < 0)
				{
					break;
				}
				else if (result <= 0)
				{
					continue;
				}
				else
				{
					memset(recvBuf, 0, cmdLength);
					int recL = tcp_client_conn.Recv(recvBuf, cmdLength);
					if (recL == cmdLength) {
						::memcpy(&revCmd, recvBuf, cmdLength);

						if (ntohl(revCmd.type) == seekfile) {
							fileOffset = ntohl(revCmd.offset);
							if (fileOffset < fileLength) {
								myfile.seekg(fileOffset, std::ios::beg);
								fileRemaining = fileLength - fileOffset;
							}
							else
							{
								break;//wrong fileseek
							}
							//myfile.seekg(0, fileOffset);
						}
						else if (ntohl(revCmd.type) == byebye) {
							break;

						}
						else if (ntohl(revCmd.type) == getfile) {
							requestFileLength = ntohl(revCmd.length);
							int offset = ntohl(revCmd.offset);

							if (requestFileLength > 0 && offset == fileOffset)
							{

								fileSendingL = min(requestFileLength, fileRemaining);
								messageCmd.type = htonl(sendfile);// cmd
								messageCmd.offset = htonl(fileOffset);
								messageCmd.length = htonl(fileSendingL);
								::memcpy(cmdBuf, &messageCmd, cmdLength);
								
							//	position = (int )( (fileLength - fileRemaining)*100/fileLength);

							//	pushProgress->setProgress(position);
								if (ret)
								{
									ret = tcp_client_conn.Send(cmdBuf, cmdLength);
									if (ret == false)
									{
										delete cmdBuf;
										return;
									}

									sendBuffer.buffer = new char[fileSendingL];
									myfile.read(sendBuffer.buffer, fileSendingL);

									ret = tcp_client_conn.Send(sendBuffer.buffer, fileSendingL);
									if (ret == false)
									{
										break;
									}

									fileRemaining -= fileSendingL;
									
									if (sendBuffer.buffer != NULL)
									{
										delete sendBuffer.buffer;
										sendBuffer.buffer = NULL;
									}

									if (fileRemaining <= 0)
									{
										//myfile.seekg(0, ios::beg);
										//fileRemaining = fileLength;
										continue;
									}

								}
							}
							else
							{
								std::cout << "request invalid file length";
							}
						}

					}
				}

			}

			//play_local_video(hWnd, fileName);
			messageCmd.type = htonl(byebye);// cmd
			messageCmd.offset = htonl(0);
			messageCmd.length = htonl(0);
			::memcpy(cmdBuf, &messageCmd, cmdLength);
			tcp_client_conn.Send(cmdBuf, cmdLength);


			if (cmdBuf != NULL) {
				delete cmdBuf;
				cmdBuf = NULL;
			}
			if (recvBuf != NULL) {
				delete recvBuf;
				recvBuf = NULL;
			}
			if (sendBuffer.buffer != NULL) {
				//delete sendBuffer.buffer;
				//sendBuffer.buffer = NULL;
			}
			DestroyeProgressBarForCancel();
						
			tcp_client_conn.Stop();
			myfile.close();
		};
		delegate
			void start_pushDelegate();
	private: System::Void start_push()
	{
		stopPush = false;
		if (this->push->InvokeRequired)
		{
			start_pushDelegate^ dl=
				gcnew start_pushDelegate(this, &MyForm::start_push);
			this->BeginInvoke(dl);
		}
		else
		{
			real_push();
		}
	}
	private: System::Void push_Click(System::Object^  sender, System::EventArgs^  e) {
			this->pushThread =
				gcnew Thread(gcnew ThreadStart(this, &MyForm::start_push));
			this->pushThread->Start();
	}
		

	private: System::Void stop_Click(System::Object^  sender, System::EventArgs^  e) {
		stopPush = true;
		if( (tcp_client_conn.getSocket() == INVALID_SOCKET))
		{
			return;
		}
		message_buffer_info messageCmd;
		
		int cmdLength = sizeof(struct message_buffer_info);
		char *cmdBuf = new char[cmdLength];
		messageCmd.type = htonl(byebye);// cmd
		messageCmd.offset = htonl(0);
		messageCmd.length = htonl(0);
		::memcpy(cmdBuf, &messageCmd, cmdLength);
		tcp_client_conn.Send(cmdBuf, cmdLength);


		if (cmdBuf != NULL) {
			delete cmdBuf;
			cmdBuf = NULL;
		}

		tcp_client_conn.Stop();
	}
	private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		
	}

private: System::Void select_Click(System::Object^  sender, System::EventArgs^  e) {
	OPENFILENAME ofn = { 0 };
	TCHAR strFilename[MAX_PATH] = { 0 };//用于接收文件名
	ofn.lStructSize = sizeof(OPENFILENAME);//结构体大小
	ofn.hwndOwner = NULL;//拥有着窗口句柄，为NULL表示对话框是非模态的，实际应用中一般都要有这个句柄
	ofn.lpstrFilter = TEXT("all\0*.*\0C/Video Flie\0*.mp4;*.h264;*.3gp\0\0");//设置过滤
	ofn.nFilterIndex = 1;//过滤器索引
	ofn.lpstrFile = strFilename;//接收返回的文件名，注意第一个字符需要为NULL
	ofn.nMaxFile = sizeof(strFilename);//缓冲区长度
	ofn.lpstrInitialDir = NULL;//初始目录为默认
	ofn.lpstrTitle = TEXT("Please choose video file");//使用系统默认标题留空即可
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;//文件、目录必须存在，隐藏只读选项
	if (GetOpenFileName(&ofn))
	{
		//MessageBox(NULL, strFilename, TEXT("The video file to send"), 0);
	}
	else {
		::MessageBox(NULL, TEXT("No file open !"), NULL, MB_ICONERROR);
		return;
	}
	fileName = TCHAR2STRING(strFilename);
	msclr::interop::marshal_context context;
	sendfilename->Text = context.marshal_as<System::String ^>(fileName);
	stopPush = false;
	return;
}
    std::string TCHAR2STRING(TCHAR *STR)
    {

			 int iLen = WideCharToMultiByte(CP_ACP, 0, STR, -1, NULL, 0, NULL, NULL);

			 char* chRtn = new char[iLen * sizeof(char)];

			 WideCharToMultiByte(CP_ACP, 0, STR, -1, chRtn, iLen, NULL, NULL);

			 std::string str(chRtn);

			 return str;

	}
private: System::Void label2_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void process1_Exited(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void statusStrip1_ItemClicked(System::Object^  sender, System::Windows::Forms::ToolStripItemClickedEventArgs^  e) {
}
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
}
};
}

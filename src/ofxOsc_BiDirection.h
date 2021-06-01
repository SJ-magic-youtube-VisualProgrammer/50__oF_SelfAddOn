/************************************************************
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"

#include "ofxOsc.h"

/* .a */
#include "sj_dotA.h"

/* dylib */
#include <dlfcn.h>
#include "sj_dylib.h"

/************************************************************
class
************************************************************/

/**************************************************
**************************************************/
class OSC_SEND{
private:
	enum{
		BUF_SIZE = 512,
	};
	
	char IP[BUF_SIZE];
	int Port;

	ofxOscSender sender;
	
	/****************************************
	noncopyable
	****************************************/
	void operator =(const OSC_SEND& src);
	OSC_SEND(const OSC_SEND& src);
	
	void _setup(const char* _IP, int _Port)
	{
		if(_Port != -1){
			sprintf(IP, "%s", _IP);
			Port = _Port;
			
			sender.setup(IP, Port);
		}
	}
	
public:
	OSC_SEND()
	: Port(-1)
	{
	}
	
	OSC_SEND(const char* _IP, int _Port)
	{
		_setup(_IP, _Port);
	}
	
	void setup(const char* _IP, int _Port)
	{
		_setup(_IP, _Port);
	}
	
	void sendMessage(ofxOscMessage &message, bool wrapInBundle = true)
	{
		if(Port != -1){
			sender.sendMessage(message, wrapInBundle);
		}
	}
};

/**************************************************
**************************************************/
class OSC_RECEIVE{
private:
	int Port;
	ofxOscReceiver	receiver;
	
	/****************************************
	noncopyable
	****************************************/
	void operator =(const OSC_RECEIVE& src);
	OSC_RECEIVE(const OSC_RECEIVE& src);
	
	void _setup(int _Port)
	{
		if(_Port != -1){
			Port = _Port;
			receiver.setup(Port);
		}
	}
	
public:
	OSC_RECEIVE()
	: Port(-1)
	{
	}
	OSC_RECEIVE(int _Port)
	{
		_setup(_Port);
	}
	
	void setup(int _Port)
	{
		_setup(_Port);
	}
	
	bool hasWaitingMessages()
	{
		if(Port == -1){
			return false;
		}else{
			return receiver.hasWaitingMessages();
		}
	}
	
	bool getNextMessage(ofxOscMessage& msg)
	{
		if(Port == -1)	return false;
		else			return receiver.getNextMessage(msg);
	}
	
	bool getNextMessage(ofxOscMessage* msg)
	{
		if(Port == -1)	return false;
		else			return receiver.getNextMessage(msg);
	}
};

/**************************************************
**************************************************/
class OSC_TARGET{
private:
	/****************************************
	noncopyable
	****************************************/
	void operator =(const OSC_TARGET& src);
	OSC_TARGET(const OSC_TARGET& src);
	
public:
	OSC_SEND	OscSend;
	OSC_RECEIVE	OscReceive;
	
	OSC_TARGET()
	{
	}
	
	OSC_TARGET(const char* _SendTo_IP, int _SendTo_Port, int _Receive_Port)
	: OscSend(_SendTo_IP, _SendTo_Port), OscReceive(_Receive_Port)
	{
	}
	
	void setup(const char* _SendTo_IP, int _SendTo_Port, int _Receive_Port)
	{
		OscSend.setup(_SendTo_IP, _SendTo_Port);
		OscReceive.setup(_Receive_Port);
	}
	
	
	void test_dotA()
	{
		sj_dotA obj;
		obj.HelloWorld("saijo");
	}
	
	void test_dylib()
	{
		//--------------------
		//--------------------
		// void* dylib_handle = dlopen("./libsj_dylib.dylib", RTLD_LAZY);
		void* dylib_handle = dlopen("libsj_dylib.dylib", RTLD_LAZY);
		if(dylib_handle == NULL){
			printf("> dylib open Error(NULL).\n");
			fflush(stdout);
			return 1;
		}else{
			printf("> dylib handle = %p\n", dylib_handle);
			fflush(stdout);
		}
		
		//--------------------
		// dlsym:シンボルをvoid*型として取り出す→ここでは関数ポインタを取り出している
		//--------------------
		IFCreator GetInterface = (IFCreator)dlsym(dylib_handle, "GetInterface");
		if(GetInterface == NULL){
			printf("> dlsym GetInterface Error: %s\n", dlerror());
			return 1;
		}
		
		IFDestructor DestroyInterface = (IFDestructor)dlsym(dylib_handle, "DestroyInterface");
		if(DestroyInterface == NULL){
			printf("> dlsym DestroyInterface Error: %s\n", dlerror());
			return 1;
		}
		
		//--------------------
		//--------------------
		sj_dylib* dylibIF = GetInterface();
		dylibIF->sj_execute();
		DestroyInterface(dylibIF);
	
		if(!dlclose(dylib_handle)){
			printf("> dlclose OK\n");
			fflush(stdout);
		}
		
		//--------------------
		//--------------------
		FILE* fp;
		fp = fopen("../../../dylib_Log.txt", "w");
		fprintf(fp, "dylib open succeeded.\n");
		fclose(fp);
	}
};



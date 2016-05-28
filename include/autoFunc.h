#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <uC++.h>

using namespace std;

typedef struct getopt_opc{
	string input_file;
	string output_file;
	int ntask;
	int size_buffer1;
	int size_buffer2;
}Options;

void usage();
Options get_variables(int, char**);

_Monitor bufferEng {
	int front, back, count, tamBuffer;
	string *elementos;
public:
	bufferEng(int largo);
	void insert(string nuevo);
	string remove();
	void destroy();
};

_Task Producer {
	bufferEng & buffer;
	string &namefile;
	int nTask;
private:
	void main();
public:
	Producer(bufferEng &buffer, string &file, int nTask);
};

_Task Consumer{
	bufferEng & bufferRead;
	bufferEng & bufferWrite;
private:
	void main();
public:
	Consumer(bufferEng &bufferR, bufferEng &bufferW);
	bool reconocer(string);
};

_Task outTask{
	bufferEng & buffer;
	string &namefile;
	int nTask;
private:
	void main();
public:
	outTask(bufferEng & buffer, string &file, int n);
};
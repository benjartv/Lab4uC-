#include "autoFunc.h"

void usage(){
	cout << "usage: exp \t-i input file" << endl;
	cout << "\t\t-o output file" << endl;
	cout << "\t\t-h number of task" << endl;
	cout << "\t\t-L size of buffer 1 (opc)" << endl;
	cout << "\t\t-l size of buffer 2 (opc)" << endl;
}

Options get_variables(int argc, char *argv[]){
	if (argc < 7){
		usage();
		exit(1);
	}
	Options variables;
	int i=0, o=0, h=0;
	variables.size_buffer1 = 10;
	variables.size_buffer2 = 10;
	int gopt;
	while((gopt = getopt(argc, argv, "ui:o:h:L:l:") ) != -1)
		switch(gopt){
			case 'u':
				usage();
				exit(1);
			case 'i':
				variables.input_file = optarg;
				i = 1;
				break;
			case 'o':
				variables.output_file = optarg;
				o = 1;
				break;
			case 'h':
				variables.ntask = atoi(optarg);
				h = 1;
				break;
			case 'L':
				variables.size_buffer1 = atoi(optarg);
				break;
			case 'l':
				variables.size_buffer2 = atoi(optarg);
				break;
			default:
				abort();
		}
	if (i == 0)
	{
		cout << "Error: missing input file" << endl;
		exit(1);
	}
	if (o == 0)
	{
		cout << "Error: missing output file" << endl;
		exit(1);
	}
	if (h == 0)
	{
		cout << "Error: missing task number" << endl;
		exit(1);
	}

	return variables;
}

bufferEng::bufferEng(int largo):front(0), back(0), count(0), tamBuffer(largo) {
	elementos = new string[largo];
}

void bufferEng::insert(string nuevo){
	if (count == tamBuffer){
		_Accept(remove);
	}
	elementos[back] = nuevo;
	back = (back+1)%tamBuffer;
	count += 1;
}
string bufferEng::remove(){
	if (count == 0){
		_Accept(insert);
	}
	string elem = elementos[front];
	front = (front+1)%tamBuffer;
	count -= 1;
	return elem;
}

void bufferEng::destroy(){
	delete [] elementos;
}

void Producer::main(){
	string expres;
	ifstream archivo;
	archivo.open(namefile.c_str());
	while(!archivo.eof()){
		expres = "";
		archivo >> expres;
		if (expres != ""){
			buffer.insert(expres);
			//cout << expres << endl;
		}
	}
	archivo.close();
	for (int i = 0; i < nTask; i++){
		buffer.insert("-1");
	}
}

Producer::Producer(bufferEng &buffer, string &file, int nTask) : buffer(buffer), namefile(file), nTask(nTask) {}

void Consumer::main(){
	string expresion;
	while(true){
		expresion = bufferRead.remove();
		if (expresion != "-1"){
			if (reconocer(expresion) == true){	
				expresion += " si";
				bufferWrite.insert(expresion);
			}
			else{
				expresion += " no";
				bufferWrite.insert(expresion);
			}
			
		}
		else{
			bufferWrite.insert("-1");
			break;
		}
	}
}

Consumer::Consumer(bufferEng &bufferR, bufferEng &bufferW): bufferRead(bufferR), bufferWrite(bufferW)  {}

bool Consumer::reconocer(string element){
	int state = 0;
	int largo = element.length();
	char c;
	for (int i = 0; i < largo; i++)
	{
		c = element[i];
		switch(state){
			case(0):{
				if (c == 'A'){
					state = 1;
				} else if (c == 'C'){
					state = 2;
				} else if (c == 'G'){
					state = 3;
				} else if (c == 'T'){
					state = 4;
				} else{
					return false;
				}
			}
			break;
			case(1):{
				if (c == 'A'){
					state = 1;
				} else if (c == 'C'){
					state = 2;
				} else if (c == 'G'){
					state = 3;
				} else if (c == 'T'){
					state = 4;
				} else{
					return false;
				}
			}
			break;
			case(2):{
				if (c == 'A'){
					state = 1;
				} else if (c == 'C'){
					state = 2;
				} else if (c == 'G'){
					state = 3;
				} else if (c == 'T'){
					state = 4;
				} else{
					return false;
				}
			}
			break;
			case(3):{
				if (c == 'A'){
					state = 1;
				} else if (c == 'C'){
					state = 5;
				} else if (c == 'G'){
					state = 3;
				} else if (c == 'T'){
					state = 6;
				} else{
					return false;
				}
			}
			break;
			case(4):{
				if (c == 'A'){
					state = 1;
				} else if (c == 'C'){
					state = 2;
				} else if (c == 'G'){
					state = 3;
				} else if (c == 'T'){
					state = 4;
				} else{
					return false;
				}
			}
			break;
			case(5):{
				if (c == 'A'){
					state = 1;
				} else if (c == 'C'){
					state = 5;
				} else if (c == 'G'){
					state = 3;
				} else if (c == 'T'){
					state = 6;
				} else{
					return false;
				}
			}
			break;
			case(6):{
				if (c == 'A'){
					state = 7;
				} else if (c == 'C'){
					state = 2;
				} else if (c == 'G'){
					state = 3;
				} else if (c == 'T'){
					state = 6;
				} else{
					return false;
				}
			}
			break;
			case(7):{
				if (c == 'A'){
					state = 8;
				} else if (c == 'C'){
					state = 2;
				} else if (c == 'G'){
					state = 3;
				} else if (c == 'T'){
					state = 4;
				} else{
					return false;
				}
			}
			break;
			case(8):{
				if (c == 'A'){
					state = 8;
				} else if (c == 'C'){
					state = 9;
				} else if (c == 'G'){
					state = 10;
				} else if (c == 'T'){
					state = 11;
				} else{
					return false;
				}
			}
			break;
			case(9):{
				if (c == 'A'){
					state = 1;
				} else if (c == 'C'){
					state = 9;
				} else if (c == 'G'){
					state = 10;
				} else if (c == 'T'){
					state = 11;
				} else{
					return false;
				}
			}
			break;
			case(10):{
				if (c == 'A'){
					state = 1;
				} else if (c == 'C'){
					state = 12;
				} else if (c == 'G'){
					state = 10;
				} else if (c == 'T'){
					state = 13;
				} else{
					return false;
				}
			}
			break;
			case(11):{
				if (c == 'A'){
					state = 1;
				} else if (c == 'C'){
					state = 9;
				} else if (c == 'G'){
					state = 10;
				} else if (c == 'T'){
					state = 11;
				} else{
					return false;
				}
			}
			break;
			case(12):{
				if (c == 'A'){
					state = 1;
				} else if (c == 'C'){
					state = 12;
				} else if (c == 'G'){
					state = 10;
				} else if (c == 'T'){
					state = 13;
				} else{
					return false;
				}
			}
			break;
			case(13):{
				if (c == 'A'){
					state = 7;
				} else if (c == 'C'){
					state = 9;
				} else if (c == 'G'){
					state = 10;
				} else if (c == 'T'){
					state = 13;
				} else{
					return false;
				}
			}
			break;
		}
	}
	cout << "State: " << state << endl;
	if (state >= 8){
		return true;
	}
	else{
		return false;
	}
}

void outTask::main(){
	string element;
	ofstream archivo;
	archivo.open(namefile.c_str());
	while(nTask > 0){
		element = buffer.remove();
		if (element == "-1"){
			nTask -= 1;
			if (nTask == 0){
				break;
			}
		}
		else{
			archivo << element << endl;
		}
	}
	archivo.close();
}

outTask::outTask(bufferEng & buffer, string &file, int n): buffer(buffer), namefile(file), nTask(n) {}
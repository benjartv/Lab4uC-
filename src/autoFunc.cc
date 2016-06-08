#include "autoFunc.h"


/*	void usage()
	Entrada: none
	Salida: none
	Func: imprime por stdout las diferentes opciones de uso del programa det
*/
void usage(){
	cout << "usage: exp \t-i input file" << endl;
	cout << "\t\t-o output file" << endl;
	cout << "\t\t-h number of task" << endl;
	cout << "\t\t-L size of buffer 1 (opc)" << endl;
	cout << "\t\t-l size of buffer 2 (opc)" << endl;
}

/*	Options get_variables(int argc, char *argv[])
	Entrada: cantidad de argumentos de ejecución del programa, argumentos de ejecución
	Salida: estructura con la información de los argumentos de ejecución
	Func: utilizando getopt() almecena los diferentes argumentos de ejecución en una
		estructura de datos
*/
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


//#################################################################################
//################################ Buffer Monitor #################################

/*	Funciones de insert y remove las que permiten agregar y sacar string del
	arreglo del monitor, utiliza scheduling externo para planificar las tareas.
*/

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


//#################################################################################
//######################### Tarea Productora ######################################

/*	Lee los string del archivo de entrada y los agrega al buffer monitor, cuando
	termina agrega tantos '-1' como tareas reconocedoras existan para avisarles
	que no quedan más string para procesar.
*/

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


//#################################################################################
//######################### Tarea  Consumidora ####################################

/*	Saca los string del buffer monitor y los analiza con la funcion reconocer(), en caso
	de que el string sea reconocido por la expresión regular se agrega un 'si' al final, en
	caso contrario un 'no'. Luego se inserta en el segundo buffer monitor, para que pueda
	ser escrito en el archivo de salida
	Cuando lee un '-1' significa que ya no hay que analizar más string, por tanto envia un '-1'
	a al segundo monitor (para avisar a la tarea escritora) y finaliza su ejecución
*/

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

/*	El automata tiene 13 estados y 6 de ellos son finales: 8, 9, 10, 11, 12, 13.
	En caso de que se llegue a un estado final luego de analizar el string la
	funcion retorna true, en caso contrario false
*/

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
					state = 9;
				} else if (c == 'C'){
					state = 10;
				} else if (c == 'G'){
					state = 11;
				} else if (c == 'T'){
					state = 12;
				} else{
					return false;
				}
			}
			break;
			case(9):{
				if (c == 'A'){
					state = 9;
				} else if (c == 'C'){
					state = 10;
				} else if (c == 'G'){
					state = 111;
				} else if (c == 'T'){
					state = 12;
				} else{
					return false;
				}
			}
			break;
			case(10):{
				if (c == 'A'){
					state = 13;
				} else if (c == 'C'){
					state = 10;
				} else if (c == 'G'){
					state = 11;
				} else if (c == 'T'){
					state = 12;
				} else{
					return false;
				}
			}
			break;
			case(11):{
				if (c == 'A'){
					state = 13;
				} else if (c == 'C'){
					state = 14;
				} else if (c == 'G'){
					state = 11;
				} else if (c == 'T'){
					state = 15;
				} else{
					return false;
				}
			}
			break;
			case(12):{
				if (c == 'A'){
					state = 13;
				} else if (c == 'C'){
					state = 10;
				} else if (c == 'G'){
					state = 11;
				} else if (c == 'T'){
					state = 12;
				} else{
					return false;
				}
			}
			break;
			case(13):{
				if (c == 'A'){
					state = 13;
				} else if (c == 'C'){
					state = 10;
				} else if (c == 'G'){
					state = 11;
				} else if (c == 'T'){
					state = 12;
				} else{
					return false;
				}
			}
			break;
			case(14):{
				if (c == 'A'){
					state = 13;
				} else if (c == 'C'){
					state = 14;
				} else if (c == 'G'){
					state = 11;
				} else if (c == 'T'){
					state = 15;
				} else{
					return false;
				}
			}
			break;
			case(15):{
				if (c == 'A'){
					state = 16;
				} else if (c == 'C'){
					state = 10;
				} else if (c == 'G'){
					state = 11;
				} else if (c == 'T'){
					state = 15;
				} else{
					return false;
				}
			}
			break;
			case(16):{
				if (c == 'A'){
					state = 17;
				} else if (c == 'C'){
					state = 10;
				} else if (c == 'G'){
					state = 11;
				} else if (c == 'T'){
					state = 12;
				} else{
					return false;
				}
			}
			break;
			case(17):{
				if (c == 'A'){
					state = 17;
				} else if (c == 'C'){
					state = 10;
				} else if (c == 'G'){
					state = 11;
				} else if (c == 'T'){
					state = 12;
				} else{
					return false;
				}
			}
			break;
		}
	}
	if (state >= 8){
		return true;
	}
	else{
		return false;
	}
}


//#################################################################################
//############################ Tarea Escritora ####################################

/*	Saca los elementos del buffer y los escribe en el archivo de salida, si lee un
	'-1' significa que se estan acabando los archivos de salida, mantiene un contador
	de '-1', cuando recibe tantos '-1' como tareas reconocedoras existan, significa que
	ya no quedan más string por escribir, finaliza su ejecución.

*/

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
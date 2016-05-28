#include "autoFunc.h"

void uMain::main(){

	Options variables = get_variables(argc, argv);
	bufferEng buffer1(variables.size_buffer1);
	bufferEng buffer2(variables.size_buffer2);

	Producer *taskP = new Producer(buffer1, variables.input_file, variables.ntask);
	Consumer *taskC[variables.ntask];
	for (int i = 0; i < variables.ntask; i++)
	{
		taskC[i] = new Consumer(buffer1, buffer2);
	}
	outTask *taskSalida = new outTask(buffer2, variables.output_file, variables.ntask);
	for (int i = 0; i < variables.ntask; i++)
	{
		delete taskC[i];
	}
	delete taskP;
	delete taskSalida;
	buffer1.destroy();
	buffer2.destroy();
}
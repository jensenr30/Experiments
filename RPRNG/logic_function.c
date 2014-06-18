#include <stdio.h>
#include "logic_function.h"

// this prints an error to file.
void error(char *errstr){
	FILE *err = fopen("error.txt", "a");
	fprintf(err, errstr);
	fclose(err);
}

// this prints an error to file.
void error_d(char *errstr, int data){
	FILE *err = fopen("error.txt", "a");
	fprintf(err, "%s\t%d",errstr, data);
	fclose(err);
}


/// this will set up a signal to draw its logic value from a certain bit in the variable "vDriver"
// returns 0 on success
// returns 1 on NULL signal
// returns 2 on NULL vDriver
// returns 3 on invalid bit outside range from [0 to LOGIC_VARIABLE_BITS-1]
short logic_signal_point_at_variable(struct logicSignal *signal, uint_fast64_t *vDriver, uint_fast8_t bit){
	
	// check to make sure all input data is valid and within range.
	if(signal == NULL){
		error("logic_signal_point_at_variable() was passed NULL logicSignal.");
		return 1;
	}
	if(vDriver == NULL){
		error("logic_signal_point_at_variable() was passed NULL vDriver.");
		return 2;
	}
	if(bit < 0|| bit >= LOGIC_VARIABLE_BITS){
		error_d("logic_signal_point_at_variable() was passed invalid bit. bit =", bit);
		return 3;
	}
	
	// copy variable adddress into the signal.
	signal->variableDriver = vDriver;
	// record the desired bit of the above data address.
	signal->bit = bit;
	
	// success
	return 0;
}



/// this will set up a signal to draw its logic value from a logic gate, "gDriver"
// returns 0 on success
// returns 1 on NULL signal
// returns 2 on NULL gDriver
short logic_signal_point_at_gate(struct logicSignal *signal, struct logicGate *gDriver){
	
	// check to make sure all input data is valid and within range.
	if(signal == NULL){
		error("logic_signal_point_at_variable() was passed NULL logicSignal.");
		return 1;
	}
	if(gDriver == NULL){
		error("logic_signal_point_at_variable() was passed NULL gDriver.");
		return 2;
	}
	
	// copy the address of the logicGate into the gateDriver pointer in the signal.
	signal->gateDriver = gDriver;
	
	// success
	return 0;
}




// returns either a 1 or a 0 always.
// it will return
uint_fast8_t logic_evaluate_signal(struct logicSignal *signal){
	
	
	// if the signal points to a logic gate,
	// return the value of the evaluating of a logic gate.
	if(signal->gateDriver != NULL)			return logic_evaluate_gate(signal->gateDriver);
	
	// if the signal points to a bit in a variable,
	// return the appropriate bit value (in the form of either a 0 or 1 value in the 0-bit place).
	else if(signal->variableDriver != NULL)	return (((*(signal->variableDriver))&(1<<signal->bit))>>(signal->bit));
	
	// if the signal points neither at a gate or a variable's bit, then just return 0.
	else{
		// report this as an error
		error("logic_evaluate_signal() was passed a signal that has no gate or variable input. returning a 0 value.");
		return 0;
	}
}


/// the will evaluate a logic gate (based on its inputs) and will return either a 1 (0x01) or a 0 (0x00)
// if there are no inputs, if a signal input is unconnected, the output of the gate will be determined as if that input was a logical 0 value.
uint_fast8_t logic_evaluate_gate(struct logicGate *gate){
	
	// evaluate both signals.
	// the logic_evaluate_signal() function will return 0 if either of the two input signals are invalid.
	uint_fast8_t x0 = logic_evaluate_signal(&(gate->inputSignal[0]));
	uint_fast8_t x1 = logic_evaluate_signal(&(gate->inputSignal[1]));
	
	// calculate the return value from this logic gate
	switch(gate->op){
		case lo_OR:
			return  (x0 | x1);
			break;
			
		case lo_AND:
			return  (x0 & x1);
			break;
			
		case lo_NOR:
			return ~(x0 | x1);
			break;
			
		case lo_NAND:
			return ~(x0 & x1);
			break;
			
		case lo_XOR:
			return  (x0 ^ x1);
			break;
			
		case lo_XNOR:
			return ~(x0 ^ x1);
			break;
			
		case lo_NOT:
			return ~x0;
			break;
			
		// if for some crazy reason, the operation isn't defined as one of the logic functions, then just return 0.
		default:
			return 0;
			break;
	}
	
	// this should never occur. But it is here to keep the compiler quiet.
	return 0;
}






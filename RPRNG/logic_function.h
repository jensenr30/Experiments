#include <stdint.h>
// there are three inputs to every logic function
//#define LOGICF_INPUT_BITS 6
// there are eight possible outputs for every logic function (2^3)
//#define LOGICF_OUTPUT_BITS 64

// this is the type of number that will be used to store function data
//typedef int_fast64_t logicf_f_type;
//typedef int_fast8_t logicf_o_type;

//#define LOGICF_1	((int_fast64_t)0x00000000)
//#define LOGICF_0	((int_fast64_t)0xffffffff)

// this stores information about a logic function

/* how to get an output from a logic function
	int index = 
	for(bit=1; b<LOGICF_INPUT_BITS; b*=2) index|evaluate

*/

/*
struct logicFunctionData{
	
	
	logicf_type f;
	
	// these are pointers to the three inputs, x[0], x[1], and x[2]
	struct logicFunctionData *x[LOGICF_INPUT_BITS];
	
	// this holds the current value of the output
	// output = f&(1<<(logic_evaluate(x[0]) + logic_evaluate(x[1])<<1 + logic_evaluate(x[2])<<2)) ONLY WHEN THE LOGIC UPDATE OCCURS! (on a clock cycle event)
	unsigned char output;
	
	// this is what the output will be when the next update, or "clock cycle" occurs.
	// this is used as temporary storage for 
	unsigned char outputBuffer;
	
	
};
*/

#define LOGIC_VARIABLE_BITS 64

// this is a logic signal. This is responsible for routing information between logic gates (and from certain bits in variables to logic gate inputs)
struct logicSignal {
	
	// this is a pointer to a gate that is acting as an output.
	// this points to the output of a logic gate.
	// if this is valid, that means this signal is being "gate driven."
	// if this is NULL, then the interpreter will check the variableDriven pointer.
	struct logicGate *gateDriver;
	
	// if this is valid (and gateDriven is NULL) then this signal is referred to as being "variable driven"
	// a certain bit will be picked from this variable and used as the signals logic level.
	// for example: logicSignal's output = (*variableDriver)&(1<<bit);
	uint_fast64_t *variableDriver;
	// this tells us what bit we want to look for in the 64 bit integer that the above pointer points to.
	uint_fast8_t bit;
	
};


/// lo stands for "logic operation"
// these are used in logic gate specification.
// Based on what number if stored in the op variable, a different operation will be performed on its signals.
// these numbers are derived from the truth tables of each logic function.
// for example,
	// NAND TRUTH TABLE
	// x0 x1 | y
	// ------|---
	//  0  0 | 1
	//  0  1 | 1
	//  1  0 | 1
	//  1  1 | 0
	// the number that is assigned the lo_NAND definition is 7 because 1*1 + 1*2 + 1*4 + 0*8 = 7 (derived from the right hand side of the truth table. the highest bit is the least significant.
	// logic_OR   is 0111 in binary (14 in decimal) (0x0e in hexadecimal)
	// logic_NOT  is 0101 in binary (5 in decimal) (0x05 in hexadecimal)
	// etc...				// MSB->LSB
#define lo_OR		0x0e	// 1110 (bin)
#define lo_AND		0x08	// 1000 (bin)
#define lo_NOR		0x01	// 0001 (bin)
#define lo_NAND		0x07	// 0111 (bin)
#define lo_XOR		0x06	// 0110 (bin)
#define lo_XNOR		0x09	// 1001 (bin)
#define lo_NOT		0x05	// 0101 (bin) NOT works on ONLY inputSignal[0]. inputSignal[1] is essentially ignored for this gate

// there are two input signals to any gate
#define LOGIC_GATE_INPUT_SIGNALS 2
/// this is a logic gate. 
struct logicGate {

	// this is the operation that will be carried out on the two operands
	uint_fast8_t op;
	
	// this is a pointer to a logicSignal.
	// A logic Signal can either be the output of another logicGate or a bit from a variable
	struct logicSignal inputSignal[LOGIC_GATE_INPUT_SIGNALS];
	
};




short logic_signal_point_at_variable(struct logicSignal *signal, uint_fast64_t *vDriver, uint_fast8_t bit);
short logic_signal_point_at_gate(struct logicSignal *signal, struct logicGate *gDriver);


uint_fast8_t logic_evaluate_signal(struct logicSignal *signal);
uint_fast8_t logic_evaluate_gate(struct logicGate *gate);
void logic_gate_test();



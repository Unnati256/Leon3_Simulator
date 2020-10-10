#ifndef REGISTER_H
#define REGISTER_H


class Register {
private:
	int registers[32];

public:
	Register();
	int getValue (int reg_address);// {return registers[reg_address];}
	void setValue (int reg_address, int value);
};


#endif
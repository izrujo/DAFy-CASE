#include "Registrar.h"

Registrar::Registrar() {
	Long i = 0;
	while (i < SHAPECOUNT) {
		this->lastNumbers[i] = 0;
		i++;
	}
}

Registrar::Registrar(const Registrar& source) {
	Long i = 0;
	while (i < SHAPECOUNT) {
		this->lastNumbers[i] = source.lastNumbers[i];
		i++;
	}
}

Registrar::~Registrar() {

}

Registrar& Registrar::operator=(const Registrar& source) {
	Long i = 0;
	while (i < SHAPECOUNT) {
		this->lastNumbers[i] = source.lastNumbers[i];
		i++;
	}

	return *this;
}

Long Registrar::Register(NShape *shape) {
	Long registrationNumber;
	Long index = -1;

	SHAPE id = shape->GetIdentify();
	switch (id) {
	case TERMINAL:
		index = 0;
		break;
	case PREPARATION:
		index = 1;
		break;
	case PROCESS:
		index = 2;
		break;
	case DECISION:
		index = 3;
		break;
	case INPUTOUTPUT:
		index = 4;
		break;
	case ARROW:
		index = 5;
		break;
	case LEFTDOWN:
		index = 6;
		break;
	case RIGHTDOWN:
		index = 7;
		break;
	case JOIN:
		index = 8;
		break;
	case REPEATTRUE:
		index = 9;
		break;
	case REPEATFALSE:
		index = 10;
		break;
	case RIGHTDOWNJOIN:
		index = 11;
		break;
	default:
		break;
	}

	registrationNumber = this->lastNumbers[index]++;
	shape->Register(registrationNumber);

	return registrationNumber;
}
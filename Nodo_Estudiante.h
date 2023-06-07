#pragma once
#include <string>
#include "Nodo.h"
class Nodo_Estudiante : public Nodo
{
public:
	Nodo_Estudiante* siguiente, * anterior;
	struct Estudiante {
		std::string codigo, nombre, ciudad;
		int edad;
	} estudiante;
	Nodo_Estudiante() : Nodo() {}
};


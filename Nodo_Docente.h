#pragma once
#include <string>
#include "Nodo.h"
class Nodo_Docente : public Nodo
{
public:
	Nodo_Docente* siguiente, * anterior;
	struct Docente {
		std::string codigo, nombre;
		int edad;
	} docente;
	int cantidad_asignaturas;
	class Nodo_Asignatura* siguiente_asignatura;
	Nodo_Docente() : Nodo(), cantidad_asignaturas(0) {}
};



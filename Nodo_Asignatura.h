#pragma once
#include <string>
#include "Nodo.h"
class Nodo_Asignatura : public Nodo
{
public:
	Nodo_Asignatura* siguiente, * anterior;
	struct Asignatura {
		std::string nombre, codigo, descripcion;
		int horas;
	} asignatura;
	int cantidad_estudiantes;
	class Nodo_Estudiante* siguiente_estudiante;
	Nodo_Asignatura() : Nodo(), siguiente_estudiante(nullptr), cantidad_estudiantes(0) {}
};


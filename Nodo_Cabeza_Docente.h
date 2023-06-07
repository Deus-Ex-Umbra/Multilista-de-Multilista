#pragma once
#include "Nodo.h"
class Nodo_Cabeza_Docente : public Nodo
{
public:
	class Nodo_Docente* siguiente_docente;
	int cantidad_docentes;
	Nodo_Cabeza_Docente() : Nodo(), siguiente_docente(nullptr), cantidad_docentes(0) {}
};


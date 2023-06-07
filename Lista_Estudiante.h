#pragma once
#include "Lista.h"
#include "Nodo_Estudiante.h"
#include "Nodo_Asignatura.h"
class Lista_Estudiante : public Lista
{
private:
	Nodo_Estudiante* nodo_inicial;
	Nodo_Estudiante* buscar(int _posicion, Nodo* _nodo = nullptr) override {
		int indice = 1;
		while (static_cast<Nodo_Estudiante*>(_nodo) != nullptr && indice != _posicion - 1) { indice++; _nodo = static_cast<Nodo_Estudiante*>(_nodo)->siguiente; }
		return static_cast<Nodo_Estudiante*>(_nodo);
	}
	Nodo_Estudiante* buscar(std::string _codigo, Nodo* _nodo = nullptr) override {
		while (static_cast<Nodo_Estudiante*>(_nodo) != nullptr && static_cast<Nodo_Estudiante*>(_nodo)->estudiante.codigo != _codigo) { _nodo = static_cast<Nodo_Asignatura*>(_nodo)->siguiente; }
		return static_cast<Nodo_Estudiante*>(_nodo);
	}
	virtual bool encontrar(Nodo* _nodo) override { return (static_cast<Nodo_Estudiante*>(_nodo) != nullptr); }
public:
	Lista_Estudiante() {}
	Lista_Estudiante(Nodo_Asignatura* _nodo) : nodo_inicial(new Nodo_Estudiante()) { _nodo->siguiente_estudiante = nodo_inicial; }
	virtual void insertar(int _posicion, Nodo* _nodo = nullptr) override {
		Nodo_Estudiante* nodo_nuevo = new Nodo_Estudiante();
		nodo_inicial = static_cast<Nodo_Asignatura*>(_nodo)->siguiente_estudiante;
		std::cout << "Ingrese el codigo del estudiante: "; std::getline(std::cin, nodo_nuevo->estudiante.codigo);
		std::cout << "Ingrese el nombre del estudiante: "; std::getline(std::cin, nodo_nuevo->estudiante.nombre);
		std::cout << "Ingrese la ciudad de origen del estudiante: "; std::getline(std::cin, nodo_nuevo->estudiante.ciudad);
		std::cout << "Ingrese la edad del estudiante: ";
		while (!(std::cin >> nodo_nuevo->estudiante.edad) || nodo_nuevo->estudiante.edad < 0) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "--------------------------------------------------------------------\n";
			std::cout << "Ingrese la edad del estudiante: ";
		}
		if (_posicion == 1 || vacia()) {
			static_cast<Nodo_Asignatura*>(_nodo)->siguiente_estudiante = nodo_nuevo;
			nodo_nuevo->siguiente = (vacia()) ? nullptr : nodo_inicial;
			if (nodo_nuevo->siguiente == nullptr) { nodo_inicial->anterior = nodo_nuevo; }
			nodo_nuevo->anterior = nullptr;
			nodo_inicial = nodo_nuevo;
		}
		else {
			Nodo_Estudiante* nodo_actual = nodo_inicial;
			nodo_actual = buscar(_posicion);
			nodo_nuevo->anterior = nodo_actual;
			nodo_nuevo->siguiente = nodo_actual->siguiente;
			nodo_actual->siguiente = nodo_nuevo;
			if (nodo_nuevo->siguiente != nullptr) { nodo_nuevo->siguiente->anterior = nodo_nuevo; }
		}
		std::cout << "Se ha insertado correctamente al estudiante.\n";
		static_cast<Nodo_Asignatura*>(_nodo)->cantidad_estudiantes++;
		std::cout << "--------------------------------------------------------------------\n";
	}
	virtual void eliminar(std::string _codigo, Nodo* _nodo = nullptr) override {
		nodo_inicial = static_cast<Nodo_Asignatura*>(_nodo)->siguiente_estudiante;
		Nodo_Estudiante* nodo_eliminar = nodo_inicial;
		nodo_eliminar = buscar(_codigo);
		if (encontrar(nodo_eliminar)) {
			if (nodo_eliminar->siguiente != nullptr) { nodo_eliminar->siguiente->anterior = nodo_eliminar->anterior; }
			if (nodo_eliminar->anterior != nullptr) { nodo_eliminar->anterior->siguiente = nodo_eliminar->siguiente; }
			if (nodo_eliminar == nodo_inicial) { nodo_inicial = nodo_eliminar->siguiente; static_cast<Nodo_Asignatura*>(_nodo)->siguiente_estudiante = nodo_inicial; }
			delete nodo_eliminar;
			std::cout << "Se ha eliminado correctamente al estudiante con código: " << _codigo << ".\n";
			static_cast<Nodo_Asignatura*>(_nodo)->cantidad_estudiantes--;
			std::cout << "--------------------------------------------------------------------\n"; return;
		}
		std::cout << "No se pudo eliminar al estudiante con código " << _codigo << " porque no existe en la lista.\n";
	}
	virtual void mostrar(Nodo* _nodo = nullptr, bool mostrar_siguiente = false, bool mostrar_siguiente_siguiente = false) override {
		nodo_inicial = static_cast<Nodo_Asignatura*>(_nodo)->siguiente_estudiante;
		Nodo_Estudiante* nodo_mostrar = nodo_inicial;
		int indice = 1;
		while (nodo_mostrar != nullptr) {
			std::cout << "Estudiante N°: " << indice++ << "\n";
			std::cout << "Código: " << nodo_mostrar->estudiante.codigo << "\n";
			std::cout << "Nombre: " << nodo_mostrar->estudiante.nombre << "\n";
			std::cout << "Ciudad: " << nodo_mostrar->estudiante.ciudad << "\n";
			std::cout << "Edad: " << nodo_mostrar->estudiante.edad << "\n";
			std::cout << "--------------------------------------------------------------------\n";
			nodo_mostrar = nodo_mostrar->siguiente;
		}
	}
	void mostrar_por_ciudad(std::string _ciudad , Nodo* _nodo = nullptr) {
		nodo_inicial = static_cast<Nodo_Asignatura*>(_nodo)->siguiente_estudiante;
		Nodo_Estudiante* nodo_mostrar = nodo_inicial;
		int indice = 1;
		while (nodo_mostrar != nullptr) {
			if (nodo_mostrar->estudiante.ciudad == _ciudad) {
				std::cout << "Docente N°: " << indice++ << "\n";
				std::cout << "Código: " << nodo_mostrar->estudiante.codigo << "\n";
				std::cout << "Nombre: " << nodo_mostrar->estudiante.nombre << "\n";
				std::cout << "Descripción: " << nodo_mostrar->estudiante.ciudad << "\n";
				std::cout << "Edad: " << nodo_mostrar->estudiante.edad << "\n";
				std::cout << "--------------------------------------------------------------------\n";
				nodo_mostrar = nodo_mostrar->siguiente;
			}
		}
	}
	virtual bool vacia(Nodo* _nodo = nullptr) override { return (static_cast<Nodo_Asignatura*>(_nodo)->siguiente_estudiante == nullptr); }
	virtual void eliminar_todo(Nodo* _nodo = nullptr) override {
		nodo_inicial = static_cast<Nodo_Asignatura*>(_nodo)->siguiente_estudiante;
		Nodo_Estudiante* nodo_eliminar = nodo_inicial;
		while (nodo_eliminar != nullptr) {
			nodo_inicial = nodo_eliminar->siguiente;
			delete nodo_eliminar;
			nodo_eliminar = nodo_inicial;
		}
	}
	virtual int numero_elementos(Nodo* _nodo = nullptr) override {
		return (static_cast<Nodo_Asignatura*>(_nodo)->cantidad_estudiantes);
	}
};


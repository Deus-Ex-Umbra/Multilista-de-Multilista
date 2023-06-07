#pragma once
#include "Lista.h"
#include "Lista_Asignatura.h"
#include "Nodo_Cabeza_Docente.h"
#include "Nodo_Docente.h"
class Lista_Docente : public Lista
{
private:
	Lista_Asignatura lista_asignatura;
	Nodo_Cabeza_Docente* nodo_cabeza;
	Nodo_Docente* nodo_inicial;
	Nodo_Docente* buscar(int _posicion, Nodo* _nodo = nullptr) override {
		int indice = 1;
		while (static_cast<Nodo_Docente*>(_nodo) != nullptr && indice != _posicion - 1) { indice++; _nodo = static_cast<Nodo_Docente*>(_nodo)->siguiente; }
		return static_cast<Nodo_Docente*>(_nodo);
	}
	Nodo_Docente* buscar(std::string _codigo, Nodo* _nodo = nullptr) override {
		while (static_cast<Nodo_Docente*>(_nodo) != nullptr && static_cast<Nodo_Docente*>(_nodo)->docente.codigo != _codigo) { _nodo = static_cast<Nodo_Docente*>(_nodo)->siguiente; }
		return static_cast<Nodo_Docente*>(_nodo);
	}
	virtual bool encontrar(Nodo* _nodo) override { return (static_cast<Nodo_Cabeza_Docente*>(_nodo) != nullptr); }
public:
	Lista_Docente() : nodo_cabeza(new Nodo_Cabeza_Docente()), nodo_inicial(new Nodo_Docente()) {}
	virtual void insertar(int _posicion, Nodo* _nodo = nullptr) override {
		Nodo_Docente* nodo_nuevo = new Nodo_Docente();
		std::cout << "Ingrese el codigo del docente: "; std::getline(std::cin, nodo_nuevo->docente.codigo);
		std::cout << "Ingrese el nombre del docente: "; std::getline(std::cin, nodo_nuevo->docente.nombre);
		std::cout << "Ingrese la edad del docente: ";
		while (!(std::cin >> nodo_nuevo->docente.edad) || nodo_nuevo->docente.edad < 0) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "--------------------------------------------------------------------\n";
			std::cout << "Ingrese la edad del docente: ";
		}
		if (_posicion == 1 || vacia()) {
			nodo_cabeza->siguiente_docente = nodo_nuevo;
			nodo_nuevo->siguiente = (vacia()) ? nullptr : nodo_inicial;
			if (nodo_nuevo->siguiente == nullptr) { nodo_inicial->anterior = nodo_nuevo; }
			nodo_nuevo->anterior = nullptr;
			nodo_nuevo->siguiente_asignatura = nullptr;
			nodo_inicial = nodo_nuevo;
		}
		else {
			Nodo_Docente* nodo_actual = nodo_inicial;
			nodo_actual = buscar(_posicion);
			nodo_nuevo->anterior = nodo_actual;
			nodo_nuevo->siguiente = nodo_actual->siguiente;
			nodo_actual->siguiente = nodo_nuevo;
			if (nodo_nuevo->siguiente != nullptr) { nodo_nuevo->siguiente->anterior = nodo_nuevo; }
			nodo_nuevo->siguiente_asignatura = nullptr;
		}
		nodo_cabeza->cantidad_docentes++;
		std::cout << "Se ha insertado correctamente al docente.\n";
		std::cout << "--------------------------------------------------------------------\n";
	}
	virtual void eliminar(std::string _codigo, Nodo* _nodo = nullptr) override {
		Nodo_Docente* nodo_eliminar = nodo_inicial;
		nodo_eliminar = buscar(_codigo);
		if (encontrar(nodo_eliminar)) {
			if (nodo_eliminar->siguiente != nullptr) { nodo_eliminar->siguiente->anterior = nodo_eliminar->anterior; }
			if (nodo_eliminar->anterior != nullptr) { nodo_eliminar->anterior->siguiente = nodo_eliminar->siguiente; }
			if (nodo_eliminar == nodo_inicial) { nodo_inicial = nodo_eliminar->siguiente; nodo_cabeza->siguiente_docente = nodo_inicial; }
			delete nodo_eliminar;
			std::cout << "Se ha eliminado correctamente al docente con código: " << _codigo << ".\n"; 
			nodo_cabeza->cantidad_docentes--;
			std::cout << "--------------------------------------------------------------------\n"; return;

		} 
		std::cout << "No se pudo eliminar al docente con código " << _codigo << " porque no existe en la lista.\n";
		std::cout << "--------------------------------------------------------------------\n";
	}
	virtual void mostrar(Nodo* _nodo = nullptr, bool mostrar_siguiente = false, bool mostrar_siguiente_siguiente = false) override {
		Nodo_Docente* nodo_mostrar = nodo_inicial;
		int indice = 1;
		while (nodo_mostrar != nullptr) {
			std::cout << "Docente N°: " << indice++ << "\n";
			std::cout << "Código: " << nodo_mostrar->docente.codigo << "\n";
			std::cout << "Nombre: " << nodo_mostrar->docente.nombre << "\n";
			std::cout << "Edad: " << nodo_mostrar->docente.edad << "\n";
			std::cout << "--------------------------------------------------------------------\n";
			if (mostrar_siguiente_siguiente) { lista_asignatura.mostrar(nodo_mostrar, true); }
			else { if (mostrar_siguiente) { lista_asignatura.mostrar(nodo_mostrar); } }
			nodo_mostrar = nodo_mostrar->siguiente;
		}
	}
	virtual bool vacia(Nodo* _nodo = nullptr) override {
		return (nodo_cabeza->siguiente_docente == nullptr);
	}
	/*Falta escribir*/
	virtual void eliminar_todo(Nodo* _nodo = nullptr) override {
		Nodo_Docente* nodo_eliminar = nodo_inicial;
		while (nodo_eliminar != nullptr) {
			nodo_inicial = nodo_eliminar->siguiente;
			lista_asignatura.eliminar_todo(nodo_eliminar);
			delete nodo_eliminar;
			nodo_eliminar = nodo_inicial;
		}
	}
	virtual int numero_elementos(Nodo* _nodo = nullptr) override {
		return (nodo_cabeza->cantidad_docentes);
	}
	void lista_de_asignaturas(std::string _codigo) {
		Nodo_Docente* nodo_buscar = nodo_inicial;
		nodo_buscar = buscar(_codigo);
		if (encontrar(nodo_buscar)) {
			int opcion, posicion;
			std::string codigo;
			do {
				system("cls");
				std::cout << "---------------------------------------------------------\n";
				std::cout << "****Lista de Asignaturas****\n";
				std::cout << "---------------------------------------------------------\n";
				std::cout << "1. Insertar Asignatura.\n";
				std::cout << "2. Eliminar Asignatura.\n";
				std::cout << "3. Mostrar Asignaturas.\n";
				std::cout << "4. Mostrar Asignaturas y Estudiantes.\n";
				std::cout << "5. Eliminar todo.\n";
				std::cout << "6. Salir.\n";
				std::cout << "---------------------------------------------------------\n";
				std::cout << "Ingrese una opción: ";
				while (!(std::cin >> opcion) || (opcion < 1 || opcion > 6)) {
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cout << "--------------------------------------------------------------------\n";
					std::cout << "Seleccione una opción válida: ";
				}
				std::cout << "---------------------------------------------------------\n";
				std::cin.ignore();
				if (nodo_buscar->siguiente_asignatura == nullptr) {
					Lista_Asignatura nueva_lista_asignatura(nodo_buscar);
					lista_asignatura = nueva_lista_asignatura;
				}
				switch (opcion)
				{
				case 1:
					std::cout << "**Se ingresará una Asignatura**\n";
					std::cout << "--------------------------------------------------------------------\n";
					std::cout << "Escriba la posición donde se ingresará la asignatura: "; 
					while (!(std::cin >> posicion) || (posicion < 1 || posicion > lista_asignatura.numero_elementos() + 1)) {
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						std::cout << "--------------------------------------------------------------------\n";
						std::cout << "Posición no válida: ";
					}
					std::cout << "--------------------------------------------------------------------\n";
					std::cin.ignore();
					lista_asignatura.insertar(posicion, nodo_buscar);
					break;
				case 2:
					std::cout << "**Se eliminará una Asignatura**\n";
					std::cout << "--------------------------------------------------------------------\n";
					std::cout << "Escriba el código de la asignatura que desea eliminar: "; std::getline(std::cin, codigo);
					lista_asignatura.eliminar(codigo, nodo_buscar);
					break;
				case 3:
					std::cout << "**Se mostrará la Lista de Asignatura**\n";
					std::cout << "--------------------------------------------------------------------\n";
					lista_asignatura.mostrar(nodo_buscar);
					system("pause");
					break;
				case 4:
					std::cout << "**Se mostrará la Lista de Asignatura y Estudiantes**\n";
					std::cout << "--------------------------------------------------------------------\n";
					lista_asignatura.mostrar(nodo_buscar, true);
					system("pause");
					break;
				case 5:
					std::cout << "**Se eliminará toda la Lista de Asignaturas**\n";
					std::cout << "--------------------------------------------------------------------\n";
					lista_asignatura.eliminar_todo(nodo_buscar);
					break;
				default:
					std::cout << "**Será retornado a la lista de docentes, gracias por usar el programa**\n";
					std::cout << "--------------------------------------------------------------------\n";
					return;
					break;
				}
			} while (true);
		}
		else {
			std::cout << "No se pudo encontrar la asignatura con código " << _codigo << " porque no existe en la lista.\n";
		}
	}
};


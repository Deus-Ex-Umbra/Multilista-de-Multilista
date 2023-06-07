#pragma once
#include "Lista.h"
#include "Lista_Estudiante.h"
#include "Nodo_Asignatura.h"
#include "Nodo_Docente.h"
class Lista_Asignatura : public Lista
{
private:
	Lista_Estudiante lista_estudiante;
	Nodo_Asignatura* nodo_inicial;
	Nodo_Asignatura* buscar(int _posicion, Nodo* _nodo = nullptr) override {
		int indice = 1;
		while (static_cast<Nodo_Asignatura*>(_nodo) != nullptr && indice != _posicion - 1) { indice++; _nodo = static_cast<Nodo_Asignatura*>(_nodo)->siguiente; }
		return static_cast<Nodo_Asignatura*>(_nodo);
	}
	Nodo_Asignatura* buscar(std::string _codigo, Nodo* _nodo = nullptr) override {
		while (static_cast<Nodo_Asignatura*>(_nodo) != nullptr && static_cast<Nodo_Asignatura*>(_nodo)->asignatura.codigo != _codigo) { _nodo = static_cast<Nodo_Asignatura*>(_nodo)->siguiente; }
		return static_cast<Nodo_Asignatura*>(_nodo);
	}
	virtual bool encontrar(Nodo* _nodo) override { return (static_cast<Nodo_Asignatura*>(_nodo) != nullptr); }
public:
	Lista_Asignatura() {}
	Lista_Asignatura(Nodo_Docente* _nodo) : nodo_inicial(new Nodo_Asignatura()) { _nodo->siguiente_asignatura = nodo_inicial; }
	virtual void insertar(int _posicion, Nodo* _nodo = nullptr) override {
		Nodo_Asignatura* nodo_nuevo = new Nodo_Asignatura();
		nodo_inicial = static_cast<Nodo_Docente*>(_nodo)->siguiente_asignatura;
		std::cout << "Ingrese el codigo de la asignatura: "; std::getline(std::cin, nodo_nuevo->asignatura.codigo);
		std::cout << "Ingrese el nombre de la asignatura: "; std::getline(std::cin, nodo_nuevo->asignatura.nombre);
		std::cout << "Ingrese la descripción de la asignatura: "; std::getline(std::cin, nodo_nuevo->asignatura.descripcion);
		std::cout << "Ingrese la cantidad de horas de la asignatura: ";
		while (!(std::cin >> nodo_nuevo->asignatura.horas) || nodo_nuevo->asignatura.horas < 1) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "--------------------------------------------------------------------\n";
			std::cout << "Ingrese la cantidad de horas de la asignatura: ";
		}
		if (_posicion == 1 || vacia()) {
			static_cast<Nodo_Docente*>(_nodo)->siguiente_asignatura = nodo_nuevo;
			nodo_nuevo->siguiente = (vacia()) ? nullptr : nodo_inicial;
			if (nodo_nuevo->siguiente == nullptr) { nodo_inicial->anterior = nodo_nuevo; }
			nodo_nuevo->anterior = nullptr;
			nodo_nuevo->siguiente_estudiante = nullptr;
			nodo_inicial = nodo_nuevo;
		}
		else {
			Nodo_Asignatura* nodo_actual = nodo_inicial;
			nodo_actual = buscar(_posicion);
			nodo_nuevo->anterior = nodo_actual;
			nodo_nuevo->siguiente = nodo_actual->siguiente;
			nodo_actual->siguiente = nodo_nuevo;
			if (nodo_nuevo->siguiente != nullptr) { nodo_nuevo->siguiente->anterior = nodo_nuevo; }
			nodo_nuevo->siguiente_estudiante = nullptr;
		}
		std::cout << "Se ha insertado correctamente la asignatura.\n";
		static_cast<Nodo_Docente*>(_nodo)->cantidad_asignaturas++;
		std::cout << "--------------------------------------------------------------------\n";
	}
	virtual void eliminar(std::string _codigo, Nodo* _nodo = nullptr) override {
		nodo_inicial = static_cast<Nodo_Docente*>(_nodo)->siguiente_asignatura;
		Nodo_Asignatura* nodo_eliminar = nodo_inicial;
		nodo_eliminar = buscar(_codigo);
		if (encontrar(nodo_eliminar)) {
			if (nodo_eliminar->siguiente != nullptr) { nodo_eliminar->siguiente->anterior = nodo_eliminar->anterior; }
			if (nodo_eliminar->anterior != nullptr) { nodo_eliminar->anterior->siguiente = nodo_eliminar->siguiente; }
			if (nodo_eliminar == nodo_inicial) { nodo_inicial = nodo_eliminar->siguiente; static_cast<Nodo_Docente*>(_nodo)->siguiente_asignatura = nodo_inicial; }
			delete nodo_eliminar;
			std::cout << "Se ha eliminado correctamente la asignatura con código: " << _codigo << ".\n"; 
			static_cast<Nodo_Docente*>(_nodo)->cantidad_asignaturas--;
			std::cout << "--------------------------------------------------------------------\n"; return;
		}
		std::cout << "No se pudo eliminar la asignatura con código " << _codigo << " porque no existe en la lista.\n";
	}
	virtual void mostrar(Nodo* _nodo = nullptr, bool mostrar_siguiente = false, bool mostrar_siguiente_siguiente = false) override {
		nodo_inicial = static_cast<Nodo_Docente*>(_nodo)->siguiente_asignatura;
		Nodo_Asignatura* nodo_mostrar = nodo_inicial;
		int indice = 1;
		while (nodo_mostrar != nullptr) {
			std::cout << "Asignatura N°: " << indice++ << "\n";
			std::cout << "Código: " << nodo_mostrar->asignatura.codigo << "\n";
			std::cout << "Nombre: " << nodo_mostrar->asignatura.nombre << "\n";
			std::cout << "Descripción: " << nodo_mostrar->asignatura.descripcion << "\n";
			std::cout << "Cantidad Horas: " << nodo_mostrar->asignatura.horas << "\n";
			if (mostrar_siguiente) { lista_estudiante.mostrar(nodo_mostrar); }
			std::cout << "--------------------------------------------------------------------\n";
			nodo_mostrar = nodo_mostrar->siguiente;
		}
	}
	virtual bool vacia(Nodo* _nodo = nullptr) override { return (static_cast<Nodo_Docente*>(_nodo)->siguiente_asignatura == nullptr); }
	virtual void eliminar_todo(Nodo* _nodo = nullptr) override {
		nodo_inicial = static_cast<Nodo_Docente*>(_nodo)->siguiente_asignatura;
		Nodo_Asignatura* nodo_eliminar = nodo_inicial;
		while (nodo_eliminar != nullptr) {
			nodo_inicial = nodo_eliminar->siguiente;
			lista_estudiante.eliminar_todo(nodo_eliminar);
			delete nodo_eliminar;
			nodo_eliminar = nodo_inicial;
		}
	}
	virtual int numero_elementos(Nodo* _nodo = nullptr) override {
		return (static_cast<Nodo_Docente*>(_nodo)->cantidad_asignaturas);
	}
	void lista_de_estudiantes (std::string _codigo) {
		Nodo_Asignatura* nodo_buscar = nodo_inicial;
		nodo_buscar = buscar(_codigo);
		if (encontrar(nodo_buscar)) {
			int opcion, posicion;
			std::string codigo;
			do {
				system("cls");
				std::cout << "---------------------------------------------------------\n";
				std::cout << "****Lista de Estudiantes****\n";
				std::cout << "---------------------------------------------------------\n";
				std::cout << "1. Insertar Estudiante.\n";
				std::cout << "2. Eliminar Estudiante.\n";
				std::cout << "3. Mostrar Estudiantes.\n";
				std::cout << "4. Mostrar Estudiantes por ciudad de origen.\n";
				std::cout << "5. Eliminar todo.\n";
				std::cout << "5. Salir.\n";
				std::cout << "---------------------------------------------------------\n";
				std::cout << "Ingrese una opción: ";
				while (!(std::cin >> opcion) || (opcion < 1 || opcion > 5)) {
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cout << "--------------------------------------------------------------------\n";
					std::cout << "Seleccione una opción válida: ";
				}
				std::cout << "---------------------------------------------------------\n";
				std::cin.ignore();
				if (nodo_buscar->siguiente_estudiante == nullptr) {
					Lista_Estudiante nueva_lista_estudiante(nodo_buscar);
					lista_estudiante = nueva_lista_estudiante;
				}
				switch (opcion)
				{
				case 1:
					std::cout << "**Se ingresará un Estudiante**\n";
					std::cout << "--------------------------------------------------------------------\n";
					while (!(std::cin >> posicion) || (posicion < 1 || posicion > lista_estudiante.numero_elementos() + 1)) {
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						std::cout << "--------------------------------------------------------------------\n";
						std::cout << "Posición no válida: ";
					}
					std::cout << "--------------------------------------------------------------------\n";
					std::cin.ignore();
					lista_estudiante.insertar(posicion, nodo_buscar);
					break;
				case 2:
					std::cout << "**Se eliminará un Estudiante**\n";
					std::cout << "--------------------------------------------------------------------\n";
					std::cout << "Ingrese el código del Estudiante que desea eliminar: "; std::getline(std::cin, codigo);
					lista_estudiante.eliminar(codigo, nodo_buscar);
					break;
				case 3:
					std::cout << "**Se mostrará la Lista de Estudiantes**\n";
					std::cout << "--------------------------------------------------------------------\n";
					lista_estudiante.mostrar(nodo_buscar);
					system("pause");
					break;
				case 4:
					std::cout << "**Se mostrará la lista de Estudiantes por ciudad de origen**\n";
					std::cout << "--------------------------------------------------------------------\n";
					std::cout << "Escriba la ciudad de origen de los estudiantes: "; std::getline(std::cin, codigo);
					lista_estudiante.mostrar_por_ciudad(codigo, nodo_buscar);
					system("pause");
					break;
				case 5:
					std::cout << "**Se eliminará toda la Lista de Estudiantes**\n";
					std::cout << "--------------------------------------------------------------------\n";
					lista_estudiante.eliminar_todo(nodo_buscar);
					break;
				default:
					std::cout << "**Será retornado a la lista de docentes, gracias por usar el programa**\n";
					std::cout << "--------------------------------------------------------------------\n";
					return;
					break;
				}
			} while (true);
		} else {
			std::cout << "No se pudo encontrar la asignatura con código " << _codigo << " porque no existe en la lista.\n";
		}
	}
};


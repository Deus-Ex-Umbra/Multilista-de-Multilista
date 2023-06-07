#pragma once
#include <iostream>
#include <string>
class Lista
{
private:
	class Nodo* nodo_inicial;
	virtual Nodo* buscar(int _posicion, Nodo* _nodo = nullptr) = 0;
	virtual Nodo* buscar(std::string _codigo, Nodo* _nodo = nullptr) = 0;
	virtual bool encontrar(Nodo* _nodo) = 0;
public:
	virtual void insertar(int _posicion, Nodo* _nodo = nullptr) = 0;
	virtual void eliminar(std::string _codigo, Nodo* _nodo = nullptr) = 0;
	virtual void mostrar(Nodo* _nodo = nullptr, bool _mostrar_siguiente = false, bool _mostrar_siguiente_siguiente = false) = 0;
	virtual bool vacia(Nodo* _nodo = nullptr) = 0;
	virtual void eliminar_todo(Nodo* _nodo = nullptr) = 0;
	virtual int numero_elementos(Nodo* _nodo = nullptr) = 0;
};


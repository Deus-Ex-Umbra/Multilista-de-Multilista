/*Universitario: Aparicio LLanquipacha Gabriel.
* Carrera: Ingenier�a en Ciencias de la Computaci�n.
* Grupo Laboratorio: Grupo 3.
*/
#include <iostream>
#include <string>
#include "Lista_Docente.h"
int main()
{
	int opcion, posicion;
	std::string codigo;
	Lista_Docente lista_docente;
	do {
		system("cls");
		std::cout << "---------------------------------------------------------\n";
		std::cout << "****Lista de Docentes****\n";
		std::cout << "---------------------------------------------------------\n";
		std::cout << "1. Ingresar un Docente.\n";
		std::cout << "2. Eliminar un Docente.\n";
		std::cout << "3. Mostrar la Lista de Docentes.\n";
		std::cout << "4. Ingresar a la lista de Asignaturas de un Docente.\n";
		std::cout << "5. Mostrar toda la Lista de Docentes y Asignaturas.\n";
		std::cout << "6. Mostrar toda la lista de Docentes, Asignaturas y Estudiantes.\n";
		std::cout << "7. Eliminar todo.\n";
		std::cout << "8. Salir.\n";
		std::cout << "---------------------------------------------------------\n";
		std::cout << "Ingrese una opcion: ";
		while (!(std::cin >> opcion) || (opcion < 1 || opcion > 8)) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "--------------------------------------------------------------------\n";
			std::cout << "Seleccione una opci�n v�lida: ";
		}
		std::cout << "---------------------------------------------------------\n";
		std::cin.ignore();
		switch (opcion)
		{
		case 1:
			std::cout << "**Se ingresar� un Docente**\n";
			std::cout << "--------------------------------------------------------------------\n";
			std::cout << "Escriba la posici�n donde se ingresar� el docente: ";
			while (!(std::cin >> posicion) || (posicion < 1 || posicion > lista_docente.numero_elementos() + 1)) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "--------------------------------------------------------------------\n";
				std::cout << "Posici�n no v�lida: ";
			}
			std::cout << "--------------------------------------------------------------------\n";
			std::cin.ignore();
			lista_docente.insertar(posicion);
			break;
		case 2:
			std::cout << "**Se eliminar� un Docente**\n";
			std::cout << "--------------------------------------------------------------------\n";
			std::cout << "Escriba el c�digo del docente que desea eliminar: "; std::getline(std::cin, codigo);
			lista_docente.eliminar(codigo);
			break;
		case 3:
			std::cout << "**Se mostrar� la Lista de Docentes**\n";
			std::cout << "--------------------------------------------------------------------\n";
			lista_docente.mostrar();
			system("pause");
			break;
		case 4:
			std::cout << "**Se ingresar� a la lista de Asignaturas de un Docente**\n";
			std::cout << "--------------------------------------------------------------------\n";
			std::cout << "Escriba el c�digo del docente al que desea ingresar: "; std::getline(std::cin, codigo);
			lista_docente.lista_de_asignaturas(codigo);
			break;
		case 5:
			std::cout << "**Se mostrar� toda la Lista de Docentes y Asignaturas**\n";
			std::cout << "--------------------------------------------------------------------\n";
			lista_docente.mostrar(nullptr, true);
			system("pause");
			break;
		case 6:
			std::cout << "**Se mostrar� toda la lista de Docentes, Asignaturas y Estudiantes**\n";
			std::cout << "--------------------------------------------------------------------\n";
			lista_docente.mostrar(nullptr, false, true);
			system("pause");
			break;
		default:
			std::cout << "**Gracias por usar el programa**\n";
			std::cout << "--------------------------------------------------------------------\n";
			return false;
			break;
		}
	} while (true);
}
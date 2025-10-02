/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Complejidad Computacional
 * Curso: 4º
 * Práctica 1: Pushdown Automaton Simulator
 * @author Himar Edhey Hernández Alonso
 * Correo: alu0101552392@ull.edu.es
 * @date Sep 15 2025
 * @file main.cc
 * @brief Main file for the Pushdown Automaton Simulator
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-1-automata-con-pila.git
 * Revision history:
 */

#include <iostream>
#include <string>

#include "AutomataFactory/PDAESFactory/pdaes-factory.h"

void printUsage(const char* program_name) {
  std::cout << "Uso: " << program_name << " <archivo_automata> <cadena_entrada>"
            << std::endl;
  std::cout << "Ejemplo: " << program_name << " automata.pda aabb" << std::endl;
}

int main(int argc, char const* argv[]) {
  std::cout << "HOLA";
  if (argc != 3) {
    printUsage(argv[0]);
    return 1;
  }

  std::string filename = argv[1];
  std::string input_string = argv[2];

  try {
    // Crear el autómata usando la factory
    PDAESFactory factory(filename);
    auto pda = factory.CreateAutomaton();

    // Imprimir información del autómata
    std::cout << "\n";
    pda->print();
    std::cout << "\n";

    // Simular el autómata con la cadena de entrada
    std::cout << "Cadena de entrada: " << input_string << std::endl;
    bool accepted = pda->simulate(input_string);

    if (accepted) {
      std::cout << "✓ Cadena ACEPTADA" << std::endl;
    } else {
      std::cout << "✗ Cadena RECHAZADA" << std::endl;
    }

    return accepted ? 0 : 1;

  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 2;
  }
}

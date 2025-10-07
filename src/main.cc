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

#include "Automata/PDA/pda.h"
#include "AutomataFactory/PDAESFactory/pdaes-factory.h"

void printUsage(const char* program_name) {
  std::cout << "Usage: " << program_name << " <automata_file>" << std::endl;
  std::cout << "Example: " << program_name << " automata.pda" << std::endl;
}

int main(int argc, char const* argv[]) {
  if (argc != 2) {
    printUsage(argv[0]);
    return 1;
  }

  std::string filename = argv[1];

  // Crear el autómata usando la factory
  PDAESFactory factory(filename);
  std::unique_ptr<PDA> pda = factory.CreateAutomaton();
  pda->resetStack();
  return pda ? 0 : 1;
}

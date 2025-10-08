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

#include <fstream>
#include <iostream>

#include "PDAFactory/pda-factory.h"
#include "Parser/args-parser.h"

int main(int argc, char* argv[]) {
  auto args_opt = ArgsParser::parse(argc, argv);
  if (!args_opt.has_value()) {
    return 1;  // Error en los argumentos
  }

  ArgsParser args = args_opt.value();

  std::cout << "Creating automaton: "
            << AutomataTypeHelper::toString(args.getPDAType()) << std::endl;
  std::cout << "Input file: " << args.getInputFile() << std::endl;

  auto pda = PDAFactory::createAutomata(args.getPDAType(), args.getInputFile());

  if (!pda) {
    std::cerr << "Error: Could not create automaton" << std::endl;
    return 1;
  }

  std::cout << "Automaton created successfully!\n" << std::endl;

  std::string input;
  std::cout << "Enter input strings (Ctrl+D to finish):" << std::endl;

  while (std::cin >> input) {
    bool accepted = pda->isAccepted(input);
    std::cout << "String '" << input
              << "': " << (accepted ? "✅ ACCEPTED" : "❌ REJECTED")
              << std::endl;
  }

  return 0;
}

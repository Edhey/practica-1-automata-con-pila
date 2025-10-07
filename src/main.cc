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

#include "Parser/args-parser.h"
#include "PDAFactory/pda-factory.h"

int main(int argc, char* argv[]) {
  ArgsParser args(argc, argv);

  std::cout << "Creating automaton: "
            << AutomataTypeHelper::toString(args.automata_type) << std::endl;
  std::cout << "Input file: " << args.input_file << std::endl;

  auto pda = PDAFactory::createAutomata(args.automata_type, args.input_file);

  if (!pda) {
    std::cerr << "Error: Could not create automaton" << std::endl;
    return 1;
  }

  std::cout << "Automaton created successfully!" << std::endl;

  std::ostream* output = &std::cout;
  std::ofstream file_output;

  if (!args.output_file.empty()) {
    file_output.open(args.output_file);
    if (file_output.is_open()) {
      output = &file_output;
    }
  }

  std::string input = "";
  std::cout << "\nEnter input strings or 'q.' to finish:" << std::endl;

  while (input != "q.") {
    std::cin >> input;
    bool accepted = pda->isAccepted(input);

    *output << "String '" << input
            << "': " << (accepted ? "✅ ACCEPTED" : "❌ REJECTED") << std::endl;

    if (args.trace_mode) {
      *output << "  [Trace information would go here]" << std::endl;
    }
  }

  return 0;
}

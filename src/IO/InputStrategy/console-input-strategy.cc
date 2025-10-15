/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Complejidad Computacional
 * Curso: 4º
 * Práctica 1: Pushdown Automaton Simulator
 * @author Himar Edhey Hernández Alonso
 * @mail: alu0101552392@ull.edu.es
 * @date Oct 10 2025
 * @file console-input-strategy.cc
 * @brief Console input strategy implementation
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-1-automata-con-pila.git
 */

#include "console-input-strategy.h"

std::optional<std::vector<std::string>> ConsoleInputStrategy::readInputs() {
  std::vector<std::string> inputs;
  std::string line;

  std::cout << "Enter input strings (one per line, 'q.' to finish):"
            << std::endl;

  while (std::cin >> line) {
    if (line == "q.") {
      break;
    }
    inputs.push_back(line);
  }

  if (inputs.empty()) {
    std::cerr << "Warning: No input strings provided" << std::endl;
    return std::nullopt;
  }

  return inputs;
}
/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Complejidad Computacional
 * Curso: 4º
 * Práctica 1: Pushdown Automaton Simulator
 * @author Himar Edhey Hernández Alonso
 * Correo: alu0101552392@ull.edu.es
 * @date Oct 10 2025
 * @file file-input-strategy.h
 * @brief File input strategy implementation
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-1-automata-con-pila.git
 */

#include "file-input-strategy.h"

std::optional<std::vector<std::string>> FileInputStrategy::readInputs() {
  std::ifstream file(filename_);

  if (!file.is_open()) {
    std::cerr << "Error: Could not open input file '" << filename_ << "'"
              << std::endl;
    return std::nullopt;
  }

  std::vector<std::string> inputs;
  std::string line;

  while (std::getline(file, line)) {
    if (line.empty() || line[0] == '#') {
      continue;
    }
    inputs.push_back(line);
  }

  file.close();

  if (inputs.empty()) {
    std::cerr << "Warning: No input strings found in file" << std::endl;
    return std::nullopt;
  }

  return inputs;
}
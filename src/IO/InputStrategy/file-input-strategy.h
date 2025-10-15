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
 * @file file-input-strategy.h
 * @brief File input strategy implementation
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-1-automata-con-pila.git
 */

#ifndef IO_INPUTSTRATEGY_FILE_INPUT_STRATEGY_H_
#define IO_INPUTSTRATEGY_FILE_INPUT_STRATEGY_H_

#include <fstream>
#include <iostream>

#include "input-strategy.h"

class FileInputStrategy : public InputStrategy {
public:
  explicit FileInputStrategy(const std::string& filename)
      : filename_(filename) {}

  std::optional<std::vector<std::string>> readInputs() override;

private:
  std::string filename_;
};

#endif  // IO_INPUTSTRATEGY_FILE_INPUT_STRATEGY_H_
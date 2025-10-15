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
 * @file file-output-strategy.h
 * @brief File output strategy implementation
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-1-automata-con-pila.git
 */

#ifndef IO_OUTPUTSTRATEGY_FILE_OUTPUT_STRATEGY_H_
#define IO_OUTPUTSTRATEGY_FILE_OUTPUT_STRATEGY_H_

#include <fstream>
#include <iostream>

#include "output-strategy.h"

class FileOutputStrategy : public OutputStrategy {
public:
  explicit FileOutputStrategy(const std::string& filename,
                              bool enable_trace = false)
      : filename_(filename), enable_trace_(enable_trace) {
    file_.open(filename_);
    if (!file_.is_open()) {
      std::cerr << "Error: Could not open output file '" << filename_ << "'"
                << std::endl;
    }
  }
  ~FileOutputStrategy() override {
    if (file_.is_open()) {
      file_.close();
    }
  }
  std::optional<std::reference_wrapper<std::ostream>> getStream() override {
    if (enable_trace_ && file_.is_open()) {
      return std::ref(file_);
    }
    return std::nullopt;
  }
  void writeResult(const std::string& input, bool accepted) override;
  void finalize() override;

private:
  std::string filename_;
  std::ofstream file_;
  bool enable_trace_;
};

#endif  // IO_OUTPUTSTRATEGY_FILE_OUTPUT_STRATEGY_H_
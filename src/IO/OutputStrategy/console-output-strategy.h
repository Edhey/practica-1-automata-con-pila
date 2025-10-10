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
 * @file console-output-strategy.h
 * @brief Console output strategy implementation
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-1-automata-con-pila.git
 */

#ifndef IO_OUTPUTSTRATEGY_CONSOLE_OUTPUT_STRATEGY_H_
#define IO_OUTPUTSTRATEGY_CONSOLE_OUTPUT_STRATEGY_H_

#include <iostream>

#include "output-strategy.h"

#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

class ConsoleOutputStrategy : public OutputStrategy {
public:
  explicit ConsoleOutputStrategy(bool enable_trace = false)
      : enable_trace_(enable_trace) {}

  std::optional<std::reference_wrapper<std::ostream>> getStream() override {
    if (enable_trace_) {
      return std::ref(std::cout);
    }
    return std::nullopt;
  }

  void writeResult(const std::string& input, bool accepted) override {
    std::cout << "String '" << input << "': "
              << (accepted ? GREEN "ACCEPTED" RESET : RED "REJECTED" RESET)
              << std::endl;
  }
  
  void finalize() override { std::cout.flush(); }

private:
  bool enable_trace_;
};

#endif  // IO_OUTPUTSTRATEGY_CONSOLE_OUTPUT_STRATEGY_H_
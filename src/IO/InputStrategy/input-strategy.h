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
 * @file input-strategy.h
 * @brief Strategy pattern for reading input strings
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-1-automata-con-pila.git
 */

#ifndef IO_INPUTSTRATEGY_INPUT_STRATEGY_H_
#define IO_INPUTSTRATEGY_INPUT_STRATEGY_H_

#include <optional>
#include <string>
#include <vector>

/**
 * @brief Abstract base class for input strategies
 */
class InputStrategy {
public:
  virtual ~InputStrategy() = default;
  
  /**
   * @brief Reads input strings
   * @return Vector of input strings, or nullopt if error
   */
  virtual std::optional<std::vector<std::string>> readInputs() = 0;
};

#endif  // IO_INPUTSTRATEGY_INPUT_STRATEGY_H_
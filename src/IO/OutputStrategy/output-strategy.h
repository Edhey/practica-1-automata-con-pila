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
 * @file output-strategy.h
 * @brief Strategy pattern for writing output
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-1-automata-con-pila.git
 */

#ifndef IO_OUTPUTSTRATEGY_OUTPUT_STRATEGY_H_
#define IO_OUTPUTSTRATEGY_OUTPUT_STRATEGY_H_

#include <functional>
#include <optional>
#include <ostream>
#include <string>

/**
 * @brief Abstract base class for output strategies
 */
class OutputStrategy {
public:
  virtual ~OutputStrategy() = default;

  /**
   * @brief Gets the output stream for writing
   * @return Optional reference wrapper to output stream
   */
  virtual std::optional<std::reference_wrapper<std::ostream>> getStream() = 0;

  /**
   * @brief Writes a result message
   */
  virtual void writeResult(const std::string& input, bool accepted) = 0;

  /**
   * @brief Finalizes output (flush, close files, etc.)
   */
  virtual void finalize() = 0;
};

#endif  // IO_OUTPUTSTRATEGY_OUTPUT_STRATEGY_H_
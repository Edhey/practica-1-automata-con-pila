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
 * @file automata.h
 * @brief Definition of the abstract class Automata
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-1-automata-con-pila.git
 * Revision history:
 */

#ifndef AUTOMATA_H
#define AUTOMATA_H

#include <set>
#include <string>

#include "../State/state.h"

/**
 * @brief Abstract class for automata (automaton interface)
 */
class Automata {
public:
  virtual ~Automata() = default;
  virtual bool isAccepted(const std::string& input) = 0;

protected:
  // State current_state;
  State initial_state;
  std::set<State> states;
  std::set<char> input_alphabet;
  static constexpr char EPSILON = '.';
};

#endif  // AUTOMATA_H
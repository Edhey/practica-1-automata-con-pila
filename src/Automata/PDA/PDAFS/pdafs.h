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
 * @file pdafs.h
 * @brief Definition of the class PDAFS, a Pushdown Automaton that accepts by
 * Final State
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-1-automata-con-pila.git
 * Revision history:
 */

#ifndef PDAFS_H
#define PDAFS_H

#include <iostream>
#include <set>

#include "../pda.h"
#include "../../State/state.h"

/**
 * @brief Class for a Pushdown Automaton that accepts by Final State
 */
class PDAFS : public PDA {
public:
  virtual ~PDAFS() = default;
  bool isAccepted(const std::string& input) override;

  const std::set<State>& getFinalStates() const { return final_states; }

private:
  std::set<State> final_states;
};

#endif  // PDAFS_H
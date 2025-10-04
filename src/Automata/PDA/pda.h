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
 * @brief Definition of the class PDA
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-1-automata-con-pila.git
 * Revision history:
 */

#ifndef PDA_H
#define PDA_H

#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <vector>

#include "../Automata/automata.h"
#include "../../State/state.h"
#include "../../Alphabet/alphabet.h"

struct PDATransitionKey {
  char input_symbol;
  char stack_top;
};

struct PDATransitionValue {
  std::string next_state_id;
  std::string push_string;  // String to push onto the stack (can be empty for pop)
};

class PDA : public Automata<PDATransitionKey, PDATransitionValue> {
public:
  virtual ~PDA() = default;
  virtual bool isAccepted(const std::string& input) override;

protected:
  std::stack<char> stack;
  Alphabet<char> stack_alphabet;
  char initial_stack_symbol;
};

#endif
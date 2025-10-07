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
 * @file pda.h
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

#include "../Alphabet/alphabet.h"
#include "../State/state.h"
#include "../automata.h"
#include "PDATransition/pda-transition.h"

class PDA : public Automata<PDATransitionKey, PDATransitionValue> {
public:
  virtual ~PDA() = default;
  virtual bool isAccepted(const std::string& string) = 0;
  void setStackAlphabet(const Alphabet<char>& alphabet) {
    stack_alphabet = alphabet;
  }
  void setInitialStackSymbol(char symbol) { initial_stack_symbol = symbol; }
  void resetStack();
  bool checkStackAlphabet(char symbol) {
    return stack_alphabet.contains(symbol);
  }
protected:
  std::stack<char> stack;
  Alphabet<char> stack_alphabet;
  char initial_stack_symbol;
};

#endif
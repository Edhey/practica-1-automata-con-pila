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
 * @file pda-transition.h
 * @brief Definition of the class PDA
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-1-automata-con-pila.git
 * Revision history:
 */

 #include <iostream>

struct PDATransitionKey {
  char input_symbol;
  char stack_top;

  bool operator<(const PDATransitionKey& other) const {
    return std::tie(input_symbol, stack_top) <
           std::tie(other.input_symbol, other.stack_top);
  }
};

struct PDATransitionValue {
  std::string next_state_id;
  std::string push_string;
};
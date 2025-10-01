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
 * @see
 * Historial de revisiones:
 */

#ifndef PDA_H
#define PDA_H

#include <iostream>
#include <map>
#include <set>
#include <stack>

class PDA {
 public:
  PDA() = default;
  ~PDA() = default;

 private:
  std::set<char> input_alphabet_;  // Input alphabet
  std::set<char> stack_alphabet_;  // Stack alphabet
  std::set<std::string> states_;    // Set of states
  std::string initial_state_;       // Initial state
  std::set<std::string> final_states_;  // Set of final states
  std::map<std::tuple<std::string, char, char>, std::set<std::pair<std::string, std::string>>> transition_function_;
  // Transition function
};

#endif
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
 * @file pdaes-parser.cc
 * @brief Implementation of the PdaESParser class
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-1-automata-con-pila.git
 * Revision history:
 */

#include "pdaes-parser.h"

std::expected<PdaData, ParseError> PdaESParser::parse() {
  std::ifstream file(file_name_);
  if (!file.is_open()) {
    return std::unexpected(
        ParseError("Error: Could not open file " + file_name_));
  }

  PdaData data;
  int line_number = 0;

  auto states_result = parseStates(file, line_number);
  if (!states_result.has_value()) {
    return std::unexpected(states_result.error());
  }
  data.states.clear();
  data.states = std::move(states_result.value());

  auto input_alpha_result = parseInputAlphabet(file, line_number);
  if (!input_alpha_result.has_value()) {
    return std::unexpected(input_alpha_result.error());
  }
  data.input_alphabet = std::move(input_alpha_result.value());

  auto stack_alpha_result = parseStackAlphabet(file, line_number);
  if (!stack_alpha_result.has_value()) {
    return std::unexpected(stack_alpha_result.error());
  }
  data.stack_alphabet = std::move(stack_alpha_result.value());

  auto init_state_result = parseInitialState(file, line_number, data.states);
  if (!init_state_result.has_value()) {
    return std::unexpected(init_state_result.error());
  }
  data.initial_state = init_state_result.value();

  auto init_stack_result = parseInitialStackSymbol(file, line_number);
  if (!init_stack_result.has_value()) {
    return std::unexpected(init_stack_result.error());
  }
  data.initial_stack_symbol = init_stack_result.value();

  auto transitions_result =
      parseTransitions(file, line_number, data.states, &data.stack_alphabet,
                       &data.input_alphabet);
  if (!transitions_result.has_value()) {
    return std::unexpected(transitions_result.error());
  }
  // data.states.clear();
  // for (const auto& [state_id, state] : mapped_states) {
  //   data.states.insert(state);
  // }

  file.close();
  return data;
}

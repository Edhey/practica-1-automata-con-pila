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
  std::string line;
  int line_number = 0;

  // Read states
  if (!readNonCommentLine(file, line)) {
    return std::unexpected(
        ParseError("Error: Missing states definition", line_number));
  }
  line_number++;
  for (const auto& token : tokenize(line)) {
    auto result = data.states.insert(
        {token, State<PDATransitionKey, PDATransitionValue>(token)});
    if (!result.second) {
      std::cerr << "Warning: Duplicate state '" << token << "' found at line "
                << line_number << std::endl;
    }
  }

  // Read input alphabet
  if (!readNonCommentLine(file, line)) {
    return std::unexpected(
        ParseError("Error: Missing input alphabet definition", line_number));
  }
  line_number++;
  for (const auto& token : tokenize(line)) {
    if (token.size() != 1) {
      return std::unexpected(
          ParseError("Error: Input alphabet symbols must be single characters",
                     line_number));
    }
    data.input_alphabet.addSymbol(token[0]);
  }

  // Read stack alphabet
  if (!readNonCommentLine(file, line)) {
    return std::unexpected(
        ParseError("Error: Missing stack alphabet definition", line_number));
  }
  line_number++;
  for (const auto& token : tokenize(line)) {
    if (token.size() != 1) {
      return std::unexpected(
          ParseError("Error: Stack alphabet symbols must be single characters",
                     line_number));
    }
    data.stack_alphabet.addSymbol(token[0]);
  }

  // Read initial stack symbol
  if (!readNonCommentLine(file, line)) {
    return std::unexpected(ParseError(
        "Error: Missing initial stack symbol definition", line_number));
  }
  line_number++;
  auto tokens = tokenize(line);
  if (tokens.size() != 1 || tokens[0].size() != 1) {
    return std::unexpected(ParseError(
        "Error: Initial stack symbol must be a single character", line_number));
  }
  data.initial_stack_symbol = tokens[0][0];

  // Read initial state
  if (!readNonCommentLine(file, line)) {
    return std::unexpected(
        ParseError("Error: Missing initial state definition", line_number));
  }
  line_number++;
  tokens = tokenize(line);
  if (tokens.size() != 1) {
    return std::unexpected(ParseError(
        "Error: Initial state must be a single state ID", line_number));
  }
  auto initial_state = data.states.find(tokens[0]);
  if (initial_state == data.states.end()) {
    return std::unexpected(ParseError(
        "Error: Initial state '" + tokens[0] + "' not defined", line_number));
  }
  data.initial_state = initial_state->second;

  // Read transitions
  while (readNonCommentLine(file, line)) {
    line_number++;
    tokens = tokenize(line);
    if (tokens.size() != 5) {
      return std::unexpected(
          ParseError("Error: Transition must have 5 components", line_number));
    }
    const std::string& current_state_id = tokens[0];
    char input_symbol = tokens[1][0];
    char stack_top = tokens[2][0];
    const std::string& next_state_id = tokens[3];
    const std::string& push_string = tokens[4];
    if (tokens[1].size() != 1 || tokens[2].size() != 1) {
      return std::unexpected(ParseError(
          "Error: Input symbol and stack top must be single characters",
          line_number));
    }
    auto current_state_it = data.states.find(current_state_id);
    if (current_state_it == data.states.end()) {
      return std::unexpected(ParseError(
          "Error: Current state '" + current_state_id + "' not defined",
          line_number));
    }
    if (!data.states.contains(next_state_id)) {
      return std::unexpected(
          ParseError("Error: Next state '" + next_state_id + "' not defined",
                     line_number));
    }
    PDATransitionKey key{input_symbol, stack_top};
    PDATransitionValue value{next_state_id, push_string};
    State<PDATransitionKey, PDATransitionValue>& state =
        current_state_it->second;
    state.addTransition(key, value);
  }

  if (readNonCommentLine(file, line)) {
    std::cerr << "Warning: Extra lines after transitions ignored at line "
              << line_number + 1 << std::endl;
  }

  file.close();
  return data;
}

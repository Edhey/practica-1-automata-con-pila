#include "pdaes-parser.h"
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
 * @brief Implementation of PdaESParser class
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-1-automata-con-pila.git
 * Revision history:
 */

std::expected<PdaData, ParseError> PdaESParser::parse() {
  std::ifstream file(file_name_);
  if (!file.is_open()) {
    return std::unexpected(
        ParseError{"Error: No se pudo abrir el archivo " + file_name_});
  }

  PdaData data;
  std::string line;
  int line_number = 0;

  if (!readNonCommentLine(file, line)) {
    return std::unexpected(
        ParseError{"Error: Archivo vacío o sin líneas válidas"});
  }
  line_number++;
  // 1. Read states
  for (const auto& token : tokenize(line)) {
    data.states.push_back(State(token));
  }
  if (data.states.empty()) {
    return std::unexpected(ParseError{"Error línea " +
                                      std::to_string(line_number) +
                                      ": No se encontraron estados"});
  }

  // 2. Reader input alphabet
  if (!readNonCommentLine(file, line)) {
    return std::unexpected(ParseError{"Error: Falta alfabeto de entrada"});
  }
  line_number++;
  std::vector<std::string> input_tokens = tokenize(line);
  for (const auto& token : input_tokens) {
    if (token.length() != 1) {
      return std::unexpected(ParseError{
          "Error línea " + std::to_string(line_number) +
          ": Los símbolos del alfabeto de entrada deben ser de un carácter"});
    }
    data.input_alphabet.insert(token[0]);
  }

  // 3. Reader stack alphabet
  if (!readNonCommentLine(file, line)) {
    return std::unexpected(ParseError{"Error: Falta alfabeto de pila"});
  }
  line_number++;
  std::vector<std::string> stack_tokens = tokenize(line);
  for (const auto& token : stack_tokens) {
    if (token.length() != 1) {
      return std::unexpected(ParseError{
          "Error línea " + std::to_string(line_number) +
          ": Los símbolos del alfabeto de pila deben ser de un carácter"});
    }
    data.stack_alphabet.insert(token[0]);
  }

  // 4. Read initial state
  if (!readNonCommentLine(file, line)) {
    throw std::runtime_error("Error: Falta estado inicial");
  }
  line_number++;
  auto initial_tokens = tokenize(line);
  if (initial_tokens.size() != 1) {
    return std::unexpected(
        ParseError{"Error línea " + std::to_string(line_number) +
                   ": Debe haber exactamente un estado inicial"});
  }
  State initial_state(initial_tokens[0]);
  if (data.states.)

    // 5. Leer símbolo inicial de pila
    if (!readNonCommentLine(file, line)) {
      throw std::runtime_error("Error: Falta símbolo inicial de pila");
    }
  line_number++;
  auto initial_stack_tokens = tokenize(line);
  if (initial_stack_tokens.size() != 1 ||
      initial_stack_tokens[0].length() != 1) {
    throw std::runtime_error(
        "Error línea " + std::to_string(line_number) +
        ": Debe haber exactamente un símbolo inicial de pila");
  }
  data.initial_stack_symbol = initial_stack_tokens[0][0];

  // 6. Leer estados finales
  if (!readNonCommentLine(file, line)) {
    throw std::runtime_error("Error: Faltan estados finales");
  }
  line_number++;
  data.final_states = tokenize(line);
  if (data.final_states.empty()) {
    throw std::runtime_error("Error línea " + std::to_string(line_number) +
                             ": Debe haber al menos un estado final");
  }

  // 7. Leer transiciones
  while (readNonCommentLine(file, line)) {
    line_number++;
    auto tokens = tokenize(line);

    if (tokens.size() != 5) {
      throw std::runtime_error(
          "Error línea " + std::to_string(line_number) +
          ": Formato de transición incorrecto. " +
          "Formato esperado: estado_actual símbolo_entrada tope_pila "
          "estado_siguiente cadena_a_apilar");
    }

    PdaData::Transition transition;
    transition.current_state = tokens[0];
    transition.input_symbol = tokens[1].length() == 1 ? tokens[1][0] : '\0';
    transition.stack_top = tokens[2].length() == 1 ? tokens[2][0] : '\0';
    transition.next_state = tokens[3];
    transition.push_string = tokens[4];

    // Validar formato
    if (tokens[1].length() != 1) {
      throw std::runtime_error(
          "Error línea " + std::to_string(line_number) +
          ": El símbolo de entrada debe ser de un carácter");
    }
    if (tokens[2].length() != 1) {
      throw std::runtime_error("Error línea " + std::to_string(line_number) +
                               ": El tope de pila debe ser de un carácter");
    }

    data.transitions.push_back(transition);
  }
  file.close();
  return data;
}
/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Complejidad Computacional
 * Curso: 4º
 * Práctica 1: Pushdown Automaton Simulator
 * @author Himar Edhey Hernández Alonso
 * @mail: alu0101552392@ull.edu.es
 * @date Sep 15 2025
 * @file pda-parser.h
 * @brief Definition of the class PdaParser
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-1-automata-con-pila.git
 * Revision history:
 */

#ifndef PARSER_PDA_PARSER_H_
#define PARSER_PDA_PARSER_H_

#include <expected>
#include <fstream>
#include <ostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "../Automata/PDA/pda.h"
#include "../State/state.h"

/**
 * @brief Estructura para almacenar los datos parseados del autómata
 */
struct PdaData {
  std::set<char> input_alphabet;
  std::set<char> stack_alphabet;
  char initial_stack_symbol;
  State initial_state;
  std::vector<State> states;
  // ! std::vector<State> final_states;
  std::vector<PDATransition> transitions;
};

/**
 * @brief Tipo de error para el parser
 */
struct ParseError {
  std::string message;
  int line_number;

  ParseError(const std::string& msg, int line = 0)
      : message(msg), line_number(line) {}
};

/**
 * @brief Clase para parsear archivos de definición de APf
 */
class PdaParser {
public:
  explicit PdaParser(const std::string& file_name);
  ~PdaParser() = default;

  std::expected<PdaData, ParseError> parse();

protected:
  std::string file_name_;
  bool readNonCommentLine(std::ifstream& ifs, std::string& line);
  const std::vector<std::string>& tokenize(const std::string& line);
};

#endif  // PARSER_PDA_PARSER_H_
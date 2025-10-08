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

#include "../../Automata/Alphabet/alphabet.h"
#include "../../Automata/PDA/pda.h"
#include "../../Automata/State/state.h"

struct PdaData {
  Alphabet<char> input_alphabet;
  Alphabet<char> stack_alphabet;
  char initial_stack_symbol;
  std::string initial_state;
  std::map<std::string, State<PDATransitionKey, PDATransitionValue>> states;
  // ! std::vector<State> final_states;
  PdaData()
      : input_alphabet(),
        stack_alphabet(),
        initial_stack_symbol(PDA::EPSILON),
        initial_state(""),
        states() {}
};

struct ParseError {
  std::string message;
  int line_number;

  ParseError(const std::string& msg, int line = 0)
      : message(msg), line_number(line) {}
};

class PdaParser {
public:
  explicit PdaParser(const std::string& file_name) : file_name_(file_name) {}
  virtual ~PdaParser() = default;
  virtual std::expected<PdaData, ParseError> parse() = 0;

protected:
  std::string file_name_;
  bool readNonCommentLine(std::ifstream& ifs, std::string& line);
  std::vector<std::string> tokenize(const std::string& line);
  bool isEpsilonInChain(const std::string& line);
  std::expected<
      std::map<std::string, State<PDATransitionKey, PDATransitionValue>>,
      ParseError>
  parseStates(std::ifstream& file, int& line_number);
  std::expected<Alphabet<char>, ParseError> parseInputAlphabet(
      std::ifstream& file, int& line_number);
  std::expected<Alphabet<char>, ParseError> parseStackAlphabet(
      std::ifstream& file, int& line_number);
  std::expected<char, ParseError> parseInitialStackSymbol(std::ifstream& file,
                                                          int& line_number);
  std::expected<std::string, ParseError> parseInitialState(
      std::ifstream& file, int& line_number,
      const std::map<std::string, State<PDATransitionKey, PDATransitionValue>>&
          states);
  std::expected<void, ParseError> parseTransitions(
      std::ifstream& file, int& line_number,
      std::map<std::string, State<PDATransitionKey, PDATransitionValue>>&
          states,
      const Alphabet<char>* stack_alphabet,
      const Alphabet<char>* input_alphabet);
};

#endif  // PARSER_PDA_PARSER_H_
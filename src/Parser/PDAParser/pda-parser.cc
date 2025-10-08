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
 * @file pda-parser.cc
 * @brief Implementation of PdaParser class
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-1-automata-con-pila.git
 * Revision history:
 */

#include "pda-parser.h"

std::expected<PdaData, ParseError> PdaParser::parse() {
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

  auto init_stack_result =
      parseInitialStackSymbol(file, line_number, data.stack_alphabet);
  if (!init_stack_result.has_value()) {
    return std::unexpected(init_stack_result.error());
  }
  data.initial_stack_symbol = init_stack_result.value();

  auto specific_result = parseSpecificData(file, line_number, data);
  if (!specific_result.has_value()) {
    return std::unexpected(specific_result.error());
  }

  auto transitions_result =
      parseTransitions(file, line_number, data.states, &data.stack_alphabet,
                       &data.input_alphabet);
  if (!transitions_result.has_value()) {
    return std::unexpected(transitions_result.error());
  }

  file.close();
  return data;
}

/**
 * @brief Ignores comment lines (starting with #)
 * @param ifs File stream
 * @param line String where the read line will be stored
 * @return true if a valid line was read, false if EOF was reached
 */
bool PdaParser::readNonCommentLine(std::ifstream& ifs, std::string& line) {
  while (std::getline(ifs, line)) {
    size_t start = line.find_first_not_of(" \t\r\n");
    if (start == std::string::npos)
      continue;  // Empty line

    line = line.substr(start);
    if (line[0] == '#')
      continue;  // Ignore comments

    size_t comment_pos = line.find('#');  // Remove comments at the line end
    if (comment_pos != std::string::npos) {
      line = line.substr(0, comment_pos);
    }

    size_t end = line.find_last_not_of(" \t\r\n");  // Remove trailing whitespac
    if (end != std::string::npos) {
      line = line.substr(0, end + 1);
    }

    if (!line.empty())
      return true;
  }
  return false;
}

/**
 * @brief Divides a line into tokens separated by spaces
 * @param line The string to be divided
 * @return A vector of tokens
 */
std::vector<std::string> PdaParser::tokenize(const std::string& line) {
  std::vector<std::string> tokens;
  std::istringstream iss(line);
  std::string token;

  while (iss >> token) {
    tokens.push_back(token);
  }

  return tokens;
}

/**
 * @brief Checks if the line contains the epsilon character between alphabet
 * symbols
 * @param line The line to check
 * @return true if the epsilon character is found, false otherwise
 */
bool PdaParser::isEpsilonInChain(const std::string& line) {
  return line.find(PDA::EPSILON) != std::string::npos;
}

std::expected<
    std::map<std::string, State<PDATransitionKey, PDATransitionValue>>,
    ParseError>
PdaParser::parseStates(std::ifstream& file, int& line_number) {
  std::string line;
  if (!readNonCommentLine(file, line)) {
    return std::unexpected(
        ParseError("Error: Missing states definition", line_number));
  }
  line_number++;

  std::map<std::string, State<PDATransitionKey, PDATransitionValue>> states;
  for (const auto& token : tokenize(line)) {
    auto result = states.insert(
        {token, State<PDATransitionKey, PDATransitionValue>(token)});
    if (!result.second) {
      std::cerr << "Warning: Duplicate state '" << token << "' at line "
                << line_number << " not added" << std::endl;
    }
  }
  return states;
}

std::expected<Alphabet<char>, ParseError> PdaParser::parseInputAlphabet(
    std::ifstream& file, int& line_number) {
  std::string line;
  if (!readNonCommentLine(file, line)) {
    return std::unexpected(
        ParseError("Error: Missing input alphabet definition", line_number));
  }
  line_number++;

  Alphabet<char> alphabet;
  for (const auto& token : tokenize(line)) {
    if (token.size() != 1) {
      return std::unexpected(
          ParseError("Error: Input alphabet symbols must be single characters",
                     line_number));
    }
    if (token[0] == PDA::EPSILON) {
      return std::unexpected(
          ParseError("Error: Input alphabet cannot contain the epsilon symbol",
                     line_number));
    }
    alphabet.addSymbol(token[0]);
  }
  return alphabet;
}

std::expected<Alphabet<char>, ParseError> PdaParser::parseStackAlphabet(
    std::ifstream& file, int& line_number) {
  std::string line;
  if (!readNonCommentLine(file, line)) {
    return std::unexpected(
        ParseError("Error: Missing stack alphabet definition", line_number));
  }
  line_number++;

  Alphabet<char> alphabet;
  for (const auto& token : tokenize(line)) {
    if (token.size() != 1) {
      return std::unexpected(
          ParseError("Error: Stack alphabet symbols must be single characters",
                     line_number));
    }
    if (token[0] == PDA::EPSILON) {
      return std::unexpected(
          ParseError("Error: Stack alphabet cannot contain the epsilon symbol",
                     line_number));
    }
    alphabet.addSymbol(token[0]);
  }

  return alphabet;
}

std::expected<char, ParseError> PdaParser::parseInitialStackSymbol(
    std::ifstream& file, int& line_number,
    const Alphabet<char>& stack_alphabet) {
  std::string line;
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
  if (tokens[0][0] == PDA::EPSILON) {
    return std::unexpected(ParseError(
        "Error: Initial stack symbol cannot be the epsilon character",
        line_number));
  }
  if (stack_alphabet.contains(tokens[0][0]) == false) {
    return std::unexpected(ParseError(
        "Error: Initial stack symbol '" + tokens[0] + "' not in stack alphabet",
        line_number));
  }

  return tokens[0][0];
}

std::expected<std::string, ParseError> PdaParser::parseInitialState(
    std::ifstream& file, int& line_number,
    const std::map<std::string, State<PDATransitionKey, PDATransitionValue>>&
        states) {
  std::string line;
  if (!readNonCommentLine(file, line)) {
    return std::unexpected(
        ParseError("Error: Missing initial state definition", line_number));
  }
  line_number++;

  auto tokens = tokenize(line);
  if (tokens.size() != 1) {
    return std::unexpected(ParseError(
        "Error: Initial state must be a single state ID", line_number));
  }

  if (!states.contains(tokens[0])) {
    return std::unexpected(ParseError(
        "Error: Initial state '" + tokens[0] + "' not defined", line_number));
  }

  return tokens[0];
}

std::expected<void, ParseError> PdaParser::parseTransitions(
    std::ifstream& file, int& line_number,
    std::map<std::string, State<PDATransitionKey, PDATransitionValue>>& states,
    const Alphabet<char>* stack_alphabet,
    const Alphabet<char>* input_alphabet) {
  std::string line;
  while (readNonCommentLine(file, line)) {
    line_number++;
    auto tokens = tokenize(line);

    if (tokens.size() != 5) {
      return std::unexpected(ParseError(
          "Error: PDA Transitions must have 5 components", line_number));
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

    if (!input_alphabet->contains(input_symbol) &&
        input_symbol != PDA::EPSILON) {
      return std::unexpected(ParseError("Error: Input symbol '" +
                                            std::string(1, input_symbol) +
                                            "' not in input alphabet",
                                        line_number));
    }

    if (!stack_alphabet->contains(stack_top) && stack_top != PDA::EPSILON) {
      return std::unexpected(ParseError("Error: Stack top symbol '" +
                                            std::string(1, stack_top) +
                                            "' not in stack alphabet",
                                        line_number));
    }

    auto current_state_it = states.find(current_state_id);
    if (current_state_it == states.end()) {
      return std::unexpected(ParseError(
          "Error: Current state '" + current_state_id + "' not defined",
          line_number));
    }

    if (!states.contains(next_state_id)) {
      return std::unexpected(
          ParseError("Error: Next state '" + next_state_id + "' not defined",
                     line_number));
    }

    if (push_string != std::string(1, PDA::EPSILON)) {
      for (char symbol : push_string) {
        if (symbol == PDA::EPSILON) {
          return std::unexpected(ParseError(
              "Error: Push string cannot contain the epsilon character",
              line_number));
        }
        if (!stack_alphabet->contains(symbol)) {
          return std::unexpected(
              ParseError("Error: Push string contains symbol '" +
                             std::string(1, symbol) + "' not in stack alphabet",
                         line_number));
        }
      }
    }

    PDATransitionKey key{input_symbol, stack_top};
    PDATransitionValue value{next_state_id, push_string};

    current_state_it->second.addTransition(key, value);
  }

  return {};
}
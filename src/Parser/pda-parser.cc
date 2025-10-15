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
 * @file pda-parser.cc
 * @brief Implementation of PdaParser class
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-1-automata-con-pila.git
 * Revision history:
 */

#include "pda-parser.h"

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

    // Remove comments at the end of the line
    size_t comment_pos = line.find('#');
    if (comment_pos != std::string::npos) {
      line = line.substr(0, comment_pos);
    }

    // Remove trailing whitespace
    size_t end = line.find_last_not_of(" \t\r\n");
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
const std::vector<std::string>& PdaParser::tokenize(const std::string& line) {
  std::vector<std::string> tokens;
  std::istringstream iss(line);
  std::string token;

  while (iss >> token) {
    tokens.push_back(token);
  }

  return tokens;
}
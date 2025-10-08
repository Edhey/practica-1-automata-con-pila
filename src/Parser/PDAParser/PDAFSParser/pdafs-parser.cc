/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Complejidad Computacional
 * Curso: 4º
 * Práctica 1: Pushdown Automaton Simulator
 * @author Himar Edhey Hernández Alonso
 * Correo: alu0101552392@ull.edu.es
 * @date Oct 05 2025
 * @file pdafs-parser.h
 * @brief Declaration of the class PdaFSParser
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-1-automata-con-pila.git
 * Revision history:
 */

#include "pdafs-parser.h"

/**
 * @brief Parses the specific data for the PDA from the given file. In this
 * case, it reads the final states and adds them to the PdaData structure.
 * @param file The input file stream.
 * @param line_number The current line number in the input file.
 * @param data The PdaData structure to populate.
 * @return An expected void on success, or a ParseError on failure.
 */
std::expected<void, ParseError> PdaFSParser::parseSpecificData(
    std::ifstream& file, int& line_number, PdaData& data) {
  std::string line;
  if (!readNonCommentLine(file, line)) {
    return std::unexpected(
        ParseError("Error: Missing final states definition", line_number));
  }
  line_number++;

  auto tokens = tokenize(line);
  if (tokens.empty()) {
    return std::unexpected(
        ParseError("Error: Final states list cannot be empty", line_number));
  }

  for (const auto& token : tokens) {
    if (!data.states.contains(token)) {
      return std::unexpected(ParseError(
          "Error: Final state '" + token + "' not defined", line_number));
    }
    data.final_states.insert(token);
  }

  return {};
}
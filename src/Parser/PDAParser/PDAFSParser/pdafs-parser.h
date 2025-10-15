/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Complejidad Computacional
 * Curso: 4º
 * Práctica 1: Pushdown Automaton Simulator
 * @author Himar Edhey Hernández Alonso
 * @mail: alu0101552392@ull.edu.es
 * @date Oct 05 2025
 * @file pdafs-parser.h
 * @brief Definition of the class PdaFSParser
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-1-automata-con-pila.git
 * Revision history:
 */

#ifndef PARSER_PDAFS_PARSER_H_
#define PARSER_PDAFS_PARSER_H_

#include "../pda-parser.h"

/**
 * @class PdaFSParser
 * @brief Specialized parser for Finite State Pushdown Automata (FS-PDA)
 * configuration files. Inherits from PdaParser and provides specific parsing
 * logic for FS-PDA data. The parser reads automaton definitions from a file and
 * populates a PdaData structure.
 */
class PdaFSParser : public PdaParser {
public:
  explicit PdaFSParser(const std::string& file_name) : PdaParser(file_name) {}

private:
  std::expected<void, ParseError> parseSpecificData(std::ifstream& file,
                                                    int& line_number,
                                                    PdaData& data);
};

#endif  // PARSER_PDAFS_PARSER_H_
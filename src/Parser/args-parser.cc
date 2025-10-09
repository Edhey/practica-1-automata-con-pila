#include "args-parser.h"

/**
 * @brief Parses command-line arguments for the automata simulator.
 * @param argc Number of command-line arguments
 * @param argv Array of command-line argument strings
 * @return std::optional<ArgsParser> Parsed arguments or std::nullopt on error
 */
std::optional<ArgsParser> ArgsParser::parse(int argc, char* argv[]) {
  if (argc < 3) {
    printUsage(argv[0]);
    std::cerr << "Error: Insufficient arguments\n";
    return std::nullopt;
  }

  ArgsParser args;

  auto type_opt = AutomataTypeHelper::fromString(argv[1]);
  if (!type_opt.has_value()) {
    std::cerr << "Error: Invalid automata type '" << argv[1] << "'\n";
    printUsage(argv[0]);
    return std::nullopt;
  }
  args.pda_type = type_opt.value();
  args.input_file = argv[2];

  for (int i = 3; i < argc; ++i) {
    std::string arg = argv[i];

    if (arg == "-o" || arg == "--output") {
      if (i + 1 < argc) {
        args.output_file = argv[++i];
      } else {
        std::cerr << "Error: Option -o/--output requires an argument\n";
        printUsage(argv[0]);
        return std::nullopt;
      }
    } else if (arg == "-t" || arg == "--trace") {
      args.trace_mode = true;
    } else if (arg == "-h" || arg == "--help") {
      printUsage(argv[0]);
      std::exit(0);
    } else {
      std::cerr << "Warning: Unknown option '" << arg << "'\n";
    }
  }

  return args;
}

/**
 * @brief Prints usage information for the program.
 * @param program_name Name of the executable program.
 */
void ArgsParser::printUsage(const char* program_name) {
  std::cout << "Usage: " << program_name << " <type> <input_file> [options]\n\n"
            << "Arguments:\n"
            << "  <type>         Automata type: es|fs|PDAES|PDAFS\n"
            << "  <input_file>   Path to the automata definition file\n\n"
            << "Options:\n"
            << "  -o, --output <file>   Write trace/results to file\n"
            << "  -t, --trace           Enable trace mode\n"
            << "  -h, --help            Show this help message\n\n"
            << "Examples:\n"
            << "  " << program_name << " es automata.pda\n"
            << "  " << program_name << " PDAFS automata.pda -o output.txt -t\n";
}

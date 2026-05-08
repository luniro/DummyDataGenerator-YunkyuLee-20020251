#include "dummy_generator/dummy_generator.hpp"
#include <iostream>
#include <stdexcept>
#include <string>

namespace {
void usage(const char* prog) {
    std::cerr
        << "Usage: " << prog << " [options]\n"
        << "  --samples      N     Number of samples to generate     (default: 5)\n"
        << "  --orders       N     Number of orders to generate      (default: 10)\n"
        << "  --productions  N     Number of productions to generate (default: 8)\n"
        << "  --output-dir   PATH  Output directory                  (default: .)\n";
}
} // namespace

int main(int argc, char* argv[]) {
    GeneratorConfig config;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (i + 1 >= argc) {
            usage(argv[0]);
            return 1;
        }
        if (arg == "--samples")
            config.sample_count = std::stoi(argv[++i]);
        else if (arg == "--orders")
            config.order_count = std::stoi(argv[++i]);
        else if (arg == "--productions")
            config.production_count = std::stoi(argv[++i]);
        else if (arg == "--output-dir")
            config.output_dir = argv[++i];
        else {
            usage(argv[0]);
            return 1;
        }
    }

    try {
        generate_dummy_data(config);
        std::cout << "Generated"
                  << " samples=" << config.sample_count
                  << " orders=" << config.order_count
                  << " productions=" << config.production_count
                  << " -> " << config.output_dir << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}

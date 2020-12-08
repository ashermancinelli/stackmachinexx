#include <cxxopts.hpp>
#include <fmt/core.hpp>
#include <string>
#include <vector>

using std::string;
using std::vector;

int main(int argc, char** argv)
{
  vector<string> args(argv, argv + argc);

  if(args[1] == "run")
  {
    fmt::print("Running\n");
    argc--; argv++;
  }
  cxxopts::Options options(args[0], "Stack machine runtime");

  options.add_options()("f,file", "Input file name",
                        cxxopts::value<std::string>());
  options.add_options()("v,verbose", "Verbose output",
                        cxxopts::value<bool>()->default_value("false"));
  options.add_options()("h,help", "Print usage");

  auto result = options.parse(argc, argv);

  if (result.count("help"))
  {
    std::cout << options.help() << std::endl;
    return 0;
  }

  if (result.count("file"))
  {

  }

  return 0;
}

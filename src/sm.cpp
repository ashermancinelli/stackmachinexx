#include <spdlog/spdlog.h>
#include <cxxopts.hpp>
#include <string>
#include <vector>
#include <stackmachine/StackMachine.hpp>

using std::string;
using std::vector;
using namespace stackmachine;

int main(int argc, char** argv)
{
  vector<string> args(argv, argv + argc);

  cxxopts::Options options(args[0], "Stack machine runtime");
  options.add_options()("f,file", "Input file name",
                        cxxopts::value<std::string>());
  options.add_options()("v,verbose", "Verbose output",
                        cxxopts::value<bool>()->default_value("false"));
  options.add_options()("h,help", "Print usage");

  try
  {
    auto result = options.parse(argc, argv);
    StackMachine sm;

    if (result.count("help"))
    {
      std::cout << options.help() << std::endl;
      return 0;
    }
    if (result.count("verbose"))
    {
      spdlog::set_level(spdlog::level::debug);
      spdlog::debug("Debugging info enabled.");
    }
    if (result.count("file"))
    {
    }
  }
  catch (cxxopts::OptionException const& e)
  {
    spdlog::error("Got error parsing arguments: {}", e.what());
    return 1;
  }

  return 0;
}

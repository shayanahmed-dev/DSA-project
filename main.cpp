#include "ui/TerminalUI.h"
#include <iostream>
#include <exception>
int main(int argc, char **argv)
{
    try
    {
        AutocompleteEngine engine;
        const char *path = argc > 1 ? argv[1] : "data/words.txt";
        if (!engine.load(path) || !engine.size())
        {
            std::cerr << "Unable to load a nonempty dictionary: " << path << "\nRun from SmartComplete or pass the dictionary path.\n";
            return 1;
        }
        TerminalUI ui(engine);
        ui.run();
        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "smartcomplete: " << e.what() << '\n';
        return 1;
    }
}

/*
BEGINNER'S GUIDE TO main.cpp
This file is the program entry point. The operating system first calls main().

  #include "ui/TerminalUI.h"
  Brings in the terminal-screen class. This header also indirectly exposes the
  autocomplete engine used below.

  #include <iostream>
  Provides std::cout and std::cerr for writing text to the terminal.

  #include <exception>
  Provides the std::exception type used to catch errors safely.

  int main(int argc, char **argv)
  argc counts command-line arguments. argv holds those argument strings.
  char **argv means "pointer to an array of character pointers."

  try { ... } catch (...)
  The try block runs normal startup code. If any class constructor or operation
  throws a standard C++ exception, control goes to the catch block instead.

  AutocompleteEngine engine;
  Creates the autocomplete engine and its custom data structures.

  const char *path = argc > 1 ? argv[1] : "data/words.txt";
  Uses a user-provided dictionary path when one is supplied. Otherwise it uses
  the default words.txt file.

  if (!engine.load(path) || !engine.size())
  load() reads words from the file. size() confirms that at least one word was
  loaded. If either check fails, the program prints an error and returns 1.

  std::cerr
  Writes error messages to the standard error stream. It is usually different
  from normal output but appears in the terminal too.

  return 1 / return 0
  1 reports an error to the operating system. 0 means successful completion.

  TerminalUI ui(engine);
  Creates the user interface and gives it a reference to the engine. This does
  not copy the engine; both names refer to the same engine object.

  ui.run();
  Starts the terminal input-and-drawing loop until the user exits.

  catch (const std::exception &e)
  If startup or UI code throws an exception, prints its message and returns 1
  instead of allowing an unhandled crash. e.what() obtains the error text.
*/
